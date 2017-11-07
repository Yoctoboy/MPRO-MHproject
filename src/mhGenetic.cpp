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

//basic constructor
mhGenetic::mhGenetic(int _poolsize, int _Rcap, int _Rcom, int _size){
  poolsize = _poolsize;
  Rcom = _Rcom;
  Rcap = _Rcap;
  size = _size;
  pool.reserve(poolsize);
  generatePool(poolsize);
  generateMask(0.2);
  //breed(pool[0], pool[1]);
}

//generate initial generation of solutions
void mhGenetic::generatePool(int initsize){
  for(int i = 0; i < initsize; i++){
	  pool.push_back(get_initial_solution(size, Rcap, Rcom, true));
  }
  sortPool();
}

//update generation by breeding and selecting best individuals
void mhGenetic::updatePool(int number, float prop, int it, int addSolutions) {
  int i0, j0;
  pair<solution, solution> result;
  for (int k = 0; k < number; k++) {
    generateMask(prop);
    i0 = rand() % (int)pool.size();
    j0 = rand() % (int)pool.size();
    while(j0==i0) j0 = rand() % poolsize;
    result = breed2(i0, j0);
    if(result.first.realisable()){
      result.first.mutateadd(rand()%2==1 ? 1 : 0); //mutate with 50% chance
      pool.push_back(result.first);
    }
    if(result.second.realisable()){
      result.second.mutateadd(rand()%2==1 ? 1 : 0);
      pool.push_back(result.second);
    }
  }
  removeCaptorsFromPool(true);
  sortPool();
  pool.resize(poolsize - addSolutions);
  for(int i = 0; i < addSolutions; i++) pool.push_back(get_initial_solution(size, Rcap, Rcom, true));
}

//compare method to sort all the solutions
bool compCapt(solution a, solution b){
  return a.getCapt() < b.getCapt();
}

//sort solutions by the amount of captors they have and resize the pool if it's too big
void mhGenetic::sortPool() {
	sort(pool.begin(), pool.end(), compCapt);
	pool.resize(poolsize);
}

//greedy heuristic to remove as many captors as possible
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

//generate new random mask for breeding - 0-1 version
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

//generate new random mask for breeding - 0-1-2 version
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
        mask[i][j] = 2; //where the mask equals 2, child will have a captor if any of the parents has one
      }
    }
  }
}

//breed using binary mask
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

//breed using 0-1-2 mask, with pool index as parameter
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
