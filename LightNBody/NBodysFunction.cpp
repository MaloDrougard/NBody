#include <vector>
#include <iterator>
#include <iostream>

#include "NBodysFunction.h"
#include "Tree.h"
#include <math.h> 

using namespace std;

int NBodysTravel(std::vector<Particle> * particlesSet, double time)
{
	for (int i = 0; i < particlesSet->size(); ++i){
		particlesSet->at(i).calculateNewPosition(time);
		particlesSet->at(i).calculateNewVelocity(time);
	}
	return 0;
}

int BarnesHutAttractions(std::vector<Particle> * set, Tree *  look, double accurancy)
{

	vector<Particle>::iterator it = set->begin();
	vector<double> force(2);
	vector<double> directionUnitTmp; // for optimisation

	while (it != set->end())
	{
		//force.clear();
		//force.push_back( calculateAttractionX( &(*it),  look, accurancy, &directionUnitTmp )); // set fx
		//force.push_back(calculateAttractionY(&(*it), look, accurancy, &directionUnitTmp)); // set fy
		force = calculateAttraction(&(*it), look, accurancy);

		it->setAccelerationByForce(&force);
		++it;
	}

	return 0;


}
double calculateAttractionX(Particle *  p, Tree * look, double accurancy, vector<double> * directionUnitTmp){
	double fx = 0;

	if (look->isNil()){
	}
	else if(look->isLeaf()){
		p->unitVectorToPoint(look->getMassCenter(), directionUnitTmp);
		double squarNorm = p->squarDistanceToPoint(look->getMassCenter());

		if (squarNorm != 0){ // to avoid selfy and extrem colision
			fx = (directionUnitTmp->at(0) * G * look->mass * p->mass) / squarNorm;
		}
	}
	else if (look->isNode()){
		if (look->area.getWitdh() / p->distanceToPoint(look->getMassCenter()) < accurancy)
		{
			p->unitVectorToPoint(look->getMassCenter(), directionUnitTmp);
			double squarNorm = p->squarDistanceToPoint(look->getMassCenter());

			if (squarNorm != 0){ // to avoid selfy and extrem colision
				fx = (directionUnitTmp->at(0) * G * look->mass * p->mass) / squarNorm;
			}
		}
		else
		{
			vector<Tree * > children = look->getChildren();
			double fx1 = calculateAttractionX(p, children.at(0), accurancy, directionUnitTmp);
			double fx2 = calculateAttractionX(p, children.at(1), accurancy, directionUnitTmp);
			double fx3 = calculateAttractionX(p, children.at(2), accurancy, directionUnitTmp);
			double fx4 = calculateAttractionX(p, children.at(3), accurancy, directionUnitTmp);
			fx = fx1 + fx2 + fx3 + fx4;
		}
	}
	else{
		cerr << "WARNING: Tree contains undetermided element" << endl;
	}

	return fx;
}

double calculateAttractionY(Particle *  p, Tree * look, double accurancy, vector<double> * directionUnitTmp){
	double fy = 0;
	if (look->isNil()){
	}
	else if (look->isLeaf()){
		p->unitVectorToPoint(look->getMassCenter(), directionUnitTmp);
		double squarNorm = p->squarDistanceToPoint(look->getMassCenter());
		if (squarNorm != 0){ // to avoid selfy and extrem colision
			fy = (directionUnitTmp->at(1) * G * look->mass * p->mass) / squarNorm;
		}
	}
	else if (look->isNode()){
		if (look->area.getWitdh() / p->distanceToPoint(look->getMassCenter()) < accurancy)
		{
			p->unitVectorToPoint(look->getMassCenter(), directionUnitTmp);
			double squarNorm = p->squarDistanceToPoint(look->getMassCenter());
			if (squarNorm != 0){ // to avoid selfy and extrem colision
				fy = (directionUnitTmp->at(1) * G * look->mass * p->mass) / squarNorm;
			}
		}
		else
		{
			vector<Tree * > children = look->getChildren();
			double fy1 = calculateAttractionY(p, children.at(0), accurancy, directionUnitTmp);
			double fy2 = calculateAttractionY(p, children.at(1), accurancy, directionUnitTmp);
			double fy3 = calculateAttractionY(p, children.at(2), accurancy, directionUnitTmp);
			double fy4 = calculateAttractionY(p, children.at(3), accurancy, directionUnitTmp);
			fy = fy1 + fy2 + fy3 + fy4;
		}
	}
	else{
		cerr << "WARNING: Tree contains undetermided element" << endl;
	}

	return fy;
}


vector<double> calculateAttraction(Particle * p, Tree * look, double accurancy)
{
	vector<double> f (2);
	f.at(0) = 0;
	f.at(1) = 0;
	vector<double> directionUnitTmp (2);


	if (look->isNil()){	
	}
	else if (look->isLeaf() ){
		
			 p->unitVectorToPoint(look->getMassCenter(), &directionUnitTmp);
			double squarNorm = p->squarDistanceToPoint(look->getMassCenter());
			if (squarNorm != 0){
				f.at(0) = (directionUnitTmp.at(0) * G * look->mass * p->mass) / squarNorm;
				f.at(1) = (directionUnitTmp.at(1) * G * look->mass * p->mass) / squarNorm;
			}
		
	}
	else if (look->isNode()){
		if ( look->area.getWitdh() / p->distanceToPoint(look->getMassCenter()) < accurancy) 
		{
			p->unitVectorToPoint(look->getMassCenter(), &directionUnitTmp);
			double squarNorm = p->distanceToPoint(look->getMassCenter());
			if (squarNorm != 0){
				f.at(0) = (directionUnitTmp.at(0) * G * look->mass * p->mass) / squarNorm;
				f.at(1) = (directionUnitTmp.at(1) * G * look->mass * p->mass) / squarNorm;
			}
		}
		else
		{
			vector<Tree * > children = look->getChildren();
			vector<double>  f1 = calculateAttraction(p, children.at(0), accurancy);
			vector<double>  f2 = calculateAttraction(p, children.at(1), accurancy);
			vector<double>  f3 = calculateAttraction(p, children.at(2), accurancy);
			vector<double>  f4 = calculateAttraction(p, children.at(3), accurancy);

			f.at(0) = f1.at(0) + f2.at(0) + f3.at(0) + f4.at(0);
			f.at(1) = f1.at(1) + f2.at(1) + f3.at(1) + f4.at(1);
		}
	}
	else{
		cerr << "WARNING: Tree contains undetermided element" << endl;
	}

	return f;
}