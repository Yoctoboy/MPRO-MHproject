#ifndef MHGENETIC_H
#define MHGENETIC_H

#include <vector>
#include <random>
#include "solution.h"

class mhGenetic {
public:
  vector< solution* > pool;
  vector<vector<int> > mask;

  mhGenetic(int,int,int,int);
  void generateMask();
  void generatePool(int);
  pair<solution,solution> breed(solution, solution);
  solution mutate(solution, int);

private:
  int Rcap;
  int Rcom;
  int size;
  int poolsize;
};

#endif;
