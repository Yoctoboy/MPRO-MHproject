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

int main(){
	int sizz = 5;
	solution sol = solution(sizz);
	for (int i = 0; i < sizz; i++) {
		for (int j = 0; j < sizz; j++) {
			sol.grid[i][j] = false;
		}
	}
	sol.grid[1][0] = true;
	sol.grid[1][1] = true;
	sol.grid[2][1] = true;
	sol.grid[1][2] = true;
	sol.grid[3][1] = true;
	sol.grid[1][3] = true;

	cout << sol.pathfinding(1) << endl;

	puts(sol.realisable() ? "OK" : "NO");

	//system("pause");

	return 0;
}
