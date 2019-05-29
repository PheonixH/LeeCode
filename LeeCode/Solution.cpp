#include "pch.h"
#include "Solution.h"
Solution::Solution()
{
}


Solution::~Solution()
{
}

//877
bool Solution::stoneGame(vector<int>& piles) {
	int N = (int)piles.size();

	// dp[i+1][j+1] = the value of the game [piles[i], ..., piles[j]]
	/*int dp[N + 2][N + 2];*/
	int **dp = new int*[N + 2];
	for (int i = 0; i < N + 2; i++)
	{
		dp[i] = new int[N + 2];
		for (int j = 0; j < N + 2; j++) {
			dp[i][j] = 0;
		}
	}
	//memset(dp, 0, sizeof(dp));
	
	for (int size = 1; size <= N; ++size)
		for (int i = 0, j = size - 1; j < N; ++i, ++j) {
			int parity = (j + i + N) % 2;  // j - i - N; but +x = -x (mod 2)
			if (parity == 1)
				dp[i + 1][j + 1] = max(piles[i] + dp[i + 2][j + 1], piles[j] + dp[i + 1][j]);
			else
				dp[i + 1][j + 1] = min(-piles[i] + dp[i + 2][j + 1], -piles[j] + dp[i + 1][j]);
		}

	return dp[1][N] > 0;
}

//70 爬楼梯
//执行用时 : 0 ms, 在Climbing Stairs的C++提交中击败了100.00% 的用户
//内存消耗: 8.6 MB, 在Climbing Stairs的C++提交中击败了17.59% 的用户
int Solution::climbStairs(int n) {
	int *p = new int[n+1];
	for (int i = 0; i < n+1;i++) {
		p[i] = 0;
	}
	p[0] = 0;
	p[1] = 1;
	if (n > 1) {
		p[2] = 2;
		for (int i = 3; i < n + 1; i++) {
			p[i] = max(p[i - 2] + p[i - 1], p[i]);
		}
	}
	return p[n];
}

//121
//执行用时 : 24 ms, 在Best Time to Buy and Sell Stock的C++提交中击败了21.81% 的用户
//内存消耗: 10.9 MB, 在Best Time to Buy and Sell Stock的C++提交中击败了5.10% 的用户
int Solution::maxProfit1(vector<int>& prices) {
	int len = prices.size();
	if (len == 0) {
		return 0;
	}
	int **p = new int*[len];
	for (int i = 0; i < len; i++) {
		p[i] = new int[2];
		for (int j = 0; j < 2; j++) {
			p[i][j] = 0;
		}
	}
	p[0][1] = 0-prices[0];

	for (int i = 1; i < len; i++) {
		p[i][1] = max(p[i - 1][1], -prices[i]);
		p[i][0] = max(p[i - 1][0], p[i - 1][1] + prices[i]);
	}
	int res = p[len - 1][0];
	delete[]p;
	return res;
}

//123
//执行用时 : 12 ms, 在Best Time to Buy and Sell Stock III的C++提交中击败了95.07% 的用户
//内存消耗: 9.5 MB, 在Best Time to Buy and Sell Stock III的C++提交中击败了65.24% 的用户
int Solution::maxProfit(vector<int>& prices) {
	int len = prices.size();
	if (len <= 1) {
		return 0;
	}
	int buy1 = -prices[0], buy2 = -prices[0];
	int sell1 = 0, sell2 = 0;
	for (int i = 1; i < len; i++) {
		buy1 = max(buy1, -prices[i]);
		sell1 = max(sell1, buy1 + prices[i]);

		buy2 = max(buy2, sell1-prices[i]);
		sell2 = max(sell2, buy2 +prices[i]);
		
	}

	return sell2>sell1?sell2:sell1;
}