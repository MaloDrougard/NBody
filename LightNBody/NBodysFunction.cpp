#include <vector>
#include <iterator>
#include <iostream>

#include "NBodysFunction.h"
#include <math.h> 

using namespace std;

int NBodysAttraction(std::vector<Particle> * particlesSet)
{
	
	vector<Particle>::iterator it = particlesSet->begin();
	vector<Particle>::iterator innerIt = particlesSet->begin();
	
	double tempAttractiveForce = 0;
	vector<double> tempRelatedVector;
	

	while (it != particlesSet->end())
	{
		innerIt = particlesSet->begin();
		double fx = 0;
		double fy = 0;

		while (innerIt != particlesSet->end()) 
		{
			if (innerIt != it) // to avoid the selfy
			{	
				tempRelatedVector = unitVector(&(*it), &(*innerIt));
				tempAttractiveForce = ((G * it->mass * (*innerIt).mass)) / squarDistance(&(*it), &(*innerIt));
				fx = fx + tempAttractiveForce * tempRelatedVector.at(0);
				fy = fy + tempAttractiveForce * tempRelatedVector.at(1);

			}
			++innerIt;
		};

		vector<double> temp;
		temp.push_back(fx);
		temp.push_back(fy);
        it->setAccelerationByForce(&temp);

		++it;
	}

	return 0;
	
}

int NBodysTravel(std::vector<Particle> * particlesSet, double time)
{

	for (int i = 0; i < (*particlesSet).size(); ++i ){
		(*particlesSet).at(i).calculateNewPosition(time);

	}

	return 0;
}