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
	int size = 20, Rcap = 1, Rcom = 1;
	puts("initializing m");
	mhGenetic m = mhGenetic(10, Rcap, Rcom, size);
	m.generateBinaryMask();
	puts("m initialized");
	/*pair<solution, solution> t = m.breed(m.pool[0], m.pool[1]);
	puts("MOTHER");
	m.pool[0].printgrid();
	puts("FATHER");
	m.pool[1].printgrid();

	puts("DAUGTHER");
	t.first.printgrid();
	puts("DAUGTHER");
	t.second.printgrid();
	printf("with %d captors\n", t.first.getCapt());*/
	for (int t = 0; t < 20000; t++) {
		m.updatePool(15);
		if (t % 2000 == t / 2000) {
			cout << t/2000 << " ";
			int count = 1000;
			for (int t = 0; t < m.getPoolsize(); t++) {
				if (count > m.pool[t].value) {
					count = m.pool[t].value;
				}
			}
			cout << count << endl;
			m.pool[0].printgrid();
		}
	}
	int count = 0;
	for (int t = 0; t < m.getPoolsize(); t++) {
		count += m.pool[t].value;
	}
	cout << "mean captors " << count / m.getPoolsize() << endl;
	//m.launchMH(1);

	//s.printgrid(false);
	//printf("Amount of captors : %d/%d\n", s.getCapt(), size*size);


	system("pause");
	return 0;
}
