#pragma once

#include <vector>
#include <string>

using namespace std;

class Particle
{
public:

	int id;
	double mass;
	vector<double> position; // in meter
	vector<double> velocity;
	vector<double> acceleration;

	
	Particle(int id, double m, vector<double> p, vector<double> v, vector<double> a);
	Particle();
	~Particle(){};

	// calculate the new position after time t
	void calculateNewPosition(double t); // in sec
	void updateVelocity(double t);
	void setAcceleration(vector <double> * a);
	void setAccelerationByForce(vector<double> * f);


};


double squarDistance(Particle* p1, Particle* p2);
double myDistance(Particle * p1, Particle * p2);

// return unit vector that have the direction of the line between p1 p2
// the sens is from p1 to p2
 vector<double> unitVector(Particle * p1, Particle * p2); 

