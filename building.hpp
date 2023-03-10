#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <string>
#include <vector>

class Building
{
public:
    Building(int y, int x);
	/*
	void setInitBuilding(int seg,int y, int x);
	void setBuilding();
	*/
	/*
	const int getWidth();
	const int getHeight();
	*/
	int getY() const{return mY;}
	int getX()const{return mX;}
	int getEndY()const {return mendY;}
	int getEndX()const {return mendX;}
    /**
     * You DO NOT have to have either of the below methods.
     * I leave them as suggestions.
     */

    /**
     * Draws self onto the given board.
     */
    // void drawIn(std::vector<std::string>& board) const;

    /**
     * Returns true if the given coordinates are contained
     * in this building.
     */
    bool contains(int y, int x) const;
	void resetCoordinates(int y, int x);

private:
    static const int width;
    static const int height;
	//vector<int> segment;
	int mY;
    int mX;
	int mendY;
	int mendX;
};

#endif // BUILDING_HPP
