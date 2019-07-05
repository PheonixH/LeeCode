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
	int** dp = new int* [N + 2];
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
	int* p = new int[n + 1];
	for (int i = 0; i < n + 1; i++) {
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
	int** p = new int* [len];
	for (int i = 0; i < len; i++) {
		p[i] = new int[2];
		for (int j = 0; j < 2; j++) {
			p[i][j] = 0;
		}
	}
	p[0][1] = 0 - prices[0];

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

		buy2 = max(buy2, sell1 - prices[i]);
		sell2 = max(sell2, buy2 + prices[i]);

	}

	return sell2 > sell1 ? sell2 : sell1;
}

//26
//执行用时 :264 ms, 在所有 C++ 提交中击败了17.15% 的用户
//内存消耗:9.9 MB, 在所有 C++ 提交中击败了83.80 % 的用户
int Solution::removeDuplicates(vector<int>& nums) {
	if (nums.size() == 0) {
		return 0;
	}
	vector<int>::iterator it;
	it = nums.begin();
	int t = nums[0];
	it++;
	for (; it != nums.end();) {
		if (*it == t) {
			it = nums.erase(it);
		}
		else {
			t = *it;
			it++;
		}
	}
	return nums.size();
}

//780
//执行用时 :8 ms, 在所有 C++ 提交中击败了67.44% 的用户
//内存消耗:8.1 MB, 在所有 C++ 提交中击败了88.89 % 的用户
bool Solution::reachingPoints(int sx, int sy, int tx, int ty) {
	while (tx > 0 && ty > 0) {//因为sx, sy, tx, ty 是范围在 [1, 10^9] 的整数，逆推不能出界
		if (sx == tx && sy == ty) {//判断是否到达了起始值
			return true;
		}
		//每次逆推只能有tx、ty中较大值减去若干个较小值
		if (tx > ty) {//此时只能有tx减去ty
			//tx - sx是目标与起始值在x的差距，我们需要一次减去n * ty达到快速逼近sx的目的
			tx -= max((tx - sx) / ty, 1) * ty;
		}
		else {//此时只能有ty减去tx
			//ty - sy是目标与起始值在y的差距，我们需要一次减去n * tx达到快速逼近sy的目的
			ty -= max((ty - sy) / tx, 1) * tx;
		}
	}
	return false;
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
	if (x + 1 < xlen && grid[x + 1][y] == 1) {
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

int Solution::minMoves2Ass(vector<int>& nums, int key) {
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
	int s1 = (C - A) * (D - B), s2 = (G - E) * (H - F);
	int w = min(C, G) - max(A, E);
	w = w > 0 ? w : 0;
	int h = min(D, H) - max(B, F);
	h = h > 0 ? h : 0;
	int s3 = w * h;
	return s1 + s2 - s3;
}

//636
//执行用时 : 128 ms, 在Exclusive Time of Functions的C++提交中击败了8.86% 的用户
//内存消耗: 20.2 MB, 在Exclusive Time of Functions的C++提交中击败了7.69% 的用户
vector<int> Solution::exclusiveTime(int n, vector<string>& logs) {
	vector<int> res(n, 0);
	stack<pair<int, int>> sta;
	for (int i = 0; i < logs.size(); ++i) {
		istringstream is(logs[i]);
		vector<string> vecS;
		string s;
		while (getline(is, s, ':')) {
			vecS.push_back(s);
		}
		int id = stoi(vecS[0]);
		int time = stoi(vecS[2]);
		if (vecS[1] == "start") {
			sta.push(make_pair(id, time));
		}
		else {
			pair<int, int> temp = sta.top();
			sta.pop();
			int time_diff = time - temp.second + 1;
			res[temp.first] += time_diff;
			if (!sta.empty()) {
				res[sta.top().first] -= time_diff;
			}
		}
	}
	return res;
}

//674
//执行用时 :20 ms, 在所有C++提交中击败了86.07%的用户
//内存消耗 :9.5 MB, 在所有C++提交中击败了42.35%的用户
int Solution::findLengthOfLCIS(vector<int>& nums) {
	int len = nums.size();
	if (len <= 1) {
		return len;
	}
	int res = 0, r = 1;
	for (int i = 1; i < len; i++) {
		if (nums[i] > nums[i - 1]) {
			r++;
		}
		else {
			res = max(res, r);
			r = 1;
		}
	}
	res = max(res, r);
	return res;
}

//668
//超出时间限制
int findKthNumber0(int m, int n, int k) {
	/*vector<vector<int>> vec(m);
	for (int i = 0; i < m;i++) {
		vec[i].resize(n);
	}*/
	vector<int> vec(m);
	vector<int> v(m, 1);
	for (int i = 0; i < m; i++) {
		vec[i] = i + 1;
	}
	int res = 0;
	while (k >= 1) {
		int t = m - 1, tv = vec[m - 1];
		for (int i = m - 1; i >= 0; i--) {
			if (vec[i] == -1) {
				continue;
			}
			if (vec[i] < tv) {
				t = i;
				tv = vec[i];
			}
		}
		res = vec[t];
		if (v[t] + 1 > n) {
			vec[t] = -1;
		}
		else {
			vec[t] = vec[t] / v[t] * (v[t] + 1);
			v[t]++;
		}
		if (k == 1) {
			return res;
		}
		k--;
	}
	return 0;
}

int Solution::findKthNumber(int m, int n, int k) {
	int t = 0, num = k;
	int a = 0, b = 2 * k;
	while (a < b - 1) {
		t = 0;
		num = (a + b) / 2;
		for (int i = 0; i < m; i++) {
			int tt = min(num / (i + 1), n);
			t += tt;
		}
		if (t > k) {
			b = num;
		}
		else if (t < k) {
			a = num;
		}
		else {
			return num;
		}
	}
	int ta = 0;
	for (int i = 0; i < m; i++) {
		ta += min(a / (i + 1), n);
	}
	return ta == k ? a : b;
}

//668
//执行用时 :40 ms, 在所有C++提交中击败了36.11%的用户
//内存消耗 :8.2 MB, 在所有C++提交中击败了76.92%的用户
//在m，n的乘法表中，寻找不大于num的元素个数
int smallNumCount(int num, int m, int n) {
	int count = 0;
	//对乘法表的每一行（每一行都是递增）进行搜索，muns[row][col] = row * col
	for (int i = 1; i <= m; i++) {
		count += min(num / i, n);//num/i代表的是如果num也在第i行，它存在的列数，而一行最多只有n个
	}
	return count;
}
int findKthNumber1(int m, int n, int k) {
	//m,n的乘法表中，取值范围为[1, m * n],使用二分法确定第k个值
	int low = 1, high = m * n + 1;
	while (low < high) {
		int mid = (low + high) / 2;
		int cnt = smallNumCount(mid, m, n);//计算乘法表中不大于mid的元素个数
		if (cnt >= k) {
			high = mid;
		}
		else {
			low = mid + 1;
		}
	}
	return low;
}


//371
//执行用时 :0 ms, 在所有C++提交中击败了100.00%的用户
//内存消耗 :8.1 MB, 在所有C++提交中击败了51.81%的用户
int Solution::getSum(int a, int b) {
	while (a & b) {
		int n = a;
		int m = b;
		a = n ^ m;
		b = (unsigned int)(n & m) << 1;
	}
	return a ^ b;
}

//344
//执行用时 :72 ms, 在所有C++提交中击败了85.24% 的用户
//内存消耗:15.2 MB, 在所有C++提交中击败了80.04%的用户
void Solution::reverseString(vector<char>& s) {
	int len = s.size();
	for (int i = 0; i < len / 2; i++) {
		s[i] = s[i] ^ s[len - 1 - i];
		s[len - 1 - i] = s[i] ^ s[len - 1 - i];
		s[i] = s[i] ^ s[len - 1 - i];
	}
}

//203
//执行用时 :44 ms, 在所有C++提交中击败了83.34% 的用户
//内存消耗:11.3 MB, 在所有C++提交中击败了48.62%的用户
ListNode* Solution::removeElements(ListNode* head, int val) {
	if (head == NULL) {
		return head;
	}
	ListNode* p = head;
	ListNode* q = head->next;

	while (q != NULL) {
		if (q->val == val) {
			p->next = q->next;
			delete(q);
			q = p->next;
		}
		else {
			q = q->next;
			p = p->next;
		}
	}
	if (val == head->val) {
		return head->next;
	}
	return head;
}

//160
//执行用时 :1072 ms, 在所有C++提交中击败了5.01% 的用户
//内存消耗:16.7 MB, 在所有C++提交中击败了46.13%的用户
ListNode* Solution::getIntersectionNode(ListNode* headA, ListNode* headB) {
	ListNode* pA = headA;
	while (pA != NULL) {
		ListNode* pB = headB;
		while (pB != NULL) {
			if (pA == pB) {
				return pB;
			}
			pB = pB->next;
		}
		pA = pA->next;
	}
	return pA;
}

//执行用时 :132 ms, 在所有C++提交中击败了13.02% 的用户
//内存消耗:16.7 MB, 在所有C++提交中击败了62.85%的用户
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
	ListNode* pA = headA, * pB = headB;
	// 如果第一次遍历到链表尾部，就指向另一个链表的头部，继续遍历，这样会抵消长度差。
	// 如果没有相交，因为遍历长度相等，最后会是NULL == NULL
	while (pA != pB) {
		if (pA == NULL) {
			pA = headB;
		}
		else {
			pA = pA->next;
		}
		if (pB == NULL) {
			pB = headA;
		}
		else {
			pB = pB->next;
		}
	}
	return pA;
}

//448
//超出时间限制
vector<int> findDisappearedNumbers(vector<int>& nums) {
	int len = nums.size();
	vector<int> vec(len, -1);
	int res = len;
	for (int n : nums) {
		if (vec[n - 1] == -1) {
			vec[n - 1]++;
		}
	}
	int i = 1;
	for (auto it = vec.begin(); it != vec.end(); i++)
	{
		if (*it >= 0) {
			it = vec.erase(it);
		}
		else {
			*it = i;
			++it;
		}
	}
	return vec;
}

//448:
/*【笔记】将所有正数作为数组下标，置对应数组值为负值。那么，仍为正数的位置即为（未出现过）消失的数字。
举个例子：
	原始数组：[4,3,2,7,8,2,3,1]

	重置后为：[-4,-3,-2,-7,8,2,-3,-1]
结论：[8,2] 分别对应的index为[5,6]（消失的数字）
*/
//执行用时 :140 ms, 在所有C++提交中击败了91.52% 的用户
//内存消耗:14.8 MB, 在所有C++提交中击败了86.06%的用户
vector<int> Solution::findDisappearedNumbers(vector<int>& nums) {
	for (int i = 0; i < nums.size(); ++i)
		nums[abs(nums[i]) - 1] = -abs(nums[abs(nums[i]) - 1]);
	vector<int> res;
	for (int i = 0; i < nums.size(); ++i) {
		if (nums[i] > 0)
			res.push_back(i + 1);
	}
	return res;
}

//216
//执行用时 :0 ms, 在所有C++提交中击败了100.00% 的用户
//内存消耗:8.7 MB, 在所有C++提交中击败了42.45%的用户
vector<vector<int>> Solution::combinationSum3(int k, int n) {
	vector<vector<int>> res;
	vector<int> tmp;
	func(k, n, 1, tmp, res);
	return res;
}
void Solution::func(int k, int n, int begin, vector<int>& tmp, vector<vector<int>>& res)
{
	if (k < 0 || n < 0) return;
	if (k == 0 && n == 0)
		res.push_back(tmp);
	for (int i = begin; i < 10; i++)
	{
		tmp.push_back(i);
		func(k - 1, n - i, i + 1, tmp, res);
		tmp.pop_back();
	}
}

//412
//执行用时 :12 ms, 在所有C++提交中击败了90.04% 的用户
//内存消耗:10.6 MB, 在所有C++提交中击败了5.55%的用户
vector<string> Solution::fizzBuzz(int n)
{
	vector<string> v;
	int i = 1;
	while (n >= i) {
		if (i / 15 * 15 == i) {
			v.push_back("FizzBuzz");

		}
		else if (i / 3 * 3 == i) {
			v.push_back("Fizz");
		}
		else if (i / 5 * 5 == i) {
			v.push_back("Buzz");
		}
		else {
			stringstream ss;
			ss << i;
			v.push_back(ss.str());
		}
		i++;
	}
	return v;
}

//58
// 执行用时 :8 ms, 在所有C++提交中击败了85.93% 的用户
//内存消耗 : 8.9 MB, 在所有C++提交中击败了61.30%的用户
int Solution::lengthOfLastWord(string s) {
	if (s.empty()) {
		return 0;
	}

	int length = 0;

	// 找到第一个非空格字符，或者遍历到字符串开头
	auto iter = s.rbegin();
	while (iter != s.rend() && *iter == ' ') {
		iter++;
	}

	// 整个字符串都是空格字符
	if (iter == s.rend()) {
		return 0;
	}

	// length一直自增，直到遇到空格字符，或者遍历到字符串开头
	while (iter != s.rend() && *iter != ' ') {
		length++;
		iter++;
	}
	return length;
}

//119
//执行用时 :0 ms, 在所有C++提交中击败了100.00% 的用户
//内存消耗:8.6 MB, 在所有C++提交中击败了23.83%的用户
vector<int> Solution::getRow(int rowIndex) {
	int i = 1;
	vector<int> v(rowIndex + 1);
	int t = 0;
	long key = 1;
	while (t <= rowIndex / 2)
	{
		v[t] = key;
		v[rowIndex - t] = key;
		t++;
		key = key * (rowIndex - t + 1) / (t);
	}
	return v;
}

//27
//执行用时 :4 ms, 在所有 C++ 提交中击败了96.01% 的用户
//内存消耗:8.5 MB, 在所有 C++ 提交中击败了86.79 % 的用户
int Solution::removeElement(vector<int>& nums, int val) {
	int i = 0, j = 0, len = nums.size();
	for (; j < len;j++) {
		if (nums[j] == val) {
			continue;
		}
		else {
			nums[i] = nums[j];
			i++;
		}
	}
	return i;
}

//28
//执行用时 :12 ms, 在所有 C++ 提交中击败了62.53% 的用户
//内存消耗:8.9 MB, 在所有 C++ 提交中击败了93.54 % 的用户
int Solution::strStr(string haystack, string needle) {
	// write your code here 
	if (needle.size() == 0) {
		return 0;
	}
	if (needle.size() > haystack.size()) {
		return -1;
	}
	//needle 指针
	int j = 0;
	int i = 0;
	for (i = 0; i < haystack.size(); ++i) {
		if (j == needle.size()) {//判断完成
			return i - needle.size();
		}
		if (haystack[i] == needle[j]) {
			j++;
		}
		else {
			i -= j;
			j = 0;
		}
	}
	if (j == needle.size()) {//判断完成
		return i - needle.size();
	}
	return -1;
}

//31
//执行用时 :16 ms, 在所有 C++ 提交中击败了73.16% 的用户
//内存消耗:8.5 MB, 在所有 C++ 提交中击败了91.76 % 的用户
void Solution::nextPermutation(vector<int>& nums) {
	int len = nums.size();
	if (len <= 1) {
		return;
	}
	int x = len - 1;
	for (; x > 0; x--) {
		if (nums[x] > nums[x - 1]) {
			break;
		}
	}
	if (x == len - 1) {
		revoltArray(nums, x-1, len - 1);
		return;
	}
	revoltArray(nums, x, len - 1);
	if (x != 0) {
		int y = x - 1;
		for (; x < len; x++) {
			if (nums[x] > nums[y]) {
				nums[x] = nums[x] ^ nums[y];
				nums[y] = nums[x] ^ nums[y];
				nums[x] = nums[x] ^ nums[y];
				break;
			}
		}
	}
	return;
}
void Solution::revoltArray(vector<int>& nums, int b, int e) {
	while (b < e)
	{
		nums[b] = nums[b] ^ nums[e];
		nums[e] = nums[b] ^ nums[e];
		nums[b] = nums[b] ^ nums[e];
		b++;
		e--;
	}
	return;
}

//41
//执行用时 :0 ms, 在所有 C++ 提交中击败了100.00% 的用户
//内存消耗:8.8 MB, 在所有 C++ 提交中击败了71.51 % 的用户
int Solution::firstMissingPositive(vector<int>& nums) {
	int len = nums.size();
	quickSort(nums, 0, len-1);
	int x = 1, i = 0;
	bool isPositive = false;
	while (i<len)
	{
		if (nums[i] == x&&!isPositive) {
			isPositive = true;
			x++;
		}
		else if (isPositive) {
			if (x < nums[i]) {
				return x;
			}
			else if (x == nums[i]) {
				x++;
			}
		}
		i++;
	}
	return x;
}

//41
/*提供两种思路：

	hash 计数：需要额外的空间。所有出现的数字，hash 值 + 1。第二次从 1 开始查找 hash 表，找不到就是它了。但是这种方案不符合题意，而且 hash 计数这个方案效率也不是最优的。
	假设原始数组为 A。先构造一个临时数组 tmp，初始化为 0，大小为A.size(). 遍历 A，把 A[i] 复制到 tmp[A[i]-1] 的位置。如果 A[i] - 1 超过了 tmp 的范围，就直接扔掉。如此一来，tmp[0...size) 中就保存了一部分 A 的值。然后从位置 0 开始检查 tmp，如果发现该位置的值和索引号不匹配，就说明找到了缺失的数了。

注意上面的方案一，没办法优化成 in-place 算法，但是方案二可以。方案二，可以不使用 tmp 数组，直接在原始数组中操作，把每个数放到正确的位置。

我们使用一种 “座位交换法" 来达到 in-place 的目的：

	从第一个位置开始，让座位上的乘客走到自己应该坐的位置，并让该位置的人坐到第一个位置。一直进行这样的操作，直到第一个位置的人坐到自己位置。不过有时候我们知道，有的人总喜欢逃票。因此终止条件就是，一旦发现第一个位置的人逃票（票号 <= 0，或 >= 最大座位号)，则终止交换。
	对第二到N个位置做相同的操作。
*/
//执行用时 :12 ms, 在所有 C++ 提交中击败了26.02% 的用户
//内存消耗:8.7 MB, 在所有 C++ 提交中击败了76.49 % 的用户
int firstMissingPositive(vector<int>& nums) {
	for (int i = 0; i < nums.size(); ++i) {
		while (0 < nums[i] && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1]) {
			swap(nums[i], nums[nums[i] - 1]);
		}
	}
	for (int i = 0; i < nums.size(); ++i) {
		if (nums[i] != i + 1) {
			return i + 1;
		}
	}
	return nums.size() + 1;
}

