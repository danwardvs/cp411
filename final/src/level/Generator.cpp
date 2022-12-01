#include "../Shape.hpp"
#include "../Cube.hpp"
#include "../World.hpp"
#include "Generator.hpp"

int blockNumber;
int difficulty;
extern World myWorld;

//determines the positions of the blocks based on the number required
void layoutGeneration() {
	//generate based on certain patterns?
	Shape *obj = NULL;
	for (int i = 0; i < blockNumber; i++) {
		obj = new Cube();
		obj->setId(5 + i);
		obj->setCondition(difficulty);
		//keep adding to row until row is full
		obj->translate(0, 0, i);
		myWorld.objlist.push_back(obj);
	}
}

//determines the number of blocks used based on the level
void blockGeneration(int level, int level_difficulty) {
	difficulty = level_difficulty;
	switch(level) {
	case 1:
		blockNumber = 25;
		break;
	case 2:
		blockNumber = 30;
		break;
	}

	//generate the objlist for the blocks
	layoutGeneration();
}


