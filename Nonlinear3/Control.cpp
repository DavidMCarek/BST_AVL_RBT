#include "stdafx.h"
#include "Control.h"
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>


Control::Control()
{
}


Control::~Control()
{
}

void Control::baseLineFileRead(char delimeters[11], std::string filePath)
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
	fileReadTime = end - start;
}

std::chrono::duration<double> Control::getFileReadTime()
{
	return fileReadTime;
}

