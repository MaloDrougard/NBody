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
double ACCURACY = 0.5;
int NUMTHREADS = 32;	
Area baseArea( -50, 50, -50 , 50); 

int main()
{	
	double startTime;
	double endTime;
	vector<Particle>  set;
	vector<Particle> * rest;
	
	Tree * root;

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
	

	/* initialization */
	rest = new vector<Particle>(0);
	set = GenerateSet(GENERATORFILE, COUNTPARTICLE);
	initFileBarnesHut(RESULTFILE, NUMTHREADS, set.size() , NUMSLOT, DELTATIME, ACCURACY);
	printToFile(&set, RESULTFILE);
			
	int count = 0;
	 
	/* core of the program */
	startTime = omp_get_wtime();
	cout << "Program start at: " << startTime << endl;
	startTime = omp_get_wtime();



	/* preparing the parallel section */
	int subSetSize = set.size() / NUMTHREADS;
	vector<vector<Particle>> subSet;
	vector<Particle>::iterator it = set.begin();
	for (int i = 0; i < NUMTHREADS - 1; ++i) {
		vector<Particle> temp(it, it + subSetSize);
		subSet.push_back(temp);
		it = it + subSetSize;
	}
	vector<Particle> last(it, set.end()); //it's possible that the numthread is not a divisor of the set.size
	subSet.push_back(last);

	vector<double>  parallelTimes;
	vector<double> soloTimes;
	vector<double> totalTimes;
	for (int i = 0; i < NUMTHREADS; ++i)
	{
		parallelTimes.push_back(0);
		totalTimes.push_back(0);
		soloTimes.push_back(0);
	}

	int tid;
	double threadStartTime;
	double threadEndTime;
	double threadStartParaTime;
	double threadEndParaTime;
	double singleThreadStartTime;
	double singleThreadEndTime;

#pragma omp parallel private(tid, count, threadStartTime, threadEndTime) shared(set, root) num_threads(NUMTHREADS)
	{
		tid = omp_get_thread_num();
		cout << "Thread: " << tid << "  Start!" << endl;
		count = 0;
		threadStartTime = omp_get_wtime();

		//Core of the software
		while (count < NUMSLOT){
#pragma omp single
			{	
				cout << "Thread " << tid << " generate the tree."  ;
				singleThreadStartTime = omp_get_wtime();
				root = GenerateTree(set, (Tree *)NULL, baseArea);
				singleThreadEndTime = omp_get_wtime();
				soloTimes.at(tid) = soloTimes.at(tid) + (singleThreadEndTime - singleThreadStartTime);
				cout << "That take " << singleThreadEndTime - singleThreadStartTime << endl;
			}// end of the single part
			
			threadStartParaTime = omp_get_wtime();

			BarnesHutAttractions(&(subSet.at(tid)), root, ACCURACY);
			NBodysTravel(&(subSet.at(tid)), DELTATIME);
			++count;
			
			threadEndParaTime = omp_get_wtime();
			parallelTimes.at(tid) = parallelTimes.at(tid) + (threadEndParaTime - threadStartParaTime);
#pragma omp barrier // the thread have all update her part
#pragma omp single
			{
				cout << "Thread " << tid << " update the set.";
				singleThreadStartTime = omp_get_wtime();
				set.clear();
				for (int i = 0; i < NUMTHREADS; ++i) {
					set.insert(set.end(), subSet.at(i).begin(), subSet.at(i).end());
				}
				singleThreadEndTime = omp_get_wtime();
				soloTimes.at(tid) = soloTimes.at(tid) + (singleThreadEndTime - singleThreadStartTime);
				cout << "That take " << singleThreadEndTime - singleThreadStartTime << endl;
			}
		} 
		threadEndTime = omp_get_wtime();
		totalTimes.at(tid) = threadEndTime - threadStartTime;
		cout << "Thread: " << tid << " have work: " << threadEndTime - threadStartTime << " Prcoess particles: " << subSet.at(tid).size() << endl;

	}  /* All threads join master thread and terminate */



	
	/* ending */
	endTime = omp_get_wtime();

	printToFile(&set, RESULTFILE);
	timeTable(&totalTimes, &parallelTimes, &soloTimes, RESULTFILE);
	timeSummary(startTime, endTime, RESULTFILE, &totalTimes, &parallelTimes, &soloTimes);
	

	timeSummaryToConsole(startTime, endTime, &totalTimes, &parallelTimes, &soloTimes);
	timeTableToConsole(&totalTimes, &parallelTimes, &soloTimes);
	cout << "Type any character to close this program "  << endl;
	cin.get();

	return 0;
}

