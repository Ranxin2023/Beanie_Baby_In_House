#include "game.hpp"
#include "curses_view.hpp"
#include "curses_controller.hpp"
#include "print_view.hpp"
#include "print_controller.hpp"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
// These should not have been here in the first place...
#define INVALID_GAME_FILE_MSG "Invalid game input file"
// #define INVALID_LEVEL_FILE_MSG "Invalid level input file"
// #define INVALID_VIEW_TYPE_MSG "Invalid view type"

const int Game::MIN_VIEW_HEIGHT = 15;
const int Game::MIN_VIEW_WIDTH = 15;
const char Game::HERO_ICON_LEFT = '<';
const char Game::HERO_ICON_RIGHT = '>';
const char Game::HERO_ICON_UP = '^';
const char Game::HERO_ICON_DOWN = 'v';

Game::Game(const std::string& filename, InterfaceType interfaceType)
    : mView{nullptr}
    , mController{nullptr}
    , mInterfaceType{interfaceType}
{
	/*set interface type*/
	mInterfaceType=interfaceType;
	int i=0;
	int j;
    // TODO: Implement.
	ifstream ifs{filename};
	//mView=new View;
	int gameHeight;
	int gameWidth;
	int num_of_level;
	string file_str;
	
	while(1){
		/*
		read the gameHeight and gameWidth 
		setup mView and map_controller
		store it in mView and map_controller. 
		*/
		if(i==0){
			ifs>>gameHeight>>gameWidth;
			if(mInterfaceType==InterfaceType::Print)
			mView=new PrintView(gameHeight,gameWidth);
			if(mInterfaceType==InterfaceType::Curses)
			mView=new CursesView(gameHeight,gameWidth);
			//map_s=new MapSegment(gameHeight,gameWidth);
		}
		/*
		read the number of level
		allocate string array for levelFiles
		*/
		else if(i==1){
			ifs>>num_of_level;
			numOfLevels=num_of_level;
			levelFiles=new string[numOfLevels];
			map_s=new MapSegment*[numOfLevels];
			for(j=0;j<numOfLevels;j++)map_s[j]=new MapSegment(gameHeight,gameWidth);
			itemsRemaining=new int [numOfLevels];
			movesRemaining=new int [numOfLevels];
			for(j=0;j<numOfLevels;j++)itemsRemaining[j]=0;
			numOfItemCaught=new int *[numOfLevels];
			catch_item_pos_y=new int **[numOfLevels];
			catch_item_pos_x=new int **[numOfLevels];
		}
		/*
		read each level_files
		store them to the string array levelFiles
		*/
		else{
			if(!(ifs>>file_str))break;
			levelFiles[i-2]=file_str;
		}
		i++;
	}
	ifs.close();
}

Game::~Game()
{
    // TODO: Usually, deallocate anything that was dynamically
    // allocated in the ctor (constructor).
	int i;
	for(i=0;i<numOfLevels;i++)delete map_s[i];
    delete []map_s;
	delete mView;
	delete mController;
	delete []levelFiles;
}

void Game::run()
{
	//load gamelevel data
	loadLevel();
	//printInfo();
	//start the game
	doGameLoop();
	
}

