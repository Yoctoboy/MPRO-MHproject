#include "solution.h"
#include <algorithm>
#include <iostream>
#include <queue>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

//constructor : create the grid nxn with captors everywhere
solution::solution(int n, int rcap, int rcom) {
	size = n;
	Rcap = rcap;
	Rcom = rcom;
	vector<bool> intermediate;
	vector<int> intermediate1;
	for (int i = 0; i < n; i++) {
		intermediate.push_back(true);
		intermediate1.push_back(0);
	}
	grid.clear();
	for (int i = 0; i < n; i++){
		grid.push_back(intermediate);
		cover.push_back(intermediate1);
	}
}

//calculates all possible transformation given a radius R
vector< pair<int, int> > solution::neighbour_transf(int R) {
	vector< pair<int, int> > transf;
	for (int i = -R; i <= R; i++) {
		for (int j = -R; j <= R; j++) {
			if (i*i + j*j <= R*R) {
				transf.push_back(make_pair(i, j));
			}
		}
	}
	return transf;
}

//return the neighbour at position pos
solution solution::getNeighbour(pair<int, int> pos) {
	//copy the current solution
	solution sol = *this;
	if (pos.first >= 0 && pos.first < size && pos.second >= 0 && pos.second < size) {
		sol.grid[pos.first][pos.second] = !this->grid[pos.first][pos.second];
		if (sol.grid[pos.first][pos.second]) {
			sol.nbCapteurs++;
		}
		else {
			sol.nbCapteurs--;
		}
	}
	return sol;
}

//Calculate the cover
void solution::updateCover() {
	//Get the transformation possible
	vector< pair<int, int> > transf = this->neighbour_transf(Rcap);
	REP(i, transf.size()){
		printf("%d %d\n", transf[i].first, transf[i].second);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (grid[i][j]) {
				for (int t = 0; t < transf.size(); t++) {
					int X = i + transf[t].first;
					if (X >= 0 && X < size) {
						int Y = j + transf[t].second;
						if (Y >= 0 && Y < size) {
							cover[X][Y]++;
						}
					}
				}
			}
		}
	}
}



//Finding if sol is realisable (only couverture)
bool solution::allcover(){
	this->updateCover();
	for(int i = 0; i < cover.size(); i++){
		for(int j = 0; j < cover.size(); j++){
			if(cover[i][j] < 1) return false;
		}
	}
	return true;
}

bool solution::allcommunicate(){
	queue< pair<int, int> > q;
	q.push(make_pair(0,0));
	return true;
}

//Controling the path finding and return how many captors are not covered by communication
int solution::pathfinding() {
	vector< pair<int, int> > transf = this->neighbour_transf(Rcom);
	//Index 2 et 3 are the transformation we cannot make
	vector<vector<int> > N = { {0,0,0,0} };
	//get neighbourhood
	vector<vector<int> > Nf = recursive(N, transf);
	//get number of captors
	int nbCapteurs = 0;
	for (int n = 0; n < size; n++) {
		for (int j = 0; j < size; j++) {
			if (grid[n][j]) { nbCapteurs++; }
		}
	}
	return nbCapteurs - Nf.size() + 1;
}



//recursive search
vector<vector<int> > solution::recursive(vector<vector<int> > N, vector< pair<int, int> > T) {
	//initialize new neighbourhood
	vector<vector<int> > newN;
	//explore neighbours with transformations
	for (int n = 0; n < N.size(); n++) {
		for (int t = 0; t < T.size(); t++) {
			int X = N[n][0] + T[t].first;
			int Y = N[n][1] + T[t].second;
			if (X >= 0 && X < size) {
				if (Y >= 0 && Y < size) {
					//if there is a captor and the transformation is allowed add new neighbour
					if (grid[X][Y] && !(N[n][2] == T[t].first && N[n][3] == T[t].second)) {
						newN.push_back({ X,Y, -T[t].first -T[t].second });
					}
				}
			}
		}
	}
	//avoid common values between newN and N
	vector<vector<int> > nnewN;
	for (int i = 0; i < newN.size(); i++) {
		bool test = false;
		for (int j = 0; j < N.size(); j++) {
			if (N[j][0] == newN[i][0] && N[j][1] == newN[i][1]) {
				test = true;
			}
		}
		if (!test) {
			nnewN.push_back(newN[i]);
		}
	}
	//if the new neighbourhood is empty
	if (nnewN.size() == 0) {
		return N;
	}
	//else we find new neighbours recursively and give back N + result of recursive in new neighbourhood
	else {
		vector<vector<int> > NN = recursive(nnewN, T);
		N.insert(N.end(), NN.begin(), NN.end());
		return N;
	}
}
