/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:26:04 by jcheron           #+#    #+#             */
/*   Updated: 2025/04/25 10:06:09 by jcheron          ###   ########.fr       */
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

std::vector<size_t>PmergeMe::generateJacobsthalSequence(size_t size) const {
	std::vector<size_t> seq;
	seq.push_back(1);
	while (seq.back() < size) {
		size_t n = seq.size();
		size_t next = (n == 1) ? 3 : seq[n - 1] + 2 * seq[n - 2];
		if (next < size)
			seq.push_back(next);
		else
			break;
	}

	std::vector<size_t> full;
	std::vector<bool> used(size, false);
	for (size_t i = 0; i < seq.size(); ++i) {
		full.push_back(seq[i]);
		used[seq[i]] = true;
	}
	for (size_t i = 0; i < size; ++i)
		if (!used[i])
			full.push_back(i);
	return full;
}

std::deque<size_t> PmergeMe::generateJacobsthalSequenceDeque(size_t n) {
	std::deque<size_t> seq;
	size_t j1 = 0, j2 = 1;

	seq.push_back(j1);
	if (n == 1) return seq;
	seq.push_back(j2);

	while (true) {
		size_t next = j2 + 2 * j1;
		if (next >= n)
			break;
		seq.push_back(next);
		j1 = j2;
		j2 = next;
	}

	for (size_t i = 0; i < n; ++i) {
		if (std::find(seq.begin(), seq.end(), i) == seq.end()) {
			seq.push_back(i);
		}
	}
	return seq;
}

std::vector<int> PmergeMe::mergeInsertSortVector(std::vector<int> &vec) {

	if (vec.size() <= 1) return vec;

	std::vector<std::pair<int, int> > pairs;
	size_t i = 0;

	while (i < vec.size()) {
		int first = vec[i++];
		if (i < vec.size()) {
			int second = vec[i++];
			if (first > second)
				pairs.push_back(std::make_pair(second, first));
			else
				pairs.push_back(std::make_pair(first, second));
		} else {
			pairs.push_back(std::make_pair(first, -1));
		}
	}

	std::vector<int> larger;
	for (size_t j = 0; j < pairs.size(); ++j)
		if (pairs[j].second != -1)
			larger.push_back(pairs[j].second);

	larger = mergeInsertSortVector(larger);

	std::vector<int> result = larger;
	std::vector<int> toInsert;
	for (size_t j = 0; j < pairs.size(); ++j)
		toInsert.push_back(pairs[j].first);

	std::vector<size_t> jacobIndexes = generateJacobsthalSequence(toInsert.size());

	for (size_t j = 0; j <jacobIndexes.size(); ++j) {
		size_t idx = jacobIndexes[j];
		if (idx > toInsert.size())
			break;
		std::vector<int>::iterator it = std::lower_bound(result.begin(), result.end(), toInsert[idx]);
		result.insert(it, toInsert[idx]);
	}
	return result;
}

std::deque<int> PmergeMe::mergeInsertSortDeque(std::deque<int> &deq) {

	if (deq.size() <= 1) return deq;

	std::deque<std::pair<int, int> > pairs;
	size_t i = 0;

	while (i < deq.size()) {
		int first = deq[i++];
		if (i < deq.size()) {
			int second = deq[i++];
			if (first > second)
				pairs.push_back(std::make_pair(second, first));
			else
				pairs.push_back(std::make_pair(first, second));
		} else {
			pairs.push_back(std::make_pair(first, -1));
		}
	}

	std::deque<int> larger;
	for (size_t j = 0; j < pairs.size(); j++)
		if (pairs[j].second != -1)
			larger.push_back(pairs[j].second);

	larger = mergeInsertSortDeque(larger);

	std::deque<int> result = larger;
	std::deque<int> toInsert;
	for (size_t j = 0; j < pairs.size(); ++j)
		toInsert.push_back(pairs[j].first);

	std::deque<size_t> jacobIndexes = generateJacobsthalSequenceDeque(toInsert.size());

	for (size_t j = 0; j < jacobIndexes.size(); ++j) {
		size_t idx = jacobIndexes[j];
		if (idx >= toInsert.size())
			break;
		std::deque<int>::iterator it = std::lower_bound(result.begin(), result.end(), toInsert[idx]);
		result.insert(it, toInsert[idx]);
	}
	return result;
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
