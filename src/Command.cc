#include "headers/Command.hh"
#include <string>
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

void Command::execute () {
    struct stat buf;
    
    if(strcmp(argArr[0], "exit") == 0){
        exit(0);
    }
    
    if(testType == false){
        pass = false;
        pid_t pid = fork();
    
        if (pid < 0) {                                                      // fork failed
               perror("Fork() failed.");
           }
        else if (pid == 0) {
            if (execvp(argArr[0], argArr) == -1) {
              perror("Command Error.");
            }
            exit(0);
        }
        else {
            while(wait(0) != pid);
            pass = true;
        }
    } else {
        //cout << "1" << endl;
        if(arguments.size() > 2) {
            //cout << "2" << endl;
            string s = arguments.at(2);
            char* uI = new char[arguments.at(2).size() + 1];
            strcpy(uI, s.c_str());
            //cout << "3" << endl;
	    //this->printArgs();
	    //cout << uI << endl;
            if(stat(uI, &buf) == -1){
		//cout << "4" << endl;
                cout << "(FALSE)" << endl;
                cout << "Path not found" << endl;     
            } else {
		//cout << "5" << endl;
                if((arguments.at(1) == "-f") && ((buf.st_mode & S_IFMT) == S_IFREG)){
                    cout << "(TRUE)" << endl;
                    pass = true;
                } else if((arguments.at(1) == "-d") && ((buf.st_mode & S_IFMT) == S_IFDIR)) {
                    cout << "(TRUE)" << endl;
                    pass = true;
                } else if((arguments.at(1) == "-e") && (((buf.st_mode & S_IFMT) == S_IFDIR) || ((buf.st_mode & S_IFMT) == S_IFREG))) {
                    cout << "(TRUE)" << endl;
                    pass = true;
                } else {
                    cout << "(FALSE)" << endl;
                }
            }
        } else {
            cout << "(FALSE)" << endl;
            cout << "Incorrect Syntax" << endl;
        }    
    }
}

// sets userInput to input
void Command::setInput(string input) {
    userInput = input;
}

// separates string by spaces and places each string block into a vector and char * array
void Command::parse() {
    
    if (userInput.size() < 1) {
        return;
    }
    
    unsigned int itrArr = 0;
    
    size_t begin = userInput.find_first_not_of(" ");
    size_t end = userInput.find_last_not_of(" ");
    size_t size = end - begin + 1;
    
    userInput = userInput.substr(begin, size);
    
    char * cstrUserInput = new char [userInput.length() + 1];
    strcpy(cstrUserInput, userInput.c_str());
    char * token = strtok(cstrUserInput, " ");
    
    while (token != NULL) {
        arguments.push_back(token);
        argArr[itrArr] = token;
        token = strtok(NULL,  " ");
        itrArr++;
    }

    unsigned int i = 0;
    end = arguments.at(i).find('[');
    
    if(arguments.at(i) == "test"){
        testType = true;
        //cout << "found test" << endl;
    }
    else if(end != std::string::npos){
        i = arguments.size() - 1;
        end = arguments.at(i).find(']');
        
        if(end != std::string::npos){
            testType = true;
            //cout << "found test" << endl;
        }
        else {
            testType = false;
            //cout << "no test found" << endl;
        }
    }
    else {
        testType = false;
        //cout << "no test" << endl;
    }

    return;
}

// outputs userInput
void Command::printInput() {
    cout << "Command::printInput(): " << userInput << endl;
}

// outputs arguments vector
void Command::printArgs() {
    for (unsigned int i = 0; i < arguments.size(); i++) {
        cout << "Command::printArgs(): " << arguments.at(i) << endl;
    }
    return;
}

// returns userInput
string Command::getInput() {
    return userInput;
}

// returns arguments vector
vector<string> Command::getArgs() {
    return arguments;
}

// returns char * array
char ** Command::getArr() {
    return argArr;
}

// sets pass to true
void Command::passed() {
    pass = true;
    return;
}

// sets pass to false
void Command::failed() {
    pass = false;
    return;
}

// returns pass
bool Command::getPass() {
    return pass;
}

//return testType
bool Command::isTest() {
    return testType;
}
