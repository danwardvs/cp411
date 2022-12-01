//#include "../Shape.hpp"
#include "Generator.hpp"
#include "../World.hpp"
#include <iostream>
#include <list>
//#include <stdlib.h>
#include "Level.hpp"

extern World myWorld;

Generator generator;

void levelLayout(int level_number, int level_difficulty) {
	//pick range of blocks based on level
	generator.blockGeneration(level_number, level_difficulty);
}
