#include <iostream>
#include <initializer_list>

template<typename T>
class SingleLinkedList {
	private:
		struct Node {
		T data;
		Node* next;
		Node(const T& _data) : data(_data), next(nullptr) {}
		};

		Node* head;
		Node* currentPos;

	public:
		SingleLinkedList() : head(nullptr), currentPos(nullptr) {}

		SingleLinkedList(std::initializer_list<T> initList) : 
		head(nullptr), currentPos(nullptr) {
			for (const T& value : initList) {
				insert(value);
			}
		}

		SingleLinkedList& operator=(SingleLinkedList& other) {
			Node* currentPosBak = other.currentPos;
			other.currentPos = other.head;
			while (other.currentPos) {
				insert(other.getCurrentVal());
				other.currentPos = other.currentPos->next;
			}
			other.currentPos = currentPosBak;
			return *this;
		}

		bool isEmpty() const {
			return head == nullptr;
		}

		void insert(T _val) {
			Node* newNode = new Node(_val);
			if (isEmpty()) {
				currentPos = newNode; 
				head = currentPos;
			} else {
				newNode->next = currentPos->next;
				currentPos->next = newNode;
				currentPos = currentPos->next;
			}
		}

		T getCurrentVal() const {
			if (currentPos == nullptr) {
				std::cerr << "Empty current position! Can't get value!" << std::endl;
				std::exit(EXIT_FAILURE);
			}
			return currentPos->data;
		}

		void setCurrentVal(const T& _val) {
			if (currentPos == nullptr) {
				std::cerr << "Empty current position! Can't set value!" << std::endl;
				std::exit(EXIT_FAILURE);
			}
			currentPos->data = _val;
			return;
		}

		// Change `remove()` such that `remove()` remove `currentPos` 
		// and `currentPos` point to the next node (if `next` not null)
		// otherwise point to the previous node. (if 'next' nullptr). 
		
		void remove() {
			if (isEmpty()) return;
			if (head == currentPos && currentPos) {
				currentPos = currentPos->next;
				delete head;
				head = currentPos;
			} else if (head == currentPos) {
				delete currentPos;
				head = nullptr;
			} else {
				Node* prev = head;
				while (prev->next != currentPos) prev = prev->next;
				if (currentPos) {
					prev->next = currentPos->next;
					delete currentPos;
					currentPos = prev->next;
				} else {
					delete currentPos;
					currentPos = prev;
				}
			}
			return;
		}

		bool find(T _val) {
			currentPos = head;
			while (currentPos && currentPos->data != _val) currentPos = currentPos->next;
			return currentPos != nullptr;
		}

		void printList() {
			Node* trav = head;
			while (trav != nullptr) {
				std::cout << trav->data << " ";
				trav = trav->next;
			}
			std::cout << std::endl;
		}
};

int main() {
	SingleLinkedList<int> a{1, 2, 3, 4, 5};
	int a_get = a.getCurrentVal();
	std::cout << a_get << std::endl;

	SingleLinkedList<char> b{'a','c','e'};
	b.setCurrentVal('g');
	b.printList(); //测试【定义值】操作是否正确，包括可能的空链表测试(//部分)，每种情况9分
	SingleLinkedList<char> e;
	std::cout << b.isEmpty() << " " << e.isEmpty() << std::endl; //测试【空链表判断】操作是否正确，18分
	SingleLinkedList<double> c1;
	SingleLinkedList<double> c2{1.5,2.0,9.0,4.7};
	SingleLinkedList<double> c3;
	c3 = c2;
	c1.insert(3.0);
	c2.insert(8.8);
	bool f_c3 = c3.find(2.0);
	c3.insert(8.8);
	c1.printList();
	c2.printList();
	c3.printList(); //测试【插入】操作是否正确，每种情况6分

	e.remove();
	c1.remove();
	bool f = c2.find(9.0);
	c2.remove();
	e.printList();
	c1.printList();
	c2.printList(); //测试【删除】操作是否正确，每种情况6分

	return 0;
}
