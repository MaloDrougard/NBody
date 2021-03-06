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

void Particle::calculateNewVelocity(double t)
{
	velocity[0] = velocity[0] + acceleration[0] * t;
	velocity[1] = velocity[1] + acceleration[1] * t;
}

void Particle::setAcceleration(vector<double>  * a)
{
	acceleration[0] = a->at(0);
	acceleration[1] = a->at(1);
}

void Particle::setAccelerationByForce(vector<double> * f)
{
	acceleration[0] = f->at(0) / mass;
	acceleration[1] = f->at(1) / mass;
}


double squarDistance(Particle* p1, Particle* p2)
{
	return pow(p1->position[0] - p2->position[0], 2) + pow(p1->position[1] - p2->position[1], 2);
}

double myDistance(Particle * p1, Particle * p2)
{
	return sqrt(squarDistance(p1, p2));
}



void unitVector(Particle * p1, Particle * p2, vector<double> * unit)
{
	unit->clear();
	double d = myDistance(p1, p2);

	for (unsigned int i = 0; i < p1->position.size(); ++i){
		unit->push_back(p2->position.at(i) - p1->position.at(i));
		unit->at(i) = unit->at(i) / d;
	}

}

void Particle::unitVectorToPoint(vector<double> * point, vector<double> * unit)
{	
	unit->clear();

	double x = point->at(0) - position.at(0);
	double y = point->at(1) - position.at(1);
	double norme = distanceToPoint(point);

	unit->push_back(x / norme);
	unit->push_back( y / norme);
}



double Particle::distanceToPoint(vector<double> * point)
{
	return sqrt(squarDistanceToPoint(point));
}



double Particle::squarDistanceToPoint(vector<double> * point)
{
	double x = point->at(0) - position.at(0);
	double y = point->at(1) - position.at(1);
	return (pow(x, 2) + pow(y, 2));

}
