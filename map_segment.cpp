#include "map_segment.hpp"
#include<iostream>
char MapSegment::VERTICAL_BORDER_CHAR = '|';
char MapSegment::HORIZONTAL_BORDER_CHAR = '=';
char MapSegment::PORTAL_CHAR = '@';

MapSegment::MapSegment(int height, int width)
    : mHeight(height), mWidth(width)
    , mPortalY{(mHeight - 1) / 2}
    , mPortalX{(mWidth - 1) / 2}
{
	//cout<<"New map with coordinates:"<<mPortalY<<" "<<mPortalX<<"is setup"<<endl;
}
/*-------------------------------------------------------------------------------Get Function---------------------------------------------------------------------------*/
/*---------------------Get Building----------------------------*/

int MapSegment::getSegment()
{
	return segment;
}

int MapSegment::getNumberOfBuilding()
{
	unsigned i;
	int numberOfBuilding=0;
	for(i=0;i<building_segment.size();i++){
		if(building_segment[i]==segment)numberOfBuilding+=1;
	}
	return numberOfBuilding;
}
/*
bool MapSegment::judgeBuildingSegment(int seg, int index)
{
	if(building_segment[index]==seg)return true;
	return false;
}
*/
int MapSegment::getBuildingIndex(int num){
	unsigned i;
	int indexOfBuilding=-1;
	for(i=0;i<building_segment.size();i++){
		if(building_segment[i]==segment){
			indexOfBuilding+=1;
			if(indexOfBuilding==num)
			return i;
		}
	}
	return -1;
}
int MapSegment::getBuildingPos_Y(int index)
{
	return m_build[index]->getY();
}
int MapSegment::getBuildingPos_X(int index)
{
	return m_build[index]->getX();
}

int MapSegment::getBuildingEndPos_Y(int index){
	return m_build[index]->getEndY();
}

int MapSegment::getBuildingEndPos_X(int index){
	return m_build[index]->getEndX();
}

/*---------------------Get Item----------------------------*/
/*
bool MapSegment::judgeItemSegment(int seg, int index)
{
	if(item_segment[index]==seg)return true;
	return false;
}
*/
int MapSegment::getItemIndex(int num)
{
	unsigned i;
	int indexOfItem=-1;
	for(i=0;i<item_segment.size();i++){
		if(item_segment[i]==segment){
			if(m_item[i]->getY()!=mPortalY||m_item[i]->getX()!=mPortalX)
			indexOfItem+=1;
			if(indexOfItem==num)
			return i;
		}
	}
	return -1;
}

int MapSegment::getNumberOfItem()
{
	unsigned i;
	int numberOfItem=0;
	for(i=0;i<item_segment.size();i++){
		if(item_segment[i]==segment){
			if(m_item[i]->getY()!=mPortalY||m_item[i]->getX()!=mPortalX)
			numberOfItem+=1;
		}
	}
	return numberOfItem;
}

int MapSegment::getItemPos_Y(int index)
{
	return m_item[index]->getY();
}
int MapSegment::getItemPos_X(int index)
{
	return m_item[index]->getX();
}

/*---------------------Get Boarder----------------------------*/

int MapSegment::getBoarderPos_Y(){
	return boarder_pos_y;
}

int MapSegment::getBoarderPos_X(){
	return boarder_pos_x;
}

int MapSegment::getBoarderPosEnd_Y(){
	return boarder_pos_y_end;
}

int MapSegment::getBoarderPosEnd_X(){
	return boarder_pos_x_end;
}

/*---------------------Get Traverse----------------------------*/
int MapSegment::getNumOfTraverse(){
	return y_traverse_pos.size();
}

int MapSegment::getTravresePos_Y(int index){
	return y_traverse_pos[index];
}

int MapSegment::getTravresePos_X(int index){
	return x_traverse_pos[index];
}

/*---------------------Get Direction----------------------------*/
int MapSegment::getDirection(){
	return direction;
}
/*-------------------------------------------------------------------------------Set Function---------------------------------------------------------------------------*/
void MapSegment::setMap_segment(int s)
{
	segment=s;
}

void MapSegment::setNumberOfSegment(int s)
{
	numOfSegment=s;
	adjacentSegment=new vector<int>[numOfSegment];
	y_traverse=new vector<int>[numOfSegment];
	x_traverse=new vector<int>[numOfSegment];
	
}

