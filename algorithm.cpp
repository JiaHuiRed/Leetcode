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


/*��һ�� ����һ�� n ��Ԫ������ģ������������� nums ��һ��Ŀ��ֵ target ��
дһ���������� nums �е� target�����Ŀ��ֵ���ڷ����±꣬���򷵻� -1��*/

class Solution {//���ֲ���˼��
public:
	int search(vector<int>& nums, int target) {//����һ������nums���������� 
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right) {//ֻҪѭ����������
			//int middle = left+((right-left) / 2);//��ֹ�����ʵ���Ͼ��� (right+left)/2
			int middle = (right + left) / 2;//�������ݲ��ÿ����������
			int num = nums[middle];
			if (num > target) {//Ѱ��Ԫ�ر��м���С��Ҳ�������������Ѱ��
				right = middle - 1;
			}else if (nums[middle] < target) {
				left = middle + 1;
			}else{
				return middle;
			}
		}
		return -1;//ʧ�ܷ���-1
	}
};
/*�ڶ��� ����һ������ nums �����顸��̬�͡��ļ��㹫ʽΪ��runningSum[i] = sum(nums[0]��nums[i]) 
�뷵�� nums �Ķ�̬��*/
class Solution {
public:
	vector<int> runningSum(vector<int>& nums) {
		int n = nums.size();
		for (int i=1;i < nums.size();i++) {
			nums[i] += nums[i - 1];
		}
	}
};
/*������ ����һ������ n ���ҳ��� 1 �� n ���������� Fizz Buzz ��ʾ�������ַ������� answer���±�� 1 ��ʼ�����ؽ�������У�
answer[i] == "FizzBuzz" ��� i ͬʱ�� 3 �� 5 �ı�����
answer[i] == "Fizz" ��� i �� 3 �ı�����
answer[i] == "Buzz" ��� i �� 5 �ı�����
answer[i] == i �����ַ�����ʽ�������������ȫ�����㡣
*/

class Solution {
public:
	vector<string> fizzBuzz(int n) {
		vector<string> answer;//����һ��string���͵�������answer
		for (int i = 1; i <= n; i++) {
			string curr;
			if (i % 3 == 0) {
				curr += "Fizz";
			}
			if (i % 5 == 0) {
				curr += "Buzz";
			}
			if (curr.size() == 0) {  // ���curr�ַ����ĳ���Ϊ0��˵�����Ȳ���FizzҲ����Buzz������curr�ַ���������ӵ�ǰ����i���ַ�����ʾ��
				curr += to_string(i);
			}
			answer.emplace_back(curr);//����һ�����󣬲�����ֱ����ӵ� vector ��ĩβ
		}
		return answer;
	}
};

/*������ ����һ�����������һ��Ŀ��ֵ�����������ҵ�Ŀ��ֵ�������������������Ŀ��ֵ�������������У����������ᱻ��˳������λ�á�
�����ʹ��ʱ�临�Ӷ�Ϊ O(log n) ���㷨��
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

/*������ ����һ�����շǵݼ�˳�����е��������� nums����һ��Ŀ��ֵ target��
�����ҳ�����Ŀ��ֵ�������еĿ�ʼλ�úͽ���λ�á���������в�����Ŀ��ֵ target������ [-1, -1]��
�������Ʋ�ʵ��ʱ�临�Ӷ�Ϊ O(log n) ���㷨��������⡣
*/
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int leftBorder = GetLeftBorder(nums, target);//Ѱ����߽�
		int rightBorder = GetRightBorder(nums, target);//Ѱ���ұ߽�
		if (leftBorder == -2 || rightBorder == -2) return { -1, -1 };
		if (rightBorder - leftBorder > 1) return { leftBorder + 1, rightBorder - 1 };
		return { -1, -1 };
	}
