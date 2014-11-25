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
				tempRelatedVector = unitVector(*it, *innerIt);
				tempAttractiveForce = ((G * it->mass * (*innerIt).mass)) / squarDistance(*it, *innerIt);
				fx = fx + tempAttractiveForce * tempRelatedVector.at(0);
				fy = fy + tempAttractiveForce * tempRelatedVector.at(1);

			}
			++innerIt;
		};

		vector<double> temp;
		temp.push_back(fx);
		temp.push_back(fy);
        it->setAccelerationByForce(temp);

		++it;
	}

	return 0;
	
}

int FakeAccessAttraction(vector<Particle> *set)
{	
	
	vector<Particle>::iterator it = set->begin();
	vector<Particle>::iterator innerIt = set->begin();
	double p = 0;
	int f = 0;

	while (it != set->end())
	{
		int tmp = it->position.at(0) / 2;

		while (innerIt != set->end()) 
			{
				if (innerIt != it) // to avoid the selfy
				{	
					tmp = innerIt->position.at(0) + tmp;
					// cost of the unit vector
						p = pow(3.0, 2) + pow(19.99, 4);
						sqrt(p);
						12 + 23 + 12 + 67;
						4 / 392; 3 / 123;
						//end cost of unit vector

						f = (G * 3 * 3) / pow(3.0, 2) + pow(19.99, 4);
						f = f + f * 3;
						f = f + f * 0.6;

						// cost of set Accelaration
						3 / 7;
						34 / 8;
				}
				++innerIt;
		}
		it->position.at(0) = tmp;
		++it;
	}
}


int FakeNBodysAttraction(int n)
{
	double p = 0;
	int f = 0;
	for (int i = 0; i < n* (n - 1); ++i)
	{
		// cost of the unit vector
		p = pow(3.0, 2) + pow(19.99, 4);
		sqrt(p);
		12 + 23 + 12 + 67;
		4 / 392; 3 / 123;
		//end cost of unit vector

		f = (G * 3 * 3) / pow(3.0, 2) + pow(19.99, 4);
		f = f + f * 3;
		f = f + f * 0.6;

		// cost of set Accelaration
		3 / 7;
		34 / 8;
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

int FakeNBodysTravel(int n)
{	
	int a = 0;
	int b = 0;
	for (int i = 0; i < n;  ++i){
		a = 1 + 1 * 1 + 0.5 * 1 * 1 * 1;
		b = 2 + 2 * 1 + 0.5 * 2 * 2 * 2;
	}
	
	return 0;
}

int FakeAccessTravel(std::vector<Particle> * set)
{
	for (int i = 0 ; i < set->size() ; ++i) {
		set->at(i).mass = set->at(i).mass + 1;
	}
}