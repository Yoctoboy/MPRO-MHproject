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

int main(){
	freopen("log.txt", "w", stderr);
	srand(time(NULL));
	int size = 15, Rcap = 2, Rcom = 2;
	puts("initializing m");
	mhMigration m = mhMigration(size, Rcap, Rcom);
	puts("m initialized");
	m.launchMH(1000);

	/*s.printgrid(false);
	printf("Amount of captors : %d/%d\n", s.getCapt(), size*size);


	mhAlea MH = mhAlea(sizz, 1, 1, 1000);
	MH.launchMH();
	mhAlea MH2 = mhAlea(sizz, 1, 1, 1000);
	MH2.launchMHremove();
	mhAlea MH3 = mhAlea(sizz, 1, 1, 1000);
	MH3.launchMHconc();
	system("pause");*/
	return 0;
}
