// EECS 2510 : BST VS AVL VS RBT
// David Carek

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Control.h"

using namespace std;

int main()
{
	string inputFilePath = "C:\\Users\\DMCar\\Desktop\\Shakespeare.txt";
	char delimeters[11] = { 9 , 10 , 13 , 32 , '.' , ',' , '!' , ';' , ':' , '(' , ')' };

	Control control;
	control.baseLineFileRead(delimeters, inputFilePath);


	// then we wait for the user to finish viewing the data
	cout << "Processing finished. Press ENTER to exit" << endl;
	char waitChar;
	cin.get(waitChar);
    return 0;
}