private:
	int GetRightBorder(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		int rightBorder = -2; // ��¼һ��rightBorderû�б���ֵ�����
		while (left <= right) {
			int middle = (right + left) / 2;
			int n = nums[middle];
			if (n> target) {
				right = middle - 1;
			}
			else { // Ѱ���ұ߽磬nums[middle] == target��ʱ�����left
				left = middle + 1;
				rightBorder = left;
			}
		}
		return rightBorder;
	}
	int GetLeftBorder(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		int leftBorder = -2; // ��¼һ��leftBorderû�б���ֵ�����
		while (left <= right) {
			int middle = (right + left) / 2;
			int n = nums[middle];
			if (n >= target) { // Ѱ����߽磬nums[middle] == target��ʱ�����right
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
//������ ��������������ϲ�Ϊһ���µ������������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ�
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
		ListNode* dummy = new ListNode(-1), *p= dummy;//����һ���ƽ��
		ListNode* p1 = list1, * p2 = list2;
		while (p1 != NULL && p2 != NULL) {
			if (p1->data > p2->data) {
				p->next = p2;
				p2= p2->next;
			}else {
				p -> next = p1;
				p1 = p1->next;
			}
			p = p->next;//p����ǰ��
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
/*������ ����һ���Ǹ����� x �����㲢���� x �� ����ƽ���� �����ڷ������������������ֻ���� �������� ��С�����ֽ��� ��ȥ ��
ע�⣺������ʹ���κ�����ָ����������������� pow(x, 0.5) ���� x** 0.5 ��*/

class Solution {//ʹ��expָ������
public:
	int mySqrt(int x) {
		if (x <= 0) return 0;
		int ans = exp(0.5 * log(x));
		return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
	}
};
//���ֲ���
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
/*�ڰ��� ����һ������ nums ��һ��ֵ val������Ҫ ԭ�� �Ƴ�������ֵ���� val ��Ԫ�أ��������Ƴ���������³��ȡ�
��Ҫʹ�ö��������ռ䣬������ʹ�� O(1) ����ռ䲢 ԭ�� �޸��������顣Ԫ�ص�˳����Ըı䡣�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�*/

class Solution {//�����ⷨ
public:
	int removeElement(vector<int>& nums, int val) {
		int n = nums.size();
		for (int i = 0;i < n;i++) {
			if (nums[i] == val) {
				for (int j = i + 1;j < n;j++) {
					nums[j - 1] = nums[j];
				}
				i--;//��Ϊʵ����i�����Ԫ�ض���ǰһλ��ԭ��iλ���Ѿ�����Ԫ�أ����ֱ��for i++����©Ԫ��
				n--;//�൱��ɾ����һ���������飬����-1��
			}
		}
		return n;
	}
};
class Solution {//����ָ��
public:
	int removeElement(vector<int>& nums, int val) {
		int leftIndex = 0;
		int rightIndex = nums.size() - 1;
		while (leftIndex <= rightIndex) {
			// ����ߵ���val��Ԫ��
			while (leftIndex <= rightIndex && nums[leftIndex] != val) {
				++leftIndex;
			}
			// ���ұ߲�����val��Ԫ��
			while (leftIndex <= rightIndex && nums[rightIndex] == val) {
				--rightIndex;
			}
			// ���ұ߲�����val��Ԫ�ظ�����ߵ���val��Ԫ��
			if (leftIndex < rightIndex) {
				nums[leftIndex++] = nums[rightIndex--];
			}
		}
		return leftIndex;   // leftIndexһ��ָ������������ĩβ����һ��Ԫ��
	}
};
/*�ھ��� ����һ�����ϸ�������е�����nums ������ԭ��ɾ���ظ����ֵ�Ԫ�أ�ʹÿ��Ԫ�� ֻ����һ�� ������ɾ����������³��ȡ�Ԫ�ص����˳��Ӧ�ñ���һ�� ��
Ȼ�󷵻� nums ��ΨһԪ�صĸ��������� nums ��ΨһԪ�ص�����Ϊ k ������Ҫ����������ȷ����������Ա�ͨ����
�������� nums ��ʹ nums ��ǰ k ��Ԫ�ذ���ΨһԪ�أ���������������� nums �г��ֵ�˳�����С�nums ������Ԫ���� nums �Ĵ�С����Ҫ��
���� k ��*/

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0) {
			return 0;
		}
		int slow = 0,fast = 0;
		while (fast < nums.size()) {//�Ҳ��ظ���Ԫ�ظ�ֵ ˼·��ͨһ��
			if (nums[fast] != nums[slow]) {
				slow++;//ά��nums[0...slow]���ظ�
				nums[slow] = nums[fast];
			}
			fast++;
		}
		return slow + 1;
	}
};

//��ʮ�� ����һ���� �ǵݼ�˳�� ������������� nums������ÿ�����ֵ�ƽ����ɵ������飬Ҫ��Ҳ���ǵݼ�˳�� ����

class Solution {//�����ⷨ
public:
	vector<int> sortedSquares(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0;i < n;i++) {
			nums[i] = nums[i] * nums[i];
		}
		sort(nums.begin(), nums.end());//����
		return nums;
	}
};
//˫ָ��
class Solution {
public:
	vector<int>sortedSquares(vector<int>& nums) {
		int i=0,k = nums.size()-1,j=nums.size()-1;
		vector<int>result(nums.size(), 0);//����һ����������������Ϊnums.size����ʼΪ0��
		for (;i <= j;) {
			if (nums[i] * nums[i] <= nums[j] * nums[j]) {
				result[k--] = nums[i] * nums[i];//���ǰ������У����ֵֻ���ܳ������ײ���β�������ԴӺ���ǰ��
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

//��ʮһ�� ����һ��������������ͷ head �� ɾ�������ظ���Ԫ�أ�ʹÿ��Ԫ��ֻ����һ�� ������ ����������� 
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

//��ʮ���� ����һ������n���������������һ�������� target ���ҳ����������������ܺʹ��ڵ��� target �ĳ�����С�� ����������[numsl
// numsl + 1, ..., numsr - 1, numsr] ���������䳤�ȡ���������ڷ��������������飬���� 0 ��

class Solution {//��������
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

/* ��ʮ���� ����һ�������� n ������һ������ 1 �� n^2 ����Ԫ�أ���Ԫ�ذ�˳ʱ��˳���������е� n x n �����ξ��� matrix ��
*/

class Solution {
public:
	vector<vector<int>>generateMatrix(int n) {
		vector<vector<int>>result(n, vector<int>(n, 0));
		int horx = 0, very = 0;//�����������
		int loop = n / 2;//������תȦ������n=3��3*3=9��ֻ��תһȦ�����������м��ֵ
		int mid = n / 2;//�м�ֵ
		int count = 1,offset=1;//count������ֵ��offset����������������ʱ�ĳ���
		while (loop--) {
			int i = horx;
			int j = very;
			//ѭ��ģ��תȦ��ֵ
			for (;j < n - offset;j++) {//��һ�Σ�ÿ�и�ֵ
				result[horx][j] = count++;
			}
			for (;i < n - offset;i++) {//���������¸�ֵ
				result[i][j] = count++;
			}
			for (;j > very;j--) {//�����д�������ֵ
				result[i][j] = count++;
			}
			// �����д��µ��ϸ�ֵ
			for (; i > horx; i--) {
				result[i][j] = count++;
			}
			horx++;very++;
			offset += 1;
		}
		//���nΪ�������������ĵ�
		if (n % 2 == 1) {
			result[mid][mid] = count;
		}
		return result;
	}
};

/* ��ʮ���� ����һ���������� nums ��һ������Ŀ��ֵ target�������ڸ��������ҳ� ��ΪĿ��ֵ target  ���� ���� ���������������ǵ������±ꡣ
����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ�������ͬһ��Ԫ���ڴ��ﲻ���ظ����֡�
*/

class Solution {//��ϣ��
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int>hash;//��ϣ���÷�
		int n = nums.size();
		for (int i = 0;i < n;i++) {
			int complement = target - nums[i];
			if (hash.count(complement)) {//�����ϣ���д��������
				return vector<int>{hash[complement], i};
			}
			hash[nums[i]] = i;//��i��ֵ�����ϣ�������´��ظ�����
		}
		return vector<int>();
	}
};

/* ��ʮ���� ����һ�� m �� n �еľ��� matrix ���밴�� ˳ʱ������˳�� �����ؾ����е�����Ԫ�ء�
*/

class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		int m = matrix.size(), n = matrix[0].size();//m����������n�����һ�е�������ʵ�ʵ����������������
		int upper_bound = 0, lower_bound = m - 1;//ȷ���߽�
		int left_bound = 0, right_bound = n - 1;
		vector<int> res;
		// res.size() == m * n ���������������
		while (res.size() < m * n) {
			if (upper_bound <= lower_bound) {
				// �ڶ����������ұ���
				for (int j = left_bound; j <= right_bound; j++) {
					res.push_back(matrix[upper_bound][j]);//��ĩβ���һ����Ԫ��
				}
				// �ϱ߽�����
				upper_bound++;
			}
			if (left_bound <= right_bound) {
				// ���Ҳ�������±���
				for (int i = upper_bound; i <= lower_bound; i++) {
					res.push_back(matrix[i][right_bound]);
				}
				// �ұ߽�����
				right_bound--;
			}
			if (upper_bound <= lower_bound) {
				// �ڵײ������������
				for (int j = right_bound; j >= left_bound; j--) {
					res.push_back(matrix[lower_bound][j]);
				}
				// �±߽�����
				lower_bound--;
			}
			if (left_bound <= right_bound) {
				// �����������ϱ���
				for (int i = lower_bound; i >= upper_bound; i--) {
					res.push_back(matrix[i][left_bound]);
				}
				// ��߽�����
				left_bound++;
			}
		}
		return res;
	}
};

//��ʮ���� ����һ�� n ��Ԫ������ģ������������� nums ��һ��Ŀ��ֵ target  ��дһ���������� nums �е� target�����Ŀ��ֵ���ڷ����±꣬���򷵻� -1��

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

/*��ʮ���� ����һ������ nums ��һ��ֵ val������Ҫ ԭ�� �Ƴ�������ֵ���� val ��Ԫ�أ��������Ƴ���������³��ȡ�
��Ҫʹ�ö��������ռ䣬������ʹ�� O(1) ����ռ䲢 ԭ�� �޸��������顣
Ԫ�ص�˳����Ըı䡣�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�*/

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

//��ʮ���� ����һ�������ͷ�ڵ� head ��һ������ val ������ɾ���������������� Node.val == val �Ľڵ㣬������ �µ�ͷ�ڵ� ��
/*
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		//ɾ������ͷ���
		while (head != NULL && head->data == val) {
			ListNode* temp = head;
			head = head->next;
			delete temp;
		}
		//ɾ����ͷ���
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

/* �����ѡ��ʹ�õ��������˫������Ʋ�ʵ���Լ�������
�������еĽڵ�Ӧ�þ߱��������ԣ�val �� next ��val �ǵ�ǰ�ڵ��ֵ��next ��ָ����һ���ڵ��ָ��/���á�
�����˫����������Ҫ���� prev ��ָʾ�����е���һ���ڵ㡣���������е����нڵ��±�� 0 ��ʼ��
ʵ�� MyLinkedList �ࣺ*/

/*class MyLinkedList {
public:
	struct ListNode {
		int val;
		ListNode* next;
		ListNode(int val) :val(val), next(nullptr) {}//���캯��
	};

	MyLinkedList() {
		this->size = 0;//this��ʾ�Ե�ǰ���������
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
private://˽���ඨ��
	int size;
	ListNode* head;
};*/

struct ListNode {//��������д��
     int val;
     ListNode *next;
    // ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     //ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
//��ʮ���� ���㵥�����ͷ�ڵ� head �����㷴ת���������ط�ת�������

/*class Solution {//��������
public:
  ListNode* reverseList(ListNode* head) {
	  ListNode* p = nullptr; // ǰһ���ڵ�
	  ListNode* curr = head;    // ��ǰ�ڵ�
	  while (curr != nullptr) {
		  ListNode* Temp = curr->next; // ��ʱ�ڵ㣬���ڱ�����һ���ڵ�
		  curr->next = p; // ����ǰ�ڵ�� next ָ��ָ��ǰһ���ڵ㣬ʵ������
		  p = curr; // ǰһ���ڵ�����ƶ�
		  curr = Temp; // ��ǰ�ڵ�����ƶ�
	  }
	  return p; // ��ѭ������ʱ��prev ��ָ���µ�ͷ�ڵ�
  }

};*/

//�ڶ�ʮ�� ����һ���������������������ڵĽڵ㣬�����ؽ����������ͷ�ڵ㡣������ڲ��޸Ľڵ��ڲ���ֵ���������ɱ��⣨����ֻ�ܽ��нڵ㽻������

/*class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		ListNode* dummyHead = new ListNode(0);//�����ƽ��
		dummyHead->next = head;
		ListNode* curr = dummyHead;
		while (curr->next != nullptr && curr->next->next != nullptr) {
			ListNode* temp = curr->next;
			ListNode* p = curr->next->next->next;
			curr->next = curr->next->next;    // ����һ
			curr->next->next = temp;          // �����
			curr->next->next->next = p;   // ������
			curr = curr->next->next; // cur�ƶ���λ��׼����һ�ֽ���
		}
		return dummyHead->next;
	}
};*/

//��21�� ����һ������ɾ������ĵ����� n ����㣬���ҷ��������ͷ��㡣
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

//��22�� ���������������ͷ�ڵ� headA �� headB �������ҳ������������������ཻ����ʼ�ڵ㡣�����������û�н��㣬���� null ��
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
		// ͬʱ������������ֱ���ҵ��ཻ�ڵ�
		while (currA != nullptr && currB != nullptr) {
			if (currA == currB) {
				return currA;
			}
			currA = currA->next;
			currB = currB->next;
		}
		// ���û���ཻ�ڵ㣬����nullptr
		return nullptr;
	}
};*/

/* ��23�� ����һ�������ͷ�ڵ�  head ����������ʼ�뻷�ĵ�һ���ڵ㡣 ��������޻����򷵻� null��
�����������ĳ���ڵ㣬����ͨ���������� next ָ���ٴε���������д��ڻ���
Ϊ�˱�ʾ���������еĻ�������ϵͳ�ڲ�ʹ������ pos ����ʾ����β���ӵ������е�λ�ã������� 0 ��ʼ������� pos �� -1�����ڸ�������û�л���
ע�⣺pos ����Ϊ�������д��ݣ�������Ϊ�˱�ʶ�����ʵ�������
�������޸� ����
*/
/*
class Solution {//����ָ��
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
				while (index1 != index2) {//���Ի���ͼ��⣬����������ͷ���ֱ�����������㼴�ǻ�����ڵ�
					index1 = index1->next;
					index2 = index2->next;
				}
				return index2;
			}
		}
		return nullptr;
	}
};*/

//��ϣ��
/* ��24��  ���������ַ��� s �� t ����дһ���������ж� t �Ƿ��� s ����ĸ��λ�ʡ�
ע�⣺�� s �� t ��ÿ���ַ����ֵĴ�������ͬ����� s �� t ��Ϊ��ĸ��λ�ʡ�
����: s = "anagram", t = "nagaram"
���: true*/

class Solution {
public:
	bool isAnagram(string s, string t) {
		int record[26] = { 0 };
		for (int i = 0;i < s.size();i++) {
			record[s[i] - 'a']++;//��¼�ַ��������ڵ����λ��
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

/* ��25�� ������������ nums1 �� nums2 ������ ���ǵĽ��� ���������е�ÿ��Ԫ��һ���� Ψһ �ġ����ǿ��� ��������������˳�� ��
*/

class Solution {//����
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		unordered_set<int> result_set;// ��Ž����֮������set��Ϊ�˸������ȥ��
		int hash[1005] = { 0 }; // Ĭ����ֵΪ0
		for (int num : nums1) { // nums1�г��ֵ�Ԫ����hash����������¼
			hash[num] = 1;
		}
		for (int num : nums2) { // nums2�г��ֵĻ���result��¼
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
			result_set; // ��Ž����֮������set��Ϊ�˸������ȥ��
		unordered_set<int> nums_set(nums1.begin(), nums1.end());//��num1��Ԫ�ط����set
		for (int num : nums2) {
			// ����nums2��Ԫ�� ��nums_set���ֳ��ֹ�
			if (nums_set.find(num) != nums_set.end()) {//���num2��Ԫ����nums_set�г��ֹ���������һ��num��set�������Ƿ���nums_set
				result_set.insert(num);//!=��Ϊ����Ԫ�أ�����Ԫ�ز���result_set
			}
		}
		return vector<int>(result_set.begin(), result_set.end());
	}
};

/*�� 26�� ��дһ���㷨���ж�һ���� n �ǲ��ǿ�������
���������� ����Ϊ��
����һ����������ÿһ�ν������滻Ϊ��ÿ��λ���ϵ����ֵ�ƽ���͡�
Ȼ���ظ��������ֱ���������Ϊ 1��Ҳ������ ����ѭ�� ��ʼ�ձ䲻�� 1��
���������� ���Ϊ 1����ô��������ǿ�������
��� n �� ������ �ͷ��� true �����ǣ��򷵻� false ��
*/

class Solution {
public:
	int getSum(int n) {
		//�������λ��֮��
		int sum = 0;
		while (n) {
			sum += (n % 10) * (n % 10);
			n /= 10;
		}
		return sum;
	}
	bool isHappy(int n) {
		unordered_set<int> set;
		while (1) {//����ѭ��
			int sum = getSum(n);
			if (sum == 1) {
				return true;
			}
			if (set.find(sum) != set.end()) {//��25��һ�� !=������set�����ظ�Ԫ��
				return false;
			}else {
				set.insert(sum);
			}
			n = sum;
		}
	}
};

/* ��27�� �����ĸ��������� nums1��nums2��nums3 �� nums4 �����鳤�ȶ��� n ����������ж��ٸ�Ԫ�� (i, j, k, l) �����㣺
0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
*/

class Solution {
public:
	int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
		unordered_map<int, int> umap; //key:a+b����ֵ��value:a+b��ֵ���ֵĴ���
		// ������A�ʹ�B���飬ͳ����������Ԫ��֮�ͣ��ͳ��ֵĴ������ŵ�map��
		for (int a : A) {
			for (int b : B) {
				umap[a + b]++;
			}
		}
		int count = 0; // ͳ��a+b+c+d = 0 ���ֵĴ���
		// �ڱ�����C�ʹ�D���飬�ҵ���� 0-(c+d) ��map�г��ֹ��Ļ����Ͱ�map��key��Ӧ��valueҲ���ǳ��ִ���ͳ�Ƴ�����
		for (int c : C) {
			for (int d : D) {
				if (umap.find(0 - (c + d)) != umap.end()) {//������һ�� .find!=end
					count += umap[0 - (c + d)];
				}
			}
		}
		return count;
	}
};

/*��28�� ���������ַ�����ransomNote �� magazine ���ж� ransomNote �ܲ����� magazine ������ַ����ɡ�
������ԣ����� true �����򷵻� false ��
magazine �е�ÿ���ַ�ֻ���� ransomNote ��ʹ��һ�Ρ�
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
			// ͨ��record���ݼ�¼ magazine������ַ����ִ���
			record[magazine[i] - 'a'] ++;
		}
		for (int j = 0; j < ransomNote.length(); j++) {
			// ����ransomNote����record���Ӧ���ַ�������--����
			record[ransomNote[j] - 'a']--;
			// ���С����˵��ransomNote����ֵ��ַ���magazineû��
			if (record[ransomNote[j] - 'a'] < 0) {
				return false;
			}
		}
		return true;
	}
};


/*��29�� ����һ���������� nums ���ж��Ƿ������Ԫ�� [nums[i], nums[j], nums[k]] ���� i != j��i != k �� j != k ��
ͬʱ������ nums[i] + nums[j] + nums[k] == 0 ��
���㷵�����к�Ϊ 0 �Ҳ��ظ�����Ԫ�顣
ע�⣺���в����԰����ظ�����Ԫ�顣
*/

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());//����֮�� ���п��ܵ��ظ�Ԫ�ض��Ἧ����һ��
		// �ҳ�a + b + c = 0
		// a = nums[i], b = nums[left], c = nums[right]
		for (int i = 0; i < nums.size(); i++) {
			// ����֮�������һ��Ԫ���Ѿ������㣬��ô���������϶������ܴճ���Ԫ�飬ֱ�ӷ��ؽ���Ϳ�����
			if (nums[i] > 0) {
				return result;
			}
			// ����ȥ��a����������©��-1,-1,2 �������
			/*
			if (nums[i] == nums[i + 1]) {
				continue;
			}
			*/
			// ��ȷȥ��a����
			if (i > 0 && nums[i] == nums[i - 1]) {//��Ϊ��������������
				continue;//��ǰ�������ε���������ʼ��һ�ε�����
			}
			int left = i + 1;
			int right = nums.size() - 1;
			while (right > left) {
				// ȥ�ظ��߼�����������0��0��0 �����������ֱ�ӵ��� right<=left �ˣ��Ӷ�©���� 0,0,0 ������Ԫ��
				/*
				while (right > left && nums[right] == nums[right - 1]) right--;
				while (right > left && nums[left] == nums[left + 1]) left++;
				*/
				if (nums[i] + nums[left] + nums[right] > 0) right--;
				else if (nums[i] + nums[left] + nums[right] < 0) left++;
				else {
					result.push_back(vector<int>{nums[i], nums[left], nums[right]});//push_back��������ĩβ���Ԫ��
					// ȥ���߼�Ӧ�÷����ҵ�һ����Ԫ��֮�󣬶�b �� cȥ��
					while (right > left && nums[right] == nums[right - 1]) right--;
					while (right > left && nums[left] == nums[left + 1]) left++;

					// �ҵ���ʱ��˫ָ��ͬʱ����
					right--;
					left++;
				}
			}

		}
		return result;
	}
};

