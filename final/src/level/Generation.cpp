#include "Generation.hpp"
#include "../World.hpp"
#include "../Shape.hpp"
#include "../Cube.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

BlockPattern pattern = NORMAL; /* pattern for level generation */

extern World myWorld;
extern CullMode cullMode;       /* culling option */
extern RenderMode renderMode;  /* shade option  */
extern bool ballCanMove;

//generates the blocks for the level
void Generation::layoutGeneration() {
	Shape *obj = NULL;
	blocksRemaining = totalBlocks; //update to indicate new level

	int blocksToPlace = totalBlocks; //keeps track of how many blocks can still be placed
    int blockId = 5;	//id's of the blocks in the objlist

	int rowTranslate = 0;		// how much the block should translate on the horizontal level
	int columnTranslate = 0;	// how much the block should translate on the vertical level
	int blocksPerRow = 0;		// how many blocks to place in the row
    int numColumns = 0;	// how many blocks can be placed in

	//place blocks based on pattern
	switch(pattern) {
		case NORMAL:
			while (blocksToPlace > 0) {
				//determine how many blocks can be put in the row
				if (blocksToPlace - 7 >= 0) blocksPerRow = 7;
				else blocksPerRow = blocksToPlace;
				columnTranslate = 0;

				//place all blocks for that row
				while (blocksPerRow > 0) {
					obj = new Cube(); //create new block (aka cube)
					obj->setId(blockId);
					obj->setCondition(currentDifficulty); //set the condition for the block (durability)
					blockId++;

					//move the block to the required position (x= column spacing, z= row spacing)
					obj->translate(-4.5 + (columnTranslate * 1.5), 0, 5 - (rowTranslate * 1));
					columnTranslate++;	// next block need to be moved to the right
					
					myWorld.objlist.push_back(obj);	// add block to objlist
					blocksToPlace--;
					blocksPerRow--;
				}
				rowTranslate++; // next row
			}
			break;
		case SPACED:
			while (blocksToPlace > 0) {
				//determine how many blocks can be put in the row
                if (blocksToPlace - 4 >= 0) blocksPerRow = 4;
                else blocksPerRow = blocksToPlace;
                columnTranslate = 0;
				
				//place all blocks for that row
                while (blocksPerRow > 0) {
                    obj = new Cube();
                    obj->setId(blockId);
                    obj->setCondition(currentDifficulty); //set the condition for the block (durability)
					blockId++;

                    //move the block to the required position (x= column spacing, z= row spacing)
                    obj->translate(-4.5 + (columnTranslate * 3), 0, 5 - (rowTranslate * 1.2));
                    columnTranslate++; // next block need to be moved to the right
                    
                    myWorld.objlist.push_back(obj); // add block to objlist
                    blocksToPlace--;
                    blocksPerRow--;
                }
                rowTranslate++;
			}
			break;
		case COLUMN:
            //determine how many blocks can be in each column
            if (blocksToPlace / 8 >= 4) {
				blocksPerRow = 4;
				numColumns = 4;
			}
            else if (blocksToPlace / 8 >= 2) {
				blocksPerRow = 3;
				numColumns = 3;
				}
            else {
				blocksPerRow = 2;
				numColumns = 2;
			}

			while (blocksToPlace > 0) {
				//determine how many blocks can be put in the row
				if (blocksToPlace - numColumns >= 0) blocksPerRow = numColumns;
				else blocksPerRow = blocksToPlace;
				columnTranslate = 0;

				//place all blocks for that row
				while (blocksPerRow > 0) {
					obj = new Cube();
					obj->setId(blockId);
					obj->setCondition(currentDifficulty);
					blockId++;

                    //move the block to the required position (based on how many columns there are) 
					//(x= column spacing, z= row spacing)
                    switch (numColumns) {
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
					columnTranslate++; // next block need to be moved to the right
					
					myWorld.objlist.push_back(obj); // add block to objlist
					blocksToPlace--;
					blocksPerRow--;
				}
				rowTranslate++;
			}
			break;
	}
	ballCanMove = true; //allow the ball to move now that level is generated
}

//determines the number of blocks used based on the level
void Generation::blockGenerator(int level, int difficulty, bool randomLevel) {
	currentLevel = level;
    currentDifficulty = difficulty;
	shouldRandomize = randomLevel;

	//only randomize block pattern if previous level was beat (if reset do not change)
  	if (shouldRandomize == true) {
		srand (time(NULL)); // initialize random seed
		int patternSelect = rand() % 3; //pick random int between 0 and 2

		// randomly pick pattern from the 3 options [NORMAL, SPACED, COLUMN]
		pattern = static_cast<BlockPattern>(patternSelect);
	}
    pattern = COLUMN; //for testing each shape ONLY- remove when eveything looks good.

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glDisable(GL_BACK);

    //assign the number of blocks based on level + pattern
	switch(level) {
		case 1:
			renderMode = SMOOTH;
			cullMode = GLCULL;
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
		
			//set the number of blocks based on the pattern
			if (pattern == NORMAL) totalBlocks = 21;
			else if (pattern == SPACED) totalBlocks = 8;
			else totalBlocks = 8;
			break;
		case 2:
			renderMode=WIRE;
			cullMode = NONE;

			//set the number of blocks based on the pattern
			if (pattern == NORMAL) totalBlocks = 28;
			else if (pattern == SPACED) totalBlocks = 12;
			else totalBlocks = 18;
			break;
		case 3:
			renderMode = CONSTANT;
			cullMode = GLCULL;
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			
			//set the number of blocks based on the pattern
			if (pattern == NORMAL) totalBlocks = 35;
			else if (pattern == SPACED) totalBlocks = 16;
			else totalBlocks = 24;
			break;
		case 4:
			renderMode=WIRE;
			cullMode = NONE;

			//set the number of blocks based on the pattern
			if (pattern == NORMAL) totalBlocks = 42;
			else if (pattern == SPACED) totalBlocks = 20;
			else totalBlocks = 32;
			break;
		case 5:
			renderMode = CONSTANT;
			cullMode = GLCULL;
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			
			//set the number of blocks based on the pattern
			if (pattern == NORMAL) totalBlocks = 49;
			else if (pattern == SPACED) totalBlocks = 24;
			else totalBlocks = 40;
			break;
		}

	//fill the world with blocks
	layoutGeneration();
}
