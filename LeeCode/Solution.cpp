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

//70 ��¥��
//ִ����ʱ : 0 ms, ��Climbing Stairs��C++�ύ�л�����100.00% ���û�
//�ڴ�����: 8.6 MB, ��Climbing Stairs��C++�ύ�л�����17.59% ���û�
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
//ִ����ʱ : 24 ms, ��Best Time to Buy and Sell Stock��C++�ύ�л�����21.81% ���û�
//�ڴ�����: 10.9 MB, ��Best Time to Buy and Sell Stock��C++�ύ�л�����5.10% ���û�
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
//ִ����ʱ : 12 ms, ��Best Time to Buy and Sell Stock III��C++�ύ�л�����95.07% ���û�
//�ڴ�����: 9.5 MB, ��Best Time to Buy and Sell Stock III��C++�ύ�л�����65.24% ���û�
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
//ִ����ʱ :264 ms, ������ C++ �ύ�л�����17.15% ���û�
//�ڴ�����:9.9 MB, ������ C++ �ύ�л�����83.80 % ���û�
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
//ִ����ʱ :8 ms, ������ C++ �ύ�л�����67.44% ���û�
//�ڴ�����:8.1 MB, ������ C++ �ύ�л�����88.89 % ���û�
bool Solution::reachingPoints(int sx, int sy, int tx, int ty) {
	while (tx > 0 && ty > 0) {//��Ϊsx, sy, tx, ty �Ƿ�Χ�� [1, 10^9] �����������Ʋ��ܳ���
		if (sx == tx && sy == ty) {//�ж��Ƿ񵽴�����ʼֵ
			return true;
		}
		//ÿ������ֻ����tx��ty�нϴ�ֵ��ȥ���ɸ���Сֵ
		if (tx > ty) {//��ʱֻ����tx��ȥty
			//tx - sx��Ŀ������ʼֵ��x�Ĳ�࣬������Ҫһ�μ�ȥn * ty�ﵽ���ٱƽ�sx��Ŀ��
			tx -= max((tx - sx) / ty, 1) * ty;
		}
		else {//��ʱֻ����ty��ȥtx
			//ty - sy��Ŀ������ʼֵ��y�Ĳ�࣬������Ҫһ�μ�ȥn * tx�ﵽ���ٱƽ�sy��Ŀ��
			ty -= max((ty - sy) / tx, 1) * tx;
		}
	}
	return false;
}

