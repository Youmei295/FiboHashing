#pragma once
#include <iostream>
#include <vector>
#include "Array_Generator.h"
using namespace std;
struct Entry
{
	int key;
	int value;
	Entry() : key(0), value(0) {}
	Entry(int newKey, int newValue) :key(newKey), value(newValue) {}
};

struct HashTable
{
	vector<vector<Entry>> Table;
	int size;
	double memberCounter;
	HashTable(int tableSize)
	{
		tableSize--;
		tableSize |= tableSize >> 1;
		tableSize |= tableSize >> 2;
		tableSize |= tableSize >> 4;
		tableSize |= tableSize >> 8;
		tableSize |= tableSize >> 16;
		tableSize++;
		Table.resize(tableSize);
		size = tableSize;
		memberCounter = 0;
	}

	int FiboHashing(int key)
	{
		int n = 0, temp = size;
		while (temp > 1)
		{
			temp >>= 1;
			n++;
		}
		return (key * 2654435769u) >> (32 - n);
	}

	int ModuloHashing(int key)
	{
		return key % size;
	}

	void insert(int newKey, int newVal=1)
	{
		int hashValue = FiboHashing(newKey);
		Entry newEntry(newKey, newVal);
		Table[hashValue].push_back(newEntry);
		memberCounter++;
	}

	void insertModulo(int newKey, int newVal = 1)
	{
		int hashValue = ModuloHashing(newKey);
		Entry newEntry(newKey, newVal);
		Table[hashValue].push_back(newEntry);
		memberCounter++;
	}

	void remove(int keytoremove)
	{
		int hashValue = FiboHashing(keytoremove);
		for (auto i = Table[hashValue].begin(); i != Table[hashValue].end(); )
		{
			if (i->key == keytoremove) i = Table[hashValue].erase(i);
			else i++;
		}
		memberCounter--;
	}

	bool search(int keytosearch, int& val)
	{
		int hashValue = FiboHashing(keytosearch);
		if (Table[hashValue].empty()) return false;
		else
		{
			for (auto i = Table[hashValue].begin(); i != Table[hashValue].end();)
			{
				if (i->key == keytosearch)
				{
					val = i->value; return true;
				}
				else i++;
			}
			return false;
		}
	}

	void printTable()
	{
		for (int i = 0; i < size; i++)
		{
			cout << "Chain of Index " << i << ": ";
			for (auto j = Table[i].begin(); j != Table[i].end(); j++)
			{
				cout << j->key << "-" << j->value << " ";
			}
			cout << endl;
		}
	}

	double getLoadFactor()
	{
		return memberCounter / size;
	}

	double averageChainLength()
	{
		double average=0;
		for (int i = 0; i < size; i++) average += Table[i].size();
		return average / size;
	}

	int maxChainLength()
	{
		if (size == 0) return 0;
		int maxx = Table[0].size();
		for (int i = 1; i < size; i++)
			if (Table[i].size() > maxx) maxx = Table[i].size();
		return maxx;
	}

	int minChainLength()
	{
		if (size == 0) return 0;
		int minn = Table[0].size();
		for (int i = 1; i < size; i++)
			if (Table[i].size() < minn) minn = Table[i].size();
		return minn;
	}

	double medianChainLength()
	{   
		double res;
		if (size == 0) return 0;
		vector<int> temp;
		for (int i = 0; i < size; i++) temp.push_back(Table[i].size());
		sort(temp.begin(), temp.end());
		if (size % 2 != 0) res = temp[(size - 1) / 2];
		else res = (temp[size/2-1] + temp[size/2]) / 2.0;
		return res;
	}

	int collisionCounter()
	{
		int counter = 0;
		for (int i = 0; i < size; i++)
			if(!Table[i].empty())counter += (Table[i].size() - 1);
		return counter;
	}
};