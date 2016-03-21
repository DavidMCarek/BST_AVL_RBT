#include "stdafx.h"
#include "BinaryTree.h"
#include <iostream>
#include <string>


BinaryTree::BinaryTree()
{
	Root = nullptr;
}


BinaryTree::~BinaryTree()
{
	if (Root == nullptr)
		return;
	deleteRemainingNodes(Root);
	Root = nullptr;
}

// recurse through the tree and delete all nodes left on the tree
void BinaryTree::deleteRemainingNodes(Node* node)
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
void BinaryTree::insert(std::string input)
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
void BinaryTree::printNodeInfo(Node* node)
{
	std::cout << node->value << " " << node->count << std::endl;
}

// lists all nodes in the tree in ascending order
void BinaryTree::list()
{ 
	// if the root is null then the set is empty and we need to output a blank line and return
	if (Root == nullptr)
	{
		std::cout << std::endl;
		return;
	}
	// if the set is not empty traverse the list in order and output the node values and counts
	traverse(Root);
}

// recurse through the tree printing the nodes in order
void BinaryTree::traverse(Node* node)
{
	// if the nodes left child is not null keep going left and then print going back up until you can 
	// go right. then keep trying to go left again and repeat
	if (node->leftChild != nullptr)
		traverse(node->leftChild);
	
	printNodeInfo(node);

	if (node->rightChild != nullptr)
		traverse(node->rightChild);
}

// takes in a node and get the leftmost node based off of that nodes children
BinaryTree::Node* BinaryTree::getLeftmostNode(Node* node)
{
	while (true)
	{
		if (node->leftChild == nullptr)
			return node;
		else
			node = node->leftChild;
	}
}

// takes in a node and get the rightmost node based off of that nodes children
BinaryTree::Node* BinaryTree::getRightmostNode(Node* node)
{
	while (true)
	{
		if (node->rightChild == nullptr)
			return node;
		else
			node = node->rightChild;
	}
}

// prints the minimum node value on the tree
void BinaryTree::min()
{
	// if the root exists then start at the root and go left until the left pointer is null
	if (Root == nullptr)
		std::cout << std::endl;
	else
	{
		Node* node = getLeftmostNode(Root);
		std::cout << node->value << std::endl;
	}
}

// prints the maximum node value on the tree
void BinaryTree::max()
{
	// if the root exists then start at the root and go right until the right pointer is null
	if (Root == nullptr)
		std::cout << std::endl;
	else
	{
		Node* node = getRightmostNode(Root);
		std::cout << node->value << std::endl;
	}
}

// prints the nodes value and count based on a users string
void BinaryTree::search(std::string input)
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
BinaryTree::Node* BinaryTree::nodeLookup(std::string input)
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

// prints the successor of the node with value of input
void BinaryTree::next(std::string input)
{
	// if the root is null then print a blank line
	if (Root == nullptr)
	{
		std::cout << std::endl;
		return;
	}

	Node* node = nodeLookup(input);

	// if we cant find the node print a blank line
	if (node == nullptr)
	{
		std::cout << std::endl;
		return;
	}
	
	// if node has right child go as far left as possible from that child
	// else go up the tree until a node has a value larger than the original node
	// then print the node info
	if (node->rightChild != nullptr)
		node = getLeftmostNode(node->rightChild);
	else
	{
		std::string nodeValue = node->value;

		do
		{
			if (node->parent != nullptr)
				node = node->parent;
			else
			{
				std::cout << std::endl;
				return;
			}
		} while (nodeValue.compare(node->value) > 0);
	}

	std::cout << node->value << std::endl;
}

// prints the predecessor of the node that has the value of the input
void BinaryTree::previous(std::string input)
{
	// if the root is null then the set is empty, print a blank line
	if (Root == nullptr)
	{
		std::cout << std::endl;
		return;
	}

	Node* node = nodeLookup(input);

	// if the node cannot be found print a blank line
	if (node == nullptr)
	{
		std::cout << std::endl;
		return;
	}

	// if node has left child go as far right as possible from that child
	// else go up the tree until a node is found that has a value less than the original node value
	// then print the node info
	if (node->leftChild != nullptr)
		node = getRightmostNode(node->leftChild);
	else
	{
		std::string nodeValue = node->value;

		do
		{
			if (node->parent != nullptr)
				node = node->parent;
			else
			{
				std::cout << std::endl;
				return;
			}
		} while (nodeValue.compare(node->value) < 0);
	}

	std::cout << node->value << std::endl;
}

// decrements the count of a node with count larger than one or removes a node with count of one
void BinaryTree::deleteInput(std::string input)
{
	// if root is null then the set is empty so output the input string and a count of -1
	if (Root == nullptr)
	{
		std::cout << input << " -1" << std::endl;
		return;
	}
	Node* node = nodeLookup(input);

	// if node not found then print out the input string and -1
	if (node == nullptr)
	{
		std::cout << input << " -1" << std::endl;
		return;
	}
	// else decrement the count and print the node info
	// if the count is 0 we need to remove the node
	else
	{
		node->count = node->count--;
		printNodeInfo(node);

		if (node->count < 1)
			removeNode(node);
	}
}

// removes a node from the tree
void BinaryTree::removeNode(Node* node)
{
	// if the node has no left child replace the node with its right child
	if (node->leftChild == nullptr)
		transplant(node, node->rightChild);
	// if the node has no right child replace the node with its left child
	else if (node->rightChild == nullptr)
		transplant(node, node->leftChild);
	// else the node has 2 or no children and we need to find the nodes successor to replace it
	else
	{
		// if the successor's parent is not the original node replace the successor with its right child
		// then set the successor's right child equal to the original node's right child
		// then set the successor's parent equal to the successor
		Node* next = getLeftmostNode(node->rightChild);
		if (next->parent != node)
		{
			transplant(next, next->rightChild);
			next->rightChild = node->rightChild;
			next->parent = next;
		}
		// then the original node gets replaced by the successor
		// the successor's left child is set to the original nodes left child
		// and the successors left child's parent is set to the successor
		transplant(node, next);
		next->leftChild = node->leftChild;
		next->leftChild->parent = next;
	}

	delete node;
}

// replaces the primary node with the secondary one
void BinaryTree::transplant(Node* primary, Node* secondary)
{
	// if the primary node's parent is null then the primary is the root so the seecondary becomes
	// the new root
	if (primary->parent == nullptr)
		Root = secondary;
	// if the primary node is its parent's left child then the primary node's parent's left child is 
	// set to the secondary node
	else if (primary == primary->parent->leftChild)
		primary->parent->leftChild = secondary;
	// else the primary nodes parent's right child is set to the secondary node
	else
		primary->parent->rightChild = secondary;

	// if the secondary node is not null then its parent needs to be set to the primary node's parent to 
	// complete the replacement
	if (secondary != nullptr)
		secondary->parent = primary->parent;
}