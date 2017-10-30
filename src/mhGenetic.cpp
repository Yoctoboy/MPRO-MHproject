#include "mhGenetic.h"
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
#include <typeinfo>
#include "solution.h"
#include "init.h"

mhGenetic::mhGenetic(int poolsizz, int rcap, int rcom, int sizz){
  poolsize = poolsizz;
  Rcom = rcom;
  Rcap = rcap;
  size = sizz;
  pool.reserve(poolsize);
  generatePool(poolsize);
  generateMask(0.2);
  //breed(pool[0], pool[1]);
}

void mhGenetic::generatePool(int initsize){
  for(int i = 0; i < initsize; i++){
	  pool.push_back(get_initial_solution(size, Rcap, Rcom, true));
  }
  sortPool();
}

void mhGenetic::updatePool(int number) {
	int i0, j0;
  pair<solution, solution> result;
	for (int k = 0; k < number; k++) {
    generateMask(0.2);
		i0 = rand() % poolsize;
		j0 = rand() % poolsize;
    while(j0==i0) j0 = rand() % poolsize;
		result = breed2(i0, j0);
		if(result.first.realisable()){
      pool.push_back(result.first);
    }
		if(result.second.realisable()){
      pool.push_back(result.second);
    }
	}
  printf("Added %d realisable solutions\n", (int)pool.size()-poolsize);
  removeCaptorsFromPool(true);
	sortPool();
}

bool comp(solution a, solution b){
  return a.getCapt() < b.getCapt();
}

void mhGenetic::sortPool() {
	sort(pool.begin(), pool.end(), comp);
	pool.resize(poolsize);
}

void mhGenetic::removeCaptorsFromPool(bool randomized){
  vector< pair<int, int> > cibles;
  for(int i = 0; i < size; i++){
    for(int j = (i==0) ? 1 : 0; j < size; j++){
      cibles.push_back(make_pair(i, j));
    }
  }
  for (int i = poolsize; i < (int)pool.size(); i++){
    if(randomized) random_shuffle(cibles.begin(), cibles.end());
    for(int k = 0; k < cibles.size(); k++){
      if(pool[i].removeCaptor(cibles[k])){
        if(!pool[i].realisable()){
          pool[i].addCaptor(cibles[k]);
        }
      }
    }
  }
}

void mhGenetic::generateBinaryMask() {
  mask.clear();
  vector<int> line;
  int x;
	for (int i = 0; i < size; i++) {
		line.clear();
		for (int j = 0; j < size; j++) {
			x = rand() % 2;
			line.push_back(x);
		}
		mask.push_back(line);
	}
}

void mhGenetic::generateMask(float prop){
  mask.clear();
  vector<int> line;
  int x;
  for (int i = 0; i < size; i++) {
		line.clear();
		for (int j = 0; j < size; j++) {
			x = rand() % 2;
			line.push_back(x);
		}
		mask.push_back(line);
	}
  for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
      if((float)rand()/RAND_MAX < prop){
        mask[i][j] = 2;
      }
    }
  }
}

solution mhGenetic::mutate(solution s, int k) {
	for (int i = 0; i < k; i++) {
		int X = rand() % size;
		int Y = rand() % size;
		s.getNeighbour({ X,Y });
	}
	return s;
}

pair<solution, solution> mhGenetic::breed(solution sm, solution sp){
	solution s1 = sm;
	solution s2 = sp;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (mask[i][j] == 0) {
				s1.setGridVal(i, j, sp.getGridVal(i, j));
				s2.setGridVal(i, j, sm.getGridVal(i, j));
			}
		}
	}
	return { s1, s2 };
}

pair<solution, solution> mhGenetic::breed2(int a, int b) {
	solution s1 = pool[a];
	solution s2 = pool[b];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (mask[i][j] == 1) {
				s2.setGridVal(i, j, pool[a].getGridVal(i, j));
				s1.setGridVal(i, j, pool[b].getGridVal(i, j));
			}
      else if (mask[i][j] == 2){
				s2.setGridVal(i, j, pool[a].getGridVal(i, j) || pool[b].getGridVal(i, j));
				s1.setGridVal(i, j, pool[a].getGridVal(i, j) || pool[b].getGridVal(i, j));
      }
		}
	}
	return { s1, s2 };
}
