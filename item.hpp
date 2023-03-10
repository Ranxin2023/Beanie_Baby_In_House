#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>

/**
 * You shouldn't have any reason to modify this file.
 *
 * This is probably the least justifiable class in the entire assignment,
 * but I want you to practice with many classes.
 */

class Item
{
public:
    Item(int y, int x);

    int getY() const { return mY; }
    int getX() const { return mX; }
	void resetCoordinates(int y, int x);
	bool collect(int y, int x);
	//void setInitItem(int seg,int y,int x);
	//void setItem(int y, int x);
    static char ICON;

private:
    /**
     * Each item is one unit, so only need to store coordinate,
     * not size.
     */
    int mY;
    int mX;
};

#endif // ITEM_HPP
