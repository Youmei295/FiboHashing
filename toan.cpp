#include <iostream>
#include <vector>
#include "Array_Generator.h"
#include "HashStruct.h"
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
  //Test 1: 100824, 403298, 806596
  //Test 2: 1613193, 6452775, 12905530
	vector<int> randomTU = randomTestUnit(n);
	vector<int> sequentialTU = sequentialTestUnit(n);
	vector<int> clusteredTU = clusteredTestUnit(n);
	HashTable htRandom((int) n*1.3);
	HashTable htSequential((int) n*1.3);
	HashTable htClustered((int) n*1.3);
	double timeRandom = measureExecutionTime2(testInsertionModulo, randomTU, htRandom, n);
	double timeSequential= measureExecutionTime2(testInsertionModulo, sequentialTU, htSequential, n);
	double timeClustered = measureExecutionTime2(testInsertionModulo, clusteredTU, htClustered, n);
	cout << "Average chain size: " << htRandom.averageChainLength()<<endl;
	cout << htRandom.size << endl;
	cout << endl;
	cout << "Random case: " << endl;
	cout << "Runtime: " << timeRandom << endl;
	cout << "minimum, median, maximum chain's size: " << htRandom.minChainLength() << " " << htRandom.medianChainLength() << " " << htRandom.maxChainLength() << endl;
	cout <<"Collisions: "<< htRandom.collisionCounter()<<endl;
	cout << "Collision rate: " << (htRandom.collisionCounter() / (n*1.0))*100<<"%"<<endl;
	cout << endl;
	cout << "Sequential case: " << endl;
	cout << "Runtime: " << timeSequential << endl;
	cout << "minimum, median, maximum chain's size: " << htSequential.minChainLength() << " " << htSequential.medianChainLength() << " " << htSequential.maxChainLength() << endl;
	cout <<"Collisions: "<< htSequential.collisionCounter()<<endl;
	cout << "Collision rate: " << (htSequential.collisionCounter() /( n*1.0)) * 100 << "%" << endl;
	cout << endl;
	cout << "Clustered case: " << endl;
	cout << "Runtime: " << timeClustered << endl;
	cout << "minimum, median, maximum chain's size: " << htClustered.minChainLength() << " " << htClustered.medianChainLength() << " " << htClustered.maxChainLength() << endl;
	cout <<"Collisions: "<< htClustered.collisionCounter()<<endl;
	cout << "Collision rate: " << (htClustered.collisionCounter() / (n*1.0)) * 100 << "%" << endl;
	cout << endl;
	return 0;
}
