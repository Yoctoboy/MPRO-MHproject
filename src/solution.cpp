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
		com.push_back(intermediate1);
	}
	grid[0][0] = false;
	transf_capt = neighbour_transf(Rcap);
	transf_com = neighbour_transf(Rcom);
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
void solution::getNeighbour(pair<int, int> pos) {
	int R = removeCaptor(pos);
	if (R == -1) {
		addCaptor(pos);
	}
}

//Finding if sol is realisable (only cover)
bool solution::allCover(){
	this->updateCover();
	for(int i = 0; i < cover.size(); i++){
		for(int j = 0; j < cover.size(); j++){
			if(cover[i][j] < 1) return false;
		}
	}
	return true;
}

//using BFS, find whether captors can all communicate together
bool solution::allCommunicate(){
	queue< pair<int, int> > q;
	pair<int, int> current;
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

	while(!q.empty()){
		current = q.front();
		q.pop();
		for (int i = -Rcom; i <= Rcom; i++) {
			for (int j = -Rcom; j <= Rcom; j++) {
				if(i*i + j*j <= Rcom*Rcom) {
					if((current.first + i >= 0 && current.first + i < size) && (current.second + j >= 0 && current.second + j < size)){
						if(!marked[current.first+i][current.second+j] && grid[current.first + i][current.second + j]){
							q.push(make_pair(current.first + i, current.second+j));
							found++;
							marked[current.first+i][current.second+j] = true;
						}
					}
				}
			}
		}
	}
	return found == nbCapteurs;
}

bool solution::realisable(){
	bool iscov = allCover();
	bool iscom = allCommunicate();
	if(!iscov) clog << "- NOT ALL COVERED";
	if(!iscom) clog << "- NOT ALL COMMUNICATE ";
	clog << endl;
	return (iscov && iscom);
}

bool solution::addCaptor(pair<int, int> pos){
	if(!grid[pos.first][pos.second]){
		grid[pos.first][pos.second] = true;
		nbCapteurs++;
		for (int t = 0; t < transf_capt.size(); t++){
			int X = pos.first + transf_capt[t].first;
			int Y = pos.second + transf_capt[t].second;
			if (X >= 0 && X < size && Y >= 0 && Y < size) {
				cover[X][Y] ++;
			}
		}
		for (int t = 0; t < transf_com.size(); t++) {
			int X = pos.first + transf_com[t].first;
			int Y = pos.second + transf_com[t].second;
			if (X >= 0 && X < size && Y >= 0 && Y < size && !(X == pos.first && Y == pos.second)) {
				com[X][Y] ++;
			}
		}
		return true;
	}
	else return false;
}

bool solution::removeCaptor(pair<int, int> pos){
	if(grid[pos.first][pos.second]){
		grid[pos.first][pos.second] = false;
		nbCapteurs--;
		for (int t = 0; t < transf_capt.size(); t++) {
			int X = pos.first + transf_capt[t].first;
			int Y = pos.second + transf_capt[t].second;
			if (X >= 0 && X < size && Y >= 0 && Y < size) {
				cover[X][Y] --;
			}
		}
		for (int t = 0; t < transf_com.size(); t++) {
			int X = pos.first + transf_com[t].first;
			int Y = pos.second + transf_com[t].second;
			if (X >= 0 && X < size && Y >= 0 && Y < size && !(X==pos.first && Y==pos.second)) {
				com[X][Y] --;
			}
		}
		return true;
	}
	else return false;
}

//Calculate the cover
void solution::updateCover() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cover[i][j] = 0;
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (grid[i][j]) {
				for (int t = 0; t < transf_capt.size(); t++) {
					int X = i + transf_capt[t].first;
					if (X >= 0 && X < size) {
						int Y = j + transf_capt[t].second;
						if (Y >= 0 && Y < size) {
							cover[X][Y]++;
						}
					}
				}
			}
		}
	}
}

//Calculate the cover
void solution::updateCom() {
	//Get the transformation possible
	REP(i, transf_com.size()) {
		//printf("%d %d\n", transf[i].first, transf[i].second);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (grid[i][j]) {
				for (int t = 0; t < transf_capt.size(); t++) {
					int X = i + transf_capt[t].first;
					if (X >= 0 && X < size) {
						int Y = j + transf_capt[t].second;
						if (Y >= 0 && Y < size && !(X == i && Y == j)) {
							com[X][Y]++;
						}
					}
				}
			}
		}
	}
}

//Unitary transformation
void solution::transf1() {
	int i0 = rand() % size;
	int j0 = rand() % size;
	this->getNeighbour({ i0,j0 });
}

//Unitary transformation
void solution::remove1() {
	int i0 = rand() % size;
	int j0 = rand() % size;
	this->removeCaptor({ i0,j0 });
}

//Unitary transformation with concentration
void solution::transfConc1() {
	int i0 = 0;
	int j0 = 0;
	for (int k = 0; k < size; k++) {
		int i = rand() % size;
		int j = rand() % size;
		if (cover[i][j] >= cover[i0][j0]) {
			i0 = i;
			j0 = j;
		}
	}

	this->getNeighbour({ i0,j0 });
}

//Evaluate quality of cover
int solution::evalCover() {
	float vmoy = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			vmoy += cover[i][j];
		}
	}
	vmoy *= 1 / (size*size);
	float vvar = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			vvar += pow(cover[i][j] - vmoy, 2);
		}
	}
	vvar *= 1 / (size*size);
	return vvar;
}

//Evaluate quality of cover
int solution::evalPath() {
	float vmoy = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (grid[i][j]) {
				vmoy += com[i][j];
			}
		}
	}
	return vmoy/(size*size);
}

void solution::printgrid(){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			printf("%c", grid[i][j] ? '#' : '.');
		}
		puts("");
	}
}
