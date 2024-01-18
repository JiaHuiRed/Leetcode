#include<string>
#include <iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<unordered_map>
#include <deque>
#include <unordered_set>
#include<stack>
#include<queue>
using namespace std;
//#pragma warning(disable:4996)
//#define _CRT_SECURE_NO_WARNINGS


/*第一题 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target ，
写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。*/

class Solution {//二分查找思想
public:
	int search(vector<int>& nums, int target) {//引用一个名叫nums的整型容器 
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right) {//只要循环条件满足
			//int middle = left+((right-left) / 2);//防止溢出，实际上就是 (right+left)/2
			int middle = (right + left) / 2;//整型数据不用考虑溢出精度
			int num = nums[middle];
			if (num > target) {//寻找元素比中间数小，也就是在左半区间寻找
				right = middle - 1;
			}else if (nums[middle] < target) {
				left = middle + 1;
			}else{
				return middle;
			}
		}
		return -1;//失败返回-1
	}
};
/*第二题 给你一个数组 nums 。数组「动态和」的计算公式为：runningSum[i] = sum(nums[0]…nums[i]) 
请返回 nums 的动态和*/
class Solution {
public:
	vector<int> runningSum(vector<int>& nums) {
		int n = nums.size();
		for (int i=1;i < nums.size();i++) {
			nums[i] += nums[i - 1];
		}
	}
};
/*第三题 给你一个整数 n ，找出从 1 到 n 各个整数的 Fizz Buzz 表示，并用字符串数组 answer（下标从 1 开始）返回结果，其中：
answer[i] == "FizzBuzz" 如果 i 同时是 3 和 5 的倍数。
answer[i] == "Fizz" 如果 i 是 3 的倍数。
answer[i] == "Buzz" 如果 i 是 5 的倍数。
answer[i] == i （以字符串形式）如果上述条件全不满足。
*/

class Solution {
public:
	vector<string> fizzBuzz(int n) {
		vector<string> answer;//定义一个string类型的容器叫answer
		for (int i = 1; i <= n; i++) {
			string curr;
			if (i % 3 == 0) {
				curr += "Fizz";
			}
			if (i % 5 == 0) {
				curr += "Buzz";
			}
			if (curr.size() == 0) {  // 如果curr字符串的长度为0，说明它既不是Fizz也不是Buzz，则在curr字符串后面添加当前整数i的字符串表示。
				curr += to_string(i);
			}
			answer.emplace_back(curr);//构造一个对象，并将其直接添加到 vector 的末尾
		}
		return answer;
	}
};

/*第四题 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为 O(log n) 的算法。
*/
class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right) {
			int middle = (left + right) / 2;
			int n = nums[middle];
			if (n >= target) {
				right = middle - 1;
			}else {
				left = middle + 1;
			}
		}
		return left;
	}
};

/*第五题 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。
请你找出给定目标值在数组中的开始位置和结束位置。如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
*/
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int leftBorder = GetLeftBorder(nums, target);//寻找左边界
		int rightBorder = GetRightBorder(nums, target);//寻找右边界
		if (leftBorder == -2 || rightBorder == -2) return { -1, -1 };
		if (rightBorder - leftBorder > 1) return { leftBorder + 1, rightBorder - 1 };
		return { -1, -1 };
	}
private:
	int GetRightBorder(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		int rightBorder = -2; // 记录一下rightBorder没有被赋值的情况
		while (left <= right) {
			int middle = (right + left) / 2;
			int n = nums[middle];
			if (n> target) {
				right = middle - 1;
			}
			else { // 寻找右边界，nums[middle] == target的时候更新left
				left = middle + 1;
				rightBorder = left;
			}
		}
		return rightBorder;
	}
	int GetLeftBorder(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		int leftBorder = -2; // 记录一下leftBorder没有被赋值的情况
		while (left <= right) {
			int middle = (right + left) / 2;
			int n = nums[middle];
			if (n >= target) { // 寻找左边界，nums[middle] == target的时候更新right
				right = middle - 1;
				leftBorder = right;
			}
			else {
				left = middle + 1;
			}
		}
		return leftBorder;
	}
};
//第六题 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
/*struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int x) : data(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : data(x), next(next) {}
};
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		ListNode* dummy = new ListNode(-1), *p= dummy;//定义一个哑结点
		ListNode* p1 = list1, * p2 = list2;
		while (p1 != NULL && p2 != NULL) {
			if (p1->data > p2->data) {
				p->next = p2;
				p2= p2->next;
			}else {
				p -> next = p1;
				p1 = p1->next;
			}
			p = p->next;//p不断前进
		}
		if (p1 != NULL) {
			p->next = p1;
		}
		if (p2 != NULL) {
			p->next = p2;
		}
		return dummy->next;
	}
};*/
/*第七题 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x** 0.5 。*/

class Solution {//使用exp指数函数
public:
	int mySqrt(int x) {
		if (x <= 0) return 0;
		int ans = exp(0.5 * log(x));
		return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
	}
};
//二分查找
class Solution {
public:
	int mySqrt(int x) {
		int left = 0, right = x, ans = -1;
		while (left <= right) {
			int middle = left + (right - left) / 2;
			if ((long long)middle * middle <= x) {
				ans = middle;
				left = middle + 1;
			}
			else {
				right = middle - 1;
			}
		}
		return ans;
	}
};
/*第八题 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。*/

class Solution {//暴力解法
public:
	int removeElement(vector<int>& nums, int val) {
		int n = nums.size();
		for (int i = 0;i < n;i++) {
			if (nums[i] == val) {
				for (int j = i + 1;j < n;j++) {
					nums[j - 1] = nums[j];
				}
				i--;//因为实际上i后面的元素都往前一位，原本i位置已经是新元素，如果直接for i++，会漏元素
				n--;//相当于删除了一个数组数组，总数-1；
			}
		}
		return n;
	}
};
class Solution {//快慢指针
public:
	int removeElement(vector<int>& nums, int val) {
		int leftIndex = 0;
		int rightIndex = nums.size() - 1;
		while (leftIndex <= rightIndex) {
			// 找左边等于val的元素
			while (leftIndex <= rightIndex && nums[leftIndex] != val) {
				++leftIndex;
			}
			// 找右边不等于val的元素
			while (leftIndex <= rightIndex && nums[rightIndex] == val) {
				--rightIndex;
			}
			// 将右边不等于val的元素覆盖左边等于val的元素
			if (leftIndex < rightIndex) {
				nums[leftIndex++] = nums[rightIndex--];
			}
		}
		return leftIndex;   // leftIndex一定指向了最终数组末尾的下一个元素
	}
};
/*第九题 给你一个非严格递增排列的数组nums ，请你原地删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的相对顺序应该保持一致 。
然后返回 nums 中唯一元素的个数。考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：
更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。
返回 k 。*/

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0) {
			return 0;
		}
		int slow = 0,fast = 0;
		while (fast < nums.size()) {//找不重复的元素赋值 思路变通一下
			if (nums[fast] != nums[slow]) {
				slow++;//维护nums[0...slow]无重复
				nums[slow] = nums[fast];
			}
			fast++;
		}
		return slow + 1;
	}
};

