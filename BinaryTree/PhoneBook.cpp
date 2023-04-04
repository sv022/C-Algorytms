#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
	Node *left;
	Node *right;
	string name;
	vector <string> numbers;

	int cnt;
	Node(string _val, string number) {
		name = _val;
		numbers.push_back(number);
		left = nullptr;
		right = nullptr;
		cnt = 1;
	}
	Node(string _val) {
		name = _val;
		left = nullptr;
		right = nullptr;
		cnt = 1;
	}
};

// Node* new_Node(int _val) {
//  Node* node = new Node;
//  node->name = _val;
//  node->left = nullptr;
//  node->right = nullptr;
//  node->cnt = 1;
//  return node;
// }

class Tree {
private:
	int lnt;

public:
	Node *root;
	Tree() {
		root = nullptr;
		lnt = 0;
	}

	void addNode(string _val, string _number) {
		Node *newNode = new Node(_val, _number);
		if (root == nullptr) {
			root = newNode;
			return;
		}
		Node *tempNode = root;
		while (true) {
			if (_val < tempNode->name) {
				if (tempNode->left != nullptr) {
					tempNode = tempNode->left;
					continue;
				}
				else {
					tempNode->left = newNode;
					return;
				}
			}
			else if (_val > tempNode->name)
			{
				if (tempNode->right != nullptr) {
					tempNode = tempNode->right;
					continue;
				}
				else {
					tempNode->right = newNode;
					return;
				}
			}
			else {
				tempNode->cnt++;
				return;
			}
		}
	};

	void addNode(string _val) {
		Node *newNode = new Node(_val);
		if (root == nullptr) {
			root = newNode;
			return;
		}
		Node *tempNode = root;
		while (true) {
			if (_val < tempNode->name) {
				if (tempNode->left != nullptr) {
					tempNode = tempNode->left;
					continue;
				}
				else {
					tempNode->left = newNode;
					return;
				}
			}
			else if (_val > tempNode->name)
			{
				if (tempNode->right != nullptr) {
					tempNode = tempNode->right;
					continue;
				}
				else {
					tempNode->right = newNode;
					return;
				}
			}
			else {
				tempNode->cnt++;
				return;
			}
		}
	};

	int depth(Node *node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			int lDepth = depth(node->left);
			int rDepth = depth(node->right);
			if (lDepth > rDepth) {
				return lDepth + 1;
			}
			return rDepth + 1;
		}
	};

	void PrintNames(Node *temp) {
		if (temp != nullptr) {
			PrintNames(temp->left);
			cout << temp->name << ' ';
			PrintNames(temp->right);
		}
		if (temp == root) cout << '\n';
	};

	Node *search(string _v)
	{
		Node *temp = root;
		if (temp == nullptr) {
			return nullptr;
		}
		while (true)
		{
			if (_v == temp->name)
				return temp;
			if (_v < temp->name)
			{
				if (temp->left != nullptr)
					temp = temp->left;
				else
					return nullptr;
			}
			else if (_v > temp->name)
			{
				if (temp->right != nullptr)
					temp = temp->right;
				else
					return nullptr;
			}
		}
	}

	void GetNumbers(string _name){
		Node *temp = search(_name);
		cout << "All numbers for " << _name << ": ";
		for (int i = 0; i < temp->numbers.size(); i++){
			cout << temp->numbers[i] << ' ';
		}
		cout << '\n';
		delete temp;
	}

	void addnumber(string _name, string _number){
		Node *temp = search(_name);
		(temp->numbers).push_back(_number);
	}

	// void delTree() {
	// 	root = nullptr;
	// }

	void deleteNode(string _v) {
		Node *parent = nullptr;
		Node *temp = root;
		while (temp != nullptr && temp->name != _v) {
			parent = temp;
			if (_v < temp->name) temp = temp->left;
			else temp = temp->right;
		}
		if (temp == nullptr) return;
		if (temp->left == nullptr && temp->right == nullptr) {
			if (temp == root) {
				root = nullptr;
			}
			else if (temp == parent->left) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
			delete temp;
		}
		else if (temp->left == nullptr) {
			if (temp == root) {
				root = temp->right;
			}
			else if (temp == parent->left) {
				parent->left = temp->right;
			}
			else {
				parent->right = temp->right;
			}
			delete temp;
		}
		  else if (temp->right == nullptr) { 
   				if (temp == root) { 
    			root = temp->left;
				} else if (temp == parent->left) {
					parent->left = temp->left;
				} else { 
    				parent->right = temp->left;
				} 
		delete temp; 
    } 
		else {
			Node *min = temp->right;
			while (min->left != nullptr) {
				min = min->left;
			}
			temp->name = min->name;
			deleteNode(min->name);
		}
		lnt--;
	}
};

int main()
{
	Tree tree;
	int n = 5;
	string names[5] = {"jeff", "nik", "vlat", "lox", "name"};
	string numbers[5] = {"534458", "632832", "237859", "834925", "847311"};
	for (int i = 0; i < n; i++) {
		tree.addNode(names[i], numbers[i]);
	}
	tree.PrintNames(tree.root);
	tree.deleteNode("jeff");
	tree.PrintNames(tree.root);
	tree.addnumber("vlat", "390847");
	tree.GetNumbers("vlat");
}