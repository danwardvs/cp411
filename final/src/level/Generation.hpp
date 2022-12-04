/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03
 */
#ifndef CGENERATION_HPP
#define CGENERATION_HPP

class Generation {
public:
	int blocksRemaining;	// how many blocks remain in the level (0 = level cleared)
	int currentLevel;		// the current level (used to determine the next level)
	int difficulty;			// the difficulty of the level (affects block health)
	void blockGenerator(int level, int difficulty);

protected:
	int totalBlocks;		// how many blocks will be placed in level
	void layoutGeneration();
	void cleanupLevel();
};

enum BlockPattern {
	NORMAL = 0,
	SPACED,
	COLUMN,
};

#endif
