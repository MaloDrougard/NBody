#pragma once

#include <vector>


using namespace std;
/*
* This class represent a laps of time 
*/
class TimeBubble{ 
public:
	double start = 0;
	double end = 0;
};

/*
* This class represent a object that permit to analyze the runtime of a code 
* using the omp_get_wtime() to set their composante
*/
class TimeAnalyzer{


public:

	int numSlots;
	int numThreads;

	vector<vector<TimeBubble>>  parallelTimes; // access order: tid, slot
	vector<TimeBubble> totalTimes; // access order: tid
	vector<vector<vector<TimeBubble>>> soloTimes; // access order: tid, slot, part

	void init(int numThread, int numSlot);
	double getTotalTime(int tid);
	double getSlotParallelTime(int tid, int slot);
	double getSlotMeanParallelTime(int slot);
	double getSlotMaxParallelTime(int slot);
	double getSlotMinParallelTime(int slot);

};

