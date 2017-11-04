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
	captors.clear();
	for(int i = 0; i < n; i++){
		for(int j = i==0 ? 1 : 0; j < n; j++){
			captors.push_back(make_pair(i,j));
		}
	}
	grid[0][0] = false;
	transf_capt = neighbour_transf(Rcap);
	transf_com = neighbour_transf(Rcom);
	loss();
}

//copy constructor
solution::solution(const solution &s){
	size = s.size;
	Rcap = s.Rcap;
	Rcom = s.Rcom;
	grid = s.grid;
	cover = s.cover;
	captors = s.captors;
	grid = s.grid;
	com = s.com;
	transf_com = s.transf_com;
	transf_capt = s.transf_capt;
	nbCapteurs = s.nbCapteurs;
	value = s.value;
}

//basic constructor with no argument
solution::solution() {
	size = 1;
	Rcap = 0;
	Rcom = 0;
	captors = {};
	nbCapteurs = 0;
	grid = {};
	cover = {};
	com = {};
	transf_capt = {};
	transf_com = {};
	value = 0;
}

//constructor creating an instance from a list of captor coordinates
solution::solution(int n, int rcap, int rcom, vector< pair<int, int> > captorsarg) {
	size = n;
	Rcap = rcap;
	Rcom = rcom;
	captors = captorsarg;
	nbCapteurs = captors.size();
	vector<bool> intermediate;
	vector<int> intermediate1;
	for (int i = 0; i < n; i++) {
		intermediate.push_back(false);
		intermediate1.push_back(0);
	}
	grid.clear();
	for (int i = 0; i < n; i++){
		grid.push_back(intermediate);
		cover.push_back(intermediate1);
		com.push_back(intermediate1);
	}
	for(int i = 0; i < captors.size(); i++){
		grid[captors[i].first][captors[i].second] = true;
	}
	transf_capt = neighbour_transf(Rcap);
	transf_com = neighbour_transf(Rcom);
	loss();
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

//sort the list of captors to in order to compare solutions more easily
void solution::sortCaptors() {
	sort(captors.begin(),
			 captors.end(),
			 [](pair<int,int> a, pair<int,int> b){
				 return a.first==b.first ? a.second<b.second : a.first < b.first;
			 });
}

//return the neighbour at position pos
void solution::getNeighbour(pair<int, int> pos) {
	int R = removeCaptor(pos);
	if (R == -1) {
		addCaptor(pos);
	}
	loss();
}

//Finding if sol is realisable (only cover)
bool solution::allCover(){
	updateCover();
	for(int i = 0; i < cover.size(); i++){
		for(int j = 0; j < cover.size(); j++){
			if(cover[i][j] < 1){
				return false;
			}
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

//returns true iff the solution is realisable
bool solution::realisable(){
	bool iscov = allCover();
	bool iscom = allCommunicate();
	return (iscov && iscom);
}

//Method to add a captor on the grid, and update every necessary variable
bool solution::addCaptor(pair<int, int> pos){
	if(!grid[pos.first][pos.second]){
		grid[pos.first][pos.second] = true;
		nbCapteurs++;
		captors.push_back(pos);
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
		loss();
		return true;
	}
	else return false;
}

//Method to remove a captor from the grid, and update every necessary variable
bool solution::removeCaptor(pair<int, int> pos){
	if(grid[pos.first][pos.second]){
		grid[pos.first][pos.second] = false;
		nbCapteurs--;
		captors.erase(find(captors.begin(), captors.end(), pos));
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
		loss();
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
double solution::evalCover() {
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
double solution::evalPath() {
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

//Print the solution using '#' for a captor, and '·' for an empty target
void solution::printgrid(bool log){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if(!log) printf(grid[i][j] ? "#" : "\u00B7");
			else fprintf(stderr, grid[i][j] ? "#" : "\u00B7");
		}
		if (!log) printf("\n");
		else fprintf(stderr, "\n");
	}
	if(!log) printf("with %d captors", getCapt());
	else fprintf(stderr, "with %d captors\n\n", getCapt());
	if(!log) printf("\n");
	else fprintf(stderr, "\n");
}

//computes loss value
void solution::loss() {
	value = getCapt() + pow(size, 2) * (2 - allCover() - allCommunicate() + evalCover() + evalPath());
	//value = getCapt();
}

//sets a value on the grid using the adequate methods
void solution::setGridVal(int i, int j, bool v){
	if(grid[i][j] && !v){
		removeCaptor(make_pair(i, j));
	}
	if(!grid[i][j] && v){
		addCaptor(make_pair(i, j));
	}
}

//custom '=' operator for custom 'solution' class
solution& solution::operator=(const solution& other){
	size = other.size;
	Rcap = other.Rcap;
	Rcom = other.Rcom;
	cover = other.cover;
	captors = other.captors;
	grid = other.grid;
	com = other.com;
	nbCapteurs = other.nbCapteurs;
	transf_com = other.transf_com;
	transf_capt = other.transf_capt;
	value = other.value;
	return *this;
}

//Mutation
void solution::mutate(int k) {
	for (int n = 0; n < k; n++) {
		if (rand() < 0.5) {
			transf1();
		}
	}
}

void solution::mutate(int k, float p) {
    for (int n = 0; n < k; n++) {
        if (rand() < p) {
            transf1();
        }
    }
}

void solution::mutateadd(int n){
	int i0, j0;
	for(int i = 0; i < n; i++){
		do{
			i0 = rand() % size;
			j0 = rand() % size;
		} while(grid[i0][j0]);
		addCaptor(make_pair(i0, j0));
	}
}
