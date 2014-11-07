
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

int timeSummary(time_t start, time_t end, const char * fileName) {
	
	ofstream ofs;
	ofs.open(fileName, std::ofstream::app);

	ofs << "\nPROGRAM START: " << ctime(&start) << endl;
	ofs << "PROGRAM END: " << ctime(&end) << endl;
	ofs << "EXECUTION TIME: " << end - start << endl;

	ofs.close();

	return 1;
}