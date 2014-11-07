#include "Tree.h"


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
	massCenter = { 0, 0 };
	area = a;
}

Node::Node(Tree * p, double m, vector<double> mC, Area a, Tree * c1, Tree * c2, Tree * c3, Tree * c4)
	:Tree(p,m,mC,a) 
{

		children1 = c1;
		children2 = c2;
		children3 = c3;
		children4 = c4;

};

Node::Node(Tree * p, Area a)
:Tree(p, a){};

Leaf::Leaf(Tree * p, Area a, Particle * part)
:Tree(p, part->mass, part->position, a)
{
	particle = part;
}

Nil::Nil(Tree * p)
: Tree(p, 0, { 0, 0 }, Area(0,0,0,0))  {}

