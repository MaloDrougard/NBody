#include <omp.h>

#include <iostream>
#include <vector>
#include <time.h>


#include "Particle.h"
#include "NBodysFunction.h"
#include "Generator.h"
#include "Print.h"
#include <string.h>


using namespace std;


char GENERATORFILE[100] = "tab1024";
char RESULTFILE[100] = "result.txt";
int COUNTPARTICLE = 100000;
int NUMSLOT = 20;
double DELTATIME = 0.01;
int NUMTHREADS = 1;
int ACCURACY = 0;
bool INPUT;

void setArguments(int argc, char * argv[]); // args: inFile, ouFile, numThreads, numSlot, deltaTime, accuracy
void getInput();

int main(int argc, char* argv[]) {

	
	setArguments(argc, argv);	
	if (INPUT){
		getInput();
	}
	
	cout << endl;
	cout << "INPUT_FILE: " << GENERATORFILE << endl;
	cout << "OUTPUT_FILE: " << RESULTFILE << endl;
	cout << "NUMBER_OF_THREADS: " << NUMTHREADS << endl;
	cout << "NUMBER_OF_SLOTS: " << NUMSLOT << endl;
	cout << "DELTATIME: " << DELTATIME << endl;
	cout << "ACCURACY: " << ACCURACY << endl << endl;

	/* initialization */

	TimeAnalyzer analyzer;
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
	if (INPUT){
		cout << "Type any character to close this program " << endl;
		getchar();
	}
	

	return 0;
}


void setArguments(int argc, char* argv[])
{
	if (argc == 1)
	{
		INPUT = true;
	}
	else if (argc == 6) // the first argument is allways the program name
	{
		INPUT = false;
		strcpy(GENERATORFILE, argv[1]);
		strcpy(RESULTFILE, argv[2]);
		NUMTHREADS = atoi(argv[3]);
		NUMSLOT = atoi(argv[4]);
		DELTATIME = atof(argv[5]);
	}
	else if (argc == 7) 
	{
		INPUT = false;
		strcpy(GENERATORFILE, argv[1]);
		strcpy(RESULTFILE, argv[2]);
		NUMTHREADS = atoi(argv[3]);
		NUMSLOT = atoi(argv[4]);
		DELTATIME = atof(argv[5]);
		ACCURACY = atof(argv[6]);
	}
	else
	{
		cerr << "invalide number of paramters";
		exit(3);
	}
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