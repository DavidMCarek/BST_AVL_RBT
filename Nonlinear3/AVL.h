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
	int getHeight();
	void calculateHeight();
private:
	struct Node {
		Node * leftChild = nullptr;
		Node * rightChild = nullptr;
		std::string value;
		int count = 1;
		int balanceFactor = 0;
	};
	int treeHeight = 0;
	void traverseForHeight(Node* node, int nodeHeight);
	Node * Root;
	Node * nodeLookup(std::string input);
	bool updateBalanceFactors = false;
	void traverseAndPrint(Node * node);
	void printNodeInfo(Node * node);
};

