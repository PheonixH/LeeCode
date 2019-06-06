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

//200
//执行用时 : 16 ms, 在Number of Islands的C++提交中击败了94.56% 的用户
//内存消耗: 10.9 MB, 在Number of Islands的C++提交中击败了77.69% 的用户
int Solution::numIslands(vector<vector<char>>& grid) {
	int xlen = grid.size();
	if (xlen < 1) {
		return 0;
	}
	int ylen = grid[0].size();
	if (xlen < 1) {
		return 0;
	}
	int res = 0;
	for (int i = 0; i < xlen; i++) {
		for (int j = 0; j < ylen; j++) {
			if (grid[i][j] == '1') {
				numIslandsAss(grid, i, j);
				res++;
			}
		}
	}
	return res;
}

void Solution::numIslandsAss(vector<vector<char>>& grid, int x, int y) {
	int xlen = grid.size();
	int ylen = grid[0].size();
	grid[x][y] = '2';
	if (x - 1 >= 0 && grid[x - 1][y] == '1') {
		numIslandsAss(grid, x - 1, y);
	}
	if (x + 1 < xlen&& grid[x + 1][y] == 1) {
		numIslandsAss(grid, x + 1, y);
	}
	if (y - 1 >= 0 && grid[x][y - 1] == 1) {
		numIslandsAss(grid, x, y - 1);
	}
	if (y + 1 < ylen && grid[x][y + 1] == 1) {
		numIslandsAss(grid, x, y + 1);
	}
}

//164
//执行用时 : 8 ms, 在Maximum Gap的C++提交中击败了98.69% 的用户
//内存消耗: 9.6 MB, 在Maximum Gap的C++提交中击败了30.61% 的用户
int Solution::maximumGap(vector<int>& nums) {
	int len = nums.size();
	if (len <= 1) {
		return 0;
	}
	quickSort(nums, 0, len - 1);
	int m = 0;
	for (int i = 1; i < len; i++) {
		m = max(m, nums[i] - nums[i - 1]);
	}
	return m;
}

void Solution::quickSort(vector<int>& nums, int begin, int end) {
	if (begin < end) {
		int t = nums[begin];
		int b = begin, e = end;
		while (b < e) {
			while (e > b && nums[e] >= t) {
				e--;
			}
			//t = t ^ nums[e];
			nums[b] = nums[e];
			//t = t ^ nums[e];
			while (b < e && nums[b] <= t) {
				b++;
			}
			nums[e] = nums[b];
		}
		nums[b] = t;
		quickSort(nums, begin, b - 1);
		quickSort(nums, b + 1, end);
	}
}

//462
//执行用时 : 252 ms, 在Minimum Moves to Equal Array Elements II的C++提交中击败了6.60% 的用户
//内存消耗: 10.4 MB, 在Minimum Moves to Equal Array Elements II的C++提交中击败了6.38% 的用户
int Solution::minMoves2(vector<int>& nums) {
	int sum = 0;
	int len = nums.size();
	quickSort(nums, 0, len - 1);
	int res = 0;
	if (len % 2 == 1) {
		sum = nums[len / 2];
		res = minMoves2Ass(nums, sum);
	}
	else {
		int a = (len - 1) / 2;
		int b = nums[a + 1];
		int c = nums[a];
		b = minMoves2Ass(nums, b);
		c = minMoves2Ass(nums, c);
		res = min(b, c);
	}

	return res;
}

int Solution::minMoves2Ass(vector<int>& nums,int key) {
	int res = 0;
	int len = nums.size();
	for (int i = 0; i < len; i++) {
		res += abs(key - nums[i]);
	}
	return res;
}

//836
//执行用时 : 0 ms, 在Rectangle Overlap的C++提交中击败了100.00% 的用户
//内存消耗: 8.3 MB, 在Rectangle Overlap的C++提交中击败了56.72% 的用户
bool Solution::isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
	int left = min(rec1[2], rec2[2]) - max(rec1[0], rec2[0]);
	int right = min(rec1[3], rec2[3]) - max(rec1[1], rec2[1]);
	return left > 0 && right > 0;
}

//223
int Solution::computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
	int s1 = (C - A)*(D - B), s2 = (G - E)*(H - F);
	int w = min(C, G) - max(A, E);
	w = w > 0 ? w : 0;
	int h = min(D, H) - max(B, F);
	h = h > 0 ? h : 0;
	int s3 = w * h;
	return s1 + s2 - s3;
}