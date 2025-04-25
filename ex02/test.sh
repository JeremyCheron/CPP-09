#!/bin/bash

# Compile ton programme (assume que le binaire s'appelle PmergeMe)
make
if [ $? -ne 0 ]; then
	echo "Compilation failed."
	exit 1
fi

# Génère 3000 entiers aléatoires uniques entre 1 et 100000
echo "Generating 3000 random integers..."
INPUT=$(shuf -i 1-100000 -n 3000 | tr "\n" " ")

# Exécute le programme avec les entiers générés
echo "Running PmergeMe with 3000 integers..."
./PmergeMe $INPUT
