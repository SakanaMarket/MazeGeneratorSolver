#include <ics46/factory/DynamicFactory.hpp>
#include "SakanaSol.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, SakanaSolvation, "Sakana Solvation (Required)");

SakanaSolvation::SakanaSolvation()
{

}

void SakanaSolvation::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
	mazeSolution.restart();
	new_city_new_followers(maze);
	please_accept_cthulhu(maze, mazeSolution, 0, 0);
}

void SakanaSolvation::new_city_new_followers(const Maze& maze)
{
	// all cells not visited
	// not visited = false
	// visited = true
	int width = maze.getWidth();
	int height = maze.getHeight();
	// make enough room for width
	followers.resize(width);

	// make enough room for height
	for (int ex = 0; ex < width; ++ex)
	{
		followers[ex].resize(height);
	}
	// fill with false
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			followers[x][y] = false;
		}
	}
}

void SakanaSolvation::please_accept_cthulhu(const Maze& maze, MazeSolution& mazeSolution, int x, int y)
{
	std::vector<Direction> whose_door = next_door(maze, mazeSolution, x, y);
	// current cell is visited
	followers[x][y] = true;
	while (whose_door.size() != 0)
	{
		// mix vector once
		auto salad = std::default_random_engine{}; 
		std::shuffle(whose_door.begin(), whose_door.end(), salad);
		
		// random int to choose from vector
		static std::default_random_engine gen;
		std::uniform_int_distribution<int> distribution(0, whose_door.size()-1);
		int i = distribution(gen);
		
		// random element
		Direction this_door = whose_door[i];
		
		// recursion
		// up
		if (this_door == Direction::up)
		{
			if (followers[x][y - 1] == false && maze.wallExists(x, y, this_door) == false)
			{
				// prevents solving other areas after end was reached
				if (mazeSolution.isComplete() == false)
				{
					mazeSolution.extend(this_door);
					please_accept_cthulhu(maze, mazeSolution, x, (y - 1));
				}
			}
		}

		// down
		else if (this_door == Direction::down)
		{
			if (followers[x][y + 1] == false && maze.wallExists(x, y, this_door) == false)
			{
				// prevents solving other areas after end was reached
				if (mazeSolution.isComplete() == false)
				{
					mazeSolution.extend(this_door);
					please_accept_cthulhu(maze, mazeSolution, x, (y + 1));
				}
			}
		}

		// left
		else if (this_door == Direction::left)
		{
			if (followers[x - 1][y] == false && maze.wallExists(x, y, this_door) == false)
			{
				// prevents solving other areas after end was reached
				if (mazeSolution.isComplete() == false)
				{
					mazeSolution.extend(this_door);
					please_accept_cthulhu(maze, mazeSolution, (x - 1), y);
				}
			}
		}

		// right
		else if (this_door == Direction::right)
		{
			if (followers[x + 1][y] == false && maze.wallExists(x, y, this_door) == false)
			{
				// prevents solving other areas after end was reached
				if (mazeSolution.isComplete() == false)
				{
					mazeSolution.extend(this_door);
					please_accept_cthulhu(maze, mazeSolution, (x + 1), y);
				}
			}
		}
		
		
		// base case // backup to original cell
		else
		{
			mazeSolution.backUp();
		}
		
		// needed a second back up
		if (followers[x][y] == true && mazeSolution.isComplete() == false)
		{
			whose_door = next_door(maze, mazeSolution, x, y);
			mazeSolution.backUp();
		}
		
		// prevents solving other areas after end was reach
		else if (mazeSolution.isComplete() == true)
		{
			break;
		}
	}
}

std::vector<Direction> SakanaSolvation::next_door(const Maze& maze, MazeSolution& mazeSolution, int x, int y)
{
	// returns vector a possible of directions
	// only possible if in bound, the next direction has not been visited, AND there is no wall in the next direction
	std::vector<Direction> Solvation;
	int width = maze.getWidth();
	int height = maze.getHeight();

	// if moving up is possible
	if (((y - 1) >= 0) && ((followers[x][y - 1]) == false))
	{
		if (maze.wallExists(x, y, Direction::up) == false)
		{
			Solvation.push_back(Direction::up);
		}
	}

	// if moving down is possible
	if (((y + 1) < height) && ((followers[x][y + 1]) == false))
	{
		if (maze.wallExists(x, y, Direction::down) == false)
		{
			Solvation.push_back(Direction::down);
		}
	}

	// if moving left is possible
	if (((x - 1) >= 0) && ((followers[x - 1][y]) == false))
	{
		if (maze.wallExists(x, y, Direction::left) == false)
		{
			Solvation.push_back(Direction::left);
		}	
	}

	// if moving right is possible
	if (((x + 1) < width) && ((followers[x + 1][y]) == false))
	{
		if (maze.wallExists(x, y, Direction::right) == false)
		{
			Solvation.push_back(Direction::right);
		}
	}

	return Solvation;
}