void Game::printInfo(){
	int i,k;
	unsigned j;
	int numOfSegment=map_s[currentLevel]->getSegment();
	int numOfBuilding;
	int buildingIndex;
	int numOfItem;
	int itemIndex;
	cout<<"# of level:"<<numOfLevels<<endl;
	cout<<"Boarder position is:"<<map_s[currentLevel]->getBoarderPos_Y()<<","<<map_s[currentLevel]->getBoarderPos_X()<<endl;
	cout<<"End Boarder position is:"<<map_s[currentLevel]->getBoarderPosEnd_Y()<<","<<map_s[currentLevel]->getBoarderPosEnd_X()<<endl;
	for(i=0;i<numOfLevels;i++){
		cout<<"# of moves remaining:"<<movesRemaining[i]<<endl;
	}
	for(i=0;i<numOfLevels;i++){
		cout<<"# of items remaining:"<<itemsRemaining[i]<<endl;
	}
	numOfBuilding=map_s[currentLevel]->getNumberOfBuilding();
	for(i=0;i<numOfBuilding;i++){
		buildingIndex=map_s[currentLevel]->getBuildingIndex(i);
		cout<<"Building Index are:"<<map_s[currentLevel]->getBuildingPos_Y(buildingIndex)<<","<<map_s[currentLevel]->getBuildingPos_X(buildingIndex)<<endl;
	}
	numOfItem=map_s[currentLevel]->getNumberOfItem();
	for(i=0;i<numOfItem;i++){
		itemIndex=map_s[currentLevel]->getItemIndex(i);
		cout<<"Building Index are:"<<map_s[currentLevel]->getItemPos_Y(itemIndex)<<","<<map_s[currentLevel]->getItemPos_X(itemIndex)<<endl;
	}
	for(i=0;i<numOfLevels;i++){
		for(k=0;k<numOfSegment;k++){
			for(j=0;j<20;j++){
				cout<<catch_item_pos_y[i][k][j]<<" ";
			}
			cout<<"\t";
		}
		cout<<endl;
	}
	cout<<"The board is:"<<endl;
	draw();
}
/*==========print===============*/
void Game::loadLevel()
{
	int fileIndex=0;
	for(;fileIndex<numOfLevels;fileIndex++)
	{
		//local variables for reading
		/*+++++++++++++++++++*/
		unsigned i=0;
		unsigned j;
		int k;
		//the segment where player is in for each level
		int segment;
		//the coordinate of player in correspond segment
		int player_x;
		int player_y;
		//the initial direction for player
		string init_direction;
		//map building item portal string for reading
		char MBIP;
		int numOfSegment=0;
		int segment_width;
		int segment_height;
		//all building variables
		int building_segment;
		int building_y;
		int building_x;
		//All item variables
		int item_segment;
		int item_y;
		int item_x;
		//all segment traverse variables
		int number_of_traverse=0;
		string segment_dir_target_str;
		string segment_dir_corres_str;
		int segment_id_target_int;
		int segment_id_corres_int;
		vector<int>segment_id_target;
		vector<int>segment_id_corres;
		//vector<int>item_catch_segment;
		vector<string>segment_dir_target;
		vector<string>segment_dir_corres;
		//all move variables
		int totalMove;
		/*+++++++++++++++++++*/
		ifstream ifs{"game_files/"+levelFiles[fileIndex]};
		while(1){
			/*
			read the start map segment of the player
			store the number to map_s
			*/
			if(i==0)
			{
				ifs>>segment;
				map_s[fileIndex]->setMap_segment(segment);
				
			}
			/*
			read the start position of the player in that map_segment
			set the position of the boarder of the map segment
			*/
			else if(i==1)
			{
				ifs>>player_y>>player_x;
				map_s[fileIndex]->setInitBoarderPosition(player_y,player_x);
				
			}
			/*
			read the start direction of the player
			*/
			else if(i==2)
			{
				ifs>>init_direction;
				map_s[fileIndex]->setInitDirection(init_direction);
			}
			else
			{
				if(!(ifs>>MBIP))break;
				/*
				read the size of each segment
				store into map_segment
				*/
				
				if(MBIP=='M')
				{
					ifs>>segment_height>>segment_width;
					map_s[fileIndex]->setSegmentSize(segment_height,segment_width);
					//store the map information to map_segment
					if(numOfSegment==map_s[fileIndex]->getSegment()){
						
						map_s[fileIndex]->setInitEndBoarderPosition();
					}
					
					numOfSegment+=1;
				}
				/*
				read the building information
				store them into map_segment
				*/
				if(MBIP=='B')
				{
					ifs>>building_segment>>building_y>>building_x;
					//store the building information to map_s;
					map_s[fileIndex]->setInitBuilding(building_segment,building_y,building_x);
				}
				/*
				read the item information 
				store it into map_segment
				*/
				if(MBIP=='I')
				{
					ifs>>item_segment>>item_y>>item_x;
					//store the item information to map_s;
					map_s[fileIndex]->setInitItem(item_segment,item_y,item_x);
					//add information to catch item array
					//add one to number of items remaining for each level
					//item_catch_segment.push_back(item_segment);
					
					itemsRemaining[fileIndex]+=1;
					
					
				}
				/*
				read the segment traverse information
				store them into segment part
				*/
				if(MBIP=='P'){
					ifs>>segment_id_target_int>>segment_dir_target_str>>segment_id_corres_int>>segment_dir_corres_str;
					segment_id_target.push_back(segment_id_target_int);
					segment_dir_target.push_back(segment_dir_target_str);
					segment_id_corres.push_back(segment_id_corres_int);
					segment_dir_corres.push_back(segment_dir_corres_str);
					//add one to number_of_traverse
					number_of_traverse+=1;
				}
				if(MBIP=='N'){
					ifs>>totalMove;
					movesRemaining[fileIndex]=totalMove;
				}
			}//end of else
			i++;
		}//end of while
		/*
		Because the number of segment is decided after the level file is read, 
		we need to do at this time. 
		*/
		map_s[fileIndex]->setNumberOfSegment(numOfSegment);
		
		numOfItemCaught[fileIndex]=new int[numOfSegment];
		catch_item_pos_y[fileIndex]=new int *[numOfSegment];
		catch_item_pos_x[fileIndex]=new int *[numOfSegment];
		
		for(k=0;k<numOfSegment;k++){
			numOfItemCaught[fileIndex][k]=0;
		}
		//cout<<"numOfItemCaught[0][0]: "<<numOfItemCaught[0][0]<<endl;
		/*
		store the number of catch item information
		*/
		for(k=0;k<numOfSegment;k++){
			catch_item_pos_y[fileIndex][k]=new int[20];
			catch_item_pos_x[fileIndex][k]=new int[20];
		}
		for(k=0;k<numOfSegment;k++){
			for(j=0;j<20;j++){
				catch_item_pos_y[fileIndex][k][j]=-1;
				catch_item_pos_x[fileIndex][k][j]=-1;
			}
		}
		//cout<<"catch_item_pos_y[0][0][0]: "<<catch_item_pos_y[0][0][0]<<endl;
		/*
		for(j=0;j<item_catch_segment.size();j++){
			//numOfItemCaught[fileIndex][item_catch_segment[j]]+=1;
			catch_item_pos_y[fileIndex][item_catch_segment[j]].push_back(-1);
			catch_item_pos_x[fileIndex][item_catch_segment[j]].push_back(-1);
		}
		
		cout<<"catch_item_pos_y[0][0][0]: "<<catch_item_pos_y[0][0][0]<<endl;
		*/
		/*
		store the number of traverse into each segment
		*/
		for(k=0;k<number_of_traverse;k++){
			map_s[fileIndex]->setInitTraverse(segment_id_target[k],segment_id_corres[k],segment_dir_target[k]);
			map_s[fileIndex]->setInitTraverse(segment_id_corres[k],segment_id_target[k],segment_dir_corres[k]);
		}
		ifs.close();
	}//end of for
}//end of loadLevel

