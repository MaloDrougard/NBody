
#include <iomanip>
#include "Print.h"



int printToFile(vector<Particle> * pSet, const char * fileName) {

	ofstream ofs;
	ofs.open(fileName, std::ofstream::app);

	ofs << "NEW_SLOT\n" ;

	vector<Particle>::iterator it = pSet->begin();

	while (it != pSet->end()){
		ofs << it->id << ": " << it->mass << " ";
		ofs << it->position.at(0) << " " << it->position.at(1) << " " << 0 << " ";
		ofs << it->velocity.at(0) << " " << it->velocity.at(1) << " " << 0 << " ";
		ofs << it->acceleration.at(0) << " " << it->acceleration.at(1) << " " << 0 << " " << "\n";
		++it;
 	}

	ofs.close();
	return 0;
}


int initFile(const char * fileName, int numberParticles, int numberSlots, double deltaTime){

	ofstream ofs;
	ofs.open(fileName, std::ofstream::out);
	ofs << "NUMBER_OF_PARTICLE: " << numberParticles << "  ";
	ofs << "NUMBER_OF_SLOT: " << numberSlots << "  ";
	ofs << "DELTA_TIME: " << deltaTime << endl;
	ofs.close();

	return 1;
}


int initFileBarnesHut(const char * fileName, int numThreads, int numberParticles, int numberSlots, double deltaTime, double accuracy){

	ofstream ofs;
	ofs.open(fileName, std::ofstream::out);
	ofs << "METHOD: BarnesHutMultiThreads ";
	ofs << "NUMBER_OF_THREADS: " << numThreads << endl;
	ofs << "NUMBER_OF_PARTICLE: " << numberParticles << "  ";
	ofs << "NUMBER_OF_SLOT: " << numberSlots << "  ";
	ofs << "DELTA_TIME: " << deltaTime << " " ;
	ofs << "ACCURACY: " << accuracy << endl;
	ofs.close();

	return 1;
}



int timeTableToStream(TimeAnalyzer * analyzer, ostream  &stream){
	stream << "TABLE: PARALLELTIME FOR EACH SLOT" << endl;
	stream << setw(6) << "THREAD ";

	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << setw(6) << "S" << i;
	}
	stream << endl;

	for (int i = 0; i < analyzer->numThreads; ++i){
		stream << setw(6) << i;
		for (int j = 0; j < analyzer->numSlots; ++j) {
			stream << fixed << setw(8) << setprecision(5) << analyzer->getSlotParallelTime(i, j);
		}
		stream << endl;
	}

	stream << setw(6) << "means";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << setw(8) << setprecision(5) << analyzer->getSlotMeanParallelTime(i);
	}
	stream << endl;

	stream << setw(6) << "max";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << setw(8) << setprecision(5) << analyzer->getSlotMaxParallelTime(i);
	}
	stream << endl;

	stream << setw(6) << "min";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << setw(8) << setprecision(5) << analyzer->getSlotMinParallelTime(i);
	}
	stream << endl;

	return 1;
}

int timeTableToConsole(TimeAnalyzer * analyzer){
	
	return timeTableToStream(analyzer, std::cout);

}

int timeTable(TimeAnalyzer * analyzer, const char * fileName)
{
	ofstream ofs;
	ofs.open(fileName, std::ofstream::app);
	
	int r = timeTableToStream(analyzer, ofs);

	ofs.close();

	return r;
}



int timeSummary(double start, double end, const char * fileName, vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes) {

	ofstream ofs;
	ofs.open(fileName, std::ofstream::app);

	ofs << "TOTAL EXECUTION TIME: " << end - start << endl;
	ofs << "EXECUTION TIME MEANS OF EACH THREAD: "  << endl;
	ofs << "PARALLEL MEAN EXECUTION TIME: "<< endl;
	ofs << "TOTAL OF SEQUANTIAL EXECUTION TIME: "  << endl;
	double dispearTime = 0;
	ofs << "DISPEAR TIME: " << dispearTime << endl;

	ofs.close();

	return 1;
}



