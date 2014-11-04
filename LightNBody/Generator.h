#pragma once

#include "Particle.h"


// generate a set from a file who a particle is describe as follow:
// m x y z vx vy vz \n
vector<Particle> GenerateSet(const char * fileName, int maxCount);