/*��30�� ����һ���� n ��������ɵ����� nums ����һ��Ŀ��ֵ target ��
�����ҳ���������������ȫ�������Ҳ��ظ�����Ԫ�� [nums[a], nums[b], nums[c], nums[d]] ����������Ԫ��Ԫ��һһ��Ӧ������Ϊ������Ԫ���ظ�����
0 <= a, b, c, d < n
a��b��c �� d ������ͬ
nums[a] + nums[b] + nums[c] + nums[d] == target
����԰� ����˳�� ���ش� ��
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
			}//����������
			if ((long)nums[i] + nums[len - 3] + nums[len - 2] + nums[len - 1] < target) {
				continue;
			}//ȥ��
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

//�ַ������� 
/* ��31�� ��дһ���������������ǽ�������ַ�����ת�����������ַ������ַ����� s ����ʽ������
��Ҫ�����������������Ŀռ䣬�����ԭ���޸��������顢ʹ�� O(1) �Ķ���ռ�����һ����
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

/* ��32�� ����һ���ַ��� s ��һ������ k�����ַ�����ͷ����ÿ������ 2k ���ַ����ͷ�ת�� 2k �ַ��е�ǰ k ���ַ���
���ʣ���ַ����� k ������ʣ���ַ�ȫ����ת��
���ʣ���ַ�С�� 2k �����ڻ���� k ������תǰ k ���ַ��������ַ�����ԭ����
*/

