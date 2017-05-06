#include <iostream>
#include <string>
#include <vector>
#include "Shell.h"

int main() {
	Shell* shell = new Shell();

	std::vector<std::string> instrucks;
	std::string input = "cr first 1";
	instrucks.push_back(input);
	input = "de first";
	instrucks.push_back(input);
	input = "req res 3";
	instrucks.push_back(input);
	input = "rel res";
	instrucks.push_back(input);
	input = "to";
	instrucks.push_back(input);
	input = "list_p";
	instrucks.push_back(input);
	input = "list_r";
	instrucks.push_back(input);

	int index = 0;
	std::cout << ">>" << instrucks.at(index) << std::endl;
	while(shell->read(instrucks.at(index)) && index+1 < instrucks.size()) {
		++index;
		std::cout << ">>" << instrucks.at(index) << std::endl;
	}

	system("pause");
}