/*This function is for storing the size of each segment*/
void MapSegment::setSegmentSize(int y, int x)
{
	segment_height.push_back(y);
	segment_width.push_back(x);
}

/*---------------------------------Direction Function---------------------------------*/
void MapSegment::setInitDirection(string s)
{
	if(!s.compare("up"))direction=0;
	if(!s.compare("left"))direction=1;
	if(!s.compare("down"))direction=2;
	if(!s.compare("right"))direction=3;
}

void MapSegment::setDirection(int command){
	if(command==0)
	{
		direction+=1;
		if(direction>=4)direction-=4;
	}
	if(command==1)
	{
		direction-=1;
		if(direction<0)direction+=4;
	}
}

/*---------------------------------Building Function---------------------------------*/
/*This function is for storing the coordination of building*/
void MapSegment::setInitBuilding(int s,int y,int x)
{
	m_build.push_back(new Building(boarder_pos_y+y,boarder_pos_x+x));
	building_segment.push_back(s);
}

void MapSegment::setMovementBuilding(){
	unsigned i;
	for(i=0;i<building_segment.size();i++)
	{
		if(building_segment[i]==segment)
		{
			/*when facing up*/
			if(direction==0)
			{
				m_build[i]->resetCoordinates(1,0);
			}
			if(direction ==1)
			{
				m_build[i]->resetCoordinates(0,1);
			}
			if(direction ==2)
			{
				m_build[i]->resetCoordinates(-1,0);
			}
			if(direction ==3)
			{
				m_build[i]->resetCoordinates(0,-1);
			}
		}
	}
}

void MapSegment::restoreBuilding()
{
	unsigned i;
	for(i=0;i<building_segment.size();i++)
	{
		if(building_segment[i]==segment)
		{
			/*when facing up*/
			if(direction==0)
			{
				m_build[i]->resetCoordinates(-1,0);
			}
			if(direction ==1)
			{
				m_build[i]->resetCoordinates(0,-1);
			}
			if(direction ==2)
			{
				m_build[i]->resetCoordinates(1,0);
			}
			if(direction ==3)
			{
				m_build[i]->resetCoordinates(0,1);
			}
		}
	}
}

/*---------------------------------Item Function---------------------------------*/
void MapSegment::setInitItem(int s,int y,int x)
{
	m_item.push_back(new Item(boarder_pos_y+y,boarder_pos_x+x));
	item_segment.push_back(s);
}

void MapSegment::setMovementItem()
{
	unsigned i;
	for(i=0;i<item_segment.size();i++)
	{
		if(item_segment[i]==segment)
		{
			/*when facing up*/
			if(direction==0)
			{
				m_item[i]->resetCoordinates(1,0);
			}
			if(direction ==1)
			{
				m_item[i]->resetCoordinates(0,1);
			}
			if(direction ==2)
			{
				m_item[i]->resetCoordinates(-1,0);
			}
			if(direction ==3)
			{
				m_item[i]->resetCoordinates(0,-1);
			}
		}
	}
}

void MapSegment::restoreItem()
{
	unsigned i;
	for(i=0;i<item_segment.size();i++)
	{
		if(item_segment[i]==segment)
		{
			/*when facing up*/
			if(direction==0)
			{
				m_item[i]->resetCoordinates(-1,0);
			}
			if(direction ==1)
			{
				m_item[i]->resetCoordinates(0,-1);
			}
			if(direction ==2)
			{
				m_item[i]->resetCoordinates(1,0);
			}
			if(direction ==3)
			{
				m_item[i]->resetCoordinates(0,1);
			}
		}
	}
}

/*---------------------------------Boarder Function---------------------------------*/

void MapSegment::setInitBoarderPosition(int y, int x)
{
	boarder_pos_y=mPortalY-y;
	boarder_pos_x=mPortalX-x;
}

void MapSegment::setInitEndBoarderPosition(){
	boarder_pos_y_end=boarder_pos_y+segment_height[segment]-1;
	boarder_pos_x_end=boarder_pos_x+segment_width[segment]-1;
}

