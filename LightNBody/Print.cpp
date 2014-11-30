
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

int timeTable(vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes, const char * fileName)
{
	ofstream ofs;
	ofs.open(fileName, std::ofstream::app);
	ofs << "TIME TABLE:" << endl;
	ofs << "THREAD " << "TOTALTIME " << "PARALLELTIME " << "SOLOTIME " << endl;
	for (int i = 0; i < totalTimes->size(); ++i)
	{
		ofs << i << " " << totalTimes->at(i) << " " << paraTimes->at(i) << " " << soloTimes->at(i) << endl;
	}

	ofs.close();

	return 1;
}

int timeTableToConsole(vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes)
{
	cout << "TIME TABLE:" << endl;
	cout << "THREAD " << "TOTALTIME " << "PARALLELTIME " << "SOLOTIME " << endl;
	for (int i = 0; i < totalTimes->size(); ++i)
	{
		cout << i << " " << totalTimes->at(i) << " " << paraTimes->at(i) << " " << soloTimes->at(i) << endl;
	}
}


int timeSummary(double start, double end, const char * fileName, vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes) {

	ofstream ofs;
	ofs.open(fileName, std::ofstream::app);

	ofs << "TOTAL EXECUTION TIME: " << end - start << endl;
	ofs << "EXECUTION TIME MEANS OF EACH THREAD: " << mean(totalTimes) << endl;
	ofs << "PARALLEL MEAN EXECUTION TIME: " << mean(paraTimes) << endl;
	ofs << "TOTAL OF SEQUANTIAL EXECUTION TIME: " << sum(soloTimes) << endl;
	double dispearTime = mean(totalTimes) - mean(paraTimes) - sum(soloTimes);
	ofs << "DISPEAR TIME: " << dispearTime << endl;

	ofs.close();

	return 1;
}



int timeSummaryToConsole(double start, double end, vector<double> * totalTimes, vector<double> * paraTimes, vector<double> * soloTimes) {
		
	cout << "TOTAL EXECUTION TIME: " << end - start << endl;
	cout << "EXECUTION TIME MEANS OF EACH THREAD: " << mean(totalTimes) << endl;
	cout << "PARALLEL MEAN EXECUTION TIME: " << mean(paraTimes) << endl;
	cout << "TOTAL OF SEQUANTIAL EXECUTION TIME: " << sum(soloTimes) << endl;
	double dispearTime = mean(totalTimes) - mean(paraTimes) - sum(soloTimes);
	cout << "DISPEAR TIME: " << dispearTime << endl;
	
	return 1;
}

double mean(vector<double> * v)
{	
	double r = 0;
	for (int i = 0; i < v->size(); ++i)
	{
		r = r + v->at(i);
	}
	r = r / v->size();
	return r;
}

double sum(vector<double> * v)
{
	double r = 0;
	for (int i = 0; i < v->size(); ++i)
	{
		r = r + v->at(i);
	}
	return r;
}














