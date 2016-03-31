#include "stdafx.h"
#include "RBT.h"
#include <string>
#include <iostream>

RBT::RBT()
{
	nil = new Node();
	nil->color = false;
	nil->count = 0;
	nil->leftChild = Root;
	nil->rightChild = Root;
}


RBT::~RBT()
{
}

void RBT::insert(std::string input)
{
	if (Root == nullptr)
	{
		Root = new Node();
		Root->value = input;
		Root->leftChild = nil;
		Root->rightChild = nil;
		Root->parent = nil;
		Root->color = false;
		nodePointerChanges += 3;
		return;
	}

	Node * currentNode = Root;
	Node * previousNode = nil;
	while (currentNode != nil)
	{
		previousNode = currentNode;

		if (input.compare(currentNode->value) < 0)
		{
			currentNode = currentNode->leftChild;
			keyComparisons++;
		}
		else if (input.compare(currentNode->value) > 0)
		{
			currentNode = currentNode->rightChild;
			keyComparisons++;
		}
		else
		{
			currentNode->count++;
			return;
		}
	}

	Node * nodeToInsert = new Node();
	nodeToInsert->value = input;
	nodeToInsert->parent = previousNode;
	nodePointerChanges++;

	if (previousNode == nil)
		Root = nodeToInsert;
	else
	{
		if (input.compare(previousNode->value) < 0)
			previousNode->leftChild = nodeToInsert;
		else
			previousNode->rightChild = nodeToInsert;

		keyComparisons++;
		nodePointerChanges++;
	}
	nodeToInsert->leftChild = nil;
	nodeToInsert->rightChild = nil;
	nodePointerChanges += 2;

	fixup(nodeToInsert);
}

void RBT::fixup(Node * node)
{
	while (node->parent->color)
	{
		if (node->parent == node->parent->parent->leftChild)
		{
			Node * uncle = node->parent->parent->rightChild;
			if (uncle->color)
			{
				node->parent->color = false;
				uncle->color = false;
				node->parent->parent->color = true;
				recolorings += 3;

				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->rightChild)
				{
					node = node->parent;
					leftRotate(node);
				}
				node->parent->color = false;
				node->parent->parent->color = true;
				recolorings += 2;

				rightRotate(node->parent->parent);
			}
		}
		else
		{
			Node * uncle = node->parent->parent->leftChild;
			if (uncle->color)
			{
				node->parent->color = false;
				uncle->color = false;
				node->parent->parent->color = true;
				recolorings += 3;

				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->leftChild)
				{
					node = node->parent;
					rightRotate(node);
				}
				node->parent->color = false;
				node->parent->parent->color = true;
				recolorings += 2;
				leftRotate(node->parent->parent);
			}
		}
	}
	Root->color = false;
	recolorings++;
}

void RBT::leftRotate(Node * node)
{
	Node * tempNode = node->rightChild;
	node->rightChild = tempNode->leftChild;
	nodePointerChanges++;

	if (tempNode != nil)
	{
		tempNode->leftChild->parent = node;
		nodePointerChanges++;
	}
	
	tempNode->parent = node->parent;
	nodePointerChanges++;

	if (node->parent == nil)
		Root = tempNode;
	else
	{
		if (node == node->parent->leftChild)
			node->parent->leftChild = tempNode;
		else
			node->parent->rightChild = tempNode;

		nodePointerChanges++;
	}
	
	tempNode->leftChild = node;
	node->parent = tempNode;

	nodePointerChanges += 2;
}

void RBT::rightRotate(Node * node)
{
	Node * tempNode = node->leftChild;
	node->leftChild = tempNode->rightChild;
	nodePointerChanges++;

	if (tempNode != nil)
	{
		tempNode->rightChild->parent = node;
		nodePointerChanges++;
	}

	tempNode->parent = node->parent;
	nodePointerChanges++;

	if (node->parent == nil)
		Root = tempNode;
	else
	{
		if (node == node->parent->rightChild)
			node->parent->rightChild = tempNode;
		else
			node->parent->leftChild = tempNode;

		nodePointerChanges++;
	}

	tempNode->rightChild = node;
	node->parent = tempNode;

	nodePointerChanges += 2;
}

// prints the value and count of a node
void RBT::printNodeInfo(Node* node)
{
	std::cout << node->value << " " << node->count << std::endl;
}

void RBT::setStats()
{
	treeHeight = 0;
	uniqueItemsInTree = 0;
	itemsInTree = 0;
	if (Root == nullptr)
		return;

	// if the set is not empty traverse the list in order and output the node values and counts
	traverseSetStats(Root, treeHeight);
}

// recurse through the tree setting important statistics
void RBT::traverseSetStats(Node* node, int nodeHeight)
{
	uniqueItemsInTree++;
	itemsInTree += node->count;
	if (node->leftChild != nil)
		traverseSetStats(node->leftChild, nodeHeight + 1);

	if (node->rightChild != nil)
		traverseSetStats(node->rightChild, nodeHeight + 1);

	if (nodeHeight > treeHeight)
		treeHeight = nodeHeight;
}

void RBT::list()
{
	// if the root is null then the set is empty and we need to output a blank line and return
	if (Root == nullptr)
	{
		std::cout << std::endl;
		return;
	}
	// if the set is not empty traverse the list in order and output the node values and counts
	traverseAndPrint(Root);
}

// recurse through the tree printing the nodes in order
void RBT::traverseAndPrint(Node* node)
{
	// if the nodes left child is not null keep going left and then print going back up until you can 
	// go right. then keep trying to go left again and repeat
	if (node->leftChild != nil)
		traverseAndPrint(node->leftChild);

	printNodeInfo(node);

	if (node->rightChild != nil)
		traverseAndPrint(node->rightChild);
}

void RBT::setInsertTime(std::chrono::duration<double> insertTime)
{
	totalInsertTime = insertTime;
}

void RBT::printStats()
{
	setStats();

	std::cout
		<< "<----------RBT Statistics---------->" << std::endl
		<< "Tree height : " << treeHeight << std::endl
		<< "Total items : " << itemsInTree << std::endl
		<< "Unique items : " << uniqueItemsInTree << std::endl
		<< "Key comparisons : " << keyComparisons << std::endl
		<< "Node pointer changes : " << nodePointerChanges << std::endl
		<< "Node recolorings : " << recolorings << std::endl;
	printf("Insert time : %.3f s\n", totalInsertTime.count());
	std::cout
		<< "<---------------------------------->" << std::endl << std::endl;
}