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
	//636
	vector<int> exclusiveTime(int n, vector<string>& logs);
	//674
	int findLengthOfLCIS(vector<int>& nums);
	//668
	int findKthNumber(int m, int n, int k);
	//371
	int getSum(int a, int b);
	//344
	void reverseString(vector<char>& s);
	//203
	ListNode* removeElements(ListNode* head, int val);
	//160
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB);
	//448
	vector<int> findDisappearedNumbers(vector<int>& nums);
	//216
	vector<vector<int>> combinationSum3(int k, int n);
	void func(int k, int n, int begin, vector<int>& tmp, vector<vector<int>>& res);
	//412
	vector<string> fizzBuzz(int n);
	//58
	int lengthOfLastWord(string s);
	//119
	vector<int> getRow(int rowIndex);
	//26
	int Solution::removeDuplicates(vector<int>& nums);
	//780
	bool reachingPoints(int sx, int sy, int tx, int ty);
	//27
	int removeElement(vector<int>& nums, int val);
	//28
	int strStr(string haystack, string needle);
};

