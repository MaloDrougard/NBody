#pragma once

#include <vector>


using namespace std;

class TimeAnalyzer{
public:

	vector<vector<double[2]>>  parallelTimes;
	vector<vector<double[2]>> soloTimes;

	vector<double[2]> totalTimes;

	void init(int numThread, int numSlot);

	double getTotalTime(int processNumber);

};