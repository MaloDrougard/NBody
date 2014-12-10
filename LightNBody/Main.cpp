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
int NUMTHREADS = 1;
double DELTATIME = 1;
double ACCURACY = 0.2;
bool INPUT = false;
Area baseArea( -50, 50, -50 , 50); 

void getInfo();

int main()
{	
	
	vector<Particle>  set;
	vector<Particle> * rest;
	TimeAnalyzer analyzer;
	Tree * root;

	if (INPUT)
	{
		getInfo();
	}
	
	/* initialization */
	rest = new vector<Particle>(0);
	set = GenerateSet(GENERATORFILE, COUNTPARTICLE);
	NUMTHREADS = omp_get_num_threads();
	analyzer.init(NUMTHREADS, NUMSLOT);
	initFileBarnesHut(RESULTFILE, NUMTHREADS, set.size() , NUMSLOT, DELTATIME, ACCURACY);
	printToFile(&set, RESULTFILE);
			
	int count = 0;
	 
	/* core of the program */
	
	cout << "Program start!" << endl;
	analyzer.totalTimes.at(0).start = omp_get_wtime();
	

	while (count < NUMSLOT){
		analyzer.soloTimes.at(0).at(count).at(0).start = omp_get_wtime();
		root = GenerateTree(set, (Tree *)NULL, baseArea, rest);
		analyzer.soloTimes.at(0).at(count).at(0).end = omp_get_wtime();

		analyzer.parallelTimes.at(0).at(count).start = omp_get_wtime();
		BarnesHutAttractions(&set, root, ACCURACY);
		NBodysTravel(&set, DELTATIME);
		analyzer.parallelTimes.at(0).at(count).end = omp_get_wtime();
		++count;
	}

	analyzer.totalTimes.at(0).end = omp_get_wtime();

	/* print informations */
	
	printToFile(&set, RESULTFILE);
	restSize(rest->size(), RESULTFILE);
	rawTableToFile(&analyzer, RESULTFILE);

	cout << "Execution time: " << analyzer.getTotalTime(0) << endl;

	if (INPUT)
	{
		cout << "Type any character to close this program " << endl;
		getchar();
	}
	
	return 0;
}

void getInfo()
{
	/* get infos from user */
	cout << "Hello Beatch!" << endl;
	cout << "Enter the file name of the input file: " << endl;
	gets(GENERATORFILE);

	cout << "Enter the file name of the output file: " << endl;
	gets(RESULTFILE);
}