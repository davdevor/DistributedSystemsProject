#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <string.h>
#include<omp.h>
#define MAX 100 //the max array value for distance_mat
using namespace std;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::iterator;
int popSize;
int CITI;
int goal;
bool sentinel = true;
long distance_mat[MAX][MAX]; //Matrix storing the distances of all cities
vector<long> Remainder; //Global Remainder vector
vector<long> tour; //Global tour Vector
long bestCost; //Global bestCost variable
vector<vector<long> > population;
vector<double> fitness;
vector<long> children;
double avgFitness;

void readDistanceMatrix()
{
	ifstream inf;
    string file = "../data/tsp";
    file += std::to_string(CITI);
    file+=".txt";
	inf.open(file);
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


void offspring() {
	double prior = 0.0;
	int index = 0;
	int count = 0;




	double r = rand() / ((double)RAND_MAX);
	prior = fitness[0] / avgFitness;
	fitness[0] = prior;

	for (int i = 1; i < popSize; ++i) {
		fitness[i] = ((double)fitness[i] / avgFitness) + prior;
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
    avgFitness = 0.0;
       double tempAvg = 0.0;
	//run loop in parallel
    #pragma omp parallel for reduction(+:avgFitness,tempAvg) private(tourCost)
    for (int i = 0; i < popSize; ++i) {
        //compute tour cost for each member of population
        tourCost = computeTourCost(population[i]);
	// do 10000 - tourcost because offspring tries to pick the highest fitness numbers
	// so if you use a file with a path cost greater than 10000 you need to change this number
        fitness[i] = 10000.0 - (double)tourCost;
        avgFitness += 10000.0 -(double)tourCost;
        #pragma omp critical
        {
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
        }

	}


    avgFitness/=popSize;
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
	//setup and seed random number generator
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, CITI-1);
    #pragma omp parallel
    {
        int swaps ,p,q;
        long temp;
        #pragma omp for
        for (int i = 0; i < popSize; ++i) {

            //get random number of swaps
            swaps = dist(mt);
            for (int k = 0; k < swaps; ++k) {
                //get two random places to swap
                p = dist(mt);
                q = dist(mt);
                //call method to swap positons in tour
                temp = population[i][p];
                population[i][p] = population[i][q];
                population[i][q] = temp;
            }
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

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, CITI-1);

	#pragma omp parallel for
	for (int i = 0; i < popSize; i += 2) {

        int conn1;
        int conn2;

		//randomly pick a start city
		int city = dist(rd);
		vector<long> newTour = vector<long>(CITI);
		/*nums holds which city has been visited
		  each postion corresponds to each city*/
		vector<long> nums = vector<long>(CITI);
		nums[city] = 1;
		nums[0] = 1;
		newTour[1] = city;

		for (int k = 2; k < CITI; ++k) {
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
			//if city is at end of parent tour there is no connecting edge max cost max int
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
			//if city is at end of parent tour there is no connecting edge max cost max int
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

				//temp vector it is going to hold all the cities not visited
				vector<int> nums2;
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
                    //if the city has been visited randomly pick a new one
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
                    //if the city has been visited randomly pick a new one
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
void clear(){
    #pragma omp parallel for simd
    for(int i = 0; i < popSize; ++i){
        fitness[i] = 0.0;
        children[i] = 0;
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
        shuffle();
        while(sentinel){
		//compute fitness of each tours
		computeFitness();
		//decide the children from the population
		offspring();
		//create the new population
		createNewPopulation();
		//edits the population some more
		heuristicCrossover();
		//reset fitness and children values
		clear();
	}

}

//read in command line input
int find_option( int argc, char **argv, const char *option )
{
    for( int i = 1; i < argc; i++ )
        if( strcmp( argv[i], option ) == 0 )
            return i;
    return -1;
}

int read_int( int argc, char **argv, const char *option, int default_value )
{
    int iplace = find_option( argc, argv, option );
    if( iplace >= 0 && iplace < argc-1 )
        return atoi( argv[iplace+1] );
    return default_value;
}

int main(int argc, char **argv)
{
    int numthreads;
    #pragma omp parallel
    {
        numthreads = omp_get_num_threads();
    }
    popSize = read_int(argc, argv, "-n", 1000);
    CITI = read_int(argc, argv,"-c",12);
    goal = read_int(argc, argv,"-g",821);
    fitness = vector<double>(popSize);
    children = vector<long>(popSize);
    bestCost = INT_MAX; //set best cost very high so we can go under it
    readDistanceMatrix(); //read in our distance_matrix
    double simulationTime = omp_get_wtime();
    gaTSP();
    cout << "time " << omp_get_wtime() - simulationTime << " popsize " << popSize << " citi " << CITI << " num threads " << numthreads<< endl;
    return 0;
}
