#include "BitcoinExchange.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

void BitcoinExchange::fillData()
{
    std::ifstream file("data.csv");
    if (!file)
    {
        std::cerr << "Error: could not open database file" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::string::size_type pos = line.find(',');
        if (pos == std::string::npos)
            continue;

        std::string date = line.substr(0, pos);
        std::string valueStr = line.substr(pos + 1);

        float value = std::strtof(valueStr.c_str(), NULL);

        m_data[date] = value;
    }
}

void BitcoinExchange::convert(std::string const &date, float const amount)
{
    if (m_data.empty())
    {
        std::cerr << "Error: empty database" << std::endl;
        return;
    }

    std::map<std::string, float>::iterator it = m_data.lower_bound(date);

    if (it == m_data.end())
    {
        --it;
    }
    else if (it->first != date && it == m_data.begin())
    {
        std::cerr << "Error: no valid lower date for " << date << std::endl;
        return;
    }
    else if (it->first != date)
    {
        --it;
    }

    std::cout << date << " => " << amount << " = " << amount * it->second << std::endl;
}