void MapSegment::setMovementBoarderPosition()
{
	if(direction==0){
		boarder_pos_y+=1;
		boarder_pos_y_end+=1;
	}
	if(direction==1){
		boarder_pos_x+=1;
		boarder_pos_x_end+=1;
	}
	if(direction==2){
		boarder_pos_y-=1;
		boarder_pos_y_end-=1;
	}
	if(direction==3){
		boarder_pos_x-=1;
		boarder_pos_x_end-=1;
	}
}

void MapSegment::restoreBoarderPosition(){
	if(direction==0){
		boarder_pos_y-=1;
		boarder_pos_y_end-=1;
	}
	if(direction==1){
		boarder_pos_x-=1;
		boarder_pos_x_end-=1;
	}
	if(direction==2){
		boarder_pos_y+=1;
		boarder_pos_y_end+=1;
	}
	if(direction==3){
		boarder_pos_x+=1;
		boarder_pos_x_end+=1;
	}
}

/*---------------------------------Traverse Function---------------------------------*/

void MapSegment::setInitTraverse(int target, int corres_seg, string dir){
	adjacentSegment[target].push_back(corres_seg);
	if(dir.compare("left")==0)
	{
		y_traverse[target].push_back(segment_height[target]/2);
		x_traverse[target].push_back(0);
		if(target==segment){
			y_traverse_pos.push_back((boarder_pos_y+boarder_pos_y_end)/2);
			x_traverse_pos.push_back(boarder_pos_x);
		}
	}
	if(dir.compare("right")==0)
	{
		y_traverse[target].push_back(segment_height[target]/2);
		x_traverse[target].push_back(segment_width[target]);
		if(target==segment){
			y_traverse_pos.push_back((boarder_pos_y+boarder_pos_y_end)/2);
			x_traverse_pos.push_back(boarder_pos_x_end);
		}
	}
	if(dir.compare("up")==0)
	{
		y_traverse[target].push_back(segment_width[target]/2);
		x_traverse[target].push_back(0);
		if(target==segment){
			x_traverse_pos.push_back((boarder_pos_x+boarder_pos_x_end)/2);
			y_traverse_pos.push_back(boarder_pos_y);
		}
	}
	if(dir.compare("down")==0)
	{
		y_traverse[target].push_back(segment_width[target]/2);
		x_traverse[target].push_back(segment_height[target]);
		if(target==segment){
			x_traverse_pos.push_back((boarder_pos_x+boarder_pos_x_end)/2);
			y_traverse_pos.push_back(boarder_pos_y_end);
		}
	}
}

void MapSegment::setTraverse()
{
	unsigned i;
	y_traverse_pos.resize(0);
	x_traverse_pos.resize(0);
	for(i=0;i<y_traverse_pos.size();i++){
		y_traverse_pos.push_back(boarder_pos_y+y_traverse[segment][i]);
		x_traverse_pos.push_back(boarder_pos_x+x_traverse[segment][i]);
	}
}

void MapSegment::setTraversePosition()
{
	unsigned i;
	if(direction==0){
		for(i=0;i<y_traverse_pos.size();i++){
			y_traverse_pos[i]+=1;
		}
	}
	if(direction==1){
		for(i=0;i<x_traverse_pos.size();i++){
			x_traverse_pos[i]+=1;
		}
	}
	if(direction==2){
		for(i=0;i<y_traverse_pos.size();i++){
			y_traverse_pos[i]-=1;
		}
	}
	if(direction==3){
		for(i=0;i<x_traverse_pos.size();i++){
			x_traverse_pos[i]-=1;
		}
	}
}

void MapSegment::restoreTraversePosition()
{
	unsigned i;
	if(direction==0){
		for(i=0;i<y_traverse_pos.size();i++){
			y_traverse_pos[i]-=1;
		}
	}
	if(direction==1){
		for(i=0;i<x_traverse_pos.size();i++){
			x_traverse_pos[i]-=1;
		}
	}
	if(direction==2){
		for(i=0;i<y_traverse_pos.size();i++){
			y_traverse_pos[i]+=1;
		}
	}
	if(direction==3){
		for(i=0;i<x_traverse_pos.size();i++){
			x_traverse_pos[i]+=1;
		}
	}
}

