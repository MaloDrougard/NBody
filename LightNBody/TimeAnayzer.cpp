#include "TimeAnalyzer.h"

double TimeAnalyzer::getTotalTime(int tid){
	return (totalTimes.at(tid).end - totalTimes.at(tid).start);
}

double TimeAnalyzer::getSlotParallelTime(int tid, int slot){
	return (parallelTimes.at(tid).at(slot).end - parallelTimes.at(tid).at(slot).start);
}

double TimeAnalyzer::getSlotMeanParallelTime(int slot){
	
	double r = 0;
	for (int i = 0; i < numThreads; ++i)
	{
		r = r + getSlotParallelTime(i,slot);
	}
	r = r / numThreads;
	return r;
}

double TimeAnalyzer::getSlotMaxParallelTime(int slot){
	double r = 0;
	for (int i = 0; i < numThreads; ++i)
	{
		if (r < getSlotParallelTime(i, slot)){
			r = getSlotParallelTime(i, slot);
		}
	}
	return r;
}

double TimeAnalyzer::getSlotMinParallelTime(int slot){
	double r = getSlotParallelTime(0, slot);
	for (int i = 0; i < numThreads; ++i)
	{
		if (r > getSlotParallelTime(i, slot)){
			r = getSlotParallelTime(i, slot);
		}
	}
	return r;
}

void TimeAnalyzer::init(int nT, int nS){
	
	numThreads = nT;
	numSlots = nS;

	totalTimes.resize(numThreads);

	parallelTimes.resize(numThreads);
	for (int i = 0; i < numThreads; ++i){
		parallelTimes.at(i).resize(numSlots);
	}

	soloTimes.resize(numThreads);
	for (int i = 0; i < numThreads; ++i){
		soloTimes.at(i).resize(numSlots);
		for (int j = 0; j < numSlots; ++j){
			soloTimes.at(i).at(j).resize(2);
		}
	}
}

