#include <omp.h>

#include <iostream>
#include <vector>
#include <time.h>


#include "Particle.h"
#include "NBodysFunction.h"
#include "Generator.h"
#include "Print.h"


using namespace std;


char GENERATORFILE[100] = "tab1024";
char RESULTFILE[100] = "result.txt";
int COUNTPARTICLE = 100000;
int NUMSLOT = 20;
double DELTATIME = 1;
int NUMTHREADS = 1;
bool INPUT = true;

void getInput();

int main()
{	
	TimeAnalyzer analyzer;
	
	if (INPUT){
		getInput();
	}
	
	/* initialization */

	vector<Particle>  set = GenerateSet(GENERATORFILE, COUNTPARTICLE);
	NUMTHREADS = omp_get_num_threads();
	initFile(RESULTFILE, set.size() , NUMTHREADS, NUMSLOT, DELTATIME);
	printToFile(&set, RESULTFILE);
	int count = 0;
	analyzer.init(NUMTHREADS, NUMSLOT);
	 
	/* core of the program */
	cout << "Program start" << endl;
	analyzer.totalTimes.at(0).start = omp_get_wtime();

	while (count < NUMSLOT){
		NBodysAttraction(&set);
		NBodysTravel(&set, DELTATIME);
		++count;
	}

	/* ending */
	analyzer.totalTimes.at(0).end = omp_get_wtime();

	printToFile(&set, RESULTFILE);
	rawTableToFile(&analyzer, RESULTFILE);

	cout << "Execution time: " << analyzer.getTotalTime(0) << endl;
	cout << "Type any character to close this program "  << endl;
	getchar();

	return 0;
}



void getInput()
{
	/* get infos from user */
	cout << "Hello Beatch!" << endl;
	cout << "Enter the file name of the input file: " << endl;
	gets(GENERATORFILE);

	cout << "Enter the file name of the output file: " << endl;
	gets(RESULTFILE);
}