//第十题 给你一个按 非递减顺序 排序的整数数组 nums，返回每个数字的平方组成的新数组，要求也按非递减顺序 排序。

class Solution {//暴力解法
public:
	vector<int> sortedSquares(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0;i < n;i++) {
			nums[i] = nums[i] * nums[i];
		}
		sort(nums.begin(), nums.end());//快排
		return nums;
	}
};
//双指针
class Solution {
public:
	vector<int>sortedSquares(vector<int>& nums) {
		int i=0,k = nums.size()-1,j=nums.size()-1;
		vector<int>result(nums.size(), 0);//构造一个整型容器，长度为nums.size，初始为0；
		for (;i <= j;) {
			if (nums[i] * nums[i] <= nums[j] * nums[j]) {
				result[k--] = nums[i] * nums[i];//考虑按序排列，最大值只可能出现在首部或尾部，所以从后往前排
				j--;
			}
			else {
				result[k--] = nums[j] * nums[j];
				i++;
			}
		}
		return result;
	}
};

//第十一题 给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 
/*
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr) {
			return head;
		}
		ListNode* slow = head, * fast = head->next;
		while (fast != nullptr) {
			if (slow->data != fast->data) {
				slow = slow->next;
				fast = fast->next;

			}else {
				fast = fast->next;
				slow->next = fast;
			}
		}
		return head;
	}
};

//第十二题 给定一个含有n个正整数的数组和一个正整数 target 。找出该数组中满足其总和大于等于 target 的长度最小的 连续子数组[numsl
// numsl + 1, ..., numsr - 1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

class Solution {//滑动窗口
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		int left = 0,right = 0, sum = 0;
		int result = INT32_MAX;
		for (; right < nums.size(); right++) {
			sum += nums[right];
			while (sum >= target) {
				result = min(result, right - left + 1);
				sum -= nums[left++];
			}
		}

		return (result == INT32_MAX) ? 0 : result;
	}
};*/

/* 第十三题 给你一个正整数 n ，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
*/

class Solution {
public:
	vector<vector<int>>generateMatrix(int n) {
		vector<vector<int>>result(n, vector<int>(n, 0));
		int horx = 0, very = 0;//定义横竖坐标
		int loop = n / 2;//定义旋转圈数，如n=3，3*3=9，只需转一圈，单独处理中间的值
		int mid = n / 2;//中间值
		int count = 1,offset=1;//count用来赋值，offset用来控制螺旋排列时的长度
		while (loop--) {
			int i = horx;
			int j = very;
			//循环模拟转圈赋值
			for (;j < n - offset;j++) {//第一次，每列赋值
				result[horx][j] = count++;
			}
			for (;i < n - offset;i++) {//最外列往下赋值
				result[i][j] = count++;
			}
			for (;j > very;j--) {//最下行从右往左赋值
				result[i][j] = count++;
			}
			// 最左列从下到上赋值
			for (; i > horx; i--) {
				result[i][j] = count++;
			}
			horx++;very++;
			offset += 1;
		}
		//如果n为奇数，则处理中心点
		if (n % 2 == 1) {
			result[mid][mid] = count;
		}
		return result;
	}
};

/* 第十四题 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
*/

class Solution {//哈希表
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int>hash;//哈希表用法
		int n = nums.size();
		for (int i = 0;i < n;i++) {
			int complement = target - nums[i];
			if (hash.count(complement)) {//如果哈希表中存在这个数
				return vector<int>{hash[complement], i};
			}
			hash[nums[i]] = i;//将i的值送入哈希表，避免下次重复出现
		}
		return vector<int>();
	}
};

/* 第十五题 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
*/

class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		int m = matrix.size(), n = matrix[0].size();//m定义行数，n定义第一行的列数，实际等于整个矩阵的列数
		int upper_bound = 0, lower_bound = m - 1;//确定边界
		int left_bound = 0, right_bound = n - 1;
		vector<int> res;
		// res.size() == m * n 则遍历完整个数组
		while (res.size() < m * n) {
			if (upper_bound <= lower_bound) {
				// 在顶部从左向右遍历
				for (int j = left_bound; j <= right_bound; j++) {
					res.push_back(matrix[upper_bound][j]);//在末尾添加一个新元素
				}
				// 上边界下移
				upper_bound++;
			}
			if (left_bound <= right_bound) {
				// 在右侧从上向下遍历
				for (int i = upper_bound; i <= lower_bound; i++) {
					res.push_back(matrix[i][right_bound]);
				}
				// 右边界左移
				right_bound--;
			}
			if (upper_bound <= lower_bound) {
				// 在底部从右向左遍历
				for (int j = right_bound; j >= left_bound; j--) {
					res.push_back(matrix[lower_bound][j]);
				}
				// 下边界上移
				lower_bound--;
			}
			if (left_bound <= right_bound) {
				// 在左侧从下向上遍历
				for (int i = lower_bound; i >= upper_bound; i--) {
					res.push_back(matrix[i][left_bound]);
				}
				// 左边界右移
				left_bound++;
			}
		}
		return res;
	}
};

//第十六题 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。

class Solution {
public:
	int search(vector<int>& nums, int target) {
		int left = 0,right=nums.size()-1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (target > nums[mid]) {
				left = mid + 1;
			}else if(target<nums[mid]) {
				right = mid - 1;
			}else {
				return mid;
			}
		}
		return -1;
	}
};

/*第十七题 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。*/

/*class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		sort(nums.begin(), nums.end());
		int slow = 0, fast = 0;
		while (fast<nums.size()) {
			if (nums[fast] != val) {
				nums[slow++] = nums[fast++];
			}
			else {
				fast++;
			}
		}
		return slow;
	}
};*/

//第十八题 给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
/*
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		//删除的是头结点
		while (head != NULL && head->data == val) {
			ListNode* temp = head;
			head = head->next;
			delete temp;
		}
		//删除非头结点
		ListNode* p = head;
		while (p != NULL && p->next != NULL) {
			if (p->next->data == val) {
				ListNode* temp = p->next;
				p->next = p->next->next;
				delete temp;
			}else {
				p = p->next;
			}
		}
		return head;
	}
};*/

/* 你可以选择使用单链表或者双链表，设计并实现自己的链表。
单链表中的节点应该具备两个属性：val 和 next 。val 是当前节点的值，next 是指向下一个节点的指针/引用。
如果是双向链表，则还需要属性 prev 以指示链表中的上一个节点。假设链表中的所有节点下标从 0 开始。
实现 MyLinkedList 类：*/

