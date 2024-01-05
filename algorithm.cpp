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

/* ��25�� 
*/

class Solution {//����
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		unordered_set<int> result_set; // ��Ž����֮������set��Ϊ�˸������ȥ��
		int hash[1005] = { 0 }; // Ĭ����ֵΪ0
		for (int num : nums1) { // nums1�г��ֵ���ĸ��hash����������¼
			hash[num] = 1;
		}
		for (int num : nums2) { // nums2�г��ֻ���result��¼
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
		unordered_set<int> result_set; // ��Ž����֮������set��Ϊ�˸������ȥ��
		unordered_set<int> nums_set(nums1.begin(), nums1.end());
		for (int num : nums2) {
			// ����nums2��Ԫ�� ��nums_set���ֳ��ֹ�
			if (nums_set.find(num) != nums_set.end()) {
				result_set.insert(num);
			}
		}
		return vector<int>(result_set.begin(), result_set.end());
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

