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
#include "solution.h"
#include "mhAlea.h"

int main(){
	int sizz = 5;
	solution sol = solution(sizz, 1, 1);
	/*for (int i = 0; i < sizz; i++) {
		for (int j = 0; j < sizz; j++) {
			sol.grid[i][j] = false;
		}
	}
	sol.grid[1][0] = true;
	sol.grid[1][1] = true;
	sol.grid[2][1] = true;
	sol.grid[1][2] = true;
	sol.grid[3][1] = true;
	sol.grid[1][3] = true;*/

	//cout << sol.pathfinding() << endl;

	puts(sol.allCover() ? "OK" : "NO");
	puts(sol.allCommunicate() ? "OK" : "NO");
	mhAlea MH = mhAlea(sizz, 1, 1, 1000);
	MH.launchMH();
	return 0;
}
