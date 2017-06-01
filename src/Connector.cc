#include "headers/Connector.hh"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

void Connector::execute() {
    
}

void Connector::parse() {
    
}

// sets Type to input
void Connector::setType(string input) {
    Type = input;
    return;
}

// returns Type
string Connector::getType() {
    return Type;
}

// outputs Type
void Connector::printInput() {
    cout << "Connector::printInput(): " << Type << endl;
}
