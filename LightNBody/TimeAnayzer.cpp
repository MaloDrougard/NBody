#include "TimeAnalyzer.h"

double TimeAnalyzer::getTotalTime(int processNumber){

	return (totalTimes.at(processNumber)[1] - totalTimes.at(processNumber)[0]);
}

void TimeAnalyzer::init(int numThread, int numSlot){
	
	totalTimes.resize(numThread);
	parallelTimes.resize(numThread);
	for (int i = 0; i < numThread; ++i){
		parallelTimes.at(i).resize(numSlot);
	}

}