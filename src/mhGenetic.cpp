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
  generateBinaryMask();
  breed(pool[0], pool[1]);
}

void mhGenetic::generatePool(int initsize){
  for(int i = 0; i < initsize; i++){
	  pool[i] = get_initial_solution(size, Rcap, Rcom, true);
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
      if((float)rand()/RAND_MAX < prop) mask[i][j] = 2;
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
			if (mask[i][j] == 0) {
				s1.setGridVal(i, j, pool[b].getGridVal(i, j));
			}
			if (mask[i][j] == 1) {
				s2.setGridVal(i, j, pool[a].getGridVal(i, j));
			}
		}
	}
	return { s1, s2 };
}
