#include <omp.h>

#include <iostream>
#include <vector>
#include <time.h>


#include "Particle.h"
#include "NBodysFunction.h"
#include "Generator.h"
#include "Print.h"
#include "TimeAnalyzer.h"

using namespace std;

char GENERATORFILE[100]  = "tab128";
char RESULTFILE[100]  = "result.txt";
int COUNTPARTICLE = 100000;
int NUMSLOT = 20;
double DELTATIME = 1;
double ACCURACY = 0;
int NUMTHREADS = 1;	
bool INPUT = true;
Area baseArea( -50, 50, -50 , 50); 

void getInput();
void setArguments(int argc, char* argv[]);

int main(int argc, char* argv[])
{	

	setArguments(argc, argv); 
	if (INPUT) {
		getInput();
	}

	cout << endl;
	cout << "INPUT_FILE: " << GENERATORFILE << endl;
	cout << "OUTPUT_FILE: " << RESULTFILE << endl;
	cout << "NUMBER_OF_THREADS: " << NUMTHREADS << endl;
	cout << "NUMBER_OF_SLOTS: " << NUMSLOT << endl;
	cout << "DELTATIME: " << DELTATIME << endl;
	cout << "ACCURACY: " << ACCURACY << endl << endl;

	vector<Particle>  set;
	vector<Particle> * rest;
	Tree * root;
	TimeAnalyzer analyzer;

	

	/* initialization */
	rest = new vector<Particle>(0);
	set = GenerateSet(GENERATORFILE, COUNTPARTICLE);
	initFileBarnesHut(RESULTFILE, NUMTHREADS, set.size() , NUMSLOT, DELTATIME, ACCURACY);
	printToFile(&set, RESULTFILE);
	analyzer.init(NUMTHREADS, NUMSLOT);
	int count = 0;
	 
	
	/* preparing the parallel section */
	int subSetSize = set.size() / NUMTHREADS;
	vector<vector<Particle>> subSet;
	vector<Particle>::iterator it = set.begin();
	for (int i = 0; i < NUMTHREADS; ++i) {
		vector<Particle> temp(it, it + subSetSize);
		subSet.push_back(temp);
		it = it + subSetSize;
	}
	vector<Particle> remainder(it, set.end());
	for(int i = 0; i < remainder.size(); ++i){
		subSet.at(i).push_back(remainder.at(i));
	}

	/* core of the program */

	cout << "Program start: " << endl;

	/* the private variable for the parallel section*/
	int tid = 0;

#pragma omp parallel private(tid, count) shared(set, root, analyzer) num_threads(NUMTHREADS)
	{
		tid = omp_get_thread_num();
		cout << "Thread: " << tid << "  Start!" << endl;
		count = 0;
		analyzer.totalTimes.at(tid).start = omp_get_wtime();

		//Core of the software
		while (count < NUMSLOT){
#pragma omp single
			{	
				cout << "Thread " << tid << " generate the tree. " << endl;
				analyzer.soloTimes.at(tid).at(count).at(0).start = omp_get_wtime();

				root = GenerateTree(set, (Tree *)NULL, baseArea);
				

				analyzer.soloTimes.at(tid).at(count).at(0).end = omp_get_wtime();
			}// end of the single part

#pragma omp barrier

			analyzer.parallelTimes.at(tid).at(count).start = omp_get_wtime();

			BarnesHutAttractions(&(subSet.at(tid)), root, ACCURACY);
			NBodysTravel(&(subSet.at(tid)), DELTATIME);
			
			analyzer.parallelTimes.at(tid).at(count).end = omp_get_wtime();
						
#pragma omp barrier // the thread weit here until all threads update his part
			
#pragma omp single
			{
				cout << "Thread " << tid << " update the set. " << endl;
				analyzer.soloTimes.at(tid).at(count).at(1).start = omp_get_wtime();

				set.clear();
				for (int i = 0; i < NUMTHREADS; ++i) {
					set.insert(set.end(), subSet.at(i).begin(), subSet.at(i).end());
				}
				analyzer.soloTimes.at(tid).at(count).at(1).end = omp_get_wtime();
				
			}

			++count;
		} 
		
		analyzer.totalTimes.at(tid).end = omp_get_wtime();
	
		cout << "Thread: " << tid << " have work: " << analyzer.getTotalTime(tid) << " Prcoess particles: " << subSet.at(tid).size() << endl;

	}  /* All threads join master thread and terminate */



	
	/* ending */
	
	printToFile(&set, RESULTFILE);
	rawTableToFile(&analyzer, RESULTFILE);

	if (INPUT){
		cout << "Type any character to close this program " << endl;
		cin.get();
	}
	

	return 0;
}






void getInput(){
	/* get infos from user */
	cout << "Hello Beatch!" << endl;
	cout << "Enter the file name of the input file: " << endl;
	gets(GENERATORFILE);

	cout << "Enter the file name of the output file: " << endl;
	gets(RESULTFILE);

	cout << "Enter the accuracy: 0 is the best, 1 the least " << endl;
	cin >> ACCURACY;
	cin.ignore();

	cout << "Enter the number of threads:" << endl;
	cin >> NUMTHREADS;
	cin.ignore();

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


