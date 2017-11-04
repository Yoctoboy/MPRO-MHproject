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
#include <chrono>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include "solution.h"
#include "mhAlea.h"
#include "init.h"
#include "mhMigration.h"
#include "mhGenetic.h"

float totalStrength;
vector<bool> threadsStatus; //true if over, else false

bool allThreadsOver(){
	for(int i = 0; i < (int)threadsStatus.size(); i++) if(!threadsStatus[i]) return false;
	return true;
}

//parameter class for every thread
struct threaddata{
	int id;
	int cap;
	int com;
	int size;
	int maxiter;
};

//check if all threads are over so we can print final result
void* check_finished(void *checkarg){
	while(!allThreadsOver()){this_thread::sleep_for(std::chrono::seconds(1));}
	printf("Total Strength = %lf\n", totalStrength);
	fprintf(stderr, "Total Strength = %lf\n", totalStrength);
	pthread_exit(NULL);
}

//executed method for every thread (one instance = one thread)
void* compute_stuff(void *threadarg){
	struct threaddata *arg;
	arg = (struct threaddata *) threadarg;
	int id = arg->id;
	int cap = arg->cap;
	int com = arg->com;
	int s = arg->size;
	int maxiter = arg->maxiter;
	mhGenetic m = mhGenetic(15, cap, com, s);
	m.generateBinaryMask();
	int curBest = 2000, bestsince = 0;
	for(int iter = 0; iter < maxiter ; iter++){
		printf("Size %dx%d - Rcap = %d - Rcom = %d // Iteration %d/%d - BEST = %d\n", s, s, cap, com, iter+1, maxiter, m.pool[0].getCapt());
		if(iter%10 == 0) m.updatePool(20, 0.8, iter, iter-bestsince >= 5 ? 5 : 0);
		else if(iter%5 == 0) m.updatePool(20, 0.6, iter, iter-bestsince >= 5 ? 5 : 0);
		else m.updatePool(20, 0.15, iter, iter-bestsince >= 5 ? 5 : 0);
		if(m.pool[0].getCapt() < curBest){
			curBest = m.pool[0].getCapt();
			bestsince = iter;
		}
	}
	printf("SOLUTION FOUND - Size %dx%d - Rcap = %d - Rcom = %d - CAPT = %d\n", s, s, cap, com, m.pool[0].getCapt());
	fprintf(stderr, "Size %dx%d - Rcap = %d - Rcom = %d\n", s, s, cap, com);
	float strength = ((float)m.pool[0].getCapt()*(pow(cap*com, 0.7)) /(s*s));
	totalStrength += strength;
	fprintf(stderr, "Strength of solution : %lf\n",  strength);
	m.pool[0].printgrid(true);
	threadsStatus[id] = true; //thread is over
	pthread_exit(NULL);
}

int main(){
	freopen("log.txt", "w", stderr);
	vector<int> sizes = {10, 15, 20, 25, 30, 40, 50};
	vector<int> cap = {1, 1, 2, 2, 3, 3};
	vector<int> com = {1, 2, 2, 3, 3, 4};
	srand(time(NULL));

	pthread_t threads[43];
	struct threaddata td[42];
	int instance = 0;
	//int maxiter = 10;
	totalStrength = 0;

	for(int s = 0; s < sizes.size(); s++){
		for(int ca = 0; ca < cap.size(); ca++){
			td[instance].id = instance;
			td[instance].cap = cap[ca];
			td[instance].com = com[ca];
			td[instance].size = sizes[s];
			td[instance].maxiter = 50;
			int rc = pthread_create(&threads[instance], NULL, compute_stuff, (void *)&td[instance]);
			if(rc){ //thread could not be created
				printf("Couldn't create thread %d, exiting...\n", instance);
				exit(-1);
			}
			instance++;
			threadsStatus.push_back(false);
		}
	}
	pthread_create(&threads[42], NULL, check_finished, (void *) 0);
	pthread_exit(NULL);
	return 0;
}
