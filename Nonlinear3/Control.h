#pragma once
#include <string>
#include <chrono>

class Control
{
public:
	Control();
	~Control();
	void baseLineFileRead(char delimeters[11], std::string filePath);
	std::chrono::duration<double> getFileReadTime();
private:
	std::chrono::duration<double> fileReadTime;
};

