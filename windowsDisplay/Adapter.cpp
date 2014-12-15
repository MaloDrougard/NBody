#include "Adapter.h"


Adapter::Adapter(double ixa, double ixb, double iya, double iyb, int pixelW, int pixelH, double massP)
{	
	setIntervalX(ixa, ixb);
	setIntervalY(iya, iyb);

	pixelWidth = pixelW;
	pixelHight = pixelH;
	massPonderation = massP;
}

Adapter::Adapter()
{
	setIntervalX(-0.5, 0.5);
	setIntervalY(-0.5, 0.5);

	pixelWidth = 1000;
	pixelHight = 1000;
	massPonderation = 0.01;
}

Adapter::~Adapter()
{
}


void Adapter::setIntervalX(double xa, double xb){
	intervalX[0] = xa;
	intervalX[1] = xb;
}

void Adapter::setIntervalY(double xa, double xb){
	intervalY[0] = xa;
	intervalY[1] = xb;
}

void Adapter::setPixelWidth(int pW){
	pixelWidth = pW;
}
void Adapter::setPixelHight(int pH){
	pixelHight = pH;
}
void Adapter::setMassPonderation(double mP){
	massPonderation = mP;
}


/*
* change the phisical coordinate int to a point to print in the screen
* remarque: the pixel (0,0) is on the top left of the screen
*/
D2D1_ELLIPSE Adapter::getPoint(Particle p)
{	

	float x = (p.position.at(0) - intervalX[0]) * (pixelWidth / (intervalX[1] - intervalX[0]));
	float y =  (intervalY[1] - p.position.at(1)) * (pixelHight / (intervalY[1] - intervalY[0]));
	double r = p.mass / massPonderation;
	
	return D2D1::Ellipse(D2D1::Point2F(x, y), r , r );
}