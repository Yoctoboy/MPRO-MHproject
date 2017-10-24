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
#include <typeinfo>
#include "solution.h"
#include "init.h"

mhMigration::mhMigration(int s, int rca, int rco){
  bestSol = get_initial_solution(s, rca, rco, true);
  bestVal = bestSol.getCapt();
  size = s;
  Rcap = rca;
  Rcom = rco;
  betteramount = 0;
  currSol = bestSol;
  currVal = currSol.getCapt();
  puts("Initial Solution :");
  bestSol.printgrid();
}

void mhMigration::launchMH(int maxiter){
  puts("mh launched");
  int smalliter;
  pair<int, int> currCap, newCap;
  for(int iter = 0; iter < maxiter; iter++){
    printf("Iteration %d\n", iter);
    currCap = get_random_captor();
    currSol.removeCaptor(currCap);
    if(!currSol.realisable()) currSol.addCaptor(currCap);
    else{
      currVal = currSol.getCapt();
      if (currVal < bestVal) replacebest();
      puts("Captor successfully removed !");
      continue;
    }
    smalliter = 0;
    do{
      newCap = move(currCap);
      smalliter++;
    }while(find(currSol.captors.begin(), currSol.captors.end(), newCap) != currSol.captors.end() && smalliter < 5);
    if(smalliter>=5){
      puts("No satisfying neighbour.");
      continue;
    }
    currSol.removeCaptor(currCap);
    currSol.addCaptor(newCap);
    puts("Working on solution :");
    //currSol.printgrid();
    if(currSol.realisable()){
      puts("Is realisable :");
      currSol.printgrid();
      continue;
    }
    else{
      puts("Not realisable, reverting..");
      currSol.addCaptor(currCap);
      currSol.removeCaptor(newCap);
    }
  }
  puts("Best solution found :");
  bestSol.printgrid();
  printf("Amount of captors : %d/%d\n", bestVal, size*size);
}

pair<int, int> mhMigration::get_random_captor(){
  srand(rand());
  int r = ((int)rand())%(currSol.getCapt());
  pair<int,int> res = currSol.captors[r];
  return res;
}

pair<int, int> mhMigration::move(pair<int, int> pos){ //move towards bottom right of the grid
  pair<int, int> res = pos;
  float r, x, y;
  srand(rand());
  while(res.first == pos.first && res.second == pos.second){
    x = (float) pos.first / (float) size;
    y = (float) pos.second / (float) size;
    r = rand() / RAND_MAX;
    if(r < 1.2*(x*x) - 1.2*x + 0.8) res.first++;
    else if (r > (1 - (1.2*(x*x) - 1.2*x + 0.8))/6) res.first--;
    r = rand() / RAND_MAX;
    if(r < 1.2*(y*y) - 1.2*x + 0.8) res.second++;
    else if (r > (1 - (1.2*(y*y) - 1.2*y + 0.8))/6) res.second--;
  }
  return res;
}

void mhMigration::replacebest(){
  bestSol = currSol;
  bestVal = currSol.getCapt();
  betteramount++;
}

















//sorry
