/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:02:04 by jcheron           #+#    #+#             */
/*   Updated: 2025/05/03 11:03:54 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &src) { this->_stack = src._stack; }

RPN &RPN::operator=(const RPN &src) {
	if (this != &src)
		this->_stack = src._stack;
	return *this;
}

bool	RPN::isOperator(const std::string &token) const {
	return
		token == "+" ||
		token == "-" ||
		token == "*" ||
		token == "/";
}

int		RPN::applyOperation(int a, int b, const std::string &op) const {
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/") {
		if (b == 0)
			throw std::runtime_error("Error: division by zero");
		return a / b;
	}
	throw std::runtime_error("Unknown operator");
}

int		RPN::evaluate(const std::string &expression) {
	std::istringstream iss(expression);
	std::string			token;

	while (iss >> token) {
		if (token.length() == 1 && std::isdigit(token[0])) {
			_stack.push(token[0] - '0');
		} else if (isOperator(token)) {
			if (_stack.size() < 2)
				throw std::runtime_error("Error: not enough operands");
			int b = _stack.top(); _stack.pop();
			int a = _stack.top(); _stack.pop();
			int result = applyOperation(a, b, token);
			_stack.push(result);
		} else {
			throw std::runtime_error("Error: unknown token => " + token);
		}
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error: invalid expression");
	return _stack.top();
}
