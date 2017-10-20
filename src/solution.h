#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;


class solution {
public:
	int size;
	int Rcap;
	int Rcom;
	int nbCapteurs;
	vector<vector<int> > cover;

	solution(int, int, int);
	solution() {};
	vector< pair<int, int> > neighbour_transf(int);
	solution getNeighbour(pair<int,int>);
	bool allCover();
	bool allCommunicate();
	void addCaptor(pair<int,int>);
	void removeCaptor(pair<int,int>);
	void updateCover();
	int pathfinding();
	vector<vector<int> > recursive(vector<vector<int> >, vector< pair<int, int> >);

private:
	vector<vector<bool> > grid;
};


#endif