/*class MyLinkedList {
public:
	struct ListNode {
		int val;
		ListNode* next;
		ListNode(int val) :val(val), next(nullptr) {}//构造函数
	};

	MyLinkedList() {
		this->size = 0;//this表示对当前对象的引用
		this->head = new ListNode(0);
	}

	int get(int index) {
		if (index < 0 || index >= size) {
			return -1;
		}
		ListNode* cur = head;
		for (int i = 0; i <= index; i++) {
			cur = cur->next;
		}
		return cur->val;
	}

	void addAtHead(int val) {
		addAtIndex(0, val);
	}

	void addAtTail(int val) {
		addAtIndex(size, val);
	}

	void addAtIndex(int index, int val) {
		if (index > size) {
			return;
		}
		index = max(0, index);
		size++;
		ListNode* pred = head;
		for (int i = 0; i < index; i++) {
			pred = pred->next;
		}
		ListNode* toAdd = new ListNode(val);
		toAdd->next = pred->next;
		pred->next = toAdd;
	}

	void deleteAtIndex(int index) {
		if (index < 0 || index >= size) {
			return;
		}
		size--;
		ListNode* pred = head;
		for (int i = 0; i < index; i++) {
			pred = pred->next;
		}
		ListNode* p = pred->next;
		pred->next = pred->next->next;
		delete p;
	}
private://私有类定义
	int size;
	ListNode* head;
};*/

struct ListNode {//完整链表写法
     int val;
     ListNode *next;
    // ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     //ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
//第十九题 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

/*class Solution {//链表逆置
public:
  ListNode* reverseList(ListNode* head) {
	  ListNode* p = nullptr; // 前一个节点
	  ListNode* curr = head;    // 当前节点
	  while (curr != nullptr) {
		  ListNode* Temp = curr->next; // 临时节点，用于保存下一个节点
		  curr->next = p; // 将当前节点的 next 指针指向前一个节点，实现逆置
		  p = curr; // 前一个节点向后移动
		  curr = Temp; // 当前节点向后移动
	  }
	  return p; // 当循环结束时，prev 将指向新的头节点
  }

};*/

//第二十题 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

/*class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		ListNode* dummyHead = new ListNode(0);//定义哑结点
		dummyHead->next = head;
		ListNode* curr = dummyHead;
		while (curr->next != nullptr && curr->next->next != nullptr) {
			ListNode* temp = curr->next;
			ListNode* p = curr->next->next->next;
			curr->next = curr->next->next;    // 步骤一
			curr->next->next = temp;          // 步骤二
			curr->next->next->next = p;   // 步骤三
			curr = curr->next->next; // cur移动两位，准备下一轮交换
		}
		return dummyHead->next;
	}
};*/

//第21题 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
/*class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* dummyhead = new ListNode(0);
		dummyhead->next = head;
		ListNode* p = dummyhead;
		ListNode* q = dummyhead;
		int count = 0;
		while (p != nullptr) {
			p = p->next;
			count++;
		}
		p = head;
		if (count < n) {
			return dummyhead;
		}
		else if (count == n) {
			p = p->next;
			dummyhead->next = p;
			return dummyhead;
		}
		else {

			for (int i = 0;i < n;i++) {
				p = p->next;
			}
			while (p != nullptr) {
				p = p->next;
				q = q->next;
			}
			ListNode* temp = q->next;
			q->next = temp->next;
			delete temp;
			return dummyhead->next;
		}
	}
};*/

//第22题 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null 。
/*
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		ListNode* currA = headA;
		ListNode* currB = headB;
		int lenA = 0, lenB = 0;
		while (currA != nullptr) {
			lenA++;
			currA = currA->next;
		}
		while (currB != nullptr) {
			lenB++;
			currB = currB->next;
		}
		currA = headA;
		currB = headB;
		if (lenA > lenB) {
			for (int i = 0; i < lenA - lenB; i++) {
				currA = currA->next;
			}
		}else {
			for (int i = 0; i < lenB - lenA; i++) {
				currB = currB->next;
			}
		}
		// 同时遍历两个链表，直到找到相交节点
		while (currA != nullptr && currB != nullptr) {
			if (currA == currB) {
				return currA;
			}
			currA = currA->next;
			currB = currB->next;
		}
		// 如果没有相交节点，返回nullptr
		return nullptr;
	}
};*/

/* 第23题 给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。
注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
不允许修改 链表。
*/
/*
class Solution {//快慢指针
public:
	ListNode* detectCycle(ListNode* head) {
		ListNode* fast = head;
		ListNode* slow = head;
		while (fast!=nullptr&&fast->next!=nullptr) {
			fast = fast->next->next;
			slow = slow->next;
			if (slow == fast) {
				ListNode* index1 = fast;
				ListNode* index2 = head;
				while (index1 != index2) {//可以画个图理解，从相遇结点和头结点分别出发，相遇点即是环的入口点
					index1 = index1->next;
					index2 = index2->next;
				}
				return index2;
			}
		}
		return nullptr;
	}
};*/

//哈希表
/* 第24题  给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。
输入: s = "anagram", t = "nagaram"
输出: true*/

class Solution {
public:
	bool isAnagram(string s, string t) {
		int record[26] = { 0 };
		for (int i = 0;i < s.size();i++) {
			record[s[i] - 'a']++;//记录字符在数组内的相对位置
		}
		for (int i = 0;i < t.size();i++) {
			record[t[i] - 'a']--;
		}
		for (int i = 0;i < 26;i++) {
			if (record[i] != 0) {
				return false;
			}
		}
		return true;
	}
};

/* 第25题 给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
*/

class Solution {//数组
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		unordered_set<int> result_set;// 存放结果，之所以用set是为了给结果集去重
		int hash[1005] = { 0 }; // 默认数值为0
		for (int num : nums1) { // nums1中出现的元素在hash数组中做记录
			hash[num] = 1;
		}
		for (int num : nums2) { // nums2中出现的话，result记录
			if (hash[num] == 1) {
				result_set.insert(num);
			}
		}
		return vector<int>(result_set.begin(), result_set.end());
	}
};

class Solution {//set
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		unordered_set<int> 
			result_set; // 存放结果，之所以用set是为了给结果集去重
		unordered_set<int> nums_set(nums1.begin(), nums1.end());//将num1的元素放入该set
		for (int num : nums2) {
			// 发现nums2的元素 在nums_set里又出现过
			if (nums_set.find(num) != nums_set.end()) {//如果num2的元素在nums_set中出现过，将返回一个num的set，而不是返回nums_set
				result_set.insert(num);//!=即为交集元素，将该元素插入result_set
			}
		}
		return vector<int>(result_set.begin(), result_set.end());
	}
};

/*第 26题 编写一个算法来判断一个数 n 是不是快乐数。
「快乐数」 定义为：
对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
如果这个过程 结果为 1，那么这个数就是快乐数。
如果 n 是 快乐数 就返回 true ；不是，则返回 false 。
*/

