#ifndef MHMIGRATION_H
#define MHMIGRATION_H

#include <vector>
#include "solution.h"

using namespace std;

class mhMigration {
public:
  mhMigration(int, int, int);
  void launchMH(int);
  solution bestSol;
  int bestVal;
  solution currSol;
  int currVal;
private:
  int Rcap;
  int Rcom;
  int size;
};

#endif
