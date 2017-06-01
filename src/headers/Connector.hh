#ifndef connector_hh
#define connector_hh

#include "RShellBase.hh"
#include <string>

using namespace std;

class Connector: public RShellBase {
	protected:
		string Type;
	public:
	    	Connector() { };
	    	Connector(string input) : Type(input) { };
		void execute();
		void parse();
		void setType(string input);
	    	string getType();
	    	void printInput();
};

#endif
