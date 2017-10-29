#include "mhAlea.h"
#include <iostream>
#include <math.h>

using namespace std;

//Constructor
mhAlea::mhAlea(int s, int rca, int rco, int it) {
	size = s;
	Rcap = rca;
	Rcom = rco;
	bestSol = solution(s, Rcap, Rcom);
	bestVal = bestSol.getCapt() +
		pow(size,2) * (bestSol.allCover() + bestSol.allCommunicate() + bestSol.evalCover() + bestSol.evalPath());
	currSol = solution(s, Rcap, Rcom);
	currVal = bestVal;
	iterations = it;
}

//Get loss of value
void mhAlea::loss() {
	currVal = currSol.getCapt() +
		pow(size,2) * (2 - currSol.allCover() - currSol.allCommunicate() + currSol.evalCover() + currSol.evalPath());
}

//Launch the meta
void mhAlea::launchMH() {
	std::cout << "initial best value " << bestVal << " " << bestSol.getCapt() << std::endl;
	for (int k = 0; k < iterations; k++) {
		currSol.transf1();
		loss();
		if (currVal < bestVal) {
			bestVal = currVal;
			bestSol = currSol;
		}
	}
	std::cout << "final best value " << bestVal << " " << bestSol.getCapt() << std::endl;
}

//Launch the meta
void mhAlea::launchMHremove() {
	std::cout << "initial best value " << bestVal << " " << bestSol.getCapt() << std::endl;
	for (int k = 0; k < iterations; k++) {
		currSol.remove1();
		loss();
		if (currVal < bestVal) {
			bestVal = currVal;
			bestSol = currSol;
		}
	}
	std::cout << "final best value " << bestVal << " " << bestSol.getCapt() << std::endl;
}

//Launch the meta
void mhAlea::launchMHconc() {
	std::cout << "initial best value " << bestVal << " " << bestSol.getCapt() << std::endl;
	for (int k = 0; k < iterations; k++) {
		currSol.transfConc1();
		loss();
		if (currVal < bestVal) {
			bestVal = currVal;
			bestSol = currSol;
		}
	}
	std::cout << "final best value " << bestVal << " " << bestSol.getCapt() << std::endl;
}
