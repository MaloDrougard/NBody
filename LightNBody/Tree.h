#pragma once

#include <vector>
#include "Particle.h"
#include "Area.h"

using namespace std;

class Tree {
public:
	
	Tree * parent;
	
	double mass;
	vector<double> massCenter;
	Area area;

	Tree(Tree * parent, double mass, vector<double> massCenter, Area area);
	Tree(Tree * parent, Area area);
};
	

class Node : public Tree {
public:

	Tree * children1;
	Tree * children2;
	Tree * children3;
	Tree * children4;

	Node(Tree * p, double m, vector<double> mC, Area area, Tree * c1, Tree * c2, Tree * c3, Tree * c4);
	Node(Tree * p, Area a);

	void setMass(double m){ mass = m; };
	void setCenterMass(vector<double> cm) { massCenter = cm; };
	void setChildren(Tree * c1, Tree * c2, Tree * c3, Tree * c4){
		children1 = c1;
		children2 = c2;
		children3 = c3;
		children4 = c4;
	}
};



class Leaf : public Tree {
public:
	Particle * particle;
	Leaf(Tree * p, Area area, Particle * part);
};

class Nil : public Tree {
public:
	Nil(Tree * p);
};