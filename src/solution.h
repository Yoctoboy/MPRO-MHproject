#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;


class solution {
public:
	vector<vector<bool> > grid;
	int size;

	solution(int);
	vector<vector<int> > neighbour_transf(int);
	solution getNeighbour(vector<int>, int);
};


#endif;