//200
//ִ����ʱ : 16 ms, ��Number of Islands��C++�ύ�л�����94.56% ���û�
//�ڴ�����: 10.9 MB, ��Number of Islands��C++�ύ�л�����77.69% ���û�
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
//ִ����ʱ : 8 ms, ��Maximum Gap��C++�ύ�л�����98.69% ���û�
//�ڴ�����: 9.6 MB, ��Maximum Gap��C++�ύ�л�����30.61% ���û�
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
//ִ����ʱ : 252 ms, ��Minimum Moves to Equal Array Elements II��C++�ύ�л�����6.60% ���û�
//�ڴ�����: 10.4 MB, ��Minimum Moves to Equal Array Elements II��C++�ύ�л�����6.38% ���û�
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
//ִ����ʱ : 0 ms, ��Rectangle Overlap��C++�ύ�л�����100.00% ���û�
//�ڴ�����: 8.3 MB, ��Rectangle Overlap��C++�ύ�л�����56.72% ���û�
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
//ִ����ʱ : 128 ms, ��Exclusive Time of Functions��C++�ύ�л�����8.86% ���û�
//�ڴ�����: 20.2 MB, ��Exclusive Time of Functions��C++�ύ�л�����7.69% ���û�
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
//ִ����ʱ :20 ms, ������C++�ύ�л�����86.07%���û�
//�ڴ����� :9.5 MB, ������C++�ύ�л�����42.35%���û�
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
//����ʱ������
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
//ִ����ʱ :40 ms, ������C++�ύ�л�����36.11%���û�
//�ڴ����� :8.2 MB, ������C++�ύ�л�����76.92%���û�
//��m��n�ĳ˷����У�Ѱ�Ҳ�����num��Ԫ�ظ���
int smallNumCount(int num, int m, int n) {
	int count = 0;
	//�Գ˷����ÿһ�У�ÿһ�ж��ǵ���������������muns[row][col] = row * col
	for (int i = 1; i <= m; i++) {
		count += min(num / i, n);//num/i����������numҲ�ڵ�i�У������ڵ���������һ�����ֻ��n��
	}
	return count;
}
int findKthNumber1(int m, int n, int k) {
	//m,n�ĳ˷����У�ȡֵ��ΧΪ[1, m * n],ʹ�ö��ַ�ȷ����k��ֵ
	int low = 1, high = m * n + 1;
	while (low < high) {
		int mid = (low + high) / 2;
		int cnt = smallNumCount(mid, m, n);//����˷����в�����mid��Ԫ�ظ���
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
//ִ����ʱ :0 ms, ������C++�ύ�л�����100.00%���û�
//�ڴ����� :8.1 MB, ������C++�ύ�л�����51.81%���û�
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
//ִ����ʱ :72 ms, ������C++�ύ�л�����85.24% ���û�
//�ڴ�����:15.2 MB, ������C++�ύ�л�����80.04%���û�
void Solution::reverseString(vector<char>& s) {
	int len = s.size();
	for (int i = 0; i < len / 2; i++) {
		s[i] = s[i] ^ s[len - 1 - i];
		s[len - 1 - i] = s[i] ^ s[len - 1 - i];
		s[i] = s[i] ^ s[len - 1 - i];
	}
}

//203
//ִ����ʱ :44 ms, ������C++�ύ�л�����83.34% ���û�
//�ڴ�����:11.3 MB, ������C++�ύ�л�����48.62%���û�
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
//ִ����ʱ :1072 ms, ������C++�ύ�л�����5.01% ���û�
//�ڴ�����:16.7 MB, ������C++�ύ�л�����46.13%���û�
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

//ִ����ʱ :132 ms, ������C++�ύ�л�����13.02% ���û�
//�ڴ�����:16.7 MB, ������C++�ύ�л�����62.85%���û�
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
	ListNode* pA = headA, * pB = headB;
	// �����һ�α���������β������ָ����һ�������ͷ��������������������������Ȳ
	// ���û���ཻ����Ϊ����������ȣ�������NULL == NULL
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
//����ʱ������
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
/*���ʼǡ�������������Ϊ�����±꣬�ö�Ӧ����ֵΪ��ֵ����ô����Ϊ������λ�ü�Ϊ��δ���ֹ�����ʧ�����֡�
�ٸ����ӣ�
	ԭʼ���飺[4,3,2,7,8,2,3,1]

	���ú�Ϊ��[-4,-3,-2,-7,8,2,-3,-1]
���ۣ�[8,2] �ֱ��Ӧ��indexΪ[5,6]����ʧ�����֣�
*/
//ִ����ʱ :140 ms, ������C++�ύ�л�����91.52% ���û�
//�ڴ�����:14.8 MB, ������C++�ύ�л�����86.06%���û�
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
//ִ����ʱ :0 ms, ������C++�ύ�л�����100.00% ���û�
//�ڴ�����:8.7 MB, ������C++�ύ�л�����42.45%���û�
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
//ִ����ʱ :12 ms, ������C++�ύ�л�����90.04% ���û�
//�ڴ�����:10.6 MB, ������C++�ύ�л�����5.55%���û�
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
// ִ����ʱ :8 ms, ������C++�ύ�л�����85.93% ���û�
//�ڴ����� : 8.9 MB, ������C++�ύ�л�����61.30%���û�
int Solution::lengthOfLastWord(string s) {
	if (s.empty()) {
		return 0;
	}

	int length = 0;

	// �ҵ���һ���ǿո��ַ������߱������ַ�����ͷ
	auto iter = s.rbegin();
	while (iter != s.rend() && *iter == ' ') {
		iter++;
	}

	// �����ַ������ǿո��ַ�
	if (iter == s.rend()) {
		return 0;
	}

	// lengthһֱ������ֱ�������ո��ַ������߱������ַ�����ͷ
	while (iter != s.rend() && *iter != ' ') {
		length++;
		iter++;
	}
	return length;
}

//119
//ִ����ʱ :0 ms, ������C++�ύ�л�����100.00% ���û�
//�ڴ�����:8.6 MB, ������C++�ύ�л�����23.83%���û�
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
//ִ����ʱ :4 ms, ������ C++ �ύ�л�����96.01% ���û�
//�ڴ�����:8.5 MB, ������ C++ �ύ�л�����86.79 % ���û�
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
//ִ����ʱ :12 ms, ������ C++ �ύ�л�����62.53% ���û�
//�ڴ�����:8.9 MB, ������ C++ �ύ�л�����93.54 % ���û�
int Solution::strStr(string haystack, string needle) {
	// write your code here 
	if (needle.size() == 0) {
		return 0;
	}
	if (needle.size() > haystack.size()) {
		return -1;
	}
	//needle ָ��
	int j = 0;
	int i = 0;
	for (i = 0; i < haystack.size(); ++i) {
		if (j == needle.size()) {//�ж����
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
	if (j == needle.size()) {//�ж����
		return i - needle.size();
	}
	return -1;
}

//31
//ִ����ʱ :16 ms, ������ C++ �ύ�л�����73.16% ���û�
//�ڴ�����:8.5 MB, ������ C++ �ύ�л�����91.76 % ���û�
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
//ִ����ʱ :0 ms, ������ C++ �ύ�л�����100.00% ���û�
//�ڴ�����:8.8 MB, ������ C++ �ύ�л�����71.51 % ���û�
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
/*�ṩ����˼·��

	hash ��������Ҫ����Ŀռ䡣���г��ֵ����֣�hash ֵ + 1���ڶ��δ� 1 ��ʼ���� hash ���Ҳ����������ˡ��������ַ������������⣬���� hash �����������Ч��Ҳ�������ŵġ�
	����ԭʼ����Ϊ A���ȹ���һ����ʱ���� tmp����ʼ��Ϊ 0����СΪA.size(). ���� A���� A[i] ���Ƶ� tmp[A[i]-1] ��λ�á���� A[i] - 1 ������ tmp �ķ�Χ����ֱ���ӵ������һ����tmp[0...size) �оͱ�����һ���� A ��ֵ��Ȼ���λ�� 0 ��ʼ��� tmp��������ָ�λ�õ�ֵ�������Ų�ƥ�䣬��˵���ҵ���ȱʧ�����ˡ�

ע������ķ���һ��û�취�Ż��� in-place �㷨�����Ƿ��������ԡ������������Բ�ʹ�� tmp ���飬ֱ����ԭʼ�����в�������ÿ�����ŵ���ȷ��λ�á�

����ʹ��һ�� ����λ������" ���ﵽ in-place ��Ŀ�ģ�

	�ӵ�һ��λ�ÿ�ʼ������λ�ϵĳ˿��ߵ��Լ�Ӧ������λ�ã����ø�λ�õ���������һ��λ�á�һֱ���������Ĳ�����ֱ����һ��λ�õ��������Լ�λ�á�������ʱ������֪�����е�����ϲ����Ʊ�������ֹ�������ǣ�һ�����ֵ�һ��λ�õ�����Ʊ��Ʊ�� <= 0���� >= �����λ��)������ֹ������
	�Եڶ���N��λ������ͬ�Ĳ�����
*/
//ִ����ʱ :12 ms, ������ C++ �ύ�л�����26.02% ���û�
//�ڴ�����:8.7 MB, ������ C++ �ύ�л�����76.49 % ���û�
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
//ִ����ʱ :1460 ms, ������ C++ �ύ�л�����5.12% ���û�
//�ڴ�����:12.3 MB, ������ C++ �ύ�л�����5.23 % ���û�
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
//ִ����ʱ :20 ms, ������ C++ �ύ�л�����94.73% ���û�
//�ڴ�����:12.4 MB, ������ C++ �ύ�л�����5.23 % ���û�
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
�����dp�취��ʵ��������ġ�����ÿ���㣬ֵΪ0����Ϊ0��
ֵ��Ϊ0����ֵΪ�������ҵ���С���Ǹ���1���ҵ�һ��д��ʱ����ʵ
�뵽��������������ǲ�֪��û�м�������ĵ���δ��������Ϻ�
���ֿ���������ɨ�跨������⡣

## ��һ��ɨ����ߺ�����ĵ㣬ȡ��Сֵ��1
## �ڶ��鵹���������½ǿ�ʼɨ�裬ȡ�ұߺ���������Сֵ��1

##�״��:��ʼ��ΪINT_MAX
##����������һ��3*3�ľ���ֻ�����½�Ϊ0������Ϊ1���ڵ�һ��
		ɨ��Ĺ����У�[1,1]�����϶���INT_MAX����1�Ĺ��̻������
		���Գ�ʼ��ΪINT_MAX-1�����õ��������ȡ��Сֵ��ԶҲ�ﲻ��
		INT_MAX

*/
//ִ����ʱ :256 ms, ������ C++ �ύ�л�����96.91% ���û�
//�ڴ�����:20.7 MB, ������ C++ �ύ�л�����97.31 % ���û�
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