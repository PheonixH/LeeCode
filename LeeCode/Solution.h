#pragma once

#include <math.h>
#include <Windows.h>
#include <vector>
using namespace std;

class Solution
{
public:
	Solution();
	~Solution();
	bool stoneGame(vector<int>& piles);
	int climbStairs(int n);
	int maxProfit1(vector<int>& prices);
	int maxProfit(vector<int>& prices);
};

