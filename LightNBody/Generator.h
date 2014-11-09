#pragma once

#include "Particle.h"
#include "Tree.h"
#include "Area.h"


// generate a set from a file who a particle is describe as follow:
// m x y z vx vy vz \n
vector<Particle> GenerateSet(const char * fileName, int maxCount);
Tree * GenerateTree(vector<Particle> set, Tree * parent, Area area);
vector<vector<Particle>> splitSet(vector<Particle> * set, Area area);