class Solution {
public:
	int getSum(int n) {
		//先算各数位上之和
		int sum = 0;
		while (n) {
			sum += (n % 10) * (n % 10);
			n /= 10;
		}
		return sum;
	}
	bool isHappy(int n) {
		unordered_set<int> set;
		while (1) {//跳出循环
			int sum = getSum(n);
			if (sum == 1) {
				return true;
			}
			if (set.find(sum) != set.end()) {//跟25题一样 !=才是在set中有重复元素
				return false;
			}else {
				set.insert(sum);
			}
			n = sum;
		}
	}
};

/* 第27题 给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，请你计算有多少个元组 (i, j, k, l) 能满足：
0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
*/

class Solution {
public:
	int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
		unordered_map<int, int> umap; //key:a+b的数值，value:a+b数值出现的次数
		// 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中
		for (int a : A) {
			for (int b : B) {
				umap[a + b]++;
			}
		}
		int count = 0; // 统计a+b+c+d = 0 出现的次数
		// 在遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就把map中key对应的value也就是出现次数统计出来。
		for (int c : C) {
			for (int d : D) {
				if (umap.find(0 - (c + d)) != umap.end()) {//跟上述一样 .find!=end
					count += umap[0 - (c + d)];
				}
			}
		}
		return count;
	}
};

/*第28题 给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。
如果可以，返回 true ；否则返回 false 。
magazine 中的每个字符只能在 ransomNote 中使用一次。
*/

class Solution {
public:
	bool canConstruct(string ransomNote, string magazine) {
		int record[26] = { 0 };
		//add
		if (ransomNote.size() > magazine.size()) {
			return false;
		}
		for (int i = 0; i < magazine.length(); i++) {
			// 通过record数据记录 magazine里各个字符出现次数
			record[magazine[i] - 'a'] ++;
		}
		for (int j = 0; j < ransomNote.length(); j++) {
			// 遍历ransomNote，在record里对应的字符个数做--操作
			record[ransomNote[j] - 'a']--;
			// 如果小于零说明ransomNote里出现的字符，magazine没有
			if (record[ransomNote[j] - 'a'] < 0) {
				return false;
			}
		}
		return true;
	}
};


/*第29题 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
同时还满足 nums[i] + nums[j] + nums[k] == 0 。
请你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。
*/

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());//排序之后 所有可能的重复元素都会集中在一起
		// 找出a + b + c = 0
		// a = nums[i], b = nums[left], c = nums[right]
		for (int i = 0; i < nums.size(); i++) {
			// 排序之后如果第一个元素已经大于零，那么无论如何组合都不可能凑成三元组，直接返回结果就可以了
			if (nums[i] > 0) {
				return result;
			}
			// 错误去重a方法，将会漏掉-1,-1,2 这种情况
			/*
			if (nums[i] == nums[i + 1]) {
				continue;
			}
			*/
			// 正确去重a方法
			if (i > 0 && nums[i] == nums[i - 1]) {//因为不符合题设条件
				continue;//提前结束本次迭代，并开始下一次迭代。
			}
			int left = i + 1;
			int right = nums.size() - 1;
			while (right > left) {
				// 去重复逻辑如果放在这里，0，0，0 的情况，可能直接导致 right<=left 了，从而漏掉了 0,0,0 这种三元组
				/*
				while (right > left && nums[right] == nums[right - 1]) right--;
				while (right > left && nums[left] == nums[left + 1]) left++;
				*/
				if (nums[i] + nums[left] + nums[right] > 0) right--;
				else if (nums[i] + nums[left] + nums[right] < 0) left++;
				else {
					result.push_back(vector<int>{nums[i], nums[left], nums[right]});//push_back是在数组末尾添加元素
					// 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
					while (right > left && nums[right] == nums[right - 1]) right--;
					while (right > left && nums[left] == nums[left + 1]) left++;

					// 找到答案时，双指针同时收缩
					right--;
					left++;
				}
			}

		}
		return result;
	}
};

/*第30题 给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。
请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：
0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。
*/

class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int> > res_list;
		if (nums.size() < 4) {
			return res_list;
		}
		sort(nums.begin(), nums.end());
		int len = nums.size();
		for (int i = 0; i < len - 3; ++i) {
			if (i > 0 && nums[i] == nums[i - 1]) {
				continue;
			}
			/*
			Since we sort the nums first, the smallest 4 numbers have to be less than target,
			or there has no quadruplets that can
			*/
			if ((long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
				break;
			}//不满足条件
			if ((long)nums[i] + nums[len - 3] + nums[len - 2] + nums[len - 1] < target) {
				continue;
			}//去重
			for (int j = i + 1; j < len - 2; j++) {
				if (j > i + 1 && nums[j] == nums[j - 1]) {
					continue;
				}
				if ((long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
					break;
				}
				if ((long)nums[i] + nums[j] + nums[len - 2] + nums[len - 1] < target) {
					continue;
				}
				int left = j + 1, right = len - 1;
				while (left < right) {
					long sum = (long)nums[i] + nums[j] + nums[left] + nums[right];
					if (sum == target) {
						res_list.push_back({ nums[i], nums[j], nums[left], nums[right] });
						while (left < right && nums[left] == nums[left + 1]) {
							left++;
						}
						left++;
						while (left < right && nums[right] == nums[right - 1]) {
							right--;
						}
						right--;
					}
					else if (sum < target) {
						left++;
					}
					else {
						right--;
					}
				}
			}
		}
		return res_list;
	}
};

//字符串部分 
/* 第31题 编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s 的形式给出。
不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题
*/


class Solution {
public:
	void reverseString(vector<char>& s) {
		int left = 0, right = s.size() - 1;
		while (left <= right) {
			swap(s[left], s[right]);
			left++;
			right--;
		}
	}
};

/* 第32题 给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符。
如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
*/

class Solution {
public:
	string reverseStr(string s, int k) {
		for (int i = 0; i < s.size(); i += (2 * k)) {
			// 1. 每隔 2k 个字符的前 k 个字符进行反转
			// 2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
			if (i + k <= s.size()) {
				reverse(s.begin() + i, s.begin() + i + k);
			}
			else {
				// 3. 剩余字符少于 k 个，则将剩余字符全部反转。
				reverse(s.begin() + i, s.end());
			}
		}
		return s;
	}
};

/*第33题 给你一个字符串 s ，请你反转字符串中 单词 的顺序。
单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
*/

