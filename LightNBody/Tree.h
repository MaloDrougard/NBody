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
	vector<Tree *> children;

	Tree(Tree * parent, double mass, vector<double> massCenter, Area area);
	Tree(Tree * parent, Area area);

	void setMass(double m){ mass = m; };
	void setCenterMass(vector<double> cm) { massCenter = cm; };

	void setChild(Tree * newChild) {
		children.push_back(newChild);
	}


	virtual void print();
	vector<Tree * > getChildren() {
		return children;
	}
};
	

class Node : public Tree {
public:

	Node(Tree * p, double m, vector<double> mC, Area area, Tree * c1, Tree * c2, Tree * c3, Tree * c4);
	Node(Tree * p, Area a);

	void setChildren(Tree * c1, Tree * c2, Tree * c3, Tree * c4){
		children.clear();
		children.push_back(c1);
		children.push_back(c2);
		children.push_back(c3);
		children.push_back(c4);
	}

	void print();
};



class Leaf : public Tree {
public:
	Particle * particle;
	Leaf(Tree * p, Area area, Particle * part);

	void print();
};

class Nil : public Tree {
public:
	Nil(Tree * p, Area a);

	void print();
};