#include "Generator.h"
#include "Particle.h"
#include <iostream>
#include <fstream>


#include <vector>

vector<Particle> GenerateSet(const char * fileName, int maxCount)
{

	ifstream ifs;
	ifs.open(fileName, std::ifstream::in);
	vector<Particle> tmp;
	Particle tmpP ;
	double tmpD;
	int count = 0;

	while (ifs.good() && count < maxCount){
		
		tmpP.id = count;
		ifs >> tmpP.mass;
		ifs.get(); // to skip the " "
		ifs >> tmpP.position.at(0);
		ifs.get();
		ifs >> tmpP.position.at(1);
		ifs.get();
		ifs >> tmpD; // to skip the z coordinate
		ifs.get();
		ifs >> tmpP.velocity.at(0);
		ifs.get();
		ifs >> tmpP.velocity.at(1);
		ifs.get();
		ifs >> tmpD; // to skip the z velocity
		
		tmp.push_back(tmpP);

		while (ifs.peek() == '.' || ifs.peek() == '\n' || ifs.peek() == ' ') { // the end can be done with '.',' 'or '\n'
			ifs.get();
		}
		
		++count;
	}
	ifs.close();

	return tmp;
}



/*
* Recursive Metohde to build a tree first call should be done with a NULL pointer as parent
* return the root of the tree
*/
Tree * GenerateTree(vector<Particle> set, Tree * parentNode, Area area)
{
	
	Tree * tmp = new Tree(parentNode, area);

	if (set.size() == 0) {
		*tmp = Nil::Nil(parentNode, area);
	}
	else if (set.size() == 1) {

		*tmp = Leaf::Leaf(parentNode, area, &(set.at(0)));
	}
	else{

		Node t(parentNode, area);

		vector<Area> areas = area.splitArea();
		vector<vector<Particle>> subSets = splitSet(&set, area);
		
		Tree * child1 = GenerateTree(subSets.at(0), &t, areas.at(0));
		Tree * child2 = GenerateTree(subSets.at(1), &t, areas.at(1));
		Tree * child3 = GenerateTree(subSets.at(2), &t, areas.at(2));
		Tree * child4 = GenerateTree(subSets.at(3), &t, areas.at(3));

		double m = child1->mass + child2->mass + child3->mass + child4->mass;
		
		vector<double> centerMass(2);
		centerMass.at(0) = (child1->mass * child1->massCenter.at(0) + child2->mass * child2->massCenter.at(0) +
			child3->mass * child3->massCenter.at(0) + child4->mass * child4->massCenter.at(0)) /m;
		centerMass.at(1) = (child1->mass * child1->massCenter.at(1) + child2->mass * child2->massCenter.at(1) +
			child3->mass * child3->massCenter.at(1) + child4->mass * child4->massCenter.at(1)) /m;


		t.setChildren(child1, child2, child3, child4);
		t.setMass(m);
		t.setCenterMass(centerMass);

		*tmp = t;
	}

	return tmp;

}


vector<vector<Particle>> splitSet(vector<Particle> * set, Area area){

	vector<Area> areas = area.splitArea();
	vector<vector<Particle>> subSets (4) ;

	vector<Particle>::iterator it = set->begin();

	while (it != set->end()){
		if (areas.at(0).contains(&(*it))) { 
			subSets.at(0).push_back(*it); 
		}
		else if (areas.at(1).contains(&(*it))) {
			subSets.at(1).push_back(*it);
		}
		else if (areas.at(2).contains(&(*it))) {
			subSets.at(2).push_back(*it);
		}
		else if (areas.at(3).contains(&(*it))) {
			subSets.at(3).push_back(*it);
		}
		++it;
	}

	return subSets;

}
