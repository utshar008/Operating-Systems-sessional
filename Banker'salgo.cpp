
#include <iostream>
using namespace std;
int main()
{

	int no_of_processes, no_of_resources, i, j, k;
	no_of_processes = 5;
	no_of_resources = 3;
	int allocate[5][3] = { { 0, 1, 0 },
						{ 2, 0, 0 },
						{ 3, 0, 2 },
						{ 2, 1, 1 },
						{ 0, 0, 2 } };
	int max[5][3] = { { 7, 5, 3 },
					{ 3, 2, 2 },
					{ 9, 0, 2 },
					{ 4, 2, 2 },
					{ 5, 3, 3 } };

	int available[3] = { 3, 3, 2 };
	int finish[no_of_processes]={0}, safe_seq[no_of_processes], index = 0;

	int need[no_of_processes][no_of_resources];

	for (i = 0; i < no_of_processes; i++) {
		for (j = 0; j < no_of_resources; j++)
			need[i][j] = max[i][j] - allocate[i][j];
	}
	int y = 0;
	for (k = 0; k < 5; k++) {
		for (i = 0; i < no_of_processes; i++) {

			if (finish[i] == 0) {
				bool flag = true;
				for (j = 0; j < no_of_resources; j++) {
					if (need[i][j] > available[j]){
						flag = false;
						break;
					}
				}

				if (flag == true) {
					safe_seq[index++] = i;
					for (y = 0; y < no_of_resources; y++)
						available[y] += allocate[i][y];
					finish[i] = 1;
				}
			}
		}
	}

	cout<<"Th SAFE Sequence is: \n";
	for (i = 0; i < no_of_processes - 1; i++)
		cout<<" P->"<<safe_seq[i];
	cout<<" P->"<<safe_seq[no_of_processes - 1];

	return 0;
}
