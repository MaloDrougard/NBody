#include <omp.h>

#include <iostream>
#include <vector>
#include <time.h>


#include "Particle.h"
#include "NBodysFunction.h"
#include "Generator.h"
#include "Print.h"


using namespace std;

char GENERATORFILE[100]  = "tab128";
char RESULTFILE[100]  = "result.txt";
int COUNTPARTICLE = 100000;
int NUMSLOT = 20;
double DELTATIME = 1;
double ACCURACY = 0.0;
Area baseArea( -50, 50, -50 , 50); 

int main()
{	
	time_t startTime;
	time_t endTime;
	vector<Particle>  set;
	vector<Particle> * rest;
	
	Tree * root;

	/* get infos from user */
	cout << "Hello Beatch!" << endl;
	cout << "Enter the file name of the input file: " << endl;
	gets(GENERATORFILE);

	cout << "Enter the file name of the output file: " << endl;
	gets(RESULTFILE);


	/* initialization */
	rest = new vector<Particle>(0);
	set = GenerateSet(GENERATORFILE, COUNTPARTICLE);
	initFileBarnesHut(RESULTFILE, set.size() , NUMSLOT, DELTATIME, ACCURACY);
	printToFile(&set, RESULTFILE);
			
	int count = 0;
	 
	/* core of the program */
	time(&startTime);
	cout << "Program start at: " << ctime(&startTime) << endl;
	time(&startTime);



	while (count < NUMSLOT){
		root = GenerateTree(set, (Tree *)NULL, baseArea);
		BarnesHutAttractions(&set, root, ACCURACY);
		NBodysTravel(&set, DELTATIME);
		++count;
	}



	
	/* ending */
	time(&endTime);

	printToFile(&set, RESULTFILE);
	timeSummary(startTime, endTime, RESULTFILE);

	cout << "Execution time: " << endTime - startTime << endl;
	cout << "Type any character to close this program "  << endl;
	getchar();

	return 0;
}

