#include <vector>
#include <iterator>
#include <iostream>

#include "NBodysFunction.h"
#include "Tree.h"
#include <math.h> 

using namespace std;

int NBodysTravel(std::vector<Particle> * particlesSet, double time)
{
	for (int i = 0; i < (*particlesSet).size(); ++i){
		(*particlesSet).at(i).calculateNewPosition(time);
	}
	return 0;
}

int BarnesHutAttractions(std::vector<Particle> * set, Tree *  look, double accurancy)
{

	vector<Particle>::iterator it = set->begin();
	vector<double> force(2);

	while (it != set->end())
	{
		force = calculateAttraction( &(*it),  look, accurancy);
		it->setAccelerationByForce(&force);
		++it;
	}

	return 0;


}

vector<double> calculateAttraction(Particle * p, Tree * look, double accurancy)
{
	vector<double> f (2);
	f.at(0) = 0;
	f.at(1) = 0;


	if (look->isNil()){	
	}
	else if (look->isLeaf() ){
		
			vector<double> directionUnit = p->unitVectorToPoint(&(look->massCenter));
			double squarNorm = p->squarDistanceToPoint(&(look->massCenter));
			if (squarNorm != 0){
				f.at(0) = (directionUnit.at(0) * G * look->mass * p->mass) / squarNorm;
				f.at(1) = (directionUnit.at(1) * G * look->mass * p->mass) / squarNorm;
			}
		
	}
	else if (look->isNode()){
		if ( look->area.getWitdh() / p->distanceToPoint(&(look->massCenter)) < accurancy) 
		{
			vector<double> directionUnit = p->unitVectorToPoint(&(look->massCenter));
			double squarNorm = p->distanceToPoint(&(look->massCenter));
			if (squarNorm != 0){
				f.at(0) = (directionUnit.at(0) * G * look->mass * p->mass) / squarNorm;
				f.at(1) = (directionUnit.at(1) * G * look->mass * p->mass) / squarNorm;
			}
		}
		else
		{
			vector<Tree * > children = look->getChildren();
			vector<double> f1 = calculateAttraction(p, children.at(0), accurancy);
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