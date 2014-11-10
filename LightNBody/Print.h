#pragma once 

#include <iostream>
#include <fstream>
#include <time.h>

#include "Particle.h"

/*
* This is print a Set of particle to a txt file using the following format:
* "id: m x y z vx vy vz \n 
*/


int printToFile(vector<Particle> * pSet, const char * fileName);

int initFile(const char * fileName, int numberParticles, int numberSlots, double deltaTime);

int initFileBarnesHut(const char * fileName, int numThreads, int numberParticles, int numberSlots, double deltaTime, double accuracy);

int timeSummary(time_t start, time_t end,  const char * fileName);