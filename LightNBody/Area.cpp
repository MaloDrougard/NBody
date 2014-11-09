#include "Area.h"
#include <iostream>



using namespace std;

vector<Area> Area::splitArea()
{
	double middleX = ((getX2() - getX1()) / 2) + getX1();
	double middleY = ((getY2() - getY1())/ 2) + getY1();

	vector<Area> ret;

	ret.push_back(Area(getX1(), middleX, getY1(), middleY));
	ret.push_back(Area(middleX, getX2(), getY1(), middleX));
	ret.push_back(Area(middleX, getX2(), middleY, getY2()));
	ret.push_back(Area(getX1(), middleX, middleY, getY2()));
	 
	return ret;
}

bool Area::contains(Particle * p){
	bool inX = ((getX1() <= p->position.at(0)) && (p->position.at(0) < getX2()));
	bool inY = (getY1() <= p->position.at(1) && p->position.at(1) < getY2());
	return (inX && inY);
}

void Area::print()
{
	cout << "{X:" << getX1() << "," << getX2() << " Y:" << getY1() << "," << getY2() << "}  ";
}