class Solution {
public:
	void reverse(string& s, int start, int end) {
		for (int i = start, j = end;i < j;i++, j--) {
			swap(s[i], s[j]);
		}
	}
	void removeExtraSpaces(string& s) {//去除前后多余空格
		int slow = 0;
		for (int i = 0;i < s.size();++i) {
			if (s[i] != ' ') {
				if (slow != 0) {
					s[slow++] = ' ';
				}
				while (i < s.size() && s[i] != ' ') {
					s[slow++] = s[i++];
				}
			}
		}
		s.resize(slow);//resize用来调整数组大小
	}
	string reverseWords(string s) {
		removeExtraSpaces(s);//去除多余空格
		reverse(s, 0, s.size() - 1);
		int start = 0;
		for (int i = 0;i <= s.size();++i) {
			if (i != s.size() || s[i] != ' ') {
				reverse(s, start, i - 1);
				start = i + 1;
			}
			
		}
		return s;
	}
};


/*第34题 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。
如果 needle 不是 haystack 的一部分，则返回  -1 。
*/

class Solution {//KMP
public:
	void getNext(int* next, const string& s) {
		int j = -1;
		next[0] = j;
		for (int i = 1; i < s.size(); i++) { // 注意i从1开始
			while (j >= 0 && s[i] != s[j + 1]) { // 前后缀不相同了
				j = next[j]; // 向前回退
			}
			if (s[i] == s[j + 1]) { // 找到相同的前后缀
				j++;
			}
			next[i] = j; // 将j（前缀的长度）赋给next[i]
		}
	}
	int strStr(string haystack, string needle) {
		if (needle.size() == 0) {
			return 0;
		}
		//int next[needle.size()];
		int* next = new int[needle.size()];//更安全，更易于管理内存。在使用动态分配的数组时，始终记得在使用完毕后释放内存。
		getNext(next, needle);
		int j = -1; // // 因为next数组里记录的起始位置为-1
		for (int i = 0; i < haystack.size(); i++) { // 注意i就从0开始
			while (j >= 0 && haystack[i] != needle[j + 1]) { // 不匹配
				j = next[j]; // j 寻找之前匹配的位置
			}
			if (haystack[i] == needle[j + 1]) { // 匹配，j和i同时向后移动
				j++; // i的增加在for循环里
			}
			if (j == (needle.size() - 1)) { // 文本串s里出现了模式串t
				return (i - needle.size() + 1);
			}
		}
		delete[] next;//释放内存
		return -1;
	}
};

/*第35题 请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
实现 MyQueue 类：
void push(int x) 将元素 x 推到队列的末尾
int pop() 从队列的开头移除并返回元素
int peek() 返回队列开头的元素
boolean empty() 如果队列为空，返回 true ；否则，返回 false
*/

class MyQueue {
public:
	stack<int>Sin;//构造栈的写法
	stack<int>Sout;
	MyQueue() {

	}

	void push(int x) {//入栈就是简单地在Sin中入栈
		Sin.push(x);
	}

	int pop() {
		//只有Sout为空时，才能从Sin中导入数据(全部) 因为出栈要从Sout出
		if (Sout.empty()) {
			while (!Sin.empty()) {
				Sout.push(Sin.top());//送入Sin的元素
				Sin.pop();
			}
		}
		int result = Sout.top();
		Sout.pop();
		return result;
	}

	int peek() {//查看函数
		int res = this->pop();//直接使用已有的pop函数
		Sout.push(res);//因为pop弹出了res，所以再添加回去
		return res;
	}

	bool empty() {
		return Sin.empty() && Sout.empty();
	}
};

/*第36题 请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。
实现 MyStack 类：
void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 
*/

class MyStack {
public:
	queue<int> que;//队列构造写法
	/** Initialize your data structure here. */
	MyStack() {

	}
	/** Push element x onto stack. */
	void push(int x) {
		que.push(x);
	}
	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int size = que.size();
		size--;
		while (size--) { // 将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部
			que.push(que.front());
			que.pop();
		}
		int result = que.front(); // 此时弹出的元素顺序就是栈的顺序了
		que.pop();
		return result;
	}

	/** Get the top element. */
	int top() {
		return que.back();
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return que.empty();
	}
};
/*//旋转函数
struct Color {
	int r;
	int g;
	int b;
};
class Rotate {
public:
	// 旋转函数
	Color* RotatePic90(int width, int height, Color input[]) {
		Color* rotated = new Color[height * width]; // 分配内存
		int centerX = width / 2;
		int centerY = height / 2;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				int new_x = centerY - (x - centerX);
				int new_y = centerY + (y - centerY);
				// 确保旋转后的坐标没有越界
				if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
					rotated[new_y * width + new_x] = input[y * width + x];
				}
			}
		}
		return rotated;
	}
};

int main(int argc,char const*argv[]) {
	// 初始化图像数据，这里只是一个示例，实际应用中应该从文件等来源获取
	Color input[400] = {
		// ... 图像数据初始化
	};
	// 创建Reverse类的实例
	Rotate* rev = new Rotate();
	// 调用旋转函数
	Color* rotated = rev->RotatePic90(20, 20, input);
	// 输出旋转后的图像数据以验证
	for (int i = 0; i < 400; ++i) {
		std::cout << "Color(" << rotated[i].r << ", " << rotated[i].g << ", " << rotated[i].b << ")" << std::endl;
	}
	// 释放内存
	delete[] rotated;
	delete rev;
	return 0;
}*/

/*第37题 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
有效字符串需满足：
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。
*/

class Solution {
public:
	bool isValid(string s) {
		if (s.size() % 2 != 0) {
			return false;
		}
		stack<char>st;
		for (int i = 0;i < s.size();i++) {
			if (s[i] == '(') {
				st.push(')');
			}else if (s[i] == '{') {
				st.push('}');
			}else if (s[i] == '[') {
				st.push(']');
			}else if (st.empty() || st.top() != s[i]) {
				return false;
			}else {
				st.pop();
			}
		}
		return st.empty();
	}
};

/*第38题 给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
在 S 上反复执行重复项删除操作，直到无法继续删除。
在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
*/

class Solution {
public:
	string removeDuplicates(string s) {
		stack<char>st;
		for (char S : s) {
			if (st.empty() || S != st.top()) {
				st.push(S);
			}else {
				st.pop();
			}
		}
		string result = "";
		while (!st.empty()) {
			result += st.top();
			st.pop();
		}
		reverse(result.begin(), result.end());
		return result;
	}
};

class Solution {
public:
	string removeDuplicates(string s) {
		string result;//将字符串自己当成栈
		for (char S : s) {
			if (result.empty() || result.back() != S) {
				result.push_back(S);//将元素放入result
			}else {
				result.pop_back();
			}
		}
		return result;
	}
};

/*第38题 给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。
请你计算该表达式。返回一个表示表达式值的整数。
注意：
有效的算符为 '+'、'-'、'*' 和 '/' 。
每个操作数（运算对象）都可以是一个整数或者另一个表达式。
两个整数之间的除法总是 向零截断 。
表达式中不含除零运算。
输入是一个根据逆波兰表示法表示的算术表达式。
答案及所有中间计算结果可以用 32 位 整数表示。
*/