/*-----------------------------Set Position----------------------------------------------*/
void MapSegment::setPosition(bool * passingFlag,bool * containFlag)
{
	unsigned i,j;
	setMovementBoarderPosition();
	setMovementItem();
	setMovementBuilding();
	if(mPortalX==boarder_pos_x||mPortalX==boarder_pos_x_end
	||mPortalY==boarder_pos_y||mPortalY==boarder_pos_y_end)
	{
		int oldSegment;
		int corres_index;
		/*Weather traverse the segment or not*/
		/*traverse the segment*/
		for(i=0;i<x_traverse_pos.size();i++){
			if(mPortalX==x_traverse_pos[i]&&mPortalY==y_traverse_pos[i])
			{
				/*
				traverse in the direction of left
				(change from leftmost to rightmost)
				*/
				oldSegment=segment;
				segment=adjacentSegment[oldSegment][i];
				
				/*change the boarder*/
				if(mPortalX==boarder_pos_x){
					boarder_pos_x_end=mPortalX+1;
					boarder_pos_x=boarder_pos_x_end-segment_width[segment]+1;
					for(j=0;j<adjacentSegment[segment].size();j++){
						if(adjacentSegment[segment][j]==oldSegment){
							corres_index=j;
							break;
						}
					}
					boarder_pos_y=mPortalY-y_traverse[segment][corres_index];
					boarder_pos_y_end=boarder_pos_y+segment_height[segment]-1;
					return ;
				}
				/*
				traverse in the direction of left
				(change from rightmost to leftmost)
				*/
				if(mPortalX==boarder_pos_x_end){
					boarder_pos_x=mPortalX-1;
					boarder_pos_x_end=boarder_pos_x+segment_width[segment]-1;
					for(j=0;j<adjacentSegment[segment].size();j++){
						if(adjacentSegment[segment][j]==oldSegment){
							corres_index=j;
							break;
						}
					}
					boarder_pos_y=mPortalY-y_traverse[segment][corres_index];
					boarder_pos_y_end=boarder_pos_y+segment_height[segment]-1;
					return ;
				}
				/*
				traverse in the direction of up
				(change from uppermost to downmost)
				*/
				if(mPortalY==boarder_pos_y){
					boarder_pos_y_end=mPortalY+1;
					boarder_pos_y=boarder_pos_y-segment_height[segment]+1;
					for(j=0;j<adjacentSegment[segment].size();j++){
						if(adjacentSegment[segment][j]==oldSegment){
							corres_index=j;
							break;
						}
					}
					boarder_pos_x=mPortalX-x_traverse[segment][corres_index];
					boarder_pos_x_end=boarder_pos_x+segment_width[segment]-1;
					return ;
				}
				/*
				traverse in the direction of down
				(change from downmost to uppermost)
				*/
				if(mPortalY==boarder_pos_y_end){
					boarder_pos_y=mPortalY-1;
					boarder_pos_y_end=boarder_pos_y+segment_height[segment]-1;
					for(j=0;j<adjacentSegment[segment].size();j++){
						if(adjacentSegment[segment][j]==oldSegment){
							corres_index=j;
							break;
						}
					}
					boarder_pos_x=mPortalX-x_traverse[segment][corres_index];
					boarder_pos_x_end=boarder_pos_x+segment_width[segment]-1;
					return ;
				}
				/*set the traverse information*/
				setTraverse();	
			}
		}
		/*doesn't traverse the segment*/
		*passingFlag=true;
		/*restore the position*/
		restoreBoarderPosition();
		restoreBuilding();
		restoreItem();
		return;
	}//endof if
	
	//check whether player catch the item or not
	for(i=0;i<item_segment.size();i++){
		if(item_segment[i]==segment){
			if(m_item[i]->collect(mPortalY,mPortalX)){
				/*doesn't have to restore the position*/
				*containFlag=true;
				return;
			}
		}
	}
	//check whether player catch the building or not
	for(i=0;i<building_segment.size();i++){
		if(building_segment[i]==segment){
			if(m_build[i]->contains(mPortalY,mPortalX))
			{
				/*doesn't have to consider traverse the segment*/
				*passingFlag=true;
				/*restore the position*/
				restoreBoarderPosition();
				restoreBuilding();
				restoreItem();
				return;
			}
		}
	}
}