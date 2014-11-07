#pragma once

#include <vector>
#include "Particle.h"

using namespace std;

class Area {


public:

	double xs[2]; // boundaries of the x interval [x1, x2[
	double ys[2];
	double center[2]; // coordinate (x,y)

	Area(double x1, double x2, double y1, double y2){
		xs[0] = x1;
		xs[1] = x2;
		ys[0] = y1;
		ys[1] = y2;

		center[0] = ((x2 - x1) / 2) + x1;
		center[1] = ((y1 - y2) / 2) + y1; 
	};

	Area(){	};

	double getX1(){	return xs[0];};
	double getX2(){	return xs[1];};
	double getY1(){	return ys[0];};
	double getY2(){	return ys[0];};

	vector<Area> splitArea();
	
	bool contains(Particle * p);

};