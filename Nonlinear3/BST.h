#pragma once
#include <string>

class BST
{
public:
	BST();
	~BST();
	void insert(std::string input);
	void search(std::string input);
	void list();
	void printStats();
	void setStats();
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
	void printNodeInfo(Node* node);
	Node* Root;
	enum ChildDirection {Left, Right, Unknown};
	void traverseSetStats(Node* node, int nodeHeight);
	void traverseAndPrint(Node* node);
	Node* nodeLookup(std::string input);
	void deleteRemainingNodes(Node* node);
};

