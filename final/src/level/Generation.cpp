#include "Generation.hpp"
#include "../World.hpp"
#include "../Shape.hpp"
#include "../Cube.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

BlockPattern pattern = NORMAL;

extern World myWorld;

//generates the blocks and moves them based on the number of blocksPerRow + pattern
void Generation::layoutGeneration() {
	Shape *obj = NULL;
	blocksRemaining = totalBlocks; //update to indicate new level

	int blocksToPlace = totalBlocks; //keeps track of how many blocks can still be placed
    int blockId = 5;	//id's of the blocks in the objlist

	//need to re-design this to it reads but also works better (very messy currently)
	// To place the blocks I need to determine how many can fit in a row (7 is the max for normal, ? is max for spaced, 4 columns are max for column).
	// To determine how many rows are possible I need to device the totalBLocks by a number based on the pattern (7 for Normal, ? for spaced, this is column based instead of row).
	// For column I can likley use same formula's but reverse for column instead of row.

	int rowTranslate;
	int columnTranslate;
	int blocksPerRow;
    int blocksPerColumn;

	//place blocks based on pattern
	switch(pattern) {
		case NORMAL:
			while (blocksToPlace > 0) {
				//set the number of blocks to be placed per row
				if (blocksToPlace - 7 >= 0) blocksPerRow = 7;
				else blocksPerRow = blocksToPlace;
				columnTranslate = 0;

				//place all blocks for that row
				while (blocksPerRow > 0) {
					printf("perRow= %d\n", blocksPerRow);
					obj = new Cube(); //create new block (aka cube)
					obj->setId(blockId);
					obj->setCondition(difficulty); //set the condition for the block (durability)
					blockId++;

					//move the block to the required position (x= column spacing, z= row spacing)
					obj->translate(-4.5 + (columnTranslate * 1.5), 0, 5 - (rowTranslate * 1));
					columnTranslate++;	// next block need to be moved to the right
					
					myWorld.objlist.push_back(obj);	// add block to objlist
					blocksToPlace--;
					blocksPerRow--;
				}
				printf("Done row %d \n", rowTranslate);
				rowTranslate++; // next row
			}
			break;
		case SPACED:
			while (blocksToPlace > 0) {
                if (blocksToPlace - 4 >= 0) blocksPerRow = 4;
                else blocksPerRow = blocksToPlace;
                columnTranslate = 0;

                while (blocksPerRow > 0) {
                    printf("perRow= %d\n", blocksPerRow);
                    obj = new Cube();
                    obj->setId(blockId);
                    obj->setCondition(difficulty);
					blockId++;

                    //x= column spacing, z= row spacing
                    obj->translate(-4.5 + (columnTranslate * 3), 0, 5 - (rowTranslate * 1.2));
                    columnTranslate++;
                    
                    myWorld.objlist.push_back(obj);
                    blocksToPlace--;
                    blocksPerRow--;
                }
                printf("Done row %d \n", rowTranslate);
                rowTranslate++;
			}
			break;
		case COLUMN:
            //determine how many columns can be placed
            if (blocksToPlace / 8 == 5) {
				blocksPerRow = 4;
				blocksPerColumn = 4;
			}
            else if (blocksToPlace / 8 >= 2) {
				blocksPerRow = 3;
				blocksPerColumn = 3;
				}
            else {
				blocksPerRow = 2;
				blocksPerColumn = 2;
			}

            printf("blocksPerColumn= %d \n", blocksPerColumn);

			while (blocksToPlace > 0) {
				if (blocksToPlace - blocksPerColumn >= 0) blocksPerRow = blocksPerColumn;
				else blocksPerRow = blocksToPlace;
				columnTranslate = 0;

				while (blocksPerRow > 0) {
                    printf("perRow= %d\n", blocksPerRow);
					obj = new Cube();
					obj->setId(blockId);
					obj->setCondition(difficulty);
					blockId++;

                    //x= column spacing, z= row spacing
                    switch (blocksPerColumn) {
                    case 4: //4 block columns
                        obj->translate(-3.5 + (columnTranslate * 2.5), 0, 5 - (rowTranslate * 0.8));
                        break;
                    case 3: // 3 block columns
                        obj->translate(-3.5 + (columnTranslate * 3), 0, 5 - (rowTranslate * 1));
                        break;
                    case 2: // 2 block columns
                        obj->translate(-2.5 + (columnTranslate * 3.5), 0, 5 - (rowTranslate * 1.5));
                        break;
                    }
					columnTranslate++;
					
					myWorld.objlist.push_back(obj);
					blocksToPlace--;
					blocksPerRow--;
				}
				printf("Done row %d \n", rowTranslate);
				rowTranslate++;
			}
			break;
	}
}

//determines the number of blocks used based on the level
void Generation::blockGenerator(int level, int levelDifficulty) {
    difficulty = levelDifficulty;

  	srand (time(NULL)); // initialize random seed
	int patternSelect = rand() % 3; //pick random int between 0 and 2

	//randomly pick pattern from the 3 options [NORMAL, SPACED, COLUMN]
	// pattern = static_cast<BlockPattern>(patternSelect);
    pattern = COLUMN; //for testing each shape ONLY- remove when eveything looks good.
    
    //assign the number of blocks based on level + pattern
	switch(level) {
	case 1:
		if (pattern == NORMAL) totalBlocks = 21;
		else if (pattern == SPACED) totalBlocks = 8;
         else totalBlocks = 8;
		break;
	case 2:
		if (pattern == NORMAL) totalBlocks = 28;
        else if (pattern == SPACED) totalBlocks = 12;
        else totalBlocks = 16;
		break;
	case 3:
		if (pattern == NORMAL) totalBlocks = 35;
        else if (pattern == SPACED) totalBlocks = 16;
        else totalBlocks = 24;
		break;
	case 4:
		if (pattern == NORMAL) totalBlocks = 42;
        else if (pattern == SPACED) totalBlocks = 20;
        else totalBlocks = 32;
		break;
	case 5:
		if (pattern == NORMAL) totalBlocks = 49;
        else if (pattern == SPACED) totalBlocks = 24;
        else totalBlocks = 40;
		break;
	}

	//fill the world's objlist with blocks
	layoutGeneration();
}