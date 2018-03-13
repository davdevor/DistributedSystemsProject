#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <chrono>
#include <algorithm>
#include <limits.h>
#include<omp.h>
#define MAX 100 //the max array value for distance_mat
#define CITI 12 //The number of cities
#define popSize 100
#define goal 821
using namespace std;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::iterator;
bool sentinel = true;
//#define INT_MAX 2147483647
long distance_mat[MAX][MAX]; //Matrix storing the distances of all cities
vector<long> Remainder; //Global Remainder vector
vector<long> tour; //Global tour Vector
long bestCost; //Global bestCost variable
vector<vector<long> > population;
vector<double> fitness(popSize);
vector<long> children(popSize);

void readDistanceMatrix()
{
	ifstream inf;
	inf.open("/home/david/github/DistributedSystemsProject/src/clion/tsp12.txt");
	int value, i, j;
	for (i = 0; i < CITI && !inf.fail(); i++) {
		for (j = i; j < CITI && !inf.fail(); j++) {
			if (i == j) {
				distance_mat[i][j] = 0;
			}
			else {
				inf >> value;
				distance_mat[i][j] = value;
				distance_mat[j][i] = value;
			}
		}
	}
}

//function for computing the cost of a tour
long computeTourCost(vector<long> tour)
{
	long sum = 0; //progressive total
	for (int i = 0; i < tour.size() - 1; i++) { //Go through the entire tour except for the last spot and add each pair of values
		long temp1 = tour.at(i);
		long temp2 = tour.at(i + 1);
		sum += distance_mat[temp1][temp2];
	}
	if (tour.size() == CITI) { //if the tour is a full tour add the return value
		long temp1 = tour.at(tour.size() - 1);
		long temp2 = tour.at(0);
		sum += distance_mat[temp1][temp2];
	}
	return sum; //return the total cost
}

void twoswap(int i, int p, int q) {

	long temp = population[i][p];
	population[i][p] = population[i][q];
	population[i][q] = temp;

}

//computes average fitness
double avgFitness() {
	double sum = 0;
    #pragma omp parallel for simd reduction(+:sum)
	for (int i = 0; i < popSize; i++) {
		sum += fitness[i];
	}
	sum /= popSize;
	return sum;
}
void offspring() {
	double prior = 0.0;
	int index = 0;
	int count = 0;
	double averageFitness = avgFitness();
	double r = rand() / ((double)RAND_MAX);
	prior = fitness[0] / averageFitness;
	fitness[0] = prior;

	for (int i = 1; i < popSize; ++i) {
		fitness[i] = ((double)fitness[i] / averageFitness) + prior;
		prior = fitness[i];
	}
	/*
	the loop kept going out of bounds of fitness
	i think due to a floating point error so I made the last postion to always
	be greater than r
	*/
	fitness[popSize - 1] = (double)(popSize + 1);
	while (count < popSize) {

		if (r < fitness[index]) {
			children[index]++;
			++count;
			r += 1.0;
		}
		else {
			++index;
		}
	}
}

void computeFitness() {
	long tourCost;

	long costs[popSize];
	//run loop in parallel
	#pragma omp parallel num_threads(4)
	{
	#pragma omp for simd
		for (int i = 0; i < popSize; ++i) {
			//compute tour cost for each member of population
			costs[i] = computeTourCost(population[i]);
		}
	}
	for (int i = 0; i < popSize; ++i) {
		tourCost = costs[i];
		if (tourCost < bestCost) { //see if this full tour is better than the best known tour
			bestCost = tourCost;
			if (tourCost == goal) {
				sentinel = false;
			}
			cout << "COST: " << bestCost << endl << "PATH: "; //if so print out the distance
			for (int k = 0; k < CITI; ++k) {
				cout << population.at(i).at(k) << " "; //now print the path taken (for verification if needed
			}
			cout << endl;
		}
		fitness[i] = (double)tourCost;
	}
}


void createNewPopulation() {
	int index = 0;
	//copy over parents the number of times the children vector specifies
	//if children[i] = 2 then copy over population[i] 2 times
	vector<vector<long> > temp(popSize, vector<long>(CITI));
	for (int i = 0; i < popSize; ++i) {
		for (int j = 0; j < children[i]; ++j) {
			for (int k = 0; k < CITI; ++k)
			{
				temp[index][k] = population[i][k];
			}
			++index;
		}
	}
	population = temp;


}