void Game::doGameLoop(){
	int i;
	//print out initial status
	cout<<"Level: "<< currentLevel+1<<endl;
	cout<<"Items remaining: "<<itemsRemaining[currentLevel]<<endl;
	cout<<"Moves remaining: "<<movesRemaining[currentLevel]<<endl;
	draw();
	//oldLevel=currentLevel;
	//mView->draw();
	while(1){
		//char input;
		Command input_com;
		
		//cin>>input;
		if(mInterfaceType==InterfaceType::Print)
		mController=new PrintController();
		if(mInterfaceType==InterfaceType::Curses)
		mController=new CursesController();
		mController->setInput();
		input_com=mController->getInput();
		//deal with input
		if(input_com==Command::Left)
		{
			map_s[currentLevel]->setDirection(0);
		}
		if(input_com==Command::Right)
		{
			map_s[currentLevel]->setDirection(1);
		}
		if(input_com==Command::Forward)
		{
			int local_segment=map_s[currentLevel]->getSegment();
			bool passingFlag=false;
			bool catchFlag=false;
			int local_item_y;
			int local_item_x;
			int numOfItem=map_s[currentLevel]->getNumberOfItem();
			int itemIndex;
			for(i=0;i<numOfItem;i++){
				itemIndex=map_s[currentLevel]->getItemIndex(i);
				local_item_y=map_s[currentLevel]->getItemPos_Y(itemIndex);
				local_item_x=map_s[currentLevel]->getItemPos_X(itemIndex);
				if(map_s[currentLevel]->getPortalY()==local_item_y&&map_s[currentLevel]->getPortalX()==local_item_x)break;
			}
			
			
			//set the position on the map
			map_s[currentLevel]->setPosition(&passingFlag,&catchFlag);
			if(!passingFlag)movesRemaining[currentLevel]--;
			if(catchFlag){
				catch_item_pos_y[currentLevel][local_segment][numOfItemCaught[currentLevel][local_segment]]=local_item_y;
				catch_item_pos_x[currentLevel][local_segment][numOfItemCaught[currentLevel][local_segment]]=local_item_x;
				numOfItemCaught[currentLevel][local_segment]++;
				itemsRemaining[currentLevel]--;
			}
		}
		if(input_com==Command::Quit){
			//print out before quit
			cout<<"You quit the game."<<endl;
			break;
		}
		//wait until a solution is comming
		//if(input_com==Invalid)continue;
		if(movesRemaining[currentLevel]==0){
			cout<<"You lost the game."<<endl;
			break;
		}
		if(itemsRemaining[currentLevel]==0){
			currentLevel+=1;
			//When change to the level larger than the number of level
			if(currentLevel==numOfLevels)
			{
				cout<<"You won the game."<<endl;
				break;
			}
			//update();
		}
		//print out information
		cout<<"Level: "<< currentLevel+1<<endl;
		cout<<"Items Remaining: "<<itemsRemaining[currentLevel]<<endl;
		cout<<"Moves Remaining: "<<movesRemaining[currentLevel]<<endl;
		draw();
		//oldLevel=currentLevel;
		//mView->draw();
	}//end of while
}