class Solution {
public:
	string reverseStr(string s, int k) {
		for (int i = 0; i < s.size(); i += (2 * k)) {
			// 1. ÿ�� 2k ���ַ���ǰ k ���ַ����з�ת
			// 2. ʣ���ַ�С�� 2k �����ڻ���� k ������תǰ k ���ַ�
			if (i + k <= s.size()) {
				reverse(s.begin() + i, s.begin() + i + k);
			}
			else {
				// 3. ʣ���ַ����� k ������ʣ���ַ�ȫ����ת��
				reverse(s.begin() + i, s.end());
			}
		}
		return s;
	}
};

/*��33�� ����һ���ַ��� s �����㷴ת�ַ����� ���� ��˳��
���� ���ɷǿո��ַ���ɵ��ַ�����s ��ʹ������һ���ո��ַ����е� ���� �ָ�����
���� ���� ˳��ߵ��� ���� ֮���õ����ո����ӵĽ���ַ�����
ע�⣺�����ַ��� s�п��ܻ����ǰ���ո�β��ո���ߵ��ʼ�Ķ���ո񡣷��صĽ���ַ����У����ʼ�Ӧ�����õ����ո�ָ����Ҳ������κζ���Ŀո�
*/

class Solution {
public:
	void reverse(string& s, int start, int end) {
		for (int i = start, j = end;i < j;i++, j--) {
			swap(s[i], s[j]);
		}
	}
	void removeExtraSpaces(string& s) {//ȥ��ǰ�����ո�
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
		s.resize(slow);//resize�������������С
	}
	string reverseWords(string s) {
		removeExtraSpaces(s);//ȥ������ո�
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


/*��34�� ���������ַ��� haystack �� needle �������� haystack �ַ������ҳ� needle �ַ����ĵ�һ��ƥ������±꣨�±�� 0 ��ʼ����
��� needle ���� haystack ��һ���֣��򷵻�  -1 ��
*/

class Solution {//KMP
public:
	void getNext(int* next, const string& s) {
		int j = -1;
		next[0] = j;
		for (int i = 1; i < s.size(); i++) { // ע��i��1��ʼ
			while (j >= 0 && s[i] != s[j + 1]) { // ǰ��׺����ͬ��
				j = next[j]; // ��ǰ����
			}
			if (s[i] == s[j + 1]) { // �ҵ���ͬ��ǰ��׺
				j++;
			}
			next[i] = j; // ��j��ǰ׺�ĳ��ȣ�����next[i]
		}
	}
	int strStr(string haystack, string needle) {
		if (needle.size() == 0) {
			return 0;
		}
		//int next[needle.size()];
		int* next = new int[needle.size()];//����ȫ�������ڹ����ڴ档��ʹ�ö�̬���������ʱ��ʼ�ռǵ���ʹ����Ϻ��ͷ��ڴ档
		getNext(next, needle);
		int j = -1; // // ��Ϊnext�������¼����ʼλ��Ϊ-1
		for (int i = 0; i < haystack.size(); i++) { // ע��i�ʹ�0��ʼ
			while (j >= 0 && haystack[i] != needle[j + 1]) { // ��ƥ��
				j = next[j]; // j Ѱ��֮ǰƥ���λ��
			}
			if (haystack[i] == needle[j + 1]) { // ƥ�䣬j��iͬʱ����ƶ�
				j++; // i��������forѭ����
			}
			if (j == (needle.size() - 1)) { // �ı���s�������ģʽ��t
				return (i - needle.size() + 1);
			}
		}
		delete[] next;//�ͷ��ڴ�
		return -1;
	}
};

/*��35�� �����ʹ������ջʵ�������ȳ����С�����Ӧ��֧��һ�����֧�ֵ����в�����push��pop��peek��empty����
ʵ�� MyQueue �ࣺ
void push(int x) ��Ԫ�� x �Ƶ����е�ĩβ
int pop() �Ӷ��еĿ�ͷ�Ƴ�������Ԫ��
int peek() ���ض��п�ͷ��Ԫ��
boolean empty() �������Ϊ�գ����� true �����򣬷��� false
*/

class MyQueue {
public:
	stack<int>Sin;//����ջ��д��
	stack<int>Sout;
	MyQueue() {

	}

	void push(int x) {//��ջ���Ǽ򵥵���Sin����ջ
		Sin.push(x);
	}

	int pop() {
		//ֻ��SoutΪ��ʱ�����ܴ�Sin�е�������(ȫ��) ��Ϊ��ջҪ��Sout��
		if (Sout.empty()) {
			while (!Sin.empty()) {
				Sout.push(Sin.top());//����Sin��Ԫ��
				Sin.pop();
			}
		}
		int result = Sout.top();
		Sout.pop();
		return result;
	}

	int peek() {//�鿴����
		int res = this->pop();//ֱ��ʹ�����е�pop����
		Sout.push(res);//��Ϊpop������res����������ӻ�ȥ
		return res;
	}

	bool empty() {
		return Sin.empty() && Sout.empty();
	}
};

/*��36�� �����ʹ����������ʵ��һ�������ȳ���LIFO����ջ����֧����ͨջ��ȫ�����ֲ�����push��top��pop �� empty����
ʵ�� MyStack �ࣺ
void push(int x) ��Ԫ�� x ѹ��ջ����
int pop() �Ƴ�������ջ��Ԫ�ء�
int top() ����ջ��Ԫ�ء�
boolean empty() ���ջ�ǿյģ����� true �����򣬷��� false 
*/

class MyStack {
public:
	queue<int> que;//���й���д��
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
		while (size--) { // ������ͷ����Ԫ�أ��������һ��Ԫ���⣩ ������ӵ�����β��
			que.push(que.front());
			que.pop();
		}
		int result = que.front(); // ��ʱ������Ԫ��˳�����ջ��˳����
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
/*//��ת����
struct Color {
	int r;
	int g;
	int b;
};
class Rotate {
public:
	// ��ת����
	Color* RotatePic90(int width, int height, Color input[]) {
		Color* rotated = new Color[height * width]; // �����ڴ�
		int centerX = width / 2;
		int centerY = height / 2;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				int new_x = centerY - (x - centerX);
				int new_y = centerY + (y - centerY);
				// ȷ����ת�������û��Խ��
				if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
					rotated[new_y * width + new_x] = input[y * width + x];
				}
			}
		}
		return rotated;
	}
};

int main(int argc,char const*argv[]) {
	// ��ʼ��ͼ�����ݣ�����ֻ��һ��ʾ����ʵ��Ӧ����Ӧ�ô��ļ�����Դ��ȡ
	Color input[400] = {
		// ... ͼ�����ݳ�ʼ��
	};
	// ����Reverse���ʵ��
	Rotate* rev = new Rotate();
	// ������ת����
	Color* rotated = rev->RotatePic90(20, 20, input);
	// �����ת���ͼ����������֤
	for (int i = 0; i < 400; ++i) {
		std::cout << "Color(" << rotated[i].r << ", " << rotated[i].g << ", " << rotated[i].b << ")" << std::endl;
	}
	// �ͷ��ڴ�
	delete[] rotated;
	delete rev;
	return 0;
}*/

/*��37�� ����һ��ֻ���� '('��')'��'{'��'}'��'['��']' ���ַ��� s ���ж��ַ����Ƿ���Ч��
��Ч�ַ��������㣺
�����ű�������ͬ���͵������űպϡ�
�����ű�������ȷ��˳��պϡ�
ÿ�������Ŷ���һ����Ӧ����ͬ���͵������š�
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

/*��38�� ������Сд��ĸ��ɵ��ַ��� S���ظ���ɾ��������ѡ��������������ͬ����ĸ����ɾ�����ǡ�
�� S �Ϸ���ִ���ظ���ɾ��������ֱ���޷�����ɾ����
����������ظ���ɾ�������󷵻����յ��ַ������𰸱�֤Ψһ��
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
		string result;//���ַ����Լ�����ջ
		for (char S : s) {
			if (result.empty() || result.back() != S) {
				result.push_back(S);//��Ԫ�ط���result
			}else {
				result.pop_back();
			}
		}
		return result;
	}
};

/*��38�� ����һ���ַ������� tokens ����ʾһ������ �沨����ʾ�� ��ʾ���������ʽ��
�������ñ��ʽ������һ����ʾ���ʽֵ��������
ע�⣺
��Ч�����Ϊ '+'��'-'��'*' �� '/' ��
ÿ����������������󣩶�������һ������������һ�����ʽ��
��������֮��ĳ������� ����ض� ��
���ʽ�в����������㡣
������һ�������沨����ʾ����ʾ���������ʽ��
�𰸼������м������������ 32 λ ������ʾ��
*/

class Solution {//����׺��ʾ��
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
					st.push(stoll(tokens[i]));//stoll���ڽ��ַ���ת����long long
				}
		}
		int result = st.top();
		st.pop();
		return result;
	}
};

