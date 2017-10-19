#include <iostream>
#include "solution.h"

int main(){
	solution sol = solution(10);
	vector<vector<int>> transf = sol.neighbour_transf(2);
	for (int i = 0; i < transf.size(); ++i){
		cout << transf[i][0] << " " << transf[i][1] << endl;
}
	system("pause");
	return 0;
}