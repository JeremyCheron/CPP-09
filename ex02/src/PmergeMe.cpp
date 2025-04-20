/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:26:04 by jcheron           #+#    #+#             */
/*   Updated: 2025/04/20 14:48:21 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseArgs(char **av, int ac) {
	for (int i = 0; i < ac; ++i) {
		std::istringstream	iss(av[i]);
		int					num;
		if (!(iss >> num) || num < 0 || !iss.eof()) {
			throw std::invalid_argument("Invalid input: " + std::string(av[i]));
		}
		_vec.push_back(num);
		_deq.push_back(num);
	}
}

template <typename T>
void PmergeMe::printContainer(const T &container, const std::string &prefix) {
	std::cout << prefix;
	for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

std::vector<int> PmergeMe::mergeInsertSortVector(std::vector<int> &vec) {

	if (vec.size() <= 1) return vec;

	std::vector<int> left(vec.begin(), vec.begin() + vec.size() / 2);
	std::vector<int> right(vec.begin() + vec.size() /2, vec.end());

	left = mergeInsertSortVector(left);
	right = mergeInsertSortVector(right);

	std::vector<int>	merged;
	std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(merged));
	return merged;

}

std::deque<int> PmergeMe::mergeInsertSortDeque(std::deque<int> &deq) {

	if (deq.size() <= 1) return deq;

	std::deque<int>	left(deq.begin(), deq.begin() + deq.size() / 2);
	std::deque<int> right(deq.begin() + deq.size() / 2, deq.end());

	left = mergeInsertSortDeque(left);
	right = mergeInsertSortDeque(right);

	std::deque<int>	merged;
	std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(merged));
	return merged;

}

void PmergeMe::sortAndMesure() {

	printContainer(_vec, "Before: ");

	std::vector<int>	vecCopy = _vec;
	clock_t start1 = clock();
	std::vector<int>	sortedVec = mergeInsertSortVector(vecCopy);
	clock_t end1 = clock();

	std::deque<int>		deqCopy = _deq;
	clock_t start2 = clock();
	std::deque<int>		sortedDeque = mergeInsertSortDeque(deqCopy);
	clock_t end2 = clock();

	printContainer(sortedVec, "After: ");

	double durationVec = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1e6;
	double durationDeq = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1e6;

	std::cout	<< "Time to process a range of " << _vec.size()
				<< " elements with std::vector : " << durationVec
				<< "μs" << std::endl;

	std::cout	<< "Time to process a range of " << _deq.size()
				<< " elements with std::deque : " << durationDeq
				<< "μs" << std::endl;

}