/*��39�� ����һ���������� nums����һ����СΪ k �Ļ������ڴ������������ƶ�����������Ҳࡣ
��ֻ���Կ����ڻ��������ڵ� k �����֡���������ÿ��ֻ�����ƶ�һλ��
���� ���������е����ֵ 
*/

class Solution {
private://˽�ж�����
	class MyQueue {//�ö���ʵ��
	public:
		deque<int>queue;
		void pop(int value) {
			if (!queue.empty() && value == queue.front()) {
				queue.pop_front();//�Ƚ�Ҫ������ֵ�Ƿ���ڶ��г���Ԫ��
			}
		}
		void push(int value) {
			while (!queue.empty() && value > queue.back()) {
				queue.pop_back();//���ѹջԪ�ش������Ԫ����ֵ����ô����β����ֵ����֤��������
			}
			queue.push_back(value);
		}
		int front() {//��ѯ��ǰ�������ֵ ֱ�ӷ��ض���ǰ��
			return queue.front();
		}
	};
public:
	vector<int>masSlidingWindow(vector<int>& nums, int k) {
		MyQueue Q;
		vector<int>result;
		for (int i = 0;i < nums.size();i++) {
			Q.pop(nums[i - k]);//�����Ƴ�������ǰ��Ԫ��,һ��ʼС��kʱ������ѭ��
			Q.push(nums[i]);
			result.push_back(Q.front());//��¼��ǰ���ֵ
		}
		return result;
	}
};

