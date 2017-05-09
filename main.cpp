#include <iostream>
#include <string>
#include <vector>
#include "Shell.h"

int main() {
	Shell* shell = new Shell();

	std::vector<std::string> instrucks;

	instrucks.push_back("cr firstProcess 2");
	instrucks.push_back("cr secondProcess 1");
	instrucks.push_back("cr thirdProcess 1");
	instrucks.push_back("cr firstProcess 2");
	instrucks.push_back("de firstProcess");

	int index = 0;
	std::cout << ">>" << instrucks.at(index) << std::endl;
	while(shell->read(instrucks.at(index)) && index+1 < instrucks.size()) {
		++index;
		std::cout << ">>" << instrucks.at(index) << std::endl;
	}

	system("pause");
}