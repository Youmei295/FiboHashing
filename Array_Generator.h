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
	vector<int> testUnit;
vector<int> pool(size * 5);
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



