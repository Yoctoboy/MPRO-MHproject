#include "mhAlea.h"

using namespace std;

//Constructor
mhAlea::mhAlea(int s, int rca, int rco, int it) {
	size = s;
	Rcap = rca;
	Rcom = rco;
	bestSol = solution(s, Rcap, Rcom);
	bestVal = 0;
	currSol = solution(s, Rcap, Rcom);
	currVal = bestVal;
	iterations = it;
}

//Get loss of value
void mhAlea::loss() {
	currVal = currSol.nbCapteurs + size^2 * currSol.allCover() + size^2 * currSol.allCommunicate();
}

//Unitary transformation
void mhAlea::transf() {
	int i0 = rand() % size;
	int j0 = rand() % size;
	currSol = currSol.getNeighbour({ i0,j0 });
	loss();
	if (currVal < bestVal) {
		bestVal = currVal;
		bestSol = currSol;
	}
}

//unitary removal transformation
void mhAlea::transfR() {
	int i0 = rand() % size;
	int j0 = rand() % size;
	currSol.removeCaptor({ i0,j0 });
	loss();
	if (currVal < bestVal) {
		bestVal = currVal;
		bestSol = currSol;
	}
}

//unitary transformation with random in high concentration cover regions
void mhAlea::transfConc() {
	int imax = 0;
	int jmax = 0;
	for (int k = 0; k < size; k++) {
		int i = rand() % size;
		int j = rand() % size;
		if (currSol.cover[i][j]) {

		}
	}
}

//Launch the meta
void mhAlea::launchMH() {
	for (int k = 0; k < iterations; k++) {
		transf();
	}
}

//Launch the meta
void mhAlea::launchMHremove() {
	for (int k = 0; k < iterations; k++) {
		transfR();
	}
}