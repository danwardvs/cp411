#include "Generation.hpp"
#include "../World.hpp"
#include "../Shape.hpp"
#include "../Cube.hpp"
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

BlockPattern pattern = NORMAL;

extern World myWorld;

//generates the blocks and moves them based on the number of blocksPerRow + pattern
void Generation::layoutGeneration() {
	//generate based on certain patterns (need to determine said patterns)
	// ex normal, spaced (space between blocks in row), columns (space between columns of blocks), etc.
	// likely need switch statement to generate based on the pattern
	Shape *obj = NULL;

	blocksRemaining = totalBlocks;

	int blocksToPlace = totalBlocks;
	int rowTranslate = 0;
	int columnTranslate = 0;
	int blockId = 5;
	int perRow = 7;

	//randomly pick pattern
	switch(pattern) {
		case NORMAL:
			while (blocksToPlace > 0) {
				if (blocksToPlace - 7 >= 0) perRow = 7;
				else perRow = blocksToPlace;
				columnTranslate = 0;

				while (perRow > 0) {
					printf("perRow= %d\n", perRow);
					obj = new Cube();
					obj->setId(blockId);
					blockId++;
					obj->setCondition(difficulty);

					//i(x) = column spacing, j(z) = row spacing
					obj->translate(-4.5 + (columnTranslate * 1.5), 0, 5 - (rowTranslate * 1));
					columnTranslate++;
					
					myWorld.objlist.push_back(obj);
					blocksToPlace--;
					perRow--;
				}
				printf("Done row %d \n", rowTranslate);
				rowTranslate++;
			}
			break;
		case SPACED:
			//TODO
			break;
		case COLUMN:
			//TODO
			break;
	}
}

//determines the number of blocks used based on the level
void Generation::blockGeneration(int level, int level_difficulty) {
	/* initialize random seed: */
  	srand (time(NULL));
	int patternSelect = rand() % 3;
	// printf("Pattern selected = %d \n", patternSelect);
	//randomly pick pattern from the 3 options [NORMAL, SPACED, COLUMN]
	pattern = static_cast<BlockPattern>(patternSelect);

	switch(level) {
	case 1:
		if (pattern == NORMAL) totalBlocks = 21;
		// else if (pattern == SPACED) totalBlocks = ?;
		break;
	case 2:
		totalBlocks = 28;
		break;
	case 3:
		totalBlocks = 35;
		break;
	case 4:
		totalBlocks = 42;
		break;
	case 5:
		totalBlocks = 49;
		break;
	}

	//generate the objlist for the blocks
	layoutGeneration();
}