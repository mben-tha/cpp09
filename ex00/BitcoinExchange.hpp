#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class	BitcoinExchange
{
public:
	void	convert(std::string const &date, float const amount);
	void	fillData();

private:
	std::map<std::string, float>	m_data;
};

#endif