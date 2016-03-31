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
		}
		else if (input.compare(currentNode->value) > 0)
		{
			currentNode = currentNode->rightChild;
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
	if (previousNode == nil)
		Root = nodeToInsert;
	else
	{
		if (input.compare(previousNode->value) < 0)
			previousNode->leftChild = nodeToInsert;
		else
			previousNode->rightChild = nodeToInsert;
	}
	nodeToInsert->leftChild = nil;
	nodeToInsert->rightChild = nil;
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
				leftRotate(node->parent->parent);
			}
		}
	}
	Root->color = false;
}

void RBT::leftRotate(Node * node)
{
	Node * tempNode = node->rightChild;
	node->rightChild = tempNode->leftChild;
	if (tempNode != nil)
		tempNode->leftChild->parent = node;
	
	tempNode->parent = node->parent;
	if (node->parent == nil)
		Root = tempNode;
	else
	{
		if (node == node->parent->leftChild)
			node->parent->leftChild = tempNode;
		else
			node->parent->rightChild = tempNode;
	}
	
	tempNode->leftChild = node;
	node->parent = tempNode;
}

void RBT::rightRotate(Node * node)
{
	Node * tempNode = node->leftChild;
	node->leftChild = tempNode->rightChild;
	if (tempNode != nil)
		tempNode->rightChild->parent = node;

	tempNode->parent = node->parent;
	if (node->parent == nil)
		Root = tempNode;
	else
	{
		if (node == node->parent->rightChild)
			node->parent->rightChild = tempNode;
		else
			node->parent->leftChild = tempNode;
	}

	tempNode->rightChild = node;
	node->parent = tempNode;
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


// prints the nodes value and count based on a users string
void RBT::search(std::string input)
{
	// if the root is null then the set is empty and we need to print that the input was not found
	if (Root == nullptr)
	{
		std::cout << input << " 0" << std::endl;
		return;
	}

	Node* node = nodeLookup(input);
	// if the node was not found print that it was not found else print that nodes value and count
	if (node == nullptr)
		std::cout << input << " 0" << std::endl;
	else
		printNodeInfo(node);
}

// finds a node in the tree given a string
RBT::Node* RBT::nodeLookup(std::string input)
{
	Node * currentNode = Root;

	// until a nullptr or the input string is found keep traversing down the the tree
	// if a nullptr is found then the string is not in the tree
	while (true)
	{
		// traverse left if input is < node value as long as lch not null
		if (input.compare(currentNode->value) < 0)
		{
			if (currentNode->leftChild == nil)
			{
				std::cout << std::endl;
				return nullptr;
			}
			currentNode = currentNode->leftChild;
		}
		// traverse right if input is > node value as long as rch not null
		else if (input.compare(currentNode->value) > 0)
		{
			if (currentNode->rightChild == nil)
			{
				std::cout << std::endl;
				return nullptr;
			}
			currentNode = currentNode->rightChild;
		}
		// else the input == node value so we return that node
		else
		{
			return currentNode;
		}
	}
}

int RBT::getHeight()
{
	return treeHeight;
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

void RBT::printStats()
{
	std::cout << "Tree height : " << treeHeight << std::endl
		<< "Total items : " << itemsInTree << std::endl
		<< "Unique items : " << uniqueItemsInTree << std::endl;
}