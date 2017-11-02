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
	vector<int> sizes = {10, 15, 20, 25, 30, 40, 50};
	vector<int> cap = {1, 1, 2, 2, 3, 3};
	vector<int> com = {1, 2, 2, 3, 3, 4};
	srand(time(NULL));
	int maxiter = 50;
	fprintf(stderr, "Iterations per instance: %d\n\n", maxiter);
	for(int s = 0; s < 1; s++){
		for(int ca = 2; ca < cap.size(); ca++){
			puts("####################");
			printf("Size %dx%d - Rcap = %d - Rcom = %d\n", sizes[s], sizes[s], cap[ca], com[ca]);
			puts("####################");
			mhGenetic m = mhGenetic(10, cap[ca], com[ca], sizes[s]);
			m.generateBinaryMask();
			for(int iter = 0; iter < maxiter ; iter++){
				printf("Iteration %d - BEST = %d\n", iter+1, m.pool[0].getCapt());
				if(iter%10 == 0) m.updatePool(10, 0.8, iter);
				else if(iter%5 == 0) m.updatePool(10, 0.6, iter);
				else m.updatePool(10, 0.2, iter);
			}
			fprintf(stderr, "Size %dx%d - Rcap = %d - Rcom = %d\n", sizes[s], sizes[s], cap[ca], com[ca]);
			m.pool[0].printgrid(true);
		}
	}
	return 0;
}
