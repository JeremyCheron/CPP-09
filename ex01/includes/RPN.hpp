/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:59:35 by jcheron           #+#    #+#             */
/*   Updated: 2025/04/20 14:09:01 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <string>

class RPN {

	public:

		RPN();
		~RPN();
		RPN(const RPN &src);
		RPN &operator=(const RPN &src);

		int evaluate(const std::string &expression);

	private:

		std::stack<int>	_stack;

		bool	isOperator(const std::string &token) const;
		int		applyOperation(int a, int b, const std::string &op) const;

};
