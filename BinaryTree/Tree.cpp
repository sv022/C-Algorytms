#include <iostream>

using namespace std;

struct Node
{
	Node *left;
	Node *right;
	int val;
	int cnt;
	Node(int _val)
	{
		val = _val;
		left = nullptr;
		right = nullptr;
		cnt = 1;
	}
};

// Node* new_Node(int _val) {
//  Node* node = new Node;
//  node->val = _val;
//  node->left = nullptr;
//  node->right = nullptr;
//  node->cnt = 1;
//  return node;
// }

class Tree
{
private:
	int lnt;

public:
	Node *root;
	Tree()
	{
		root = nullptr;
		lnt = 0;
	}

	void addNode(int _val)
	{
		Node *newNode = new Node(_val);
		if (root == nullptr) {
			root = newNode;
			return;
		}
		Node *tempNode = root;
		while (true) {
			if (_val < tempNode->val) {
				if (tempNode->left != nullptr) {
					tempNode = tempNode->left;
					continue;
				}
				else {
					tempNode->left = newNode;
					return;
				}
			}
			else if (_val > tempNode->val)
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

	void printTree(Node *temp) {
		if (temp != nullptr) {
			printTree(temp->left);
			cout << temp->val << ' ';
			printTree(temp->right);
		}
		if (temp == root) cout << '\n';
	};

	Node *search(int _v)
	{
		Node *temp = root;
		if (temp == nullptr)
		{
			return nullptr;
		}
		while (true)
		{
			if (_v == temp->val)
				return temp;
			if (_v < temp->val)
			{
				if (temp->left != nullptr)
					temp = temp->left;
				else
					return nullptr;
			}
			else if (_v > temp->val)
			{
				if (temp->right != nullptr)
					temp = temp->right;
				else
					return nullptr;
			}
		}
	}

	// void delTree() {
	// 	root = nullptr;
	// }

	void deleteNode(int _v) {
		Node *parent = nullptr;
		Node *temp = root;
		while (temp != nullptr && temp->val != _v) {
			parent = temp;
			if (_v < temp->val) temp = temp->left;
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
			temp->val = min->val;
			deleteNode(min->val);
		}
		lnt--;
	}
};

int randint(int n)
{
	return rand() % n + 1;
}

int main()
{
	Tree tree;
	int n = 10;
	for (int i = 0; i < n; i++)
	{
		tree.addNode(randint(10));
	}
	tree.printTree(tree.root);
	tree.deleteNode(5);
}