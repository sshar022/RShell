#ifndef command_hh
#define command_hh

#include "RShellBase.hh"
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Command: public RShellBase {
	protected:
		string userInput;
		vector<string> arguments;
		char * argArr[256];
		bool pass;
		bool testType;
	public:
		Command() { };
		Command(string input) : userInput(input) { };
		void execute();
		void setInput(string input);
		void parse();
		void printInput();
		void printArgs();
		string getInput();
		vector<string> getArgs();
		char ** getArr();
		void passed();
		void failed();
		bool getPass();
		bool isTest();
};

#endif
