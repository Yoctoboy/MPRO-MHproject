#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;


class solution {
public:
	vector<vector<bool> > grid;
	int size;
	int Rcap;
	int Rcom;
	vector<vector<int> > cover;

	solution(int, int, int);
	vector< pair<int, int> > neighbour_transf(int);
	solution getNeighbour(vector<int>);
	bool realisable();
	void updateCover();
	int pathfinding();
	vector<vector<int> > recursive(vector<vector<int> >, vector< pair<int, int> >);
};


#endif
