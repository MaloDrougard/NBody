#include "Area.h"

vector<Area> Area::splitArea()
{
	double middleX = (getX1() - getX2() / 2) + getX1();
	double middleY = (getY1() - getY2() / 2) + getY1();

	vector<Area> ret;

	ret.push_back(Area(getX1(), middleX, getY1(), middleY));
	ret.push_back(Area(middleX, getX2(), getY1(), middleX));
	ret.push_back(Area(middleX, getX2(), middleY, getY2()));
	ret.push_back(Area(getX1(), middleX, middleY, getY2()));
	 
	return ret;
}

bool Area::contains(Particle * p){
	return ( (getX1() <= p->position.at(0) < getX2()) && ((getY1() <= p->position.at(1) < getY2()))  );
}