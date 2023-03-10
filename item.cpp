#include "item.hpp"

char Item::ICON = '$';

Item::Item(int y, int x)
    : mY(y), mX(x)
{
}


void Item::resetCoordinates(int y, int x)
{
	mY+=y;
	mX+=x;
}

bool Item::collect(int y, int x)
{
	if(mY==y&&mX==x)return true;
	return false;
}