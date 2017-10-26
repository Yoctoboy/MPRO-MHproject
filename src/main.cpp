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
	puts("initializing m");
	mhGenetic m = mhGenetic(30, Rcap, Rcom, size);
	puts("m initialized");
	//m.launchMH(1);

	//s.printgrid(false);
	//printf("Amount of captors : %d/%d\n", s.getCapt(), size*size);


	system("pause");
	return 0;
}
