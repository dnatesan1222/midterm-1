// COMSC-210 | Midterm #1 | Diksha Tara Natesan
// IDE used: Vim/Terminal

#include <iostream>	//imports cpp standard library that allows cout to be used
using namespace std;	//allows usage of cout/endl for output and other features if necessary without needing to do std:: before each individual usage
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;	//constant values are set so they can be referenced later formin/max values/sizes
class DoublyLinkedList {	//header for a class which is an object
	private:	//private access for the struct, head, and tail so they can only be accessed within the object or through methods in the public access. promotes security in each DLL that is created
		struct Node {	//struct header
			int data;	//instance variable for the struct - the data that is stored in a node
			Node* prev;	//pointer to the previous node of the list (stores the address so that node can be accessed)
			Node* next;	//pointer to the next node in the list (stores the address, not an instance variable)
			Node(int val, Node* p = nullptr, Node* n = nullptr) {	//struct constructor? initializes the members of the struct (data, prev, and next)
				data = val;	//sets data to store the inputted value
				prev = p;	//initializes to nullptr
				next = n;	//initializes to nullptr
			}	//end of struct function
		};	//end of struct
		Node* head;	//pointer for DLL object to first/head node
		Node* tail;	//pointer for DLL object to last/tail node
	public:		//public access for these methods so the DLL can be manipulated in main()/driver. promotes security of the DLL's head and tail
		DoublyLinkedList() { head = nullptr; tail = nullptr; }	//default constructor initializes head + tail pointer to nullptr when DLL is first created as the list starts empty
		void insert_after(int value, int position) {	//DLL method header. takes two parameters: node value and node position at which the new node should be placed after
			if (position < 0) {	//if statement ensures the position entered is >=0
				cout << "Position must be >= 0." << endl;	//gives the user an error message if not
				return;		//stops the rest of the method from running because the method should not work for negative values
			}	//end of if block
			Node* newNode = new Node(value);	//creates a new node with the argument value's value stored in data and newNode stires the address at which the node is located
			if (!head) {	//checks if the list is empty
				head = tail = newNode;	//if so, the address stored in newNode pointer becomes the same address stored in the head/tail pointers because this is the only node in the list so the head and tail both point to one node address
				return;		//stops the rest of the method from running because the node was added and the position isn't something that needed to be accounted for because the list was originally empty
			}	//end of if block
			Node* temp = head;	//creates a temporary pointer to store the location at which the head node is at
			for (int i = 0; i < position && temp; ++i)	//for loop finds the node at the position from the argument and ensures temp stays within the list's bounds
				temp = temp->next;	//sets pointer to the next pointer until correct pos is found
			if (!temp) {	//check if the pos was out of bounds
				cout << "Position exceeds list size. Node not inserted.\n";	//error message
				delete newNode;		//delete the stored pointer to free up space
				return;		//ends the method once it is discovered that the pos is invalid
			}
			newNode->next = temp->next;	//set the new node's next pointer to the next pointer of the temp node
			newNode->prev = temp;		//set the new node's prev pointer to the pointer of the temp node so the new node is wedged between those two nodes
			if (temp->next)	//check if the node after the inserted node exists so its prev pointer can be edited to point to this newly created node
				temp->next->prev = newNode;
			else	//if the next node in the list doesn't exist, update the tail pointer because the newly added node is the new tail of the DLL
				tail = newNode;
			temp->next = newNode;	//make sure the node that originally existed in the list points to the new node as the next node as well
		}
		void delete_val(int value) {
			if (!head) return;	//checks if list is empty
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
