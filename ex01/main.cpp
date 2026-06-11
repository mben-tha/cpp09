#include "RPN.hpp"

#include <iostream>
#include <string>
#include <sstream>

int main(int ac, char **av)
{
	if (ac != 2)
        return (std::cerr << "Error: bad arguments" << std::endl, 1);

	RPN	rpn;
	rpn.calcul(av[1]);
	
	return 0;
}
