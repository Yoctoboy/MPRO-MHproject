#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;


class solution {
public:
	int getCapt() { return nbCapteurs; }
	vector<vector<int> > cover;
	vector<vector<int> > com;

	solution(int, int, int);
	solution() {};
	vector< pair<int, int> > neighbour_transf(int);
	void getNeighbour(pair<int,int>);
	bool allCover();
	bool allCommunicate();
	bool realisable();
	bool addCaptor(pair<int,int>);
	bool removeCaptor(pair<int,int>);
	void updateCover();
	void updateCom();
	void transf1();
	void remove1();
	void transfConc1();
	int evalCover();
	int evalPath();
	void printgrid();

private:
	int size;
	int Rcap;
	int Rcom;
	int nbCapteurs;
	vector<vector<bool> > grid;
	vector<pair<int, int> > transf_capt;
	vector<pair<int, int> > transf_com;
};

#endif
