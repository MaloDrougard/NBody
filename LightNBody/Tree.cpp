#include "Tree.h"
#include <iostream>

using namespace std;


Tree::Tree(Tree * p, double m, vector<double> mC, Area a)
{
	parent = p;
	mass = m;
	massCenter = mC;
	area = a;
}

Tree::Tree(Tree * p, Area a)
{
	parent = p;
	mass = 0;
	massCenter.push_back(0);
	massCenter.push_back(0);
	area = a;
}

Node::Node(Tree * p, double m, vector<double> mC, Area a, Tree * c1, Tree * c2, Tree * c3, Tree * c4)
	:Tree(p,m,mC,a) 
{
	setChildren(c1, c2, c3, c4);

};


Node::Node(Tree * p, Area a)
:Tree(p, a){};


Leaf::Leaf(Tree * p, Area a, Particle * part)
:Tree(p, part->mass, part->position, a)
{
	particle = part;
}



Nil::Nil(Tree * p, Area a)
: Tree(p, a)  {}

void Tree::print(){
	cout << "Tree:";
}

void Node::print()
{
	cout << "Node: " << mass;
}
 
void Leaf::print()
{
	cout << "Leaf: " << mass;
}

void Nil::print()
{
	cout << "Nil ";
}