//57
//执行用时 :1460 ms, 在所有 C++ 提交中击败了5.12% 的用户
//内存消耗:12.3 MB, 在所有 C++ 提交中击败了5.23 % 的用户
vector<vector<int>> Solution::insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
	if (intervals.size() == 0) {
		intervals.push_back(newInterval);
		return intervals;
	}
	bool isAdd = false;
	vector<vector<int>> ::iterator  it = intervals.begin();
	for (; it != intervals.end();) {
		vector<int> &vec = *it;
		if (vec[1] < newInterval[0])
		{
			++it;
			continue;
		}
		if (vec[0] < newInterval[0]) {
			newInterval[0] = vec[0];
			vec[0] = -100;
		}
		if (vec[0]<=newInterval[1]&&vec[1] > newInterval[1]) {
			newInterval[1] = vec[1];
			vec[0] = -100;
		}
		if (vec[0] >= newInterval[0] && vec[1] <= newInterval[1]) {
			vec[0] = -100;
		}
		if (vec[0] > newInterval[1]) {
			it = intervals.insert(it, newInterval);
			isAdd = true;
			break;
		}
		if (vec[0] == -100) {
			it = intervals.erase(it);
		}
		else {
			++it;
		}
	}
	if (!isAdd) {
		intervals.push_back(newInterval);
	}
	return intervals;
}

