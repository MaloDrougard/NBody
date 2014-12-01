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
double ACCURACY = 0.5;
int NUMTHREADS = 32;	
Area baseArea( -50, 50, -50 , 50); 

int main()
{	
	
	vector<Particle>  set;
	vector<Particle> * rest;

	Tree * root;
	TimeAnalyzer analyzer;

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
	analyzer.init(NUMTHREADS, NUMSLOT);
	int count = 0;
	 
	
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


	/* core of the program */

	cout << "Program start: " << endl;

	/* the private variable for the parallel section*/
	int tid = 0;

#pragma omp parallel private(tid, count, threadStartTime, threadEndTime) shared(set, root, analyzer) num_threads(NUMTHREADS)
	{
		tid = omp_get_thread_num();
		cout << "Thread: " << tid << "  Start!" << endl;
		count = 0;
		analyzer.totalTimes.at(tid)[0] = omp_get_wtime();

		//Core of the software
		while (count < NUMSLOT){
#pragma omp single
			{	
				cout << "Thread " << tid << " generate the tree. "  ;
				analyzer.soloTimes.at(tid).at(count)[0] = omp_get_wtime();
				root = GenerateTree(set, (Tree *)NULL, baseArea);
			}// end of the single part

#pragma omp barrier

			analyzer.parallelTimes.at(tid).at(count)[0] = omp_get_wtime();

			BarnesHutAttractions(&(subSet.at(tid)), root, ACCURACY);
			NBodysTravel(&(subSet.at(tid)), DELTATIME);
			++count;
			
			analyzer.parallelTimes.at(tid).at(count)[1] = omp_get_wtime();
			
#pragma omp barrier // the thread weit here until all threads update his part

#pragma omp single
			{
				cout << "Thread " << tid << " update the set. ";
				
				set.clear();
				for (int i = 0; i < NUMTHREADS; ++i) {
					set.insert(set.end(), subSet.at(i).begin(), subSet.at(i).end());
				}
				
			}
		} 
		
		analyzer.totalTimes.at(tid)[1]= omp_get_wtime();
	
		cout << "Thread: " << tid << " have work: " << analyzer.getTotalTime(tid) << " Prcoess particles: " << subSet.at(tid).size() << endl;

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

