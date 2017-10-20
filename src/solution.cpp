#include "solution.h"
#include <algorithm>
#include <iostream>

//constructor : create the grid nxn with captors everywhere
solution::solution(int n) {
	size = n;
	for (int i = 0; i < n; i++) {
		vector<bool> intermediate;
		for (int j = 0; j < n; j++) {
			intermediate.push_back(true);
		}
		grid.push_back(intermediate);
	}
}

//calculates all possible transformation given a radius R
vector<vector<int> > solution::neighbour_transf(int R) {
	vector<vector<int> > transf;
	for (int i = -R; i <= R; i++) {
		for (int j = -R; j <= R; j++) {
			if (i*i + j*j <= R*R) {
				transf.push_back({ i,j });
			}
		}
	}
	return transf;
}

//return the neighbour at position pos
solution solution::getNeighbour(vector<int> pos) {
	//copy the current solution
	solution sol = *this;
	if (pos[0] >= 0 && pos[0] < size && pos[1] >= 0 && pos[1] < size) {
		sol.grid[pos[0]][pos[1]] = !this->grid[pos[0]][pos[1]];
	}
	return sol;
}

//Calculate the cover
void solution::updateCover(int R) {
	//Get the transformation possible
	vector<vector<int> > transf = this->neighbour_transf(R);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int t = 0; t < transf.size(); t++) {
				int X = i + transf[i][0];
				if (X >= 0 && X < size) {
					int Y = j + transf[i][1];
					if (Y >= 0 && Y < size) {
						cover[X][Y] ++;
					}
				}
			}
		}
	}
}

int solution::pathfinding(int R) {
	vector<vector<int> > transf = this->neighbour_transf(R);
	vector<vector<int> > N = { {0,0,0,0} };
	vector<vector<int> > Nf = recursive(N, transf);
	int nbCapteurs = 0;
	for (int n = 0; n < size; n++) {
		for (int j = 0; j < size; j++) {
			if (grid[n][j]) { nbCapteurs++; }
		}
	}
	return nbCapteurs - Nf.size() + 1;
}

vector<vector<int> > solution::recursive(vector<vector<int> > N, vector<vector<int> > T) {
	vector<vector<int> > newN;
	for (int n = 0; n < N.size(); n++) {
		for (int t = 0; t < T.size(); t++) {
			int X = N[n][0] + T[t][0];
			int Y = N[n][1] + T[t][1];
			if (X >= 0 && X < size) {
				if (Y >= 0 && Y < size) {
					if (grid[X][Y] && !(N[n][2] == T[t][0] && N[n][3] == T[t][1])) {
						newN.push_back({ X,Y, -T[t][0], -T[t][1] });
					}
				}
			}
		}
	}
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
	if (nnewN.size() == 0) {
		return N;
	}
	else {
		vector<vector<int> > NN = recursive(nnewN, T);
		N.insert(N.end(), NN.begin(), NN.end());
		return N;
	}
}