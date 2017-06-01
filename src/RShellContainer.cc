#include "headers/RShellContainer.hh"
#include "headers/Command.hh"
#include "headers/Connector.hh"
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

// sets userInput with input
void RShellContainer::getInput(string input) {
    userInput = input;
    return;
}

// pushes command into Commands vector
void RShellContainer::addCommand(Command * command) {
    Commands.push_back(command);
    return;
}

// pushes connect into Connectors vector
void RShellContainer::addConnector(Connector * connect) {
    Connectors.push_back(connect);
    return;
}


// Parse userInput into a commands vector and a connectors vector
void RShellContainer::parse() {
    string tempStr;                                                             // holds string blocks between connectors and edges
    
    if (userInput.length() == 0) {                                              // if empty input string
        return;
    }
    
    char * cstrUserInput = new char [userInput.length() + 1];                   // + 1 for \0 (null character)
    strcpy(cstrUserInput, userInput.c_str());                                   // convert input string to cstring
    
    char * token = strtok(cstrUserInput, ";|&#");                               // seperates string blocks from Connector symbols
    
    while (token != NULL) {                                                     // creates a Command using token and 
        addCommand(new Command(token));                                         // pushes it onto Command Vector
        token = strtok(NULL, ";|&#");
    }
    
    unsigned itr = 0;
    bool mult = false;                                                          // determines if there will be two connects in series
    while (itr < userInput.length()) {
        if ((itr + 1) >= userInput.length()) {}
        else if (userInput[itr] == ';' && !mult) {
            addConnector(new Connector(";"));
            mult = true;
        }
        else if (userInput[itr] == '#' && !mult) {
            addConnector(new Connector("#"));
            mult = true;
        }
        else if (userInput[itr] == '|' && userInput[itr + 1] == '|' && !mult) {
            addConnector(new Connector("||"));
            mult = true;
        }
        else if (userInput[itr] == '&' && userInput[itr + 1] == '&' && !mult) {
            addConnector(new Connector("&&"));
            mult = true;
        }
        else if (userInput[itr] != ' ' && userInput[itr] != ';' && 
                 userInput[itr] != '#' && userInput[itr] != '|' && 
                 userInput[itr] != '&') {
            mult = false;
        }
        else {}
        
        itr++;
    }
    
    if ((Commands.size() - Connectors.size()) != 1) {                           // Commands should have one more element than Connectors
        perror("Error: Incorrect number of commands to connects.\n");
    }
    
    for (unsigned int i = 0; i < Commands.size(); i++) {                        // parses each element in Commands Vector
        Commands.at(i)->parse();
    }
    
    return;
}

// executes Commands in Commands vector
void RShellContainer::execute() {                                               // executes all Commands within Commands vector
    if (Commands.size() == 0) {                                                 // using Connectors vector to determine if a
        return;                                                                 // Command will run
    }
    
    pass = true;                                                        // bool to determine if next Command will run or not
    
    for (unsigned i = 0; i < Commands.size(); i++) {
        
        // fork process
        if (pass) {
            Commands.at(i)->execute();
            
        }
        
        // change cntPass depending on whether command passed and connector
        if (Connectors.size() > i) {
            if (Connectors.at(i)->getType() == ";") {
                pass = true;
            }
            else if (Connectors.at(i)->getType() == "#") {
                return;
            }
            else if (Connectors.at(i)->getType() == "&&") {
                if (Commands.at(i)->getPass()) {
                    pass = true;
                }
                else {
                    pass = false;
                }
            }
            else if (Connectors.at(i)->getType() == "&&") {
                if (Commands.at(i)->getPass()) {
                    pass = false;
                }
                else {
                    pass = true;
                }
            }
        }
    }
}

// clears Commands and Connectors vectors. ERROR WITH FUNCTION FIX ASAP
void RShellContainer::clear() {
    Commands.clear();
    Connectors.clear();
    return;
}

// outputs userInput string
void RShellContainer::printInput() {
    cout << "RShellContainer::PrintInput(): " << userInput << endl;
}

// outputs each Command in Commands vector using Command::printInput()
void RShellContainer::printCommandsInput() {
    cout << "RShellContainer::PrintCommandsInput(): " << endl;
    
    if (Commands.size() < 1) {
        return;
    }
    
    for (unsigned int i = 0; i < Commands.size(); i++) {
        Commands.at(i)->printInput();
    }
    return;
}

// outputs each Connector in Connectors vector using Connector::printInput()
void RShellContainer::printConnectors() {
    cout << "RShellContainer::PrintConnectors(): " << endl;
    
    if (Connectors.size() < 1) {
        return;
    }
    
    for (unsigned int i = 0; i < Connectors.size(); i++) {
        Connectors.at(i)->printInput();
    }
}

// outputs each argument of each Command in Commands vector using Command::printArgs()
void RShellContainer::printCommandsArgs() {
    cout << "RShellContainer::PrintCommandsArgs(): " << endl;
    
    if (Commands.size() < 1) {
        return;
    }
    
    for (unsigned int i = 0; i < Commands.size(); i++) {
        Commands.at(i)->printArgs();
    }
    return;
}

bool RShellContainer::getPass() {
    return pass;
}
