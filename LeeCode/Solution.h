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
	//877
	bool stoneGame(vector<int>& piles);
	//70
	int climbStairs(int n);
	//121
	int maxProfit1(vector<int>& prices);
	//123
	int maxProfit(vector<int>& prices);
	//200
	int numIslands(vector<vector<char>>& grid);
	void numIslandsAss(vector<vector<char>>& grid, int x, int y);
	//164
	int maximumGap(vector<int>& nums);
	void quickSort(vector<int>& nums, int begin, int end);
	//462
	int minMoves2(vector<int>& nums);
	int minMoves2Ass(vector<int>& num, int key);
	//836
	bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2);
	//223
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H);
};

