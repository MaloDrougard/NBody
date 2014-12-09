#pragma once

#include <vector>
#include "Particle.h"

/*
 *This function take the a set of particles 
* and compute the new position of particle after a laps of time
*/
int NBodysAttraction(std::vector<Particle> * particlesSet);
int NBodysTravel(std::vector<Particle> * particlesSet, double time );

const double G = 0.0000000000667259;  // 1; // 0.0000000000667259;

/* this function are just for testing the program */
void FakeAccessTravel(std::vector<Particle> * set);
void FakeAccessAttraction(vector<Particle> *set);
int OneCycle();
