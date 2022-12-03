/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03
 */
#ifndef GENERATION_HPP
#define GENERATION_HPP

class Generation {
public:
	int totalBlocks;
	int difficulty;
	int blocksRemaining;
	void blockGeneration(int level, int difficulty);
	void layoutGeneration();
};

//possible move to another header?
enum BlockPattern {
	NORMAL = 0,
	SPACED,
	COLUMN,
};

#endif
