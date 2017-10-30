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
#include "mhAlea.h"
#include "init.h"
#include "mhMigration.h"
#include "mhGenetic.h"

int main(){
	freopen("log.txt", "w", stderr);
	srand(time(NULL));
	int size = 10, Rcap = 1, Rcom = 1;
	mhGenetic m = mhGenetic(10, Rcap, Rcom, size);
	m.generateBinaryMask();
	for(int iter = 0; iter < 100 ; iter++){
		printf("\nIteration %d - BEST = %d\n", iter, m.pool[0].getCapt());
		m.updatePool(10);
	}
	puts("BEST SOLUTION :");
	m.pool[0].printgrid();
	return 0;
}
