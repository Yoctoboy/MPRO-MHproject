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

int main(){
	freopen("log.txt", "w", stderr);
	srand(time(NULL));
	int size = 10, Rcap = 1, Rcom = 1;
	solution s = get_initial_solution(size, Rcap, Rcom);
	s.printgrid();


	/*mhAlea MH = mhAlea(sizz, 1, 1, 1000);
	MH.launchMH();
	mhAlea MH2 = mhAlea(sizz, 1, 1, 1000);
	MH2.launchMHremove();
	mhAlea MH3 = mhAlea(sizz, 1, 1, 1000);
	MH3.launchMHconc();
	system("pause");*/
	return 0;
}
