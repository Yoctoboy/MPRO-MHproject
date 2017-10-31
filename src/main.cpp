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
#include <ctime>
#include <pthread.h>
#include "solution.h"
#include "mhAlea.h"
#include "init.h"
#include "mhMigration.h"
#include "mhGenetic.h"

struct threaddata{
	int cap;
	int com;
	int size;
	int maxiter;
};

void* compute_stuff(void *threadarg){
	struct threaddata *arg;
	arg = (struct threaddata *) threadarg;
	int cap = arg->cap;
	int com = arg->com;
	int s = arg->size;
	int maxiter = arg->maxiter;
	mhGenetic m = mhGenetic(10, cap, com, s);
	m.generateBinaryMask();
	for(int iter = 0; iter < maxiter ; iter++){
		printf("Size %dx%d - Rcap = %d - Rcom = %d // Iteration %d/%d - BEST = %d\n", s, s, cap, com, iter+1, maxiter, m.pool[0].getCapt());
		if(iter%10 == 0) m.updatePool(10, 0.8);
		else if(iter%5 == 0) m.updatePool(10, 0.6);
		else m.updatePool(10, 0.2);
	}
	printf("SOLUTION FOUND - Size %dx%d - Rcap = %d - Rcom = %d - CAPT = %d\n", s, s, cap, com, m.pool[0].getCapt());
	fprintf(stderr, "Size %dx%d - Rcap = %d - Rcom = %d\n", s, s, cap, com);
	m.pool[0].printgrid(true);
	pthread_exit(NULL);
}

int main(){
	freopen("log.txt", "w", stderr);
	vector<int> sizes = {10, 15, 20, 25, 30, 40, 50};
	vector<int> cap = {1, 1, 2, 2, 3, 3};
	vector<int> com = {1, 2, 2, 3, 3, 4};
	srand(time(NULL));
	pthread_t threads[42];
	struct threaddata td[42];
	int instance = 0;
	int maxiter = 15;

	fprintf(stderr, "Iterations per instance: %d\n\n", maxiter);
	for(int s = 0; s < sizes.size(); s++){
		for(int ca = 0; ca < cap.size(); ca++){
			td[instance].cap = cap[ca];
			td[instance].com = com[ca];
			td[instance].size = sizes[s];
			td[instance].maxiter = maxiter;
			int rc = pthread_create(&threads[instance], NULL, compute_stuff, (void *)&td[instance]);
			if(rc){
				printf("Couldn't create thread %d, exiting...\n", instance);
				exit(-1);
			}
			instance++;
		}
	}
	pthread_exit(NULL);
	return 0;
}
