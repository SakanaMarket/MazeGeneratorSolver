#ifndef SAKANASAL_HPP
#define SAKANASAL_HPP

#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

class SakanaSolvation : public MazeSolver
{
public:
	SakanaSolvation();
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	void new_city_new_followers(const Maze& maze);
	void please_accept_cthulhu(const Maze& maze, MazeSolution& mazeSolution, int x, int y);
	std::vector<Direction> next_door(const Maze& maze, MazeSolution& mazeSolution, int x, int y);
private:
	std::vector<std::vector<bool>> followers;
};

#endif