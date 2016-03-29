#include "stdafx.h"
#include "AVL.h"
#include <string>
#include <iostream>

AVL::AVL()
{
}


AVL::~AVL()
{
}

void AVL::insert(std::string input)
{
	// If the root is null we only need to do a dumb insert and nothing else
	if (Root == nullptr)
	{
		Root = new Node();
		Root->value = input;
		return;
	}

	Node * p; // our current location on the tree
	Node * q; // lags behind current node
	Node * a; // the last parent of current node that had a balance factor of +- 1
	Node * f; // lags behind recent nonzero

	p = a = Root;
	q = f = nullptr;

	// while the current node is not at the child of a leaf or a duplicate value keep traversing through the tree
	// keeping track of the most recent nonzero balance factor node
	while (p != nullptr)
	{
		if (input.compare(p->value) == 0)
		{
			p->count++;
			return;
		}

		if (p->balanceFactor != 0)
		{
			a = p;
			f = q;
		}

		q = p;
		p = (input.compare(p->value) < 0) ? p->leftChild : p->rightChild;
	}

	// Now the previous node is a leaf and the current node is the child of that leaf so we need
	// to create a new node to insert

	// node to insert is y
	Node * y = new Node();
	y->value = input;
	Node * b; // this is the child of the most recent nonzero balance factor in the direction of the potential rotation
	int displacement; // this is used to correct balance factors later

	// we need to know if the new node we are inserting is the left or the right child of the previous node so we
	// can have the correct child pointer point to the new node
	if (input.compare(q->value) < 0)
		q->leftChild = y;
	else
		q->rightChild = y;

	// if the value of the node we just inserted is less than that of the most recent nonzero balance factor node
	// then we went left so the pivot needs to be the left child else its the right child
	// the displacement is set based on the direction taken

	if (input.compare(a->value) > 0)
	{
		p = a->rightChild;
		b = p;
		displacement = -1;
	}
	else
	{
		p = a->leftChild;
		b = p;
		displacement = 1;
	}


	// then we traverse down from the most recent nonzero balance factor node to the node we inserted setting balance factors
	// on the way down
	while (p != y)
	{
		if (input.compare(p->value) > 0)
		{
			p->balanceFactor = -1;
			p = p->rightChild;
		}
		else
		{
			p->balanceFactor = 1;
			p = p->leftChild;
		}
	}

	// if the tree was completely balanced recentNonZero will be at the root of the tree and our insert will
	// have pushed the tree slightly out of balance
	if (0 == a->balanceFactor)
	{
		a->balanceFactor = displacement;
		return;
	}

	// if the most reent nonzero balance factor is opposite the displacement then we put the tree back in balance 
	if (a->balanceFactor == -displacement)
	{
		a->balanceFactor = 0;
		return;
	}

	// At this point we have thrown the tree out of balance by inserting
	// the displacement tells us the first direction of the rotation 
	if (displacement == 1)
	{
		if (b->balanceFactor == 1) //LL
		{
			a->leftChild = b->rightChild;
			b->rightChild = a;
			a->balanceFactor = b->balanceFactor = 0;
		}
		else //LR
		{
			Node * c = b->rightChild;
			a->leftChild = c->rightChild;
			b->rightChild = c->leftChild;
			c->leftChild = b;
			c->rightChild = a;

			a->balanceFactor = b->balanceFactor = 0;
			
			if (c->balanceFactor == 1)
				a->balanceFactor = -1;
			else if (c->balanceFactor == -1)
				b->balanceFactor = 1;
			
			c->balanceFactor = 0;
			b = c;
		}
	}
	else
	{
		if (b->balanceFactor == -1) //RR
		{
			a->rightChild = b->leftChild;
			b->leftChild = a;
			a->balanceFactor = b->balanceFactor = 0;
		}
		else //RL
		{
			Node * c = b->leftChild;
			a->rightChild = c->leftChild;
			b->leftChild = c->rightChild;
			c->rightChild = b;
			c->leftChild = a;

			a->balanceFactor = b->balanceFactor = 0;

			if (c->balanceFactor == 1)
				b->balanceFactor = -1;
			else if (c->balanceFactor == -1)
				a->balanceFactor = 1;

			c->balanceFactor = 0;
			b = c;
		}
	}
	if (f == nullptr)
	{
		Root = b;
		return;
	}
		

	if (f->leftChild == a)
		f->leftChild = b;
	else
		f->rightChild = b;
}

void AVL::list()
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
void AVL::traverseAndPrint(Node * node)
{
	// if the nodes left child is not null keep going left and then print going back up until you can 
	// go right. then keep trying to go left again and repeat
	if (node->leftChild != nullptr)
		traverseAndPrint(node->leftChild);

	printNodeInfo(node);

	if (node->rightChild != nullptr)
		traverseAndPrint(node->rightChild);
}

void AVL::printNodeInfo(Node * node)
{
	std::cout << node->value << " " << node->count << std::endl;
}

// prints the nodes value and count based on a users string
void AVL::search(std::string input)
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

AVL::Node * AVL::nodeLookup(std::string input)
{
	Node * currentNode = Root;

	// until a nullptr or the input string is found keep traversing down the the tree
	// if a nullptr is found then the string is not in the tree
	while (true)
	{
		// traverse left if input is < node value as long as lch not null
		if (input.compare(currentNode->value) < 0)
		{
			if (currentNode->leftChild == nullptr)
				return nullptr;
			
			currentNode = currentNode->leftChild;
		}
		// traverse right if input is > node value as long as rch not null
		else if (input.compare(currentNode->value) > 0)
		{
			if (currentNode->rightChild == nullptr)
				return nullptr;
			
			currentNode = currentNode->rightChild;
		}
		// else the input == node value so we return that node
		else
		{
			return currentNode;
		}
	}
}

void AVL::calculateHeight()
{
	treeHeight = 0;
	if (Root == nullptr)
		return;

	// if the set is not empty traverse the list in order and output the node values and counts
	traverseForHeight(Root, treeHeight);
}

// recurse through the tree printing the nodes in order
void AVL::traverseForHeight(Node* node, int nodeHeight)
{
	if (node->leftChild != nullptr)
		traverseForHeight(node->leftChild, nodeHeight + 1);

	if (node->rightChild != nullptr)
		traverseForHeight(node->rightChild, nodeHeight + 1);

	if (nodeHeight > treeHeight)
		treeHeight = nodeHeight;
}

int AVL::getHeight()
{
	return treeHeight;
}