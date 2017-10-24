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
#include "solution.h"
#include "init.h"

solution get_initial_solution(int size, int rcap, int rcom, bool randomized){
  clock_t t = clock();
  solution sol = solution(size, rcap, rcom);

  vector< pair<int,int> > cibles;
  for(int i = 0; i < size; i++){
    for(int j = (i==0) ? 1 : 0; j < size; j++){
      cibles.push_back(make_pair(i, j));
    }
  }

  if(randomized) random_shuffle(cibles.begin(), cibles.end());
  for(int k = 0; k < cibles.size(); k++){
    if(sol.removeCaptor(cibles[k])){
      if(!sol.realisable()){
        sol.addCaptor(cibles[k]);
      }
    }
  }
  t = clock()-t;
  printf("Initial solution found in %lfs\n\n", ((float(t))/CLOCKS_PER_SEC));
  sol.sortCaptors();
  return sol;
}
