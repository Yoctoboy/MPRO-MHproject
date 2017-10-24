#ifndef MHMIGRATION_H
#define MHMIGRATION_H

#include <vector>
#include "solution.h"

using namespace std;

class mhMigration {
public:
  mhMigration(int, int, int);
  solution bestSol;
  int bestVal;
  solution currSol;
  int currVal;
  int getSize() {return size;};

  pair<int, int> get_random_captor();
  void launchMH(int);
  pair<int, int> move(pair<int, int>);
  void replacebest();

private:
  int Rcap;
  int Rcom;
  int size;
  int betteramount;
};

#endif