/*��40�� ����һ���������� nums ��һ������ k �����㷵�����г���Ƶ��ǰ k �ߵ�Ԫ�ء�����԰� ����˳�� ���ش𰸡�
*/

class Solution {//����
public:
	//��һ��С����
	class mycomparison{
	public:
		bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
			return lhs.second > rhs.second;//pair �еĵڶ���Ԫ�ؽ�����������Ĺؼ��֡�
		}
	};
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int>map;//map<nums[i],��Ӧ���ֵĴ���
		for (int i = 0;i < nums.size();i++) {//ͳ��Ԫ�س��ֵ�Ƶ��
			map[nums[i]]++;
		}
		//��Ƶ������
		//����С����
		priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison>pri_que;//priority_queue���ȼ����о��Ǹ��� ��׼д�� ��һ��
		for (unordered_map<int, int>::iterator it = map.begin();it != map.end();it++) {
			pri_que.push(*it);
			if (pri_que.size() > k) {
				pri_que.pop();//����ѵĴ�С����k������е���
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

//������

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

/*��41�� �������
*/
class Solution {//�������
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
			if (node->right) {//��ջ�����󣬳�ջ������
				Tree.push(node->right);
			}
			if (node->left) {
				Tree.push(node->left);
			}
		}
		return result;
	}
};

