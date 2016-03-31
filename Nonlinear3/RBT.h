#pragma once
#include <string>
#include <chrono>

class RBT
{
public:
	RBT();
	~RBT();
	void insert(std::string input); //inserts a node into the tree
	void list(); // prints all elements of the tree in order with the counts
	void printStats(); // displays statistics for the tree
	void setInsertTime(std::chrono::duration<double> insertTime);
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
	long keyComparisons = 0;
	long nodePointerChanges = 0;
	long recolorings = 0;
	std::chrono::duration<double> totalInsertTime;
	void setStats(); // sets and calculates some of the important
	void fixup(Node * node);
	void leftRotate(Node * node);
	void rightRotate(Node * node);
	void traverseSetStats(Node* node, int nodeHeight);
	Node * Root;
	Node * nil;
	void traverseAndPrint(Node * node);
	void printNodeInfo(Node * node);
};

