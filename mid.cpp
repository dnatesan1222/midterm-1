// COMSC-210 | Midterm #1 | Diksha Tara Natesan
// IDE used: Vim/Terminal

#include <iostream>	//imports cpp standard library that allows cout to be used
using namespace std;	//allows usage of cout/endl for output and other features if necessary without needing to do std:: before each individual usage
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;	//constant values are set so they can be referenced later formin/max values/sizes
class DoublyLinkedList {	//header for a class which is an object
	private:	//private access for the struct, head, and tail so they can only be accessed within the object or through methods in the public access. promotes security in each DLL that is created
		struct Node {	//struct header
			int data;	//instance variable - the data that is stored in a node
			Node* prev;	//pointer to the previous node of the list (stores the address so that node can be accessed)
			Node* next;	//pointer to the next node in the list (stores the address, not an instance variable)
			Node(int val, Node* p = nullptr, Node* n = nullptr) {	//struct constructor? initializes the members of the struct (data, prev, and next)
				data = val;
				prev = p;
				next = n;
			}
		};
		Node* head;
		Node* tail;
	public:
		DoublyLinkedList() { head = nullptr; tail = nullptr; }
		void insert_after(int value, int position) {
			if (position < 0) {
				cout << "Position must be >= 0." << endl;
				return;
			}
			Node* newNode = new Node(value);
			if (!head) {
				head = tail = newNode;
				return;
			}
			Node* temp = head;
			for (int i = 0; i < position && temp; ++i)
				temp = temp->next;
			if (!temp) {
				cout << "Position exceeds list size. Node not inserted.\n";
				delete newNode;
				return;
			}
			newNode->next = temp->next;
			newNode->prev = temp;
			if (temp->next)
				temp->next->prev = newNode;
			else
				tail = newNode;
			temp->next = newNode;
		}
		void delete_val(int value) {
			if (!head) return;
			Node* temp = head;
			while (temp && temp->data != value)
				temp = temp->next;
			if (!temp) return;
			if (temp->prev)
				temp->prev->next = temp->next;
			else
				head = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			else
				tail = temp->prev;
			delete temp;
		}
		void delete_pos(int pos) {
			if (!head) {
				cout << "List is empty." << endl;
				return;
			}
			if (pos == 1) {
				pop_front();
				return;
			}
			Node* temp = head;
			for (int i = 1; i < pos; i++){
				if (!temp) {
					cout << "Position doesn't exist." << endl;
					return;
				}
				else
					temp = temp->next;
			}
			if (!temp) {
				cout << "Position doesn't exist." << endl;
				return;
			}
			if (!temp->next) {
				pop_back();
				return;
			}
			Node* tempPrev = temp->prev;
			tempPrev->next = temp->next;
			temp->next->prev = tempPrev;
			delete temp;
		}
		void push_back(int v) {
			Node* newNode = new Node(v);
			if (!tail)
				head = tail = newNode;
			else {
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			}
		}
		void push_front(int v) {
			Node* newNode = new Node(v);
			if (!head)
				head = tail = newNode;
			else {
				newNode->next = head;
				head->prev = newNode;
				head = newNode;
			}
		}
		void pop_front() {
			if (!head) {
				cout << "List is empty." << endl;
				return;
			}
			Node * temp = head;
			if (head->next) {
				head = head->next;
				head->prev = nullptr;
			}
			else
				head = tail = nullptr;
			delete temp;
		}
		void pop_back() {
			if (!tail) {
				cout << "List is empty." << endl;
				return;
			}
			Node * temp = tail;
			if (tail->prev) {
				tail = tail->prev;
				tail->next = nullptr;
			}
			else
				head = tail = nullptr;
			delete temp;
		}
		~DoublyLinkedList() {
			while (head) {
				Node* temp = head;
				head = head->next;
				delete temp;
			}
		}
		void print() {
			Node* current = head;
			if (!current) {
				cout << "List is empty." << endl;
				return;
			}
			while (current) {
				cout << current->data << " ";
				current = current->next;
			}
			cout << endl;
		}
		void print_reverse() {
			Node* current = tail;
			if (!current) {
				cout << "List is empty." << endl;
				return;
			}
			while (current) {
				cout << current->data << " ";
				current = current->prev;
			}
			cout << endl;
		}
		void every_other_element(){
			Node* current = head;
			if (!current) {
                                cout << "List is empty." << endl;
                                return;
                        }
			int even = 0;
			while (current) {
                                if (even%2 == 0)
                                        cout << current->data << " ";
				current = current->next;
				even += 1;
                        }
			cout << endl;
		}
};
int main() {
	DoublyLinkedList list;
	list.every_other_element();
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
        list.push_back(4);
	list.push_back(5);
        list.push_back(6);
	list.push_back(7);
	list.print();
	list.every_other_element();

	cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
	return 0;
}
