#include "mhAlea.h"

//Constructor
mhAlea::mhAlea(int s, int rca, int rco) {
	size = s;
	Rcap = rca;
	Rcom = rco;
	bestSol = solution(s, Rcap, Rcom);
	bestVal = 0;
	currSol = solution(s, Rcap, Rcom);
	currVal = bestVal;
}

//Get loss of value
void mhAlea::loss() {
	currVal = currSol.nbCapteurs;
}

//Unitary transformation
void mhAlea::transf() {
	int i0 = std::rand() % size;
	int j0 = std::rand() % size;
	currSol = currSol.getNeighbour({ i0,j0 });
	loss();
	if (currVal < bestVal) {
		bestVal = currVal;
		bestSol = currSol;
	}
}

//Launch the meta
void mhAlea::lauchMH() {
	for (int k = 0; k < iterations; k++) {
		transf();
	}
}