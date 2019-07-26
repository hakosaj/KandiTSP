#include "Functions.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <Windows.h> 
#include <omp.h>
#include <string>
#include <chrono>
#include <time.h> 
#include <thread>
#include <sstream>
#include <cassert>
#include <tuple>
#include <math.h>
#include <set>
#include <random>
#include <fstream>
#include <utility>
#include <queue>
#include <concurrencysal.h>
#include <numeric>
#include "Constants.h"
#include "Objects.h"
#include "AlgFunctions.h"
#include "AuxilaryClasses.h"


//Functions for selection methods 

//Ranked selection
void rankedSelection(int gensize)
{
	std::cout << "Doing elitism selection" << std::endl;
	auxtours.clear();
	//std::cout << "debug 2. tours size: " << tours.size() << std::endl;
	for (int i = 0; i < generationSize; i++)
	{
		auxtours.push_back(tours[i]);
		//std::cout << tours[i].representation() << std::endl;
	}
}


//Functions for crossovers

//Poista vierekkyysunioneista
std::vector<std::pair<City, std::vector<City>>> removeFromAdjacencyUnions(City N, std::vector<std::pair<City, std::vector<City>>> adjacencyUnions)
{
	int r = adjacencyUnions.size();
	for (int i = 0; i < r; i++)
	{
		adjacencyUnions[i].second.erase(std::remove(adjacencyUnions[i].second.begin(), adjacencyUnions[i].second.end(), N), adjacencyUnions[i].second.end());

	}
	return adjacencyUnions;

}
//EX-crossover
void edgeRecombinationCrossover(std::vector<std::pair<int, int>> parentPairs)
{
	for (int g = 0; g < generationSize; g++)

	{
		Tour parent1 = auxtours[std::get<0>(parentPairs[g])];
		Tour parent2 = auxtours[std::get<1>(parentPairs[g])];
		//Löydä se elementti, jossa adjacencyvektorin ekan id:t vastaa. yhdistä naapurit.
		auto adjacency1 = generateAdjacencyMatrix(parent1);
		auto adjacency2 = generateAdjacencyMatrix(parent2);
		//generate adjacency union set
		std::vector<std::pair<City, std::vector<City>>> adjacencyUnions;

		//generate one adjacency union pair
		for (int i = 0; i < parent1.cintour.size(); i++)
		{

			int idq = std::get<0>(adjacency1[i]).id;

			auto position = std::find_if(adjacency2.begin(), adjacency2.end(),
				[=](auto item)
			{
				std::cout << "Found!" << std::endl;
				return std::get< 0 >(item).id == idq;
			});

			std::tuple<City, City, City> a1 = adjacency1[i];
			std::tuple<City, City, City> a2 = *position;
			//std::cout << "Adj 1: " << std::get<0>(a1).id << std::get<1>(a1).id<< std::get<2>(a1).id << std::endl;
			//std::cout << "Adj 2: " << std::get<0>(a2).id << std::get<1>(a2).id << std::get<2>(a2).id << std::endl;

			int rar;
			std::cin >> rar;


			//the city component of the pair:
			City paircity = std::get<0>(a1);

			// comparison element for the set
			struct CustomCompare
			{
				bool operator()(const int& lhs, const int& rhs)
				{
					return lhs < rhs;
				}

				bool operator()(const City& lhs, const City& rhs)
				{
					return lhs.id < rhs.id;
				}
			};
			//generate the city vector component of the pair
			std::vector<City> adjacentCities;
			std::set<City, CustomCompare> adjacentCitiesSet;
			adjacentCitiesSet.insert(std::get<1>(a1));
			adjacentCitiesSet.insert(std::get<2>(a1));
			adjacentCitiesSet.insert(std::get<1>(a2));
			std::copy(adjacentCitiesSet.begin(), adjacentCitiesSet.end(), std::back_inserter(adjacentCities));
			adjacencyUnions.push_back(std::make_pair(paircity, adjacentCities));
		}

		/*for (int r = 0; r < adjacencyUnions.size(); r++)
		{
		std::cout << "Union: " << adjacencyUnions[r].first.id << " : ";
		printVector(adjacencyUnions[r].second);
		}*/


		//Do the actual crossover
		std::vector<City> routePlaceholder;

		int randomslot = std::rand() % parent2.cintour.size();
		City N = adjacencyUnions[randomslot].first;


		while (routePlaceholder.size() < parent1.cintour.size())
		{
			//std::cout << "Currentroute: ";
			//printVector(routePlaceholder);

			//std::cout << "N = " << N.id << std::endl;
			routePlaceholder.push_back(N);
			adjacencyUnions = removeFromAdjacencyUnions(N, adjacencyUnions);
			//get N's neighbor list


			auto neighborListIter = std::find_if(adjacencyUnions.begin(), adjacencyUnions.end(),
				[=](auto item)
			{
				return item.first == N;
			});
			std::pair<City, std::vector<City>>neighborList = *neighborListIter;
			//if N's neighbor list is not empty:
			if (!neighborList.second.empty())
			{
				//find the neighbor with fewest neighbors in its neigbor list

				int current = 0;

				//iterate trough all neighbor lists of N's neighbors
				std::vector<std::pair<City, std::vector<City>>> NNeighborLists;
				for (int z = 0; z < neighborList.second.size(); z++)
				{
					auto NNeighbor = neighborList.second[z];
					//get N's neighbor's neighbor list
					auto NNeighborListIter = std::find_if(adjacencyUnions.begin(), adjacencyUnions.end(),
						[=](auto item)
					{
						return item.first == NNeighbor;
					});
					std::pair<City, std::vector<City>>NNeighborList = *NNeighborListIter;
					NNeighborLists.push_back(NNeighborList);


				}
				/*for (int nl = 0; nl < NNeighborLists.size(); nl++)
				{
				printVector(NNeighborLists[nl].second);

				}*/
				//Select shortest neighbor list
				int currentsize = 100;
				int chosen = 0;
				for (int x = 0; x < NNeighborLists.size(); x++)
				{
					if (NNeighborLists[x].second.size() < currentsize)
					{
						currentsize = NNeighborLists[x].second.size();
						chosen = x;

					}

				}
				currentsize = 100;
				City NStar = NNeighborLists[chosen].first;
				N = NStar;
			}
			else {
				int random_slot = std::rand() % parent2.cintour.size();
				City randomNeighbor = parent2.cintour[random_slot];
				while (std::find(routePlaceholder.begin(), routePlaceholder.end(), randomNeighbor) == routePlaceholder.end())
				{
					random_slot = std::rand() % parent2.cintour.size();
					randomNeighbor = parent2.cintour[random_slot];
				}
				City NStar = randomNeighbor;
				N = NStar;

			}

		}
		assert(isLegitRoute(Tour(routePlaceholder)));
		newgen.push_back(Tour(routePlaceholder));
	}

};
//Tekee adjasenssimatriisin
std::vector<std::tuple<City, City, City>> generateAdjacencyMatrix(Tour tour)
//ekan naapurit on kaksi seuraavaa: nykyinen, edellinen, seuraava
{
	auto cities = tour.cintour;
	std::vector<std::tuple<City, City, City>> neighbors;

	neighbors.push_back(std::make_tuple(cities[0], cities.back(), cities[1]));
	for (int i = 1; i < cities.size() - 1; i++)
	{
		neighbors.push_back(std::make_tuple(cities[i], cities[i - 1], cities[i + 1]));
	}
	neighbors.push_back(std::make_tuple(cities.back(), cities[cities.size() - 2], cities[0]));

	return neighbors;

}
//Order crossover.
void orderCrossover(std::vector<std::pair<int, int>> parentPairs)
{
	bool printed = false;
	for (int g = 0; g < generationSize; g++)
	{
		//std::cout << "Doing order crossover for parent pair: " << std::get<0>(parentPairs[g]) << " , " << std::get<1>(parentPairs[g]) << std::endl;
		//std::cout << "Original pairs are:" << std::endl;

		Tour parent1 = auxtours[std::get<0>(parentPairs[g])];
		Tour parent2 = auxtours[std::get<1>(parentPairs[g])];
		assert(isLegitRoute(parent1));
		assert(isLegitRoute(parent2));
		int subsetLoLimit = rand() % dotcount - 1 + 1;
		int subsetHiLimit = rand() % dotcount - 1 + 1;

		if (subsetLoLimit > subsetHiLimit)
		{
			int templ = subsetLoLimit;
			subsetLoLimit = subsetHiLimit;
			subsetHiLimit = templ;
		}

		if (subsetLoLimit == subsetHiLimit) { subsetHiLimit += 2; }

		//Parent 1 subset
		std::vector<City> citiesInSubset;
		//std::cout << "Lowlimit ja hilimit: " << subsetLoLimit << " ja " << subsetHiLimit << std::endl;
		for (int a = subsetLoLimit; a < subsetHiLimit; a++)
		{
			citiesInSubset.push_back(parent1.cintour[a]);
		}


		//std::cout << "Constructing a new tour" << std::endl;
		Tour newtour(citiesInSubset);
		//newtour.printTour();
		//std::cout << "Parent1: " << std::endl;
		//parent1.printTour();
		//std::cout << "Parent2: " << std::endl;
		//parent2.printTour();
		//std::vector<int> points;
		//std::cout << "First and last cut elements: " << parent2.cintour[subsetLoLimit].id << "and " << parent2.cintour[subsetHiLimit-1].id << std::endl;
		//std::cout << "Parent 2-mukaiseen jarjestykseen:" << std::endl;
		//std::cout << "P2-alkupiste: " << parent2.cintour[subsetHiLimit].id<< std::endl;
		//Tehdään uudelleenjärjestelty parent2-vektori, jossa siis loppuosa, alkuosa, cut;
		std::vector<City> parent2rorder;
		for (int a = subsetHiLimit; a < parent2.size(); a++)
		{
			parent2rorder.push_back(parent2.cintour[a]);
		}
		for (int a = 0; a < subsetHiLimit; a++)
		{
			parent2rorder.push_back(parent2.cintour[a]);
		}
		Tour rordertour(parent2rorder);
		assert(isLegitRoute(rordertour));

		//std::cout << "debuggausta1" << std::endl;
		//std::cout << "Reordered p2: " << std::endl;
		//printVector(rordertour.ids());
		//std::cout << "current newtour: " << std::endl;
		//printVector(newtour.ids());

		//Käydään läpi loppuvektori. Jokainen slotti: Jos tämä löytyy cutista, edetään p2rorderia yks eteenpäin. Jos ei löydy, lisätään cuttiin. Poistetaan reorderedin eka elementti aina.
		int count = 0;
		for (int a = subsetHiLimit; a < parent2.size(); a++)
		{
			int r = 0 + count;
			const std::vector<int> jada = newtour.ids();
			std::vector<int>::const_iterator st = jada.begin();
			std::vector<int>::const_iterator en = jada.end();
			while (std::find(st, en, rordertour.cintour[r - count].id) != en)
			{
				r++;

			}
			newtour.cintour.push_back(rordertour.cintour[r - count]);
			count++;
			//std::cout << "newtour size after first: " << newtour.cintour.size() << std::endl;


		}


		//Käydään läpi alkuvektori. Jokainen slotti: Jos tämä löytyy cutista, edetään p2rorderia yks eteenpäin. Jos ei löydy, lisätään cuttiin. Poistetaan reorderedin eka elementti aina.
		int insertIterator = 0;
		for (int a = subsetLoLimit; a > 0; a--)
		{

			int r = 0 + count;
			std::vector<int> jada = newtour.ids();
			std::vector<int>::const_iterator st = jada.begin();
			std::vector<int>::const_iterator en = jada.end();
			//std::cout << "debuggausta2" << std::endl;
			if (!printed) {
				//std::cout << " size, r ja count: " << rordertour.cintour.size() << r << count << std::endl;
				printed = true;
			}

			while (std::find(st, en, rordertour.cintour.at(r - count).id) != en)
			{
				//std::cout << "r is: " << r << " and count is: " << count << std::endl;
				//std::cout << "rorderCIn size is: " << rordertour.cintour.size() << std::endl;
				r++;

			}


			newtour.cintour.insert(newtour.cintour.begin() + insertIterator, rordertour.cintour[r - count]);




			insertIterator++;
			//std::cout << "current newtour: " << std::endl;
			//printVector(newtour.ids());
			count++;


		}

		assert(isLegitRoute(newtour));
		newgen.push_back(newtour);
	}

	std::cout << "Order crossover ready" << std::endl;



};
//Valitsee crossover-metodin
void crossover(std::string identifier, std::vector<std::pair<int, int>> parentPairs)
{
	std::cout << "Starting crossover. Selected operation: " << identifier << std::endl;
	if (identifier == "OX") { orderCrossover(parentPairs); }
	if (identifier == "EX") { edgeRecombinationCrossover(parentPairs); }


}
//Ottaa tietyt kaksi reittiä gensizestä, yhdistää nämä pareiksi
std::vector<std::pair<int, int>> getParentPairs(int gensize)
{
	std::vector<std::pair<int, int>> parentPairs;
	for (int i = 0; i < gensize; i++)
	{
		int p1 = rand() % gensize;
		int p2 = rand() % gensize;
		parentPairs.push_back(std::make_pair(p1, p2));
		//std::cout << p1 << '+' << p2 <<  std::endl;
	}
	return parentPairs;

}



