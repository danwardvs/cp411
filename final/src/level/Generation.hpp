#ifndef CGENERATION_HPP
#define CGENERATION_HPP

class Generation {
public:
	int blocksRemaining;	// how many blocks remain in the level (0 = level cleared)
	int currentLevel;		// the current level (used to determine the next level)
	int currentDifficulty;			// the difficulty of the level (affects block health)
	void blockGenerator(int level, int difficulty, bool randomLevel);	//starts level generation by picking a pattern (if requested) then setting the number of blocks based on the level

protected:
	int totalBlocks;			// how many blocks will be placed in level
	bool shouldRandomize;
	void layoutGeneration();	// generates the level by placing blocks in the world
	void cleanupLevel();		// cleans up the level by reseting the world
};

enum BlockPattern {
	NORMAL = 0,
	SPACED,
	COLUMN,
};

#endif
