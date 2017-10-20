#include <iostream>
#include "solution.h"

int main(){
	solution sol = solution(10);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
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
	//system("pause");
	return 0;
}