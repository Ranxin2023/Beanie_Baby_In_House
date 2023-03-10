#ifndef MAP_SEGMENT_HPP
#define MAP_SEGMENT_HPP

#include <string>
#include <vector>

#include "building.hpp"
#include "item.hpp"

/**
 * This is probably the class that will have the second biggest portion of
 * your code for this assignment. (The biggest would likely be held
 * by the Game class.)
 *
 * Some things I did that you don't have to do:
 * - Define an enum class for portal directions.
 * - Method for connecting two map segments' portals.
 * - Methods for adding buildings or items to a map segment.
 */
using namespace std;
class MapSegment
{
public:

    MapSegment(int height, int width);
	char getVERTICAL_BORDER_CHAR(){return VERTICAL_BORDER_CHAR;}
	char getHORIZONTAL_BORDER_CHAR(){return HORIZONTAL_BORDER_CHAR;}
	char getPORTAL_CHAR(){return PORTAL_CHAR;}
    int getHeight() const { return mHeight; }
    int getWidth() const { return mWidth; }
    int getPortalX() const { return mPortalX; }
    int getPortalY() const { return mPortalY; }
	int getSegment();
	//get building
	//bool judgeBuildingSegment(int seg, int index);
	int getBuildingIndex(int num);
	int getNumberOfBuilding();
	//int getBuildingHeight();
	//int getBuildingWidth();
	int getBuildingPos_Y(int index);
	int getBuildingPos_X(int index);
	int getBuildingEndPos_Y(int index);
	int getBuildingEndPos_X(int index);
	//get item
	//bool judgeItemSegment(int seg, int index);
	int getItemIndex(int num);
	int getNumberOfItem();
	int getItemPos_Y(int index);
	int getItemPos_X(int index);
	//get boarder
	int getBoarderPos_Y();
	int getBoarderPos_X();
	int getBoarderPosEnd_Y();
	int getBoarderPosEnd_X();
	//get traverse
	int getNumOfTraverse();
	int getTravresePos_Y(int index);
	int getTravresePos_X(int index);
	//get direction
	int getDirection();
	//segment set
	void setMap_segment(int s);
	void setNumberOfSegment(int s);
	void setSegmentSize(int y, int x);
	//direction set
	void setInitDirection(string s);
	void setDirection(int command);
	//building set
	void setInitBuilding(int s,int y,int x);
	void setMovementBuilding();
	void restoreBuilding();
	void setInitItem(int s,int y, int x);
	void setMovementItem();
	void restoreItem();
	//boarder set
	void setInitBoarderPosition(int y, int x);
	void setInitEndBoarderPosition();
	void setMovementBoarderPosition();
	void restoreBoarderPosition();
	//traverse part
	void setInitTraverse(int target, int corres_seg, string dir);
	void setTraverse();
	void setTraversePosition();
	void restoreTraversePosition();
	//largest function
	void setPosition(bool * passingFlag,bool * containFlag);
    /**
     * Returns representation of this map segment as a vector of strings,
     * including any contained items and buildings.
     */
    // std::vector<std::string> getAsLines() const;

private:
    static char VERTICAL_BORDER_CHAR;
    static char HORIZONTAL_BORDER_CHAR;
    static char PORTAL_CHAR;

    /**
     * As always, you don't need to have these member variables if you don't
     * think they would be useful to you.
     */
	
    int mHeight;
    int mWidth;
    /**
     * For helping position the portals.
     * See how they are initialized in the constructor.
     */
    int mPortalY;
    int mPortalX;
	
	/*the segment player is in */
	int segment;
	int numOfSegment;
	/*the position of boarder in correspond segment */
	int boarder_pos_y;
	int boarder_pos_x;
	
	/*the end position of the boarder*/
	int boarder_pos_y_end;
	int boarder_pos_x_end;
	
	/*direction of the player*/
	int direction=-1;
	/*
	Store the information of building inside building array
	Store the segment of each building in building_segment
	*/
	vector<Building *> m_build;
	vector<int>building_segment;
	/*
	Store the information of item inside m_item array
	Store the segment of each item in item_segment
	*/
	vector<Item *> m_item;
	vector<int>item_segment;
	
	/*store the size of each segment*/
	vector<int>segment_height;
	vector<int>segment_width;
	
	/*store the position and adjacent segment for each segment*/
	vector<int>*adjacentSegment;
	vector<int>*y_traverse;
	vector<int>*x_traverse;
	vector<int> y_traverse_pos;
	vector<int> x_traverse_pos;
};

#endif // MAP_SEGMENT_HPP