class Solution {//即后缀表示法
public:
	int evalRPN(vector<string>& tokens) {
		stack<long long>st;
		for (int i = 0;i < tokens.size();i++) {
			if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
				long long num1 = st.top();
				st.pop();
				long long num2 = st.top();
				st.pop();
				if (tokens[i] == "+") {
					st.push(num2 + num1);
				}if (tokens[i] == "-") {
					st.push(num2 - num1);
				}if (tokens[i] == "*") {
					st.push(num2 * num1);
				}if (tokens[i] == "/") {
					st.push(num2 / num1);
				}
			}else {
					st.push(stoll(tokens[i]));//stoll用于将字符串转换成long long
				}
		}
		int result = st.top();
		st.pop();
		return result;
	}
};

/*第39题 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
返回 滑动窗口中的最大值 
*/

class Solution {
private://私有队列类
	class MyQueue {//用队列实现
	public:
		deque<int>queue;
		void pop(int value) {
			if (!queue.empty() && value == queue.front()) {
				queue.pop_front();//比较要弹出数值是否等于队列出口元素
			}
		}
		void push(int value) {
			while (!queue.empty() && value > queue.back()) {
				queue.pop_back();//如果压栈元素大于入口元素数值，那么弹出尾端数值，保证单调队列
			}
			queue.push_back(value);
		}
		int front() {//查询当前队列最大值 直接返回队列前端
			return queue.front();
		}
	};
public:
	vector<int>masSlidingWindow(vector<int>& nums, int k) {
		MyQueue Q;
		vector<int>result;
		for (int i = 0;i < nums.size();i++) {
			Q.pop(nums[i - k]);//滑动移除窗口最前面元素,一开始小于k时不产生循环
			Q.push(nums[i]);
			result.push_back(Q.front());//记录当前最大值
		}
		return result;
	}
};

/*第40题 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
*/

class Solution {//大数
public:
	//建一个小根堆
	class mycomparison{
	public:
		bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
			return lhs.second > rhs.second;//pair 中的第二个元素将被用作排序的关键字。
		}
	};
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int>map;//map<nums[i],对应出现的次数
		for (int i = 0;i < nums.size();i++) {//统计元素出现的频率
			map[nums[i]]++;
		}
		//对频率排序
		//定义小根堆
		priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison>pri_que;//priority_queue优先级队列就是根堆 标准写法 记一下
		for (unordered_map<int, int>::iterator it = map.begin();it != map.end();it++) {
			pri_que.push(*it);
			if (pri_que.size() > k) {
				pri_que.pop();//如果堆的大小大于k，则队列弹出
			}
		}
		vector<int>result(k);
		for (int i = k - 1;i >= 0;i--) {
			result[i] = pri_que.top().first;
			pri_que.pop();
		}
		return result;
	}
};

//二叉树

/*struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 */
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
};

/*第41题 三大遍历
*/
class Solution {//先序遍历
public:
	vector<int> preorderTraversal(TreeNode* root) {
		stack<TreeNode*>Tree;
		vector<int>result;
		if (root == nullptr) {
			return result;
		}
		Tree.push(root);
		while (!Tree.empty()) {
			TreeNode* node = Tree.top();
			Tree.pop();
			result.push_back(node->val);
			if (node->right) {//进栈根右左，出栈根左右
				Tree.push(node->right);
			}
			if (node->left) {
				Tree.push(node->left);
			}
		}
		return result;
	}
};

class Solution {//迭代法
public:
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			if (node != NULL) {
				st.pop();
				if (node->right) st.push(node->right);  // 右
				if (node->left) st.push(node->left);    // 左
				st.push(node);                          // 中
				st.push(NULL);
			}
			else {
				st.pop();
				node = st.top();
				st.pop();
				result.push_back(node->val);
			}
		}
		return result;
	}
};

class Solution {//中序遍历
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> Tree;
		TreeNode* curr = root;
		while (curr != NULL || !Tree.empty()) {
			if (curr != NULL) { // 指针来访问节点，访问到最底层
				Tree.push(curr); // 将访问的节点放进栈
				curr = curr->left;                // 左
			}
			else {
				curr = Tree.top(); // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
				Tree.pop();
				result.push_back(curr->val);     // 中
				curr = curr->right;               // 右
			}
		}
		return result;
	}
};
class Solution {//迭代法中序遍历
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			if (node != NULL) {
				st.pop(); // 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
				if (node->right) st.push(node->right);  // 添加右节点（空节点不入栈）

				st.push(node);                          // 添加中节点
				st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记。

				if (node->left) st.push(node->left);    // 添加左节点（空节点不入栈）
			}
			else { // 只有遇到空节点的时候，才将下一个节点放进结果集
				st.pop();           // 将空节点弹出
				node = st.top();    // 重新取出栈中元素
				st.pop();
				result.push_back(node->val); // 加入到结果集
			}
		}
		return result;
	}
};

class Solution {//后序遍历
public:
	vector<int>postorderTraversal(TreeNode* root) {
		stack<TreeNode*> Tree;
		vector<int>result;
		if (root == nullptr) {
			return result;
		}
		Tree.push(root);
		while (!Tree.empty()) {
			TreeNode* node = Tree.top();
			Tree.pop();
			result.push_back(node->val);
			if (node->left) {
				Tree.push(node->left);
			}
			if (node->right) {
				Tree.push(node->right);
			}
		}
		reverse(result.begin(), result.end());
		return result;
	}
};

class Solution {//迭代法
public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			if (node != NULL) {
				st.pop();
				st.push(node);                          // 中
				st.push(NULL);

				if (node->right) st.push(node->right);  // 右
				if (node->left) st.push(node->left);    // 左

			}
			else {
				st.pop();
				node = st.top();
				st.pop();
				result.push_back(node->val);
			}
		}
		return result;
	}
};

//第42题 层序遍历


class Solution {
public:
	vector<vector<int>>levelOrder(TreeNode* root) {
		queue<TreeNode*>que;
		if (root != nullptr) {
			que.push(root);
		}
		vector<vector<int >> result;
		while (!que.empty()) {
			int size = que.size();
			vector<int>vec;
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();//最开始即为根结点
				que.pop();
				vec.push_back(node->val);
				if (node->left) {
					que.push(node->left);//层序遍历
				}
				if (node->right) {
					que.push(node->right);
				}
			}
			result.push_back(vec);
		}
		return result;
	}
};

//层序遍历2

class Solution {//从下往上
public:
	vector<vector<int>>levelOrderBottom(TreeNode* root) {
		queue<TreeNode*>que;
		if (root != nullptr) {
			que.push(root);
		}
		vector<vector<int>>result;
		while (!que.empty()) {
			int size = que.size();
			vector<int>vec;
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();
				que.pop();
				vec.push_back(node->val);
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
			}
			result.push_back(vec);
		}
		reverse(result.begin(), result.end());
		return result;
	}
};

