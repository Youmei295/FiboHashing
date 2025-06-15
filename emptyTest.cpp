#include <iostream>
#include <vector>
#include "Array_Generator.h"
#include "HashStruct.h"
#include <fstream>
using namespace std;

void testInsertion(vector<int> testUnit, HashTable& Table, int n)
{
	for (int i = 0; i < n; i++)
		Table.insert(testUnit[i]);
}

void testInsertionModulo(vector<int> testUnit, HashTable& Table, int n)
{
	for (int i = 0; i < n; i++)
		Table.insertModulo(testUnit[i]);
}

int main()
{
	srand(time(NULL));
	int n;
	cin >> n;
	vector<int> randomTU = randomTestUnit(n);
	vector<int> sequentialTU = sequentialTestUnit(n);
	vector<int> clusteredTU = clusteredTestUnit(n);
	HashTable htRandom((int)n * 1.3);
	HashTable htSequential((int)n * 1.3);
	HashTable htClustered((int)n*1.3 );
	//toan:1.3, long:1, hieu:/1.5
	testInsertion(randomTU, htRandom, n);
	testInsertion(sequentialTU, htSequential, n);
	testInsertion(clusteredTU, htClustered, n);
	cout << "Random: " << htRandom.EmptySlotCounter()<<endl;
	cout << "Sequential: " << htSequential.EmptySlotCounter() << endl;
	cout << "Cluster: " << htClustered.EmptySlotCounter() << endl;
	return 0;
}
