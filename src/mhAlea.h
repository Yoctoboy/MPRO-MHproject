#ifndef MHALEA_H
#define MHALEA_H
#include "solution.h"
#include <stdlib.h>  

class mhAlea {
public:
	solution bestSol;
	int bestVal;
	int iterations;
	solution currSol;
	int currVal;
	int Rcap;
	int Rcom;
	int size;

	mhAlea(int, int, int, int);
	void loss();
	void transf();
	void transfR();
	void transfConc();
	void launchMHremove();
	void launchMH();
};


#endif