// request facilities for i/o from STANDARD LIBRARY
#include <iostream>
#include <string>

// main is required to return an int. zero indicates success
int main()
{
	// BASIC OUTPUT ----------------------
	// namespace::name
	// << is the LEFT-ASSOCIATIVE output operator
	// it takes as much as it can from the left, as little as posible from the right
	// returns left operand
	// std::cout << "Hello, world!" << std::endl;
	// std::cout and std::endl here have TYPE std::ostream
	// std::endl is a MANIPULATOR instead of a STRING-LITERAL
	// it causes << to manipulate the stream, then return it
	// ; silences return value
	
	// BASIC INPUT -----------------------
	std::cout << "Enter your name:";

	std::string name;
	std::cin >> name;

	std::cout << "Hello, " << name << "!" << std::endl;

	return 0;
}