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
	int getHeight();
	void calculateHeight();
private:
	struct Node {
		Node* parent = nullptr;
		Node* leftChild = nullptr;
		Node* rightChild = nullptr;
		std::string value;
		int count = 1;
	};
	int treeHeight = 0;
	void printNodeInfo(Node* node);
	Node* Root;
	enum ChildDirection {Left, Right, Unknown};
	void traverseForHeight(Node* node, int nodeHeight);
	void traverseAndPrint(Node* node);
	Node* nodeLookup(std::string input);
	void deleteRemainingNodes(Node* node);
};

