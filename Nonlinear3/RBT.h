#pragma once
#include <string>

class RBT
{
public:
	RBT();
	~RBT();
	void insert(std::string input);
	void list();
	void search(std::string input);
	int getHeight();
	void setStats();
	void printStats();
private:
	struct Node {
		Node * leftChild = nullptr;
		Node * rightChild = nullptr;
		Node * parent = nullptr;
		std::string value;
		int count = 1;
		bool color = true; // red = True, black = False
	};
	int treeHeight = 0;
	long itemsInTree = 0;
	long uniqueItemsInTree = 0;
	void fixup(Node * node);
	void leftRotate(Node * node);
	void rightRotate(Node * node);
	void traverseSetStats(Node* node, int nodeHeight);
	Node * Root;
	Node * nil;
	Node * nodeLookup(std::string input);
	void traverseAndPrint(Node * node);
	void printNodeInfo(Node * node);
};

