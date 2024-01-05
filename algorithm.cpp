#include<string>
#include <iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<unordered_map>
#include <deque>
#include <unordered_set>
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

class Solution {
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
};

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

/* 第25题 
*/

class Solution {//数组
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
		int hash[1005] = { 0 }; // 默认数值为0
		for (int num : nums1) { // nums1中出现的字母在hash数组中做记录
			hash[num] = 1;
		}
		for (int num : nums2) { // nums2中出现话，result记录
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
		unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
		unordered_set<int> nums_set(nums1.begin(), nums1.end());
		for (int num : nums2) {
			// 发现nums2的元素 在nums_set里又出现过
			if (nums_set.find(num) != nums_set.end()) {
				result_set.insert(num);
			}
		}
		return vector<int>(result_set.begin(), result_set.end());
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

