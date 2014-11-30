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

int timeSummary(double start, double end, const char * fileName, vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes);

int timeTable(vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes, const char * fileName);

int timeTableToConsole(vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes);

int timeSummaryToConsole(double start, double end, vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes);

double mean(vector<double> * v);

double sum(vector<double> * v);