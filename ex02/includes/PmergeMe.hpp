/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:21:20 by jcheron           #+#    #+#             */
/*   Updated: 2025/05/03 11:17:34 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <algorithm>

class PmergeMe {

	public:

		PmergeMe();
		~PmergeMe();

		void	parseArgs(char **av, int ac);
		void	sortAndMesure();

	private:

		std::vector<int>	_vec;
		std::deque<int>		_deq;

		void sortVector(std::vector<int> &input);
		void sortDeque(std::deque<int> &input);
		// std::vector<int>	mergeInsertSortVector(std::vector<int> &vec);
		// std::deque<int>		mergeInsertSortDeque(std::deque<int> &deq);

		template <typename T>
		void printContainer(const T &container, const std::string &prefix);
		std::vector<size_t> generateJacobsthalSequence(size_t size) const;
		std::deque<size_t> generateJacobsthalSequenceDeque(size_t n);

};
