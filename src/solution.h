#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;


class solution {
public:
	vector<vector<int> > cover;
	solution(int, int, int);
	solution() {};
	vector< pair<int, int> > neighbour_transf(int);
	solution getNeighbour(pair<int,int>);
	bool allCover();
	bool allCommunicate();
	bool addCaptor(pair<int,int>);
	bool removeCaptor(pair<int,int>);
	void updateCover();

private:
	int size;
	int Rcap;
	int Rcom;
	int nbCapteurs;
	vector<vector<bool> > grid;
};

#endif
