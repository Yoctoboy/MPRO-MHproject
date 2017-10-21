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
#include "solution.h"
#include "init.h"

solution get_initial_solution(int size, int rcap, int rcom){
  solution sol = solution(size, rcap, rcom);
  bool remove_possible = true;
  bool done_iter = false;
  while(remove_possible){
    done_iter = false;
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size && !done_iter; j++){
        if(i!=0 || j!=0){
          if(sol.removeCaptor(make_pair(i, j))){
            if(sol.realisable()){
              done_iter = true;
            }
            else{
              sol.addCaptor(make_pair(i, j));
            }
          }
        }
      }
    }
    if(!done_iter) remove_possible = false;
  }
  return sol;
}