//57
//执行用时 :20 ms, 在所有 C++ 提交中击败了94.73% 的用户
//内存消耗:12.4 MB, 在所有 C++ 提交中击败了5.23 % 的用户
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
	if (intervals.size() == 0)
	{
		intervals.push_back(newInterval);
		return intervals;
	}

	int N = intervals.size();
	for (vector<vector<int>>::iterator iter = intervals.begin(); iter != intervals.end(); iter++)
	{
		if ((*iter)[0] <= newInterval[0] && (*iter)[1] >= newInterval[1])
		{
			return intervals;
		}
		else if ((*iter)[0] >= newInterval[0] && (*iter)[0] <= newInterval[1])
		{
			(*iter)[0] = newInterval[0];
			(*iter)[1] = max((*iter)[1], newInterval[1]);
			vector<vector<int>>::iterator temp = iter;
			int index = 0;
			++temp;
			bool flag = true;
			while (temp != intervals.end() && (*temp)[0] <= newInterval[1])
			{
				index++;
				if ((*temp)[1] <= newInterval[1])
				{
					temp++;
				}
				else if ((*temp)[1] >= newInterval[1])
				{
					flag = false;
					(*iter)[1] = (*temp)[1];
					break;
				}
			}
			++iter;
			intervals.erase(iter, iter + index);
			return intervals;
		}
		else if ((*iter)[0] <= newInterval[0] && (*iter)[1] >= newInterval[0] && (*iter)[1] < newInterval[1])
		{
			cout << "fuck" << endl;
			vector<vector<int>>::iterator temp = iter;
			temp++;
			(*iter)[1] = newInterval[1];
			int index = 0;
			while (temp != intervals.end() && (*temp)[0] <= newInterval[1])
			{
				index++;
				if ((*temp)[1] <= newInterval[1])
				{
					temp++;
				}
				else if ((*temp)[1] >= newInterval[1])
				{
					(*iter)[1] = (*temp)[1];
					break;
				}
			}
			iter++;
			intervals.erase(iter, iter + index);
			return intervals;
		}
		else if ((*iter)[0] > newInterval[1])
		{
			intervals.insert(iter, newInterval);
			return intervals;
		}
	}
	intervals.push_back(newInterval);

	return intervals;
}

