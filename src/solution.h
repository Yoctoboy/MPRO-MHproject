#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;


class solution {
public:
	vector<vector<bool> > grid;
	int size;
	vector<vector<int> > cover;

	solution(int);
	vector<vector<int> > neighbour_transf(int);
	solution getNeighbour(vector<int>, int);
	bool realisable();
	void updateCover(int);
	int pathfinding(int);
	vector<vector<int> > recursive(vector<vector<int> >, vector<vector<int> >);
};


#endif;
