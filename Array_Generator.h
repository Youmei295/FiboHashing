#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <random>
#include <vector>
#include <numeric>
using namespace std;

template <typename Func, typename... Args>
double measureExecutionTime1(Func&& func, Args&&... args) {
	auto start = std::chrono::high_resolution_clock::now();

	std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	return duration.count() / 1000.0;
}

template <typename Func, typename... Args>
double measureExecutionTime2(Func func, Args &&...args) {
	auto start = std::chrono::high_resolution_clock::now();

	func(std::forward<Args>(args)...);

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	return duration.count() / 1000.0;
}

vector<int> randomTestUnit(int size)
{
	vector<int> testUnit;
	vector<int> pool(size * 50);
	iota(pool.begin(), pool.end(), 0);
	random_device rd;
	mt19937 g(rd());
	shuffle(pool.begin(), pool.end(), g);
	for (int i = 0; i < size; i++)
	{
		testUnit.push_back(pool[i]);
	}
	return testUnit;
}

vector<int> sequentialTestUnit(int size)
{
	vector<int> testUnit = randomTestUnit(size);
	sort(testUnit.begin(), testUnit.end());
	return testUnit;
}

vector<int> clusteredTestUnit(int size)
{   
	random_device rd;
	mt19937 g(rd());

	vector<int> testUnit(size);

	testUnit[0] = 0;

	for (int i = 1; i <= size / 25; i++)
	{
		testUnit[i] = testUnit[i - 1] + 1 + rand() % 5;
	}

	int flag = testUnit[size/25];

	shuffle(testUnit.begin(), testUnit.begin() + size / 25 + 1, g);

	for (int i = 2; i <= 24; i++)
	{
		testUnit[((i-1)*size)/25 + 1] = flag + size + rand() % size;
		for (int j = ((i - 1) * size) / 25 + 2; j <= (i * size) / 25; j++)
		{
			testUnit[j] = testUnit[j - 1] + 1 + rand() % 5;
		}
		flag= testUnit[(i*size) / 25];
		shuffle(testUnit.begin()+ ((i - 1) * size) / 25 + 1, testUnit.begin() + (i  * size) / 25 + 1, g);
	}

	testUnit[(24*size)/25+1]=flag + rand() % size;

	for(int i=(24*size)/25+2;i<size;i++)
		testUnit[i] = testUnit[i - 1] + 1 + rand() % 5;
	shuffle(testUnit.begin() + (24 * size) / 25 + 1, testUnit.end(), g);
	return testUnit;
}