void shuffle() {
	//seed random number generator
	srand(time(NULL));

	//#pragma omp parallel for num_threads(4)
	for (int i = 0; i < popSize; i++) {
		//get random number of swaps
		int swaps = 1 + (rand() % (CITI - 1));
		for (int k = 0; k < swaps; k++) {
			//get two random places to swap
			int p = 1 + (rand() % (CITI - 1));
			int q = 1 + (rand() % (CITI - 1));
			//call method to swap positons in tour
			twoswap(i, p, q);
		}
	}
}
/*
	this method takes two parents and produces a child
	you start by randomly choosing a starting city then
	you find that city in both of the parents and look at the edge that
	the city in both of the parents are connected to you choose the better of the
	two edges and put that city in the child, if you run into a cycle you randomly choose a city
	then you continue the process, after you are done I replace the worse of the two parents with the child
*/
void heuristicCrossover() {




	#pragma omp parallel for
	for (int i = 0; i < popSize; i += 2) {
        srand(time(NULL)*omp_get_thread_num());
        int conn1;
        int conn2;

		//randomly pick a start city
		int city = 1 + (rand() % (CITI - 1));
		vector<long> newTour = vector<long>(CITI);
		//holds which city has been visited
		//each postion corresponds to each city
		vector<long> nums = vector<long>(CITI);
		nums[city] = 1;
		nums[0] = 1;
		newTour[1] = city;
		int k;
		for (k = 2; k < CITI; ++k) {
			int pos1 = 0;
			//find the start city in parent 1
			while (population[i][pos1] != city)
			{
				++pos1;
			}

			int pos2 = 0;
			//find start city in parent 2
			while (population[i + 1][pos2] != city)
			{
				++pos2;
			}

			int cost1;
			//if city is at end of parent no connecting edge max cost max int
			if (pos1 == (CITI - 1)) {
				cost1 = INT_MAX;
			}
			else {
				//else get cost of city connected to it
				//save city connected to city we are looking for
				conn1 = population[i][pos1 + 1];
				cost1 = distance_mat[city][conn1];
			}

			int cost2;
			//if city is at end of parent no connecting edge max cost max int
			if (pos2 == (CITI - 1)) {
				cost2 = INT_MAX;
			}
			else {
				//else get cost of city connected to it
				//save city connected to city we are looking for
				conn2 = population[i + 1][pos2 + 1];
				cost2 = distance_mat[city][conn2];
			}

			//if both cities are at end of parents this means no connecting edges
			//randomly choose the conenecting city
			if (cost1 == INT_MAX && cost2 == INT_MAX) {

				//temp vector
				vector<long> nums2;
				for (int z = 0; z < CITI; ++z) {
					//if 0 means city z has not been visited
					//add z to nums2
					if (nums[z] == 0) {
						nums2.push_back(z);
					}
				}
				//choose a random number in range of size of nums2
				//city at that postion is new city
				conn1 = nums2[rand() % nums2.size()];
				newTour[k] = conn1;
				city = conn1;
				nums[city] = 1;

			}
			else {
				//first connection is better than second
				if (cost1 < cost2) {
					//check and see if city has been visited
					if (nums[conn1] == 1) {
						vector<long> nums2;
						for (int z = 0; z < CITI; ++z) {
							if (nums[z] == 0) {
								nums2.push_back(z);
							}
						}
						conn1 = nums2[rand() % nums2.size()];
					}
					//put city in tour
					newTour[k] = conn1;
					city = conn1;
				}
				else {
					//check and see if city has been visited
					if (nums[conn2] == 1) {
						vector<long> nums2;
						for (int k = 0; k < CITI; ++k) {
							if (nums[k] == 0) {
								nums2.push_back(k);
							}
						}
						conn2 = nums2[rand() % nums2.size()];
					}
					//put city in tour
					newTour[k] = conn2;
					city = conn2;
				}
				//mark citi as visited
				nums[city] = 1;
			}


		}
		//get cost of parents and replace the worse one with child
		int parentCost1 = computeTourCost(population[i]);
		int parentCost2 = computeTourCost(population[i + 1]);
		if (parentCost1 > parentCost2) {
			population[i] = newTour;
		}
		else {
			population[i + 1] = newTour;
		}
	}
}
void gaTSP() {
	//init population
	//population is a vector of vectors, and each vector
	//holds a complete tour in it, it is initialized to 0- CITI-1
	for (int i = 0; i < popSize; i++) {
		population.push_back(vector<long>(CITI));

		for (int j = 0; j < CITI; j++) {
			population.at(i).at(j) = j;
		}
	}
	while (sentinel) {

		//randomly shuffle the populations to a new tour
		shuffle();
		//compute fitness of each tours
		computeFitness();
		//decide the children from the population
		offspring();
		//create the new population
		createNewPopulation();
		//edits the tour some more
		heuristicCrossover();
		//reset fitness and children values
		fitness = vector<double>(popSize, 0.0);
		children = vector<long>(popSize, 0);
	}

}



int main()
{
	bestCost = INT_MAX; //set best cost very high so we can go under it

	readDistanceMatrix(); //read in our distance_matrix

	auto start = chrono::steady_clock::now();
	gaTSP();
	auto end = chrono::steady_clock::now();
	cout << "elapsed time in seconds: " << chrono::duration_cast <chrono::seconds>(end - start).count() << endl;
	system("pause"); //allows a pause before shutting down for use outside the compiler
	return 0;
}