class Solution {//������
public:
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			if (node != NULL) {
				st.pop();
				if (node->right) st.push(node->right);  // ��
				if (node->left) st.push(node->left);    // ��
				st.push(node);                          // ��
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

class Solution {//�������
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> Tree;
		TreeNode* curr = root;
		while (curr != NULL || !Tree.empty()) {
			if (curr != NULL) { // ָ�������ʽڵ㣬���ʵ���ײ�
				Tree.push(curr); // �����ʵĽڵ�Ž�ջ
				curr = curr->left;                // ��
			}
			else {
				curr = Tree.top(); // ��ջ�ﵯ�������ݣ�����Ҫ��������ݣ��Ž�result����������ݣ�
				Tree.pop();
				result.push_back(curr->val);     // ��
				curr = curr->right;               // ��
			}
		}
		return result;
	}
};
class Solution {//�������������
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			if (node != NULL) {
				st.pop(); // ���ýڵ㵯���������ظ������������ٽ�������ڵ���ӵ�ջ��
				if (node->right) st.push(node->right);  // ����ҽڵ㣨�սڵ㲻��ջ��

				st.push(node);                          // ����нڵ�
				st.push(NULL); // �нڵ���ʹ������ǻ�û�д�������սڵ���Ϊ��ǡ�

				if (node->left) st.push(node->left);    // �����ڵ㣨�սڵ㲻��ջ��
			}
			else { // ֻ�������սڵ��ʱ�򣬲Ž���һ���ڵ�Ž������
				st.pop();           // ���սڵ㵯��
				node = st.top();    // ����ȡ��ջ��Ԫ��
				st.pop();
				result.push_back(node->val); // ���뵽�����
			}
		}
		return result;
	}
};

