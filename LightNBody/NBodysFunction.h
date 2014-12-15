#pragma once

#include <vector>
#pragma once
#include "Particle.h"
#include "Tree.h"

/*
 *This function take the a set of particles 
* and compute the new position of particle after a laps of time
*/
int NBodysAttraction(std::vector<Particle> * particlesSet);

int NBodysAttraction(std::vector<Particle> * particlesSetRead , std::vector<Particle> * particlesToCompute);

int NBodysTravel(std::vector<Particle> * particlesSet, double time);

int BarnesHutAttractions(std::vector<Particle> * set, Tree *  look, double accurancy);
vector<double> calculateAttraction(Particle * p, Tree * look, double accurancy); 
double calculateAttractionX(Particle *  p, Tree * look, double accurancy, vector<double> * directionUnitTmp);
double calculateAttractionY(Particle *  p, Tree * look, double accurancy, vector<double> * directionUnitTmp);

void setG(double newG);
double getG();

/* this function are just for testing the program */
void FakeAccessTravel(std::vector<Particle> * set);
void FakeAccessAttraction(vector<Particle> *set);
int OneCycle();
