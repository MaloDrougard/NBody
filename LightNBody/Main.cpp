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
int NUMTHREADS = 4; 
double ACCURACY = 0;
bool INPUT = false;

void getInfo();
void setArguments(int argc, char* argv[]);

int main(int argc, char* argv[])
{	
	
	
	setArguments(argc, argv);
	if (INPUT)
	{
		getInfo();
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
	analyzer.init(NUMTHREADS, NUMSLOT);
	initFile(RESULTFILE, NUMTHREADS, set.size() , NUMSLOT, DELTATIME);
	printToFile(&set, RESULTFILE);
	int count = 0;
	 	
	/* preparing the parallel section */ 
	int subSetSize = set.size() / NUMTHREADS;
	vector<vector<Particle>> subSet;
	vector<Particle>::iterator it = set.begin();
	for( int i = 0 ; i < NUMTHREADS - 1 ; ++i ) {
		vector<Particle> temp (it , it + subSetSize);
		subSet.push_back(temp);
		it = it + subSetSize;
	}
	vector<Particle> last (it , set.end()); //it's possible that the numthread is not a divisor of the set.size
	subSet.push_back(last);

	int tid;
	time_t threadTime;
	

#pragma omp parallel private(tid, count, threadTime) shared(set) num_threads(NUMTHREADS)
{	
	count = 0;
	tid = omp_get_thread_num();
	analyzer.totalTimes.at(tid).start = omp_get_wtime();
	cout << "Thread: " << tid << "  start" << endl;

	while (count < NUMSLOT){
		analyzer.parallelTimes.at(tid).at(count).start = omp_get_wtime();
		NBodysAttraction(&set, &(subSet.at(tid)) );
		NBodysTravel(&(subSet.at(tid)), DELTATIME);
		analyzer.parallelTimes.at(tid).at(count).end = omp_get_wtime();
		
#pragma omp barrier // the thread have all update her part
#pragma omp single
		{	
			analyzer.soloTimes.at(tid).at(count).at(0).start = omp_get_wtime();
			set.clear();
			for(int i = 0; i < NUMTHREADS; ++i) {
				set.insert(set.end(), subSet.at(i).begin(), subSet.at(i).end());
			}
			analyzer.soloTimes.at(tid).at(count).at(0).end = omp_get_wtime();
		}

		++count;
	}
	
	analyzer.totalTimes.at(tid).end = omp_get_wtime();
	cout << "Thread: " << tid << "EXUCTIONTIME: " <<  analyzer.getTotalTime(tid)  << " Prcoess particles: " << subSet.at(tid).size() << endl;

}  /* All threads join master thread and terminate */


	/* ending */
	
	printToFile(&set, RESULTFILE);
	rawTableToFile(&analyzer, RESULTFILE);

	if (INPUT)
	{
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


void getInfo()
{
	/* get infos from user */
	cout << "Hello Beatch!" << endl;
	cout << "Enter the file name of the input file: " << endl;
	gets(GENERATORFILE);

	cout << "Enter the file name of the output file: " << endl;
	gets(RESULTFILE);

}