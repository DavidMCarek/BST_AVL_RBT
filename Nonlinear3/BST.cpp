#include "stdafx.h"
#include "BST.h"
#include <iostream>
#include <string>


BST::BST()
{
	Root = nullptr;
}


BST::~BST()
{
	if (Root == nullptr)
		return;
	deleteRemainingNodes(Root);
	Root = nullptr;
}

// recurse through the tree and delete all nodes left on the tree
void BST::deleteRemainingNodes(Node* node)
{
	// if the current node has any children it will go down until it hits a leaf
	if (node->leftChild != nullptr)
		deleteRemainingNodes(node->leftChild);
	if (node->rightChild != nullptr)
		deleteRemainingNodes(node->rightChild);

	// if the leaf has no parent it is th root and can just be deleted
	if (node->parent == nullptr)
	{
		delete node;
		return;
	}
	// if the node is a left child the pointer from parent to left child is set to null
	else if (node->parent->leftChild == node)
		node->parent->leftChild = nullptr;
	// else the node is a right child and the pointer from parent to right child is set to null
	else
		node->parent->rightChild = nullptr;

	// now that there are no references left the node gets deleted
	delete node;
	
}

// this will insert a new node to the tree if the value is not already in the tree
// if the input value is in the tree then the count will be incremented
void BST::insert(std::string input)
{
	Node* currentNode = Root;
	Node* previousNode = nullptr;

	// keep getting the next node until we hit a null leaf or the input value matches the value of a node
	// if the values match then the count gets incremented and we return from the function
	while (currentNode != nullptr)
	{
		previousNode = currentNode;
		if (input.compare(currentNode->value) < 0)
			currentNode = currentNode->leftChild;
		else if (input.compare(currentNode->value) > 0)
			currentNode = currentNode->rightChild;
		else
		{
			currentNode->count = currentNode->count++;
			printNodeInfo(currentNode);
			return;
		}
	}

	// since we are at a null leaf we need to create a new node and set its value to the input
	currentNode = new Node();
	currentNode->value = input;
	printNodeInfo(currentNode);

	// if the previous node is null then it must be the root so we need to set the root node
	// to the current node
	// else we need to set the current nodes parent and the parents child to the current node
	if (previousNode == nullptr)
		Root = currentNode;
	else
	{
		currentNode->parent = previousNode;

		if (currentNode->value.compare(previousNode->value) < 0)
			previousNode->leftChild = currentNode;
		else
			previousNode->rightChild = currentNode;
	}	
}

// prints the value and count of a node
void BST::printNodeInfo(Node* node)
{
	std::cout << node->value << " " << node->count << std::endl;
}

void BST::calculateHeight()
{ 
	treeHeight = 0;
	if (Root == nullptr)
		return;
	
	// if the set is not empty traverse the list in order and output the node values and counts
	traverse(Root, treeHeight);
}

// recurse through the tree printing the nodes in order
void BST::traverse(Node* node, int nodeHeight)
{
	if (node->leftChild != nullptr)
		traverse(node->leftChild, nodeHeight + 1);

	if (node->rightChild != nullptr)
		traverse(node->rightChild, nodeHeight + 1);

	if (nodeHeight > treeHeight)
		treeHeight = nodeHeight;
}


// prints the nodes value and count based on a users string
void BST::search(std::string input)
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
BST::Node* BST::nodeLookup(std::string input)
{
	Node* currentNode = Root;

	// until a nullptr or the input string is found keep traversing down the the tree
	// if a nullptr is found then the string is not in the tree
	while (true)
	{
		// traverse left if input is < node value as long as lch not null
		if (input.compare(currentNode->value) < 0)
		{
			if (currentNode->leftChild == nullptr)
			{
				std::cout << std::endl;
				return nullptr;
			}
			currentNode = currentNode->leftChild;
		}
		// traverse right if input is > node value as long as rch not null
		else if (input.compare(currentNode->value) > 0)
		{
			if (currentNode->rightChild == nullptr)
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

int BST::getHeight()
{
	return treeHeight;
}