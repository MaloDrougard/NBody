#include <vector>
#include <iterator>
#include <iostream>

#include "NBodysFunction.h"
#include <math.h> 

using namespace std;
int OPPERCYCLE = 10000;
int NBodysAttraction(std::vector<Particle> * particlesSet)
{
	
	vector<Particle>::iterator it = particlesSet->begin();
	vector<Particle>::iterator innerIt = particlesSet->begin();
	
	double tempAttractiveForce = 0;
	vector<double> tempRelatedVector;
	
	//loop variables
	vector<double> temp;
	double fx;
	double fy;

	while (it != particlesSet->end())
	{
		innerIt = particlesSet->begin();
		fx = 0;
		fy = 0;
		temp.clear();

		while (innerIt != particlesSet->end()) 
		{
			if (innerIt != it) // to avoid the selfy
			{	
				tempRelatedVector = unitVector(&(*it), &(*innerIt));
				tempAttractiveForce = ((G * it->mass * innerIt->mass)) / squarDistance(&(*it), &(*innerIt));
				fx = fx + tempAttractiveForce * tempRelatedVector.at(0);
				fy = fy + tempAttractiveForce * tempRelatedVector.at(1);

			}
			++innerIt;
		};
		temp.push_back(fx);
		temp.push_back(fy);
        it->setAccelerationByForce(&temp);

		++it;
	}

	return 0;
	
}
void FakeAccessAttraction(vector<Particle> *set)
{	
	
	vector<Particle>::iterator it = set->begin();
	vector<Particle>::iterator innerIt = set->begin();

	vector<double> tmpA;
	vector<double> tmpP;
	vector<double> tmpV;

	double p = 0;

	while (it != set->end())
	{
		int tmp = it->position.at(0) / 2;
		tmpA.clear();
		tmpP.clear();
		tmpV.clear();


		while (innerIt != set->end()) 
			{

			tmpA = it->acceleration;
			tmpV = it->velocity;
			tmpP = it->position;

				if (innerIt != it) // to avoid the selfy
				{	
					tmp = innerIt->position.at(0) + tmp;
				
					for (int i = 0; i < OPPERCYCLE ; ++i){
						innerIt->mass;
						innerIt->id;					
						tmpA.at(0) = tmpA.at(0) + innerIt->acceleration.at(0) / 16;
						tmpA.at(1) = tmpA.at(1) + innerIt->acceleration.at(1)/16;
						tmpV.at(0) = tmpV.at(0) + innerIt->velocity.at(0) / 16;
						tmpV.at(1) = tmpV.at(1) + innerIt->velocity.at(1) / 16;
						tmpP.at(0) = tmpP.at(0) + innerIt->position.at(0) / 16;
						tmpP.at(1) = tmpP.at(1) + innerIt->position.at(1) / 16;
						
						p = pow(3.0, 2) + pow(19.99, 4);
						sqrt(p);
						
						
					
					}
					
				}

				innerIt->acceleration.at(0) = tmpA.at(0);
				innerIt->acceleration.at(1) = tmpA.at(1);
				innerIt->position.at(0) = tmpP.at(0);
				innerIt->position.at(1) = tmpP.at(1);
				innerIt->velocity.at(0) = tmpV.at(0);
				innerIt->velocity.at(1) = tmpV.at(1);
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
void FakeAccessTravel(std::vector<Particle> * set)
{

	for (int i = 0 ; i < set->size() ; ++i) {
		set->at(i).mass = set->at(i).mass + 1;
		for (int j = 0; j < OPPERCYCLE; ++j){
			set->at(i).acceleration;
			set->at(i).velocity;
			set->at(i).position;

		}

	}
}