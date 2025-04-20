/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 07:31:43 by jcheron           #+#    #+#             */
/*   Updated: 2025/04/20 13:50:13 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <limits>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
	this->data = other.data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		this->data = other.data;
	}
	return *this;
}

void	BitcoinExchange::loadDatabase(const std::string &filename) {
	std::ifstream	file(filename.c_str());

	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open database file.");
	}

	std::string	line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::stringstream	ss(line);
		std::string			date, valueStr;

		if (!std::getline(ss, date, ',') || !std::getline(ss, valueStr)) {
			continue;
		}
		float				value = static_cast<float>(std::atof(valueStr.c_str()));
		this->data[date] = value;
	}
	file.close();
}

bool	BitcoinExchange::isValidDate(const std::string &date) const {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	int		year = atoi(date.substr(0, 4).c_str());
	int		month = atoi(date.substr(5, 2).c_str());
	int		day = atoi(date.substr(8, 2).c_str());

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	return true;
}

void	BitcoinExchange::processInput(const std::string &filename) const {
	std::ifstream	file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string	line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::stringstream	ss(line);
		std::string			date, valueStr;

		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		trim(date);
		trim(valueStr);

		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		double				value;
		std::stringstream	valStream(valueStr);

		if (!(valStream >> value)) {
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}

		if (value < 0) {
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}

		if (value > 1000) {
			std::cerr << "Error: too large number." << std::endl;
			continue;
		}

		std::map<std::string, float>::const_iterator it = this->data.lower_bound(date);
		if (it == this->data.end() || it->first != date) {
			if (it == this->data.begin()) {
				std::cerr << "Error: no earlier date in database." <<std::endl;
				continue;
			}
		--it;
		}
		std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
	}
	file.close();
}

void	BitcoinExchange::trim(std::string &str) {
	size_t	start = str.find_first_not_of(" \t");
	size_t	end =str.find_last_not_of(" \t");
	if (start == std::string::npos || end == std::string::npos)
		str = "";
	else
		str = str.substr(start, end - start + 1);
}
