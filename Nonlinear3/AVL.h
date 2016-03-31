#pragma once
#include <string>

class AVL
{
public:
	AVL();
	~AVL();
	void insert(std::string input);
	void list(); 
	void search(std::string input);
	void printStats();
	void setStats();
private:
	struct Node {
		Node * leftChild = nullptr;
		Node * rightChild = nullptr;
		std::string value;
		int count = 1;
		int balanceFactor = 0;
	};
	int treeHeight = 0;
	long itemsInTree = 0;
	long uniqueItemsInTree = 0;
	void traverseSetStats(Node* node, int nodeHeight);
	Node * Root;
	Node * nodeLookup(std::string input);
	void traverseAndPrint(Node * node);
	void printNodeInfo(Node * node);
};

