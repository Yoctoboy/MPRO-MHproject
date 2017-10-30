#ifndef MHGENETIC_H
#define MHGENETIC_H

#include <vector>
#include <random>
#include "solution.h"
using namespace std;

class mhGenetic {
public:
  vector<solution> pool;

  vector<vector<int> > mask;

  int getPoolsize() { return poolsize; };

  mhGenetic(int,int,int,int);
  void generateBinaryMask();
  void generateMask(float);
  void generatePool(int);
  void updatePool(int);
  void sortPool();
  pair<solution,solution> breed(solution, solution);
  pair<solution,solution> breed2(int, int);
  solution mutate(solution, int);
  bool compare(const solution & l, const solution & r) { return l.value < r.value; }

private:
  int Rcap;
  int Rcom;
  int size;
  int poolsize;
};

#endif