//542
/*
这题的dp办法其实是最最简洁的。对于每个点，值为0距离为0，
值不为0，则值为上下左右点最小的那个加1，我第一遍写的时候其实
想到了这个方法，但是不知道没有计算出来的点如何处理。查资料后
发现可以用两遍扫描法解决问题。

## 第一遍扫描左边和上面的点，取最小值加1
## 第二遍倒过来从右下角开始扫描，取右边和下面点的最小值加1

##易错点:初始化为INT_MAX
##分析：假如一个3*3的矩阵，只有右下角为0，其余为1。在第一遍
		扫描的过程中，[1,1]点左上都是INT_MAX，加1的过程会溢出，
		所以初始化为INT_MAX-1，不用担心溢出，取最小值永远也达不到
		INT_MAX

*/
//执行用时 :256 ms, 在所有 C++ 提交中击败了96.91% 的用户
//内存消耗:20.7 MB, 在所有 C++ 提交中击败了97.31 % 的用户
vector<vector<int>> Solution::updateMatrix(vector<vector<int>>& matrix) {
	int m = matrix.size(), n = matrix[0].size();
	vector<vector<int>> res = matrix;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (res[i][j]) res[i][j] = INT_MAX - 1;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (res[i][j]) {
				if (i > 0) res[i][j] = min(res[i][j], res[i - 1][j] + 1);
				if (j > 0) res[i][j] = min(res[i][j], res[i][j - 1] + 1);
			}
		}
	}
	for (int i = m - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			if (res[i][j]) {
				if (i < m - 1) res[i][j] = min(res[i][j], res[i + 1][j] + 1);
				if (j < n - 1) res[i][j] = min(res[i][j], res[i][j + 1] + 1);
			}
		}
	}
	return res;
}