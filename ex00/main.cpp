#include "BitcoinExchange.hpp"

#include <fstream>
#include <istream>
#include <cstdlib>
#include <string>
#include <iostream>

bool	extract(std::string line, std::string &date, std::string &literal)
{
	std::string::size_type	pos(0);

	pos = line.find('|');
	if (pos == std::string::npos)
		return false;

	date = line.substr(0, pos);
	literal = line.substr(pos + 1);

	std::string::size_type start = date.find_first_not_of(" \t");
    if (start == std::string::npos)
        return false;
    date = date.substr(start);

    std::string::size_type end = date.find_last_not_of(" \t");
    date = date.substr(0, end + 1);

    start = literal.find_first_not_of(" \t");
    if (start == std::string::npos)
        return false;
    literal = literal.substr(start);

    end = literal.find_last_not_of(" \t");
    literal = literal.substr(0, end + 1);

	return true;
}

bool isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;
    return false;
}

bool checkDate(std::string const &date)
{
    if (date.size() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    if (!isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[2]) || !isdigit(date[3])
	|| !isdigit(date[5]) || !isdigit(date[6]) || !isdigit(date[8]) || !isdigit(date[9]))
            return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;

    int maxDay = 31;

    if (month == 2)
    {
        if (isLeapYear(year))
            maxDay = 29;
        else
            maxDay = 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        maxDay = 30;
    }

    if (day < 1 || day > maxDay)
        return false;

    return true;
}

bool	checkValue(std::string const &literal, float &value)
{
	if (literal.empty())
        return false;

    std::string::size_type i = 0;
    bool point = false;

    if (literal[i] == '-')
        return false;

    for (; i < literal.size(); i++)
    {
        if (literal[i] == '.')
        {
            if (point)
                return false;
            point = true;
        }
        else if (!std::isdigit(literal[i]))
        {
            return false;
        }
    }

    char *end;
    value = std::strtof(literal.c_str(), &end);

    if (*end != '\0')
        return false;

    if (value < 0 || value > 1000)
        return false;

    return true;
}

int main(int ac, char **av)
{
	if (ac != 2)
        return (std::cerr << "Error: bad arguments" << std::endl, 1);

    BitcoinExchange test;
    test.fillData();

    std::ifstream input(av[1]);
    if (!input)
    {
        std::cerr << "Error: could not open file" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(input, line);
    if (line != "date | value")
    {
        std::cerr << "Error: bad header" << std::endl;
        return 1;
    }

    std::string date;
    std::string literal;
    float value;

    while (std::getline(input, line))
    {
        if (!extract(line, date, literal))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (!checkDate(date))
        {
            std::cerr << "Error: bad date => " << date << std::endl;
            continue;
        }

        if (!checkValue(literal, value))
        {
            std::cerr << "Error: bad value => " << literal << std::endl;
            continue;
        }

        test.convert(date, value);
    }

    return 0;
}
