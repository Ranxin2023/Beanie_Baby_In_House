#include "building.hpp"

const int Building::width = 6;
const int Building::height = 4;

Building::Building(int y, int x)
    : mY(y), mX(x)
{
	
	mendY=mY+height-1;
	mendX=mX+width-1;
	
}

bool Building::contains(int y, int x)const
{
	if((y>=mY&&y<=mendY)&&(x>=mX&&x<=mendX))return true;
	return false;
}

void Building::resetCoordinates(int y, int x)
{
	mY+=y;
	mX+=x;
	mendY=mY+height-1;
	mendX=mX+width-1;
}
/*
const int Building::getWidth()
{
	return width;
}
const int Building::getHeight()
{
	return height;
}
*/