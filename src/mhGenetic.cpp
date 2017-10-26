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

mhGenetic::mhGenetic(int poolsize, int rcap, int rcom, int size){
  puts("init in progress.....");
  poolsize = poolsize;
  Rcom = rcom;
  Rcap = rcap;
  size = size;
  mask.reserve(100);
  pool = {get_initial_solution(size, Rcap, Rcom, true)};
  pool.reserve(poolsize);
  generatePool(10);
}

void mhGenetic::generatePool(int initsize){
	vector<solution*> store;
	store.resize(10);
  for(int i = 0; i < initsize; i++){
    printf("%d\n", i);
	solution* s = new solution(size, Rcap, Rcom);
    store.push_back(s);
  }
}
