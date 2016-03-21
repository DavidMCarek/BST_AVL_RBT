
#include "stdafx.h"
#include "CommandValidator.h"
#include <string>

CommandValidator::CommandValidator(){}

CommandValidator::~CommandValidator(){}

// sets the command enum based on the input command 
void CommandValidator::setCommand(std::string command)
{
	// we need to make sure that the command is set to all lowercase when checking its value
	command = toLower(command);

	currentCommand = Invalid;
	if (command == "exit")
		currentCommand = Exit;
	else if (command == "insert")
		currentCommand = Insert;
	else if (command == "delete")
		currentCommand = Delete;
	else if (command == "search")
		currentCommand = Search;
	else if (command == "min")
		currentCommand = Min;
	else if (command == "max")
		currentCommand = Max;
	else if (command == "next")
		currentCommand = Next;
	else if (command == "prev")
		currentCommand = Previous;
	else if (command == "list")
		currentCommand = List;
	else if (command == "help")
		currentCommand = Help;

}

CommandValidator::Command CommandValidator::getCurrentCommand() 
{
	return currentCommand;
}

bool CommandValidator::isValidCommand()
{
	return currentCommand != Invalid;
}

// takes in a string and makes all letters lowercase
std::string CommandValidator::toLower(std::string input)
{
	std::string lowerInput = "";

	// iterate through the characters of the input and if the character is uppercase
	// tolower will convert it to a lowercase char and then append it to the new string
	for (int i = 0; i < input.length(); i++)
	{
		std::string lowercaseChar = std::string(1, tolower(input[i]));
		lowerInput.append(lowercaseChar);
	}

	return lowerInput;
}