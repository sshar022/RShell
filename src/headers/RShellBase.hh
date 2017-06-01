#ifndef rshellbase_hh
#define rshellbase_hh

class RShellBase {
	private:
	public:
		// Constructors
		RShellBase() { };
		
		// Pure Virtual Functions
		virtual void execute() = 0;
		virtual void parse() = 0;
};

#endif
