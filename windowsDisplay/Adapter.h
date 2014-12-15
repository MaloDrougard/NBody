#pragma once

#include <d2d1.h>

#include "Particle.h"

/*
The purpose of this class is to transform a particle into a drawable graphic object
*/

class Adapter
{
private:

	// phisical input
	double intervalX[2]; 
	double intervalY[2];

	// display input
	int pixelWidth; // to set in relation with the main window width
	int pixelHight;
	double massPonderation;

public:
	Adapter(double ixa, double ixb, double iya, double iyb, int pixelW, int pixelH, double massP);
	Adapter();
	~Adapter();

	void setIntervalX(double xa, double xb);
	void setIntervalY(double ya, double yb);
	void setPixelWidth(int pW);
	void setPixelHight(int pH);
	void setMassPonderation(double mP);

	D2D1_ELLIPSE getPoint(Particle p);

};
		
