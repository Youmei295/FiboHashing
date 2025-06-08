#include <iostream>
#include <vector>
#include "Array_Generator.h"
#include "HashStruct.h"
#include <fstream>
using namespace std;

void testInsertion(vector<int> testUnit, HashTable& Table, int n,ofstream& file)
{
	for (int i = 0; i < n; i++)
		Table.insert(testUnit[i]);
	for (int i = 0; i < Table.Table.size(); i++)
		for (int j = 0; j < Table.Table[i].size(); j++)
			file << i << endl;
}

void testInsertionModulo(vector<int> testUnit, HashTable& Table, int n, ofstream& file)
{
	for (int i = 0; i < n; i++)
		Table.insertModulo(testUnit[i]);
	for (int i = 0; i < Table.Table.size(); i++)
		for (int j = 0; j < Table.Table[i].size(); j++)
			file << i << endl;
}

int main()
{   
	ofstream fileRandom("outputRandom.txt");
	ofstream fileSequential("outputSequential.txt");
	ofstream fileClustered("outputClustered.txt");
	srand(time(NULL));
	int n;
	cin >> n;
	n *= 50000;
	vector<int> randomTU = randomTestUnit(n);
	vector<int> sequentialTU = sequentialTestUnit(n);
	vector<int> clusteredTU = clusteredTestUnit(n);
  	HashTable htRandom((int)n * 1.3);
	HashTable htSequential((int)n * 1.3);
	HashTable htClustered((int)n * 1.3);
	cout << htRandom.size<<endl;
	testInsertion(randomTU, htRandom, n,fileRandom);
	testInsertion(sequentialTU, htSequential, n, fileSequential);
	testInsertion(clusteredTU, htClustered, n, fileClustered);
	file.close();
	return 0;
}
