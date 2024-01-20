#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ofstream ofile("wyniki.txt");
int countInst = 0;
vector<int> incl = {1, 2, 3, 4};
vector<int> excl= {9, 10, 11, 12};

bool inVector(vector<int>& searchVec, int val)
{
	return find(searchVec.begin(), searchVec.end(), val) != searchVec.end();
}

void simplePrint(vector<int>& data)
{
	for (int item : data)
	{
		ofile << item << ' ';
	}
}

void printIter(vector<vector<int>>& ansVec, int num)
{
	for (int i = 0; i < num; i++)
	{
		simplePrint(ansVec[i]);
		ofile << '\t';
	}
}

bool printCombinations(vector<int>& data, int arraySize, int iter, vector<vector<int>>& ansVec, bool& was)
{
	if (iter == 0)
	{
		ansVec[iter] = data;
		simplePrint(data);
		ofile << '\t';
		return true;
	}
	else if (arraySize)
	{
		if (!was)
		{
			printIter(ansVec, iter);
		}
		ansVec[iter] = data;
		simplePrint(data);
		ofile << '\t';
		return true;
	}
	else
	{
		if (!was)
		{
			printIter(ansVec, iter);
		}
		ansVec[iter] = data;
		simplePrint(data);
		ofile << '\n';
		countInst++;
		clog << countInst << '\n';
		return false;
	}
}

void combinationUtil(vector<int> arr, vector<int>& data, int start, int end, int index, int r, int smallestIndex, bool goPrint, vector<vector<int>>& ansVec, bool& was)
{
	if (index == r && goPrint)
	{
		bool resWas = printCombinations(data, arr.size(), (end + 1 - arr.size() - r)/r, ansVec, was);
		was = resWas;
		vector<int> addData;
		addData.resize(r);
		combinationUtil(arr, addData, 0, end, 0, r, 0, false, ansVec, was);
	}
	else
	{
		for (int i = start; i - index < arr.size() && (!inVector(incl, data[0]) || !inVector(excl, arr[i - index])) && i <= end && end - i + 1 >= r - index && (start > 0 || i == smallestIndex); i++)
		{
			data[index%r] = arr[i - index];
			vector<int> temp = arr;
			temp.erase(temp.begin() + (i - index));
			combinationUtil(temp, data, i + 1, end, index + 1, r, smallestIndex, true, ansVec, was);
		}
	}
}

void allCombination(vector<int>& arr, int n, int r)
{
	vector<int> data;
	data.resize(r);
	vector<vector<int>> ansVec;
	for (int i = 0; i < n/r; i++)
	{
		vector<int> prevVec;
		prevVec.resize(r);
		ansVec.push_back(prevVec);
	}
	bool initWas = true;
	combinationUtil(arr, data, 0, n - 1, 0, r, 0, true, ansVec, initWas);
}

int main()
{
	vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int n = arr.size();
	int r = 4;
	allCombination(arr, n, r);
}