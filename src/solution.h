#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;


class solution {
public:
	int getCapt() { return nbCapteurs; }
	int getSize() { return size; }
	vector<vector<int> > cover;
	vector<vector<int> > com;
	vector< pair<int, int> > captors;
	double value;

	solution(int, int, int);
	solution(int, int, int, vector< pair<int, int> >);
	solution(const solution &);
	solution();
	void loss();
	vector< pair<int, int> > neighbour_transf(int);
	void sortCaptors();
	void getNeighbour(pair<int, int>);
	bool allCover();
	bool allCommunicate();
	bool realisable();
	bool addCaptor(pair<int, int>);
	bool removeCaptor(pair<int, int>);
	void updateCover();
	void updateCom();
	void transf1();
	void remove1();
	void transfConc1();
	double evalCover();
	double evalPath();
	void printgrid(bool log = false);
	vector< vector<bool> > getGrid() {return grid;};
	bool getGridVal(int i, int j) { return grid[i][j]; };
	void setGridVal(int i, int j, int v) { grid[i][j] = v; };
	vector<pair<int, int> > getTransf_capt() {return transf_capt;};
	vector<pair<int, int> > getTransf_com() {return transf_com;};

	solution& operator=(const solution& other);
	bool operator<(const  solution & other) { return value < other.value; }

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
