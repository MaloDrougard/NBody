#include "Particle.h"

#include <math.h>

using namespace std;

Particle::Particle()
{
	id = 0;
	mass = 0;
	
	position.resize(2, 0.0);
	acceleration.resize(2, 0.0);
	velocity.resize(2, 0.0);

}


Particle::Particle(int identity, double m, vector<double> p, vector<double> v, vector<double> a)
{
	id = identity;
	mass = m;

	// to create space
	position.resize(2, 0.0);
	acceleration.resize(2, 0.0);
	velocity.resize(2, 0.0);

	position[0] = p[0];
	position[1] = p[1];

	velocity[0] = v[0];
	velocity[1] = v[1];

	acceleration[0] = a[0];
	acceleration[1] = a[1];
}


void Particle::calculateNewPosition(double t)
{
	position[0] = position[0] + velocity[0] * t + 0.5 * acceleration[0] * t * t;
	position[1] = position[1] + velocity[1] * t + 0.5 * acceleration[1] * t * t;
}

void Particle::setAcceleration(vector<double> a)
{
	acceleration[0] = a[0];
	acceleration[1] = a[1];
}

void Particle::setAccelerationByForce(vector<double> f)
{
	acceleration[0] = f[0] / mass;
	acceleration[1] = f[1] / mass;
}


double squarDistance(Particle p1, Particle p2)
{
	return pow(p1.position[0] - p2.position[0], 2) + pow(p1.position[1] - p2.position[1], 2);
}

double myDistance(Particle p1, Particle p2)
{
	return sqrt(squarDistance(p1, p2));
}

vector<double> unitVector(Particle p1, Particle p2)
{
	vector<double> u ;
	double d = myDistance(p1, p2);


	for (unsigned int i = 0; i < p1.position.size(); ++i){
		u.push_back(p2.position.at(i) - p1.position.at(i));
		u.at(i) = u.at(i) / d;
	}

	return u;
}


