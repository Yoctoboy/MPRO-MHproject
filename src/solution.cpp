#include "solution.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <map>
#include <deque>
#include <queue>
#include <climits>
#include <queue>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

//constructor : create the grid nxn with captors everywhere
solution::solution(int n, int rcap, int rcom) {
	size = n;
	Rcap = rcap;
	Rcom = rcom;
	nbCapteurs = (n*n)-1;
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
bool solution::allCover(){
	this->updateCover();
	for(int i = 0; i < cover.size(); i++){
		for(int j = 0; j < cover.size(); j++){
			if(cover[i][j] < 1) return false;
		}
	}
	return true;
}

void solution::addCaptor(pair<int, int> pos){
	if(!grid[pos.first][pos.second]){
		grid[pos.first][pos.second] = true;
		nbCapteurs++;
	}
}

void solution::removeCaptor(pair<int, int> pos){
	if(grid[pos.first][pos.second]){
		grid[pos.first][pos.second] = false;
		nbCapteurs--;
	}
}

//using BFS, find whether captors can all communicate together
bool solution::allCommunicate(){
	queue< pair<int, int> > q;
	vector< vector<bool> > marked;
	vector<bool> markedline;
	for(int i = 0; i < size; i++){
		markedline.push_back(false);
	}
	for(int i = 0; i < size; i++){
		marked.push_back(markedline);
	}
	q.push(make_pair(0,0));
	marked[0][0] = true;
	int found = 0;
	pair<int, int> current;
	while(!q.empty()){
		current = q.front();
		marked[current.first][current.second] = true;
		q.pop();
		for (int i = -Rcom; i <= Rcom; i++) {
			for (int j = -Rcom; j <= Rcom; j++) {
				if(i*i + j*j <= Rcom*Rcom) {
					if((current.first + i >= 0 && current.first + i < size) && (current.second + j >= 0 && current.second + j < size)){
						if(!marked[current.first+i][current.second+j] && grid[current.first + i][current.second + j]){
							q.push(make_pair(current.first + i, current.second+j));
							found++;
						}
					}
				}
			}
		}
	}
	return found == nbCapteurs;
}
