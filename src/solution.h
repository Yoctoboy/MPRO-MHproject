#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;

//Solution class : a grid (1 if captor, 0 else) with a given size and a cover.
class solution {
public:
	//grid
	vector<vector<bool> > grid;
	//size of the grid
	int size;
	//cover : how many captors cover each vertex of the grid
	vector<vector<int> > cover;

	//constructor
	solution(int);
	//find all transformations given a certain radius
	vector<vector<int> > neighbour_transf(int);
	//Get the neighbour given a certain transformation and a position
	solution getNeighbour(vector<int>);
	//update the cover by calculating for each captor how far it reaches
	void updateCover(int);
	//Finding if there is a path between (0,0) and every captor, return the number of uncovered captors
	int pathfinding(int);
	//recursive function for path finding
	vector<vector<int> > recursive(vector<vector<int> >, vector<vector<int> >);
};


#endif;