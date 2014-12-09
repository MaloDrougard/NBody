#include <vector>
#include <iterator>
#include <iostream>

#include "NBodysFunction.h"
#include <math.h> 

using namespace std;
int OPPERCYCLE = 1;


int NBodysAttraction(std::vector<Particle> * particlesSet)
{
	
	vector<Particle>::iterator it = particlesSet->begin();
	vector<Particle>::iterator innerIt = particlesSet->begin();
	

	//loop variables
	double tempAttractiveForce = 0;
	vector<double> tempRelatedVector;
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

				unitVector(&(*it), &(*innerIt), &tempRelatedVector);
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



int NBodysTravel(std::vector<Particle> * particlesSet, double time)
{

	for (int i = 0; i < (*particlesSet).size(); ++i){
		(*particlesSet).at(i).calculateNewPosition(time);
		(*particlesSet).at(i).calculateNewVelocity(time);

	}

	return 0;
}

/*
* THE FOLLOWING METHOD CAN BE USE IN A PARALLEL SECTION
*/


int NBodysAttraction(std::vector<Particle> * particlesSetRead, std::vector<Particle> * particlesCalculus)
{
	
	vector<Particle>::iterator it = particlesCalculus->begin();
	vector<Particle>::iterator innerIt = particlesSetRead->begin();
	
	double tempAttractiveForce = 0;
	vector<double> tempRelatedVector;
	

	while (it != particlesCalculus->end())
	{
		innerIt = particlesSetRead->begin();
		double fx = 0;
		double fy = 0;

		while (innerIt != particlesSetRead->end()) 
		{
			if (innerIt->id != it->id) // to avoid the selfy
			{	
				unitVector(&(*it), &(*innerIt), &tempRelatedVector);
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



/*
* THE FOLLOWING METHODE ARE JUST TO TEST THE SPEED OF THE PROGRAM
* DO NOT USE FOR REAL CALCULATION
*/

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

		innerIt = set->begin();

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
						
						//OneCycle();
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


int OneCycle()
{
	double p = 0;
	int f = 0;
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
	return p;
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