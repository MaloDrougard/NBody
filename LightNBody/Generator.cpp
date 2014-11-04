#include "Generator.h"
#include "Particle.h"
#include <iostream>
#include <fstream>


#include <vector>

vector<Particle> GenerateSet(const char * fileName, int maxCount)
{

	ifstream ifs;
	ifs.open(fileName, std::ifstream::in);
	vector<Particle> tmp;
	Particle tmpP ;
	double tmpD;
	int count = 0;

	while (ifs.good() && count < maxCount){
		
		tmpP.id = count;
		ifs >> tmpP.mass;
		ifs.get(); // to skip the " "
		ifs >> tmpP.position.at(0);
		ifs.get();
		ifs >> tmpP.position.at(1);
		ifs.get();
		ifs >> tmpD; // to skip the z coordinate
		ifs.get();
		ifs >> tmpP.velocity.at(0);
		ifs.get();
		ifs >> tmpP.velocity.at(1);
		ifs.get();
		ifs >> tmpD; // to skip the z velocity
		
		tmp.push_back(tmpP);

		while (ifs.peek() == '.' || ifs.peek() == '\n' || ifs.peek() == ' ') { // the end can be done with '.',' 'or '\n'
			ifs.get();
		}
		
		++count;
	}


	ifs.close();

	return tmp;

}