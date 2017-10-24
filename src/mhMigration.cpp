#include "mhMigration.h"
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

mhMigration::mhMigration(int size, int Rcap, int Rcom){
  bestSol = get_initial_solution(size, Rcap, Rcom);
  bestVal = bestSol.getCapt();
  size = size;
  Rcap = Rcap;
  Rcom = Rcom;
  currSol = bestSol;
  currVal = currSol.getCapt();
}

void mhMigration::launchMH(int maxiter){

}