//Functions for mutates

//Reverse two segments
std::tuple<double, Tour> reverse_segment_if_better(Tour tour, int i, int j, int k)
{
	//std::cout << "DELTASSA!" << "i on: " << i << " j on: " << j << " k on: " << k << std::endl;
	City A = tour.cintour[i - 1];
	City B = tour.cintour[i];
	City C = tour.cintour[j - 1];
	City D = tour.cintour[j];
	City E = tour.cintour[k - 1];
	City F = tour.cintour[k % tour.cintour.size()];
	//std::cout << "DELTASSA!2" << std::endl;

	double d0 = distanceTwoCities(A, B) + distanceTwoCities(C, D) + distanceTwoCities(E, F);
	double d1 = distanceTwoCities(A, C) + distanceTwoCities(B, D) + distanceTwoCities(E, F);
	double d2 = distanceTwoCities(A, B) + distanceTwoCities(C, E) + distanceTwoCities(D, F);
	double d3 = distanceTwoCities(A, D) + distanceTwoCities(E, B) + distanceTwoCities(C, F);
	double d4 = distanceTwoCities(F, B) + distanceTwoCities(C, D) + distanceTwoCities(E, A);

	/*std::cout << "d0: " << d0 << std::endl;
	std::cout << "d1: " << d1 << std::endl;
	std::cout << "d2: " << d2 << std::endl;
	std::cout << "d3: " << d3 << std::endl;
	std::cout << "d4: " << d4 << std::endl;*/

	if (d0 > d1) {
		std::reverse(tour.cintour.begin() + i, tour.cintour.begin() + j);
		return std::make_tuple(-d0 + d1, tour);
	}
	else if (d0 > d2) {
		std::reverse(tour.cintour.begin() + j, tour.cintour.begin() + k);
		return std::make_tuple(-d0 + d2, tour);
	}
	else if (d0 > d4) {
		std::reverse(tour.cintour.begin() + i, tour.cintour.begin() + k);
		return std::make_tuple(-d0 + d4, tour);
	}
	else if (d0 > d3) {
		std::vector<City>  tmp1(tour.cintour.begin() + j, tour.cintour.begin() + k);
		std::vector<City>  tmp2(tour.cintour.begin() + i, tour.cintour.begin() + j);
		tmp1.insert(tmp1.end(), tmp2.begin(), tmp2.end());
		std::copy(tmp1.begin(), tmp1.end(), tour.cintour.begin() + i);
		std::make_tuple(-d0 + d3, tour);
	}
	return std::make_tuple(0, tour);



}
//Give all segments
std::vector<std::tuple<int, int, int>> all_segments(int N)
{
	std::vector<std::tuple<int, int, int>> tuples;
	for (int i = 1; i < N; i++) {
		for (int j = i + 2; j < N; j++) {
			for (int k = j + 2; k < N + (i > 0); k++) {
				auto a = std::make_tuple(i, j, k);
				tuples.push_back(a);
			}
		}
	}
	return tuples;
}
//Initiate threeopt mutate
void threeOptMutate()
{
	for (int i = 0; i < newgen.size(); i++) {
		newgen[i] = threeOpt(newgen[i]);
	}


}
//3-opt mutate routine
Tour threeOpt(Tour currentTour)
{
	auto rettour = currentTour;
	std::cout << "3-opt hillclimb in progress" << std::endl;
	auto start = std::chrono::steady_clock::now();
	int N = rettour.cintour.size();

	while (true)
	{
		float delta = 0;
		for (int i = 1; i < N; i++) {
			for (int j = i + 2; j < N; j++) {
				for (int k = j + 2; k < N + (i>0); k++) {
					auto a = reverse_segment_if_better(rettour, i, j, k);
					delta += std::get<0>(a);
					rettour = std::get<1>(a);

				}
			}
		}

		if (delta >= 0) {
			break;
		}

	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << std::endl;

	return rettour;
}
//Initiate 2-opt mutate
void twoOptMutate()
{
	std::cout << "2-opt hillclimb in progress" << std::endl;

	for (int i = 0; i < newgen.size(); i++) {
		newgen[i] = twoOpt(newgen[i]);
	}


}
//2-opt mutate routine
Tour twoOpt(Tour currentTour)
{

	auto route = currentTour.cintour;
	auto best = route;
	bool improved = true;
	//std::cout << "Current path: ";
	//printVector(route); 
	//std::cout << "Dotcount: " << dotcount << std::endl;
	//std::cout << "Routesize: " << route.size() << std::endl;
	//std::cout << "Currenttour cintour size: " << currentTour.cintour.size() << std::endl;
	assert(isLegitRoute(currentTour));

	auto start = std::chrono::steady_clock::now();

	while (improved) {
		improved = false;
		for (int i = 1; i < route.size() - 2; i++) {
			for (int j = i + 1; j < route.size(); j++) {
				if (j - i == 1) { continue; }
				auto newroute = route;
				//std::cout << "Not reversed:";
				//printVector(newroute);
				std::reverse(newroute.begin() + (i - 1), newroute.begin() + (j - 1));
				//std::cout << "Reversed:    ";
				//printVector(newroute);

				if (distance(newroute) < distance(best)) { best = newroute; improved = true; }

			}
		}
		route = best;
	}
	Tour restour(best);
	assert(isLegitRoute(restour));


	auto end = std::chrono::steady_clock::now();
	std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << std::endl;

	return restour;



}
//Routine for swap mutate
void swapMutate(float mutationrate)
{
	std::cout << "Doing swap mutation. Mutation rate: " << mutationrate << std::endl;
	int swaps = std::max((int)floor(mutationrate*dotcount), 1);
	for (int i = 0; i < generationSize; i++) {
		for (int s = 0; s < swaps; s++);
		{
			int pos1 = rand() % 19 + 1;
			int pos2 = rand() % 19 + 1;
			std::iter_swap(newgen[i].cintour.begin() + pos1, newgen[i].cintour.begin() + pos2);
		}
	}
}
//Mutation method chooser
void mutate(std::string identifier, float mutationrate)
{
	std::cout << "Mutation underway. Chosen mutation method: " << identifier << std::endl;
	if (identifier == "swap") { swapMutate(mutationrate); }
	if (identifier == "2opt") { twoOptMutate(); }
	if (identifier == "3opt") { threeOptMutate(); }


}