void Game::draw()
{
	int i,j,k;
	unsigned l;
	char ** lines;
	vector<string>lines_vector_str;
	string line_str;
	lines=new char*[mView->getHeight()+2];
	for(i=0;i<mView->getHeight()+2;i++){
		lines[i]=new char[mView->getWidth()+2];
	}
	for(i=0;i<mView->getHeight()+2;i++){
		for(j=0;j<mView->getWidth()+2;j++){
			//map boarder
			if(i==0||j==0||i==mView->getHeight()+1||j==mView->getWidth()+1){
				lines[i][j]='*';
			}
			else if((i>=map_s[currentLevel]->getBoarderPos_Y()&&i<=map_s[currentLevel]->getBoarderPosEnd_Y())
				&&(j>=map_s[currentLevel]->getBoarderPos_X()&&j<=map_s[currentLevel]->getBoarderPosEnd_X()))
			{
				//segment boarder
				if(i==map_s[currentLevel]->getBoarderPos_Y()||i==map_s[currentLevel]->getBoarderPosEnd_Y()||
				j==map_s[currentLevel]->getBoarderPos_X()||j==map_s[currentLevel]->getBoarderPosEnd_X())
				{
					if(i==map_s[currentLevel]->getBoarderPos_Y()||i==map_s[currentLevel]->getBoarderPosEnd_Y())
					{
						bool portalFlag=false;
						for(k=0;k<map_s[currentLevel]->getNumOfTraverse();k++)
						{
							if(map_s[currentLevel]->getTravresePos_X(k)==j){
								lines[i][j]=map_s[currentLevel]->getPORTAL_CHAR();
								portalFlag=true;
							}
						}
						if(!portalFlag)
						lines[i][j]=map_s[currentLevel]->getHORIZONTAL_BORDER_CHAR();
					}
					else
					{
						bool portalFlag=false;
						for(k=0;k<map_s[currentLevel]->getNumOfTraverse();k++)
						{
							if(map_s[currentLevel]->getTravresePos_Y(k)==i){
								lines[i][j]=map_s[currentLevel]->getPORTAL_CHAR();
								portalFlag=true;
							}
						}
						if(!portalFlag)
						lines[i][j]=map_s[currentLevel]->getVERTICAL_BORDER_CHAR();
					}
				}
				//building and item
				else{ 
					int numberOfBuilding=map_s[currentLevel]->getNumberOfBuilding();
					int numOfItem=map_s[currentLevel]->getNumberOfItem();
					int segment=map_s[currentLevel]->getSegment();
					//zero building in the segment
					if(numberOfBuilding==0)
					{
						if(i==map_s[currentLevel]->getPortalY()&&j==map_s[currentLevel]->getPortalX())
						{
							if(map_s[currentLevel]->getDirection()==0)lines[i][j]=HERO_ICON_UP;
							if(map_s[currentLevel]->getDirection()==1)lines[i][j]=HERO_ICON_LEFT;
							if(map_s[currentLevel]->getDirection()==2)lines[i][j]=HERO_ICON_DOWN;
							if(map_s[currentLevel]->getDirection()==3)lines[i][j]=HERO_ICON_RIGHT;
						}
						else {
							if(numOfItem==0){
								lines[i][j]=' ';
							}
							if(numOfItem==1){
								bool catchFlag=false;
								int itemIndex=map_s[currentLevel]->getItemIndex(0);
								for(l=0;l<20;l++){
									if(catch_item_pos_y[currentLevel][segment][l]==i&&catch_item_pos_x[currentLevel][segment][l]==j)
									{
										catchFlag=true;
									}
								}
								if(i==map_s[currentLevel]->getItemPos_Y(itemIndex)&&j==map_s[currentLevel]->getItemPos_X(itemIndex)){
									if(catchFlag==true){
										lines[i][j]=' ';
									}
									else{
										lines[i][j]='$';
									}
								}
								else lines[i][j]=' ';
							}
							if(numOfItem==2){
								bool catchFlag=false;
								int itemIndex0=map_s[currentLevel]->getItemIndex(0);
								int itemIndex1=map_s[currentLevel]->getItemIndex(1);
								for(l=0;l<20;l++){
									if(catch_item_pos_y[currentLevel][segment][l]==i&&catch_item_pos_x[currentLevel][segment][l]==j)
									{
										catchFlag=true;
									}
								}
								if((i==map_s[currentLevel]->getItemPos_Y(itemIndex0)&&j==map_s[currentLevel]->getItemPos_X(itemIndex0))
								||(i==map_s[currentLevel]->getItemPos_Y(itemIndex1)&&j==map_s[currentLevel]->getItemPos_X(itemIndex1))){
									if(catchFlag==true){
										lines[i][j]=' ';
									}
									else{
										lines[i][j]='$';
									}
								}
								else lines[i][j]=' ';
							}
						}//end of else
					}
					//one building in the segment
					if(numberOfBuilding==1){
						int buildingIndex=map_s[currentLevel]->getBuildingIndex(0);
						if(i>=map_s[currentLevel]->getBuildingPos_Y(buildingIndex)&&i<=map_s[currentLevel]->getBuildingEndPos_Y(buildingIndex)
						&&j>=map_s[currentLevel]->getBuildingPos_X(buildingIndex)&&j<=map_s[currentLevel]->getBuildingEndPos_X(buildingIndex))
						{
							if((i==map_s[currentLevel]->getBuildingPos_Y(buildingIndex)+2&&j==map_s[currentLevel]->getBuildingPos_X(buildingIndex)+2)
							||(i==map_s[currentLevel]->getBuildingPos_Y(buildingIndex)+2&&j==map_s[currentLevel]->getBuildingPos_X(buildingIndex)+3)
							||(i==map_s[currentLevel]->getBuildingPos_Y(buildingIndex)+3&&j==map_s[currentLevel]->getBuildingPos_X(buildingIndex)+2)
							||(i==map_s[currentLevel]->getBuildingPos_Y(buildingIndex)+3&&j==map_s[currentLevel]->getBuildingPos_X(buildingIndex)+3))
							{
								lines[i][j]='&';
							}
							else 
							{
								lines[i][j]='.';
							}
						}
						else{
							if(i==map_s[currentLevel]->getPortalY()&&j==map_s[currentLevel]->getPortalX())
							{
								if(map_s[currentLevel]->getDirection()==0)lines[i][j]=HERO_ICON_UP;
								if(map_s[currentLevel]->getDirection()==1)lines[i][j]=HERO_ICON_LEFT;
								if(map_s[currentLevel]->getDirection()==2)lines[i][j]=HERO_ICON_DOWN;
								if(map_s[currentLevel]->getDirection()==3)lines[i][j]=HERO_ICON_RIGHT;
							}
							else{
								if(numOfItem==0){
									lines[i][j]=' ';
								}
								if(numOfItem==1){
									bool catchFlag=false;
									int itemIndex=map_s[currentLevel]->getItemIndex(0);
									for(l=0;l<20;l++){
										if(catch_item_pos_y[currentLevel][segment][l]==i&&catch_item_pos_x[currentLevel][segment][l]==j)
										{
											catchFlag=true;
										}
									}
									if(i==map_s[currentLevel]->getItemPos_Y(itemIndex)&&j==map_s[currentLevel]->getItemPos_X(itemIndex)){
										if(catchFlag==true){
											lines[i][j]=' ';
										}
										else{
											lines[i][j]='$';
										}
									}
									else lines[i][j]=' ';
								}
								if(numOfItem==2){
								bool catchFlag=false;
								int itemIndex0=map_s[currentLevel]->getItemIndex(0);
								int itemIndex1=map_s[currentLevel]->getItemIndex(1);
								for(l=0;l<20;l++){
									if(catch_item_pos_y[currentLevel][segment][l]==i&&catch_item_pos_x[currentLevel][segment][l]==j)
									{
										catchFlag=true;
									}
								}
								if((i==map_s[currentLevel]->getItemPos_Y(itemIndex0)&&j==map_s[currentLevel]->getItemPos_X(itemIndex0))
								||(i==map_s[currentLevel]->getItemPos_Y(itemIndex1)&&j==map_s[currentLevel]->getItemPos_X(itemIndex1))){
									if(catchFlag==true){
										lines[i][j]=' ';
									}
									else{
										lines[i][j]='$';
									}
								}
								else lines[i][j]=' ';
								}
							}//end of else
						}//end of else
					}//end of if
					
				}//end of else building and item
			}//end of if for segment
			//out of segment
			else {
				lines[i][j]='~';
			}
		}//end of for j
	}//end of for i
	//copy to the lines_vector_str
	for(i=0;i<mView->getHeight()+2;i++){
		line_str=lines[i];
		lines_vector_str.push_back(line_str);
	}
	mView->draw(lines_vector_str);
}//end of function
