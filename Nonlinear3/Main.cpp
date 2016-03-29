// EECS 2510 : BST VS AVL VS RBT
// David Carek

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Control.h"
#include "BST.h"
#include "AVL.h"

using namespace std;

int main()
{
	void insertBST(char delimeters[11], string inputFilePath, BST & tree);
	void insertAVL(char delimeters[11], string inputFilePath, AVL & tree);

	string inputFilePath = "C:\\Users\\DMCar\\Desktop\\Shakespeare.txt";
	char delimeters[11] = { 9 , 10 , 13 , 32 , '.' , ',' , '!' , ';' , ':' , '(' , ')' };

	Control control;
	control.baseLineFileRead(delimeters, inputFilePath);

	/*BST bst;
	insertBST(delimeters, inputFilePath, bst);

	AVL avl;
	insertAVL(delimeters, inputFilePath, avl);*/

	// then we wait for the user to finish viewing the data
	cout << "Processing finished. Press ENTER to exit" << endl;
	char waitChar;
	cin.get(waitChar);
    return 0;
}

void insertAVL(char delimeters[11], string filePath, AVL & tree)
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
				{
					//tree.list();
					//cout << endl;
					tree.insert(nextWord);
				}
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
}

void insertBST(char delimeters[11], string filePath, BST & tree)
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
}