class Solution {//�������
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

class Solution {//������
public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			if (node != NULL) {
				st.pop();
				st.push(node);                          // ��
				st.push(NULL);

				if (node->right) st.push(node->right);  // ��
				if (node->left) st.push(node->left);    // ��

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

//��42�� �������


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
				TreeNode* node = que.front();//�ʼ��Ϊ�����
				que.pop();
				vec.push_back(node->val);
				if (node->left) {
					que.push(node->left);//�������
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

//�������2

class Solution {//��������
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

//����һ���������� ���ڵ� root�������Լ�վ�������Ҳ࣬���մӶ������ײ���˳�򣬷��ش��Ҳ����ܿ����Ľڵ�ֵ��

class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		queue<TreeNode*>que;
		if (root != nullptr) {
			que.push(root);
		}
		vector<int>result;
		while (!que.empty()) {
			int size = que.size();//�ص�����������size
			for (int i = 0;i < size;i++) {
				TreeNode* node = que.front();
				que.pop();
				if (i == (size - 1)) {//ÿ�����һ��
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

//����һ���ǿն������ĸ��ڵ� root , ���������ʽ����ÿһ��ڵ��ƽ��ֵ����ʵ�ʴ���� 10-5 ���ڵĴ𰸿��Ա����ܡ�

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

/*����һ�� N ������������ڵ�ֵ�Ĳ�����������������ң�����������
�������л��������ò��������ÿ���ӽڵ㶼�� null ֵ�ָ����μ�ʾ������
*/

/*class Node {//N������㶨��
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
					if (node->children[i]) {//����㺢�Ӽ������
						que.push(node->children[i]);
					}
				}
				
			}
			result.push_back(vec);
		}
		return result;
	}
};*/

//����һ�ö������ĸ��ڵ� root �����ҳ��ö�������ÿһ������ֵ��

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

/*����һ�� ���������� ��������Ҷ�ӽڵ㶼��ͬһ�㣬ÿ�����ڵ㶼�������ӽڵ㡣�������������£�
�������ÿ�� next ָ�룬�����ָ��ָ������һ���Ҳ�ڵ㡣����Ҳ�����һ���Ҳ�ڵ㣬�� next ָ������Ϊ NULL��
��ʼ״̬�£����� next ָ�붼������Ϊ NULL��
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
					nodePre = que.front();//ȡ��һ���ͷ���
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

/* ����һ����������
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
�������ÿ�� next ָ�룬�����ָ��ָ������һ���Ҳ�ڵ㡣����Ҳ�����һ���Ҳ�ڵ㣬�� next ָ������Ϊ NULL ��
��ʼ״̬�£����� next ָ�붼������Ϊ NULL 
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

//���ض������������ȡ� ��ָ�Ӹ��ڵ㵽��ԶҶ�ӽڵ���·���ϵĽڵ�����

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

//����һ�����������ҳ�����С��ȡ�

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

//��43�� ����һ�ö������ĸ��ڵ� root ����ת��ö�����������������ڵ㡣

class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {//ǰ�����ʵ��
		if (root == nullptr) {
			return root;
		}
		swap(root->left, root->right);
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
};

class Solution {//������ȱ��� �������
public:
	TreeNode* invertTree(TreeNode* root) {
		queue<TreeNode*> que;
		if (root != NULL) que.push(root);
		while (!que.empty()) {
			int size = que.size();
			for (int i = 0; i < size; i++) {
				TreeNode* node = que.front();
				que.pop();
				swap(node->left, node->right); // �ڵ㴦��
				if (node->left) que.push(node->left);
				if (node->right) que.push(node->right);
			}
		}
		return root;
	}
};

/*��44�� ����һ���������ĸ��ڵ� root �� ������Ƿ���Գơ�
*/

class Solution {
public:
	bool compare(TreeNode* left, TreeNode* right) {
		//�����ų��սڵ����
		if (left == nullptr && right != nullptr) {
			return false;
		}else if (left != nullptr && right == nullptr) {
			return false;
		}else if (left == nullptr && right == nullptr) {
			return true;
		}else if (left->val != right->val) {
			return false;
		}//�ų���ֵ��ͬ�����
		//ʣ�µľ������ҽڵ㲻Ϊ�գ�����ֵ��ͬ�����
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

//��֦
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

/*��45�� �������ö������ĸ��ڵ� p �� q ����дһ���������������������Ƿ���ͬ��
����������ڽṹ����ͬ�����ҽڵ������ͬ��ֵ������Ϊ��������ͬ�ġ�

*/

class Solution {
public:
	bool compare(TreeNode* p, TreeNode* q) {
		//�ų������пսڵ�����
		if (p == nullptr && q != nullptr) {
			return false;
		}else if (p != nullptr && q == nullptr) {
			return false;
		}else if (p == nullptr && q == nullptr) {
			return true;
		}else if (p->val != q->val) {//��ʼ���ǲ��ǿ��������
			return false;
		}else {
			return compare(p->left, q->left) && compare(p->right, q->right);
		}
	}
	bool isSameTree(TreeNode* p, TreeNode* q) {
		return compare(p, q);
	}
};

/*��46�� �������ö����� root �� subRoot ������ root ���Ƿ������ subRoot ������ͬ�ṹ�ͽڵ�ֵ��������
������ڣ����� true �����򣬷��� false ��
������ tree ��һ���������� tree ��ĳ���ڵ������ڵ�����к���ڵ㡣
tree Ҳ���Կ����������һ��������
*/

class Solution {
public:
	bool compare(TreeNode* p, TreeNode* q) {//�ж�������ͬ�ĺ���
		//�ų������пսڵ�����
		if (p == nullptr && q != nullptr) {
			return false;
		}
		else if (p != nullptr && q == nullptr) {
			return false;
		}
		else if (p == nullptr && q == nullptr) {
			return true;
		}
		else if (p->val != q->val) {//��ʼ���ǲ��ǿ��������
			return false;
		}
		else {
			return compare(p->left, q->left) && compare(p->right, q->right);
		}
	}
	bool isSubtree(TreeNode* root, TreeNode* subRoot) {
		if (!root) { //root�������ߵ���
			return false;
		}
		if (compare(root, subRoot)) {
			return true;
		}
		return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot); //���Ϊ��Ͳ������ұ��ˣ������ǻ��ϵ
	}
};

/*��47�� ����һ�� N �������ҵ��������ȡ�
��������ָ�Ӹ��ڵ㵽��ԶҶ�ӽڵ���·���ϵĽڵ�������
N �������밴����������л���ʾ��ÿ���ӽڵ��ɿ�ֵ�ָ�
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
		for (auto child : root->children) {//int i = 0; i < root->children.size(); i++ auto���ִ�
			depth = max(depth, maxDepth(child));//root->children[i]
		}
		return depth + 1;
	}
};*/

/* ��48�� ����һ�� ��ȫ������ �ĸ��ڵ� root ����������Ľڵ������
��ȫ������ �Ķ������£�����ȫ�������У�������ײ�ڵ����û�����⣬����ÿ��ڵ������ﵽ���ֵ������������һ��Ľڵ㶼�����ڸò�����ߵ�����λ�á�
����ײ�Ϊ�� h �㣬��ò���� 1~ 2h ���ڵ�
*/

class Solution {//����ݹ�
public:
	int countNodes(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		return 1 + countNodes(root->left) + countNodes(root->right);
	}
};

/* ��49�� ����һ�����������ж����Ƿ��Ǹ߶�ƽ��Ķ�������
*/

class Solution {//�Ƚϸ߶��ú������
public:
	//�����Ըýڵ�Ϊ���ڵ�Ķ������ĸ߶ȣ�������Ƿ���-1
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

//��50�� ����һ���������ĸ��ڵ� root ���� ����˳�� ���������дӸ��ڵ㵽Ҷ�ӽڵ��·����

class Solution {//ǰ����� �е�Ѿ� ���һ��
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
			path.pop_back();//����
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


class Solution {//��֦
private:

	void traversal(TreeNode* cur, string path, vector<string>& result) {
		path += to_string(cur->val); // ��
		if (cur->left == NULL && cur->right == NULL) {
			result.push_back(path);
			return;
		}
		if (cur->left) traversal(cur->left, path + "->", result); // ��
		if (cur->right) traversal(cur->right, path + "->", result); // ��
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

//��51�� �����������ĸ��ڵ� root ������������Ҷ��֮�͡�

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

/*��52�� ����һ���������� ���ڵ� root�����ҳ��ö������� ��ײ� ����� �ڵ��ֵ��
�����������������һ���ڵ㡣
*/

class Solution {//����������Ž�
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

/*��53�� ����������ĸ��ڵ� root ��һ����ʾĿ��͵����� targetSum ��
�жϸ������Ƿ���� ���ڵ㵽Ҷ�ӽڵ� ��·��������·�������нڵ�ֵ��ӵ���Ŀ��� targetSum ��
������ڣ����� true �����򣬷��� false ��
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

class Solution {//��֦
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























//Ѱ��Ԫ��
/*class Solution {
public:
	int getValue(vector<int>& nums, int n) {//Ѱ��һ��������������һ�����Ԫ��
		int i, Major, count = 1;//Major���������ѡԪ��
		Major = nums[0];
		for (i = 1;i < n;i++) {
			if (nums[i] == Major) {
				count++;//��������Ԫ�ؼ���
			}else {
				if (count > 0) {//��������Ԫ�ص����
					count--;
				}else {
					Major = nums[i];//������ѡԪ�أ����¼���
					count = 1;
				}
			}
		}
		if (count > 0) {
			for (i = count = 0;i < n;i++) {
				if (nums[i] == Major) {//ͳ�ƺ�ѡԪ�س��ֵ�ʵ�ʴ���
					count++;
				}
			}
		}
		if (count > n / 2) {
			return Major;//ȷ��Ԫ��
		}else {
			return 0;//�������򷵻�
		}
	}
};//Ҳ����ʹ�ü������򣬵��ǻ�ʹ�ø������飬������ռ価��С��Ҫ��
*/

