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
}

void mhGenetic::generatePool(int initsize){
  for(int i = 0; i < initsize; i++){
    pool[i]=(get_initial_solution(size, Rcap, Rcom, true));
  }
}
