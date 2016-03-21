#pragma once
#include <string>

class CommandValidator
{
public:
	CommandValidator();
	~CommandValidator();
	void setCommand(std::string command);
	bool isValidCommand();
	enum Command { Insert, Delete, Search, Min, Max, Next, Previous, List, Help, Exit, Invalid };
	Command getCurrentCommand();
private:
	Command currentCommand;
	std::string toLower(std::string input);
};