int timeSummaryToConsole(double start, double end, vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes) {
	
	return 1;
}

int rawTableToFile(TimeAnalyzer * analyzer, const char * fileName){
	ofstream ofs;
	ofs.open(fileName, std::ofstream::app);
	int r = rawTableToStream(analyzer, ofs);
	ofs.close();

	return r;

}

int rawTableToStream(TimeAnalyzer * analyzer, ostream &stream){
	
	stream << fixed;
	stream << setprecision(16);
	stream << "TOTALTIME_TABLE_START:" << endl;
	stream <<  "THREAD START" << endl;;
	for (int i = 0; i < analyzer->totalTimes.size(); ++i){
		stream << i << " " << analyzer->totalTimes.at(i).start << endl;
	}

	stream << endl;
	
	stream << "TOTALTIME_TABLE_END:" << endl;
	stream << "THREAD END" << endl;;
	for (int i = 0; i < analyzer->totalTimes.size(); ++i){
		stream << i << " " << analyzer->totalTimes.at(i).end << endl;
	}

	stream << endl; 

	stream << "PARALLELTIME_START:" << endl;
	stream << "THREAD ";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << "S" << i << " ";
	}
	stream << endl;
	for (int i = 0; i < analyzer->numThreads; ++i){
		stream << i << " ";
		for (int j = 0; j < analyzer->numSlots; ++j){
			stream << analyzer->parallelTimes.at(i).at(j).start << " ";
		}
		stream << endl;
	}
	
	stream << endl;

	stream << "PARALLELTIME_END:" << endl;
	stream << "THREAD ";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << "S" << i << " ";
	}
	stream << endl;
	for (int i = 0; i < analyzer->numThreads; ++i){
		stream << i << " ";
		for (int j = 0; j < analyzer->numSlots; ++j){
			stream << analyzer->parallelTimes.at(i).at(j).end << " ";
		}
		stream << endl;
	}

	stream << endl;

	stream << "SOLOTIME_START_PART1:" << endl;
	stream << "THREAD ";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << "S" << i << " ";
	}
	stream << endl;
	for (int i = 0; i < analyzer->numThreads; ++i){
		stream << i << " ";
		for (int j = 0; j < analyzer->numSlots; ++j){
			stream << analyzer->soloTimes.at(i).at(j).at(0).start << " ";
		}
		stream << endl;
	}

	stream << endl;

	stream << "SOLOTIME_END_PART1:" << endl;
	stream << "THREAD ";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << "S" << i << " ";
	}
	stream << endl;
	for (int i = 0; i < analyzer->numThreads; ++i){
		stream << i << " ";
		for (int j = 0; j < analyzer->numSlots; ++j){
			stream << analyzer->soloTimes.at(i).at(j).at(0).end << " ";
		}
		stream << endl;
	}

	stream << endl;

	stream << "SOLOTIME_START_PART2:" << endl;
	stream << "THREAD ";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << "S" << i << " ";
	}
	stream << endl;
	for (int i = 0; i < analyzer->numThreads; ++i){
		stream << i << " ";
		for (int j = 0; j < analyzer->numSlots; ++j){
			stream << analyzer->soloTimes.at(i).at(j).at(1).start << " ";
		}
		stream << endl;
	}

	stream << endl;

	stream << "SOLOTIME_END_PART2:" << endl;
	stream << "THREAD ";
	for (int i = 0; i < analyzer->numSlots; ++i){
		stream << "S" << i << " ";
	}
	stream << endl;
	for (int i = 0; i < analyzer->numThreads; ++i){
		stream << i << " ";
		for (int j = 0; j < analyzer->numSlots; ++j){
			stream << analyzer->soloTimes.at(i).at(j).at(1).end << " ";
		}
		stream << endl;
	}

	stream << endl;

	return 1;



}














