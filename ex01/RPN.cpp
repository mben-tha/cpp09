#include "RPN.hpp"

#include <string>
#include <sstream>
#include <stack>
#include <iostream>

void	RPN::calcul(std::string input)
{
	std::istringstream	literal(input);
	std::string			c;
	int					n1;
	int					n2;

	while (literal >> c)
	{
		if (isdigit(c[0]) && c.size() == 1)
			m_tab.push(c[0] - '0');
		else if (c[0] == '*' && c.size() == 1 && m_tab.size() >= 2)
		{
			n2 = m_tab.top();
			m_tab.pop();
			n1 = m_tab.top();
			m_tab.pop();
			m_tab.push(n1 * n2);
		}
		else if (c[0] == '/' && c.size() == 1 && m_tab.size() >= 2)
		{
			n2 = m_tab.top();
			if (n2 == 0)
			{
				std::cerr << "Error" << std::endl;
				return ;
			}
			m_tab.pop();
			n1 = m_tab.top();
			m_tab.pop();
			m_tab.push(n1 / n2);
		}
		else if (c[0] == '+' && c.size() == 1 && m_tab.size() >= 2)
		{
			n2 = m_tab.top();
			m_tab.pop();
			n1 = m_tab.top();
			m_tab.pop();
			m_tab.push(n1 + n2);
		}
		else if (c[0] == '-' && c.size() == 1 && m_tab.size() >= 2)
		{
			n2 = m_tab.top();
			m_tab.pop();
			n1 = m_tab.top();
			m_tab.pop();
			m_tab.push(n1 - n2);
		}
		else
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
	}
	if (m_tab.size() == 1)
		std::cout << m_tab.top() << std::endl;
	else
	{
		std::cerr << "Error" << std::endl;
		return ;
	}
}
