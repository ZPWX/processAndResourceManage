#pragma once
/************************************************************************/
/* Ωªª•Ω‚Œˆ¿‡£∫*/
/************************************************************************/

#include <iostream>

class Shell
{
public:
	Shell(void);
	~Shell(void);

	//read user input and execute
	bool read(std::string input);
	//Create init process
	void init();
	//Create corresponding process
	bool createProcess();
	//Delete corresponding process
	bool deleteProcess();
	//Apply for resource
	bool requestResource();
	//Release resource
	bool releaseResource();
	//Clock interrupt
	bool timeInt();
	//Look process information
	bool listProcess();
	//Look resource information
	bool listResource();

};

