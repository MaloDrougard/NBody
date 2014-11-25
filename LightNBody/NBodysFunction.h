#pragma once

#include <vector>
#include "Particle.h"


// This function take the a set of particles 
// and compute the new position of particle after a laps of time

int NBodysAttraction(std::vector<Particle> * particlesSet);
int NBodysTravel(std::vector<Particle> * particlesSet, double time );

int FakeNBodysAttraction(int n); // do the same number of operation as NbodysAttraction but without any call and setup
int FakeNBodysTravel(int n);
int FakeAccessTravel(std::vector<Particle> * set);
int FakeAccessAttraction(vector<Particle> *set);

const double G = 1; // 0.0000000000667259;