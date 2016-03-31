#pragma once
#include <string>
#include <chrono>

class BST
{
public:
	BST();
	~BST();
	void insert(std::string input);
	void list();
	void printStats();
	void setInsertTime(std::chrono::duration<double> insertTime);
private:
	struct Node {
		Node* parent = nullptr;
		Node* leftChild = nullptr;
		Node* rightChild = nullptr;
		std::string value;
		int count = 1;
	};
	int treeHeight = 0;
	long itemsInTree = 0;
	long uniqueItemsInTree = 0;	
	long keyComparisons = 0;
	long nodePointerChanges = 0;
	std::chrono::duration<double> totalInsertTime;
	void setStats();
	void printNodeInfo(Node* node);
	Node* Root;
	void traverseSetStats(Node* node, int nodeHeight);
	void traverseAndPrint(Node* node);
};