//给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		queue<TreeNode*>que;
		if (root != nullptr) {
			que.push(root);
		}
		vector<int>result;
		while (!que.empty()) {
			int size = que.size();//重点在于理解这个size
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();
				que.pop();
				if (i == (size - 1)) {//每层最后一个
					result.push_back(node->val);
				}
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
			}	
		}
		return result;
	}
};

//给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。

class Solution {
public:
	vector<double> averageOfLevels(TreeNode* root) {
		queue<TreeNode*>que;
		if (root != nullptr) {
			que.push(root);
		}
		vector<double>result;
		while (!que.empty()) {
			int size = que.size();
			double sum = 0;
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();
				que.pop();
				sum += node->val;
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
			}
			result.push_back(sum / size);
		}
		return result;
	}
};

/*给定一个 N 叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）。
树的序列化输入是用层序遍历，每组子节点都由 null 值分隔（参见示例）。
*/

/*class Node {//N叉树结点定义
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val) {
		val = _val;
	}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};

class Solution {
public:
	vector<vector<int>> levelOrder(Node* root) {
		queue<Node*>que;
		if (root != nullptr) {
			que.push(root);
		}
		vector<vector<int>>result;
		while (!que.empty()) {
			int size = que.size();
			vector<int>vec;
			for (int i = 0;i < size;i++) {
				Node* node = que.front();
				que.pop();
				vec.push_back(node->val);
				for (int i = 0;i < node->children.size();i++) {
					if (node->children[i]) {//将结点孩子加入队列
						que.push(node->children[i]);
					}
				}
				
			}
			result.push_back(vec);
		}
		return result;
	}
};*/

//给定一棵二叉树的根节点 root ，请找出该二叉树中每一层的最大值。

class Solution {
public:
	vector<int> largestValues(TreeNode* root) {
		queue<TreeNode*>que;
		if (root != nullptr) {
			que.push(root);
		}
		vector<int>result;
		while (!que.empty()) {
			int size = que.size();
			int maxValue = INT_MIN;
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();
				que.pop();
				maxValue = node->val > maxValue ? node->val : maxValue;
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
			}
			result.push_back(maxValue);
		}
		return result;
	}
};

/*给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
初始状态下，所有 next 指针都被设置为 NULL。
*/
/*struct Node {
	int val;
	Node* left;
	Node* right;
	Node* next;
};

class Solution {
public:
	Node* connect(Node* root) {
		queue<Node*>que;
		if (root != nullptr) {
			que.push(root);
		}
		while (!que.empty()) {
			int size = que.size();
			Node* nodePre;
			Node* node;
			for (int i = 0;i < size;i++) {
				if (i == 0) {
					nodePre = que.front();//取出一层的头结点
					que.pop();
					node = nodePre;
				}else {
					node = que.front();
					que.pop();
					nodePre->next = node;
					nodePre = nodePre->next;
				}
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
			}
			nodePre->next = nullptr;
		}
		return root;
	}
};*/

/* 给定一个二叉树：
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。
初始状态下，所有 next 指针都被设置为 NULL 
*/

/*class Solution {
public:
	Node* connect(Node* root) {
		queue<Node*>que;
		if (root != nullptr) {
			que.push(root);
		}
		while (!que.empty()) {
			int size = que.size();
			vector<int>vec;
			Node* nodePre;
			Node* node;
			for (int i = 0;i < size;i++) {
				if (i == 0) {
					nodePre = que.front();
					que.pop();
					node = nodePre;
				}else {
					node = que.front();
					que.pop();
					nodePre->next = node;
					nodePre = nodePre->next;
				}
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
			}
			nodePre->next = nullptr;
		}
		return root;
	}
};*/

//返回二叉树其最大深度。 是指从根节点到最远叶子节点的最长路径上的节点数。

class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		int depth = 0;
		queue<TreeNode*>que;
		que.push(root);
		while (!que.empty()) {
			int size = que.size();
			depth++;
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();
				que.pop();
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
			}
		}
		return depth;
	}
};

//给定一个二叉树，找出其最小深度。

class Solution {
public:
	int minDepth(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		int depth = 0;
		queue<TreeNode*>que;
		que.push(root);
		while (!que.empty()) {
			int size = que.size();
			depth++;
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();
				que.pop();
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
				if (!node->left && !node->right) {
					return depth;
				}
			}
		}
		return depth;
	}
};

//第43题 给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。

class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {//前序遍历实现
		if (root == nullptr) {
			return root;
		}
		swap(root->left, root->right);
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
};

class Solution {//广度优先遍历 层序遍历
public:
	TreeNode* invertTree(TreeNode* root) {
		queue<TreeNode*> que;
		if (root != NULL) que.push(root);
		while (!que.empty()) {
			int size = que.size();
			for (int i = 0; i < size; i++) {
				TreeNode* node = que.front();
				que.pop();
				swap(node->left, node->right); // 节点处理
				if (node->left) que.push(node->left);
				if (node->right) que.push(node->right);
			}
		}
		return root;
	}
};

/*第44题 给你一个二叉树的根节点 root ， 检查它是否轴对称。
*/

class Solution {
public:
	bool compare(TreeNode* left, TreeNode* right) {
		//首先排除空节点情况
		if (left == nullptr && right != nullptr) {
			return false;
		}else if (left != nullptr && right == nullptr) {
			return false;
		}else if (left == nullptr && right == nullptr) {
			return true;
		}else if (left->val != right->val) {
			return false;
		}//排除数值不同的情况
		//剩下的就是左右节点不为空，且数值相同的情况
		bool outside = compare(left->left, right->right);
		bool inside = compare(left->right, right->left);
		bool isSame = outside && inside;
		return isSame;
	}
	bool isSymmetric(TreeNode* root) {
		if (root == nullptr) {
			return true;
		}
		return compare(root->left, root->right);
	}
};

//剪枝
class Solution {
public:
	bool compare(TreeNode*left,TreeNode*right){
		if (left != nullptr && right == nullptr) {
			return false;
		}else if (left == nullptr && right != nullptr) {
			return false;
		}else if (left == nullptr && right == nullptr) {
			return true;
		}else if (left->val != right->val) {
			return false;
		}else {
			return compare(left->left, right->right) && compare(left->right, right->left);
		}
	}
	bool isSymmetric(TreeNode* root) {
		if (root == nullptr) {
			return true;
		}
		return compare(root->left, root->right);
	}
};

/*第45题 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。
如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

*/

class Solution {
public:
	bool compare(TreeNode* p, TreeNode* q) {
		//排除两树有空节点的情况
		if (p == nullptr && q != nullptr) {
			return false;
		}else if (p != nullptr && q == nullptr) {
			return false;
		}else if (p == nullptr && q == nullptr) {
			return true;
		}else if (p->val != q->val) {//开始考虑不是空树的情况
			return false;
		}else {
			return compare(p->left, q->left) && compare(p->right, q->right);
		}
	}
	bool isSameTree(TreeNode* p, TreeNode* q) {
		return compare(p, q);
	}
};

