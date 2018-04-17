# Distributed Systems Project

## Problem Definition
This project is to parallelize code that solves the Traveling Salesperson problem with a genetic algorithm(GA). With how I implemented the problem it requires a fully connected graph for my genetic algorithm to work. The Traveling Salesperson I am defining as choosing a start city, then travel to every other city and end at the start. The goal is to find the least cost path.

## Implementation
How the Genetic algorithm is setup is, first you initialize the population and randomize it. Then it gets the fitness of each member in the population. After that it uses stochastic universal sampling to determine the children for the next generation [link](https://en.wikipedia.org/wiki/Stochastic_universal_sampling). After the children are chosen the heuristic crossover method is applied.
Heuristic crossover is a recombination method that selects two parents. Then it chooses a random starting city for the child, after that it finds that chosen city in both parents and looks at what city is connected to it. It picks the better of the two connections to put in the child. Then it repeats that process with the new city. If it runs into a cycle it randomly chooses an available city. 
Once a full child is created it replaces the worse of the two parents. After heuristic crossover methods is finished the next generation starts and you do the same process.

## The layout of src folder
* Data is a folder that has the adjacency matrices for the various city sizes. It also contains a file of the best path cost for each file.
* openmp folder has the openmp implementation of the GA. It also contains a makefile to build it.
* serial folder has the serial implementation of the GA. It also contains a makefile to build it.
* test folder contains slightly edited code for testing. It also contains some test data and scripts. It also has a graph.py file to graph the data use python3 to run.
* moretesting folder contains different tests that test the average fitness. It also has a graph.py file to graph the data use python3 to run.

## How to run the project
I have this project setup to build on Linux platforms. To run the project, you can go into the serial or the openmp folder and run make in the terminal to build the executables. When you run the program can use -c to specify the city number, -g to specify the lowest cost path, -n to specify the population size.
If you leave those out it defaults to city size of 12, goal of 821, population size of 1000. For example you could run it as ./serial -c 14 -g 958 -n 10000 .


