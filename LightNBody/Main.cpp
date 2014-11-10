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
	time(&startTime);
	cout << "Program start at: " << ctime(&startTime) << endl;
	time(&startTime);



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

	int tid;
	time_t threadTime;


#pragma omp parallel private(tid, count, threadTime) shared(set, root) num_threads(NUMTHREADS)
	{
		tid = omp_get_thread_num();



	
		time(&threadTime);
		cout << "Thread: " << tid << "  Start at:" << ctime(&threadTime) << endl;
		count = 0;

		/*
		* Here start the core of the software
		*/
		while (count < NUMSLOT){
#pragma omp single
			{
				root = GenerateTree(set, (Tree *)NULL, baseArea);
			}

			BarnesHutAttractions(&(subSet.at(tid)), root, ACCURACY);
			NBodysTravel(&(subSet.at(tid)), DELTATIME);
			++count;

#pragma omp barrier // the thread have all update her part
#pragma omp single
			{
				set.clear();
				for (int i = 0; i < NUMTHREADS; ++i) {
					set.insert(set.end(), subSet.at(i).begin(), subSet.at(i).end());
				}
			}
		} 
		/*
		* Here end the core of the software
		*/

		time(&threadTime);
		cout << "Thread: " << tid << "  End at:" << ctime(&threadTime) << "Prcoess particles: " << subSet.at(tid).size() << endl;

	}  /* All threads join master thread and terminate */



	
	/* ending */
	time(&endTime);

	printToFile(&set, RESULTFILE);
	timeSummary(startTime, endTime, RESULTFILE);

	cout << "Execution time: " << endTime - startTime << endl;
	cout << "Type any character to close this program "  << endl;
	cin.get();

	return 0;
}

