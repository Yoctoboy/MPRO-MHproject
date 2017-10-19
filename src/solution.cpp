#include "solution.h"

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

solution solution::getNeighbour(vector<int> pos, int R) {
	solution sol = *this;
	vector<vector<int> > transf = neighbour_transf(R);
	for (int i = 0; i <= transf.size(); i++){
		int X = pos[0] + transf[i][0];
		if (X >= 0 && X < size) {
			int Y = pos[1] + transf[i][1];
			if (Y >= 0 && Y < size) {
				sol.grid[X][Y] = !this->grid [X][Y];
			}
		}
	}
}