#pragma once
#include <string>

class RBT
{
public:
	RBT();
	~RBT();
	void insert(std::string input);
	void list();
	void search(std::string input);
	int getHeight();
	void calculateHeight();
};

