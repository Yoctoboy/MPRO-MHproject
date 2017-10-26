#ifndef MHGENETIC_H
#define MHGENETIC_H

#include <vector>
#include "solution.h"

class mhGenetic {
public:
  vector< solution* > pool;
  vector<int> mask;

  mhGenetic(int,int,int,int);
  void generateMask();
  void generatePool(int);
  void mutate(solution, int);

private:
  int Rcap;
  int Rcom;
  int size;
  int poolsize;
};

#endif;