/*第46题 给你两棵二叉树 root 和 subRoot 。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。
如果存在，返回 true ；否则，返回 false 。
二叉树 tree 的一棵子树包括 tree 的某个节点和这个节点的所有后代节点。
tree 也可以看做它自身的一棵子树。
*/

class Solution {
public:
	bool compare(TreeNode* p, TreeNode* q) {//判断两树相同的函数
		//排除两树有空节点的情况
		if (p == nullptr && q != nullptr) {
			return false;
		}
		else if (p != nullptr && q == nullptr) {
			return false;
		}
		else if (p == nullptr && q == nullptr) {
			return true;
		}
		else if (p->val != q->val) {//开始考虑不是空树的情况
			return false;
		}
		else {
			return compare(p->left, q->left) && compare(p->right, q->right);
		}
	}
	bool isSubtree(TreeNode* root, TreeNode* subRoot) {
		if (!root) { //root不可能走到空
			return false;
		}
		if (compare(root, subRoot)) {
			return true;
		}
		return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot); //左边为真就不用求右边了，所以是或关系
	}
};

/*第47题 给定一个 N 叉树，找到其最大深度。
最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。
N 叉树输入按层序遍历序列化表示，每组子节点由空值分隔
*/

/*class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val) {
		val = _val;
	}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};

class Solution {
public:
	int maxDepth(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		int depth = 0;
		for (auto child : root->children) {//int i = 0; i < root->children.size(); i++ auto更现代
			depth = max(depth, maxDepth(child));//root->children[i]
		}
		return depth + 1;
	}
};*/

/* 第48题 给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。
完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。
若最底层为第 h 层，则该层包含 1~ 2h 个节点
*/

class Solution {//层序递归
public:
	int countNodes(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		return 1 + countNodes(root->left) + countNodes(root->right);
	}
};

/* 第49题 给定一个二叉树，判断它是否是高度平衡的二叉树。
*/

class Solution {//比较高度用后序遍历
public:
	//返回以该节点为根节点的二叉树的高度，如果不是返回-1
	int GetHight(TreeNode* node) {
		if (node == nullptr) {
			return 0;
		}
		int leftheight = GetHight(node->left);
		if (leftheight == -1) {
			return -1;
		}
		int rightheight = GetHight(node->right);
		if (rightheight == -1) {
			return -1;
		}
		return abs(leftheight - rightheight) > 1 ? -1 : 1 + max(leftheight, rightheight);
	}
	bool isBalanced(TreeNode* root) {
		return GetHight(root) == -1 ? false : true;
	}
};

//第50题 给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。

class Solution {//前序遍历 有点费劲 理解一下
private:
	void traversal(TreeNode* curr, vector<int>& path, vector<string>& result) {
		path.push_back(curr->val);
		if (curr->left == nullptr && curr->right == nullptr) {
			string sPath;
			for (int i = 0;i < path.size() - 1;i++) {
				sPath += to_string(path[i]);
				sPath += "->";
			}
			sPath += to_string(path[path.size() - 1]);
			result.push_back(sPath);
			return;
		}
		if (curr->left) {
			traversal(curr->left, path, result);
			path.pop_back();//回溯
		}
		if (curr->right) {
			traversal(curr->right, path, result);
			path.pop_back();
		}
	}
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string>result;
		vector<int>path;
		if (root == nullptr) {
			return result;
		}
		traversal(root, path, result);
		return result;
	}
};


class Solution {//剪枝
private:

	void traversal(TreeNode* cur, string path, vector<string>& result) {
		path += to_string(cur->val); // 中
		if (cur->left == NULL && cur->right == NULL) {
			result.push_back(path);
			return;
		}
		if (cur->left) traversal(cur->left, path + "->", result); // 左
		if (cur->right) traversal(cur->right, path + "->", result); // 右
	}

public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> result;
		string path;
		if (root == NULL) return result;
		traversal(root, path, result);
		return result;

	}
};

//第51题 给定二叉树的根节点 root ，返回所有左叶子之和。

class Solution {
public:
	int sumOfLeftLeaves(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		int leftValue = 0;
		if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
			leftValue = root->left->val;
		}
		return leftValue + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
	}
};

/*第52题 给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。
假设二叉树中至少有一个节点。
*/

class Solution {//层序遍历最优解
public:
	int findBottomLeftValue(TreeNode* root) {
		queue<TreeNode*>que;
		if (root != nullptr) {
			que.push(root);
		}
		int result = 0;
		while (!que.empty()) {
			int size = que.size();
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();
				que.pop();
				if (i == 0) {
					result = node->val;
				}
				if (node->left) {
					que.push(node->left);
				}
				if (node->right) {
					que.push(node->right);
				}
			}
		}
		return result;
	}
};

/*第53题 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。
判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。
如果存在，返回 true ；否则，返回 false 。
*/

class Solution {
private:
	bool traversal(TreeNode* curr, int count) {
		if (!curr->left && !curr->right && count == 0) {
			return true;
		}
		if (!curr->left && !curr->right) {
			return false;
		}
		if (curr->left) {
			count -= curr->left->val;
			if (traversal(curr->left, count)) {
				return true;
			}
			count += curr->left->val;
		}
		if (curr->right) {
			count -= curr->right->val;
			if (traversal(curr->right, count)) {
				return true;
			}
			count += curr->right->val;
		}
		return false;
	}
public:
	bool hasPathSum(TreeNode* root, int targetSum) {
		if (root == nullptr) {
			return false;
		}
		return traversal(root, targetSum - root->val);
	}
};

class Solution {//剪枝
public:
	bool hasPathSum(TreeNode* root, int targetSum) {
		if (!root) {
			return false;
		}
		if (!root->left && !root->right && targetSum == root->val) {
			return true;
		}
		return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
	}
};























//寻找元素
/*class Solution {
public:
	int getValue(vector<int>& nums, int n) {//寻找一个可能数量多于一半的主元素
		int i, Major, count = 1;//Major用来保存候选元素
		Major = nums[0];
		for (i = 1;i < n;i++) {
			if (nums[i] == Major) {
				count++;//对数组内元素计数
			}else {
				if (count > 0) {//处理不是主元素的情况
					count--;
				}else {
					Major = nums[i];//更换候选元素，重新计数
					count = 1;
				}
			}
		}
		if (count > 0) {
			for (i = count = 0;i < n;i++) {
				if (nums[i] == Major) {//统计候选元素出现的实际次数
					count++;
				}
			}
		}
		if (count > n / 2) {
			return Major;//确认元素
		}else {
			return 0;//不存在则返回
		}
	}
};//也可以使用计数排序，但是会使用辅助数组，不满足空间尽量小的要求
*/

