#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include "Shell.h"

int main() {
	Shell* shell = new Shell();

	std::vector<std::string> instrucks;

	instrucks.push_back("cr firstProcess 2");
	instrucks.push_back("list_r");
	instrucks.push_back("cr secondProcess 1");
	instrucks.push_back("list_r");
	instrucks.push_back("list_p");
	instrucks.push_back("de firstProcess");
	instrucks.push_back("list_p");
	instrucks.push_back("list_r");
	instrucks.push_back("cr firstProcess 2");
	instrucks.push_back("cr secondProcess 1");
	instrucks.push_back("list_r");
	instrucks.push_back("list_p");
	instrucks.push_back("to");
	instrucks.push_back("list_r");
	instrucks.push_back("list_p");
	instrucks.push_back("cr P3 2");
	instrucks.push_back("cr P4 2");
	instrucks.push_back("list_r");
	instrucks.push_back("list_p");
	instrucks.push_back("rel");
	instrucks.push_back("list_r");
	instrucks.push_back("list_p");
	instrucks.push_back("cr P5 1");
	instrucks.push_back("cr P6 1");
	instrucks.push_back("list_r");
	instrucks.push_back("list_p");
	//instrucks.push_back("de secondProcess");
	//instrucks.push_back("list_p");
	//instrucks.push_back("cr thirdProcess 1");
	//instrucks.push_back("cr firstProcess 2");
	//instrucks.push_back("cr firstProcess 2");

	int index = 0;
	std::cout << ">>" << instrucks.at(index) << std::endl;
	while(shell->read(instrucks.at(index)) && index+1 < instrucks.size()) {
		++index;
		std::cout << std::endl;
		std::cout << ">>" << instrucks.at(index) << std::endl;
	}

	system("pause");
}