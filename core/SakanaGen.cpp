#include <ics46/factory/DynamicFactory.hpp>
#include "SakanaGen.hpp"
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, SakanaGenesis, "Sakana Genesis (Required)");

SakanaGenesis::SakanaGenesis()
{

}

void SakanaGenesis::generateMaze(Maze& maze)
{
	maze.removeAllWalls();
	maze.addAllWalls();
	no_knocked_doors(maze);
	would_you_like_to_hear_about_our_lord_and_savior_cthulhu(maze, 0, 0);
}

void SakanaGenesis::no_knocked_doors(Maze& maze)
{
	// all cells not visited
	// not visited = false
	// visited = true
	int width = maze.getWidth();
	int height = maze.getHeight();
	
	// make enough room for width
	knocked.resize(width);
	
	// make enough room for height
	for (int ex = 0; ex < width; ++ex)
	{
		knocked[ex].resize(height);
	}

	// fill with false
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			knocked[x][y] = false;
		}
	}
}

void SakanaGenesis::would_you_like_to_hear_about_our_lord_and_savior_cthulhu(Maze& maze, int x, int y)
{
	// Finds a direction to go in
	std::vector<Direction> doors = whose_day_do_i_ruin(maze, x, y);
	knocked[x][y] = true;

	while (doors.size() != 0)
	{
		// mix vector once
		auto mix = std::default_random_engine{}; 
		std::shuffle(doors.begin(), doors.end(), mix);
		
		// random int to choose from vector
		static std::default_random_engine gen;
		std::uniform_int_distribution<int> distribution(0, doors.size()-1);
		int i = distribution(gen);

		// random element
		Direction this_door = doors[i];

		// recursion to break wall ONLY if next direction has not been visited AND there exists a wall in the next direction
		// up
		if (this_door == Direction::up)
		{
			if (knocked[x][y - 1] == false && maze.wallExists(x, (y - 1), this_door) == true)
			{
				maze.removeWall(x, y, this_door);
				would_you_like_to_hear_about_our_lord_and_savior_cthulhu(maze, x, (y - 1));
			}
		}
		// down
		if (this_door == Direction::down)
		{
			if (knocked[x][y + 1] == false && maze.wallExists(x, (y + 1), this_door) == true)
			{
				maze.removeWall(x, y, this_door);
				would_you_like_to_hear_about_our_lord_and_savior_cthulhu(maze, x, (y + 1));
			}
		}
		// left
		if (this_door == Direction::left)
		{
			if (knocked[x - 1][y] == false && maze.wallExists((x - 1), y, this_door) == true)
			{
				maze.removeWall(x, y, this_door);
				would_you_like_to_hear_about_our_lord_and_savior_cthulhu(maze, (x - 1), y);
			}
		}
		// right
		if (this_door == Direction::right)
		{
			if (knocked[x + 1][y] == false && maze.wallExists((x + 1), y, this_door) == true)
			{
				maze.removeWall(x, y, this_door);
				would_you_like_to_hear_about_our_lord_and_savior_cthulhu(maze, (x + 1), y);
			}
		}
		// base case // recreates the vector of direction of original cell to run through the while loop again
		// visited cells already marked
		doors = whose_day_do_i_ruin(maze, x, y);

	}
}

std::vector<Direction> SakanaGenesis::whose_day_do_i_ruin(Maze& maze, int x, int y)
{
	// Creates vector of direction ONLY if in bounds AND next direction has NOT been visited
	std::vector<Direction> is_you;
	int width = maze.getWidth();
	int height = maze.getHeight();

	//if moving up is possible
	if (((y - 1) >= 0) && (knocked[x][y - 1] == false))
	{
		is_you.push_back(Direction::up);
	}

	//if moving down is possible
	if (((y + 1) < height) && (knocked[x][y + 1] == false))
	{
		is_you.push_back(Direction::down);
	}

	//if moving left is possible
	if (((x - 1) >= 0) && (knocked[x - 1][y] == false))
	{
		is_you.push_back(Direction::left);
	}

	//if moving right is possible
	if (((x+1) < width) && (knocked[x + 1][y] == false))
	{
		is_you.push_back(Direction::right);
	}

	return is_you;
}