#ifndef SAKANAGEN_HPP
#define SAKANAGEN_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>



class SakanaGenesis : public MazeGenerator
{
public:
	SakanaGenesis();
	virtual void generateMaze(Maze& maze);
	void no_knocked_doors(Maze& maze);
	void would_you_like_to_hear_about_our_lord_and_savior_cthulhu(Maze& maze, int x, int y);
	std::vector<Direction> whose_day_do_i_ruin(Maze& maze, int x, int y);
private:
	std::vector<std::vector<bool>> knocked;
};

#endif