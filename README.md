Rshell 
======
UCR CS100 Assignment3

Authors and Contributors
------------
David Nguyen

Shashank Sharma

Files
-----
```
Command.cc
Command.hh
Connector.cc
Connector.hh
LICENSE
main.cpp
README.md
RShellBase.cc
RShellBase.hh
RShellContainer.cc
RShellContainer.hh
```

Bugs
-----
Parenthetical precedence operator not implemented, due to errors. Current version contains working 
test functionality and no code relating to precedence operator.

Bugs in current version:
1. Exits regardless of preceding operator if exit is called after system call. 
2. If "#" is at	the beginning of input, program will throw an out_of_range error on strcmp. (Parsing error)
3. Will exit out of "test" command with more than one argument instead of throwing error, returning false, 
   and continuing to process commands inputed by user.
4. Will take "[asdf" as a valid  command for test, works similarly with "asdfsf]"
5. Does not throw error when incompatible option (ie. -o, -zp, etc.) is used with test


