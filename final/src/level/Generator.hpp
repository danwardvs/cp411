#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "../Shape.hpp"
#include "../Cube.hpp"
#include "../World.hpp"
//#include <stdlib.h>

//using namespace std;

class Generator {
protected:
	int blockNumber;	//how many blocks will be used for the level
	int difficulty;
public:
	void blockGeneration(int level, int level_difficulty);	//
	void layoutGeneration();
};
#endif
