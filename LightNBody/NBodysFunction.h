#pragma once

#include <vector>
#pragma once
#include "Particle.h"
#include "Tree.h"


// This function take the a set of particles 
// and compute the new position of particle after a laps of time

int NBodysTravel(std::vector<Particle> * particlesSet, double time);
int BarnesHutAttractions(std::vector<Particle> * set, Tree *  look, double accurancy);
vector<double> calculateAttraction(Particle * p, Tree * look, double accurancy); 


const double G = 1; // 0.0000000000667259;