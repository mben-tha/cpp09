#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <string>

class	RPN
{
public:
	void	calcul(std::string	input);

private:
	std::stack<int> m_tab;
};

#endif