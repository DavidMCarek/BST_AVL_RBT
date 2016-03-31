// EECS 2510 : BST VS AVL VS RBT
// David Carek

//883299
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Control.h"
#include "BST.h"
#include "AVL.h"
#include "RBT.h"

using namespace std;

int main()
{
	void insertBST(char delimeters[11], string inputFilePath, BST & tree, Control control);
	void insertAVL(char delimeters[11], string inputFilePath, AVL & tree, Control control);
	void insertRBT(char delimeters[11], string inputFilePath, RBT & tree, Control control);

	bool worstCaseTest = false;

	string inputFilePath = "C:\\Users\\DMCar\\Desktop\\Shakespeare.txt";
	char delimeters[11] = { 9 , 10 , 13 , 32 , '.' , ',' , '!' , ';' , ':' , '(' , ')' };

	Control control;
	control.baseLineFileRead(delimeters, inputFilePath);


	if (worstCaseTest)
	{
		RBT RBT_T; // instantiate each of the trees
		AVL AVL_T;
		BST BST_T;
		char chari[10];
		for (int i = 0; i<10; i++) chari[i] = '\0';
		for (int i = 1001; i <= 9200; i++) // insert 8200 strings in BST
		{
			RBT_T.insert(to_string(i));
		}
		for (int i = 1001; i <= 9200; i++) // insert 8200 strings in AVL Tree
		{
			AVL_T.insert(to_string(i));
		}
		for (int i = 1001; i <= 9200; i++) // insert 8200 strings in RBT
		{
			BST_T.insert(to_string(i));
		}

		BST_T.printStats();
		AVL_T.printStats();
		RBT_T.printStats();
	}
	else
	{
		BST bst;
		insertBST(delimeters, inputFilePath, bst, control);
		bst.printStats();

		AVL avl;
		insertAVL(delimeters, inputFilePath, avl, control);
		avl.printStats();

		RBT rbt;
		insertRBT(delimeters, inputFilePath, rbt, control);
		rbt.printStats();
	}

	// then we wait for the user to finish viewing the data
	cout << "Processing finished. Press ENTER to exit" << endl;
	char waitChar;
	cin.get(waitChar);
    return 0;
}

void insertRBT(char delimeters[11], string filePath, RBT & tree, Control control)
{
	std::ifstream inputStream;
	inputStream.open(filePath, std::ios::binary);

	// if we couldn't open the file, let the user know and return
	if (inputStream.fail())
	{
		std::cout << "Could not open file" << std::endl;
		return;
	}

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	std::string nextWord = "";

	bool isDelimeter = false;
	char nextChar;
	inputStream.get(nextChar);

	while (!inputStream.eof())
	{
		for each (char delimeter in delimeters)
		{
			if (nextChar == delimeter)
			{
				if (nextWord != "")	
					tree.insert(nextWord);
				
				nextWord = "";
				isDelimeter = true;
			}
		}

		if (!isDelimeter)
			nextWord.push_back((unsigned char)nextChar);

		isDelimeter = false;

		inputStream.get(nextChar);
	}

	end = std::chrono::system_clock::now();
	tree.setInsertTime(end - start - control.getFileReadTime());
}

void insertAVL(char delimeters[11], string filePath, AVL & tree, Control control)
{
	std::ifstream inputStream;
	inputStream.open(filePath, std::ios::binary);

	// if we couldn't open the file, let the user know and return
	if (inputStream.fail())
	{
		std::cout << "Could not open file" << std::endl;
		return;
	}

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	std::string nextWord = "";

	bool isDelimeter = false;
	char nextChar;
	inputStream.get(nextChar);

	while (!inputStream.eof())
	{
		for each (char delimeter in delimeters)
		{
			if (nextChar == delimeter)
			{
				if (nextWord != "")
					tree.insert(nextWord);

				nextWord = "";
				isDelimeter = true;
			}
		}

		if (!isDelimeter)
			nextWord.push_back((unsigned char)nextChar);

		isDelimeter = false;

		inputStream.get(nextChar);
	}

	end = std::chrono::system_clock::now();
	tree.setInsertTime(end - start - control.getFileReadTime());
}

void insertBST(char delimeters[11], string filePath, BST & tree, Control control)
{
	std::ifstream inputStream;
	inputStream.open(filePath, std::ios::binary);

	// if we couldn't open the file, let the user know and return
	if (inputStream.fail())
	{
		std::cout << "Could not open file" << std::endl;
		return;
	}

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	std::string nextWord = "";

	bool isDelimeter = false;
	char nextChar;
	inputStream.get(nextChar);

	while (!inputStream.eof())
	{
		for each (char delimeter in delimeters)
		{
			if (nextChar == delimeter)
			{
				if (nextWord != "")
					tree.insert(nextWord);

				nextWord = "";
				isDelimeter = true;
			}
		}

		if (!isDelimeter)
			nextWord.push_back((unsigned char)nextChar);

		isDelimeter = false;

		inputStream.get(nextChar);
	}

	end = std::chrono::system_clock::now();
	tree.setInsertTime(end - start - control.getFileReadTime());
}