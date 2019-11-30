#include "Functions.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
//#include <Windows.h> 
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
//#include <concurrencysal.h>
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
	auxtours.push_back(tours[0]);
	//std::cout << "debug 2. tours size: " << tours.size() << std::endl;


	int ind = 1;
	while (auxtours.size() < generationSize/2 +1) {
		try {
			auto candidate = tours[ind];
			bool isLegitCandidate = true;
			for (int a = 0; a < auxtours.size(); a++) {
				if (candidate.cintour == auxtours[a].cintour) {
					isLegitCandidate = false;
				}

			}
			if (isLegitCandidate) {
				auxtours.push_back(candidate);
			}
			ind++;
		}
		catch (const std::exception& e) {
			cout << "Kaikki k�yty l�pi. Fuck." << endl;

		}



	}


	assert(areLegitTours(auxtours));
}


//Functions for crossovers

//EX-crossover
void edgeRecombinationCrossover(std::vector<std::pair<int, int>> parentPairs)
{
	while (newgen.size()<generationSize)
		
		
	{

		static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
	

		int otherint = 0;
		int thisint = 0;
		while (otherint == thisint || thisint==generationSize || otherint==generationSize) {
			otherint = static_cast<int>((generationSize) * (std::rand() * fraction));

			thisint = static_cast<int>((generationSize + 1) * (std::rand() * fraction));
		}


		Tour parent11 = auxtours[std::get<0>(parentPairs[thisint])];
		Tour parent22 = auxtours[std::get<1>(parentPairs[otherint])];
		assert(isLegitRoute(parent22));
		assert(isLegitRoute(parent11));


		std::vector<int> parent1 = parent11.ids();
		std::vector<int> parent2 = parent22.ids();

		int amount = parent1.size();

		std::map<int, std::set<int>> edgeMap1;
		std::map<int, std::set<int>> edgeMap2;
		std::map<int, std::set<int>> edgeMap;
		//t�m�;edellinen,seruaava

		//Add parent1 first and last
		edgeMap1.insert({ parent1[0],{parent1.back(),parent1[1]} });
		edgeMap1.insert({ parent1.back(),{ parent1[amount-2],parent1[0] } });

		//Add parent1 rest
		for (int i = 1; i < amount - 1; i++) {
			edgeMap1.insert({ parent1[i],{parent1[i - 1],parent1[i + 1]} });
		}

		//Add parent2 first and last
		edgeMap2.insert({ parent2[0],{ parent2.back(),parent2[1] } });
		edgeMap2.insert({ parent2.back(),{ parent2.back() - 1,parent2[0] } });

		//Add parent2 rest
		for (int i = 1; i < amount - 1; i++) {
			edgeMap2.insert({ parent2[i],{ parent2[i - 1],parent2[i + 1] } });
		}



		//Get the keyset from edgemap
		std::vector<int> edgeMapKeys;
		for (auto const& element : edgeMap1) {
			edgeMapKeys.push_back(element.first);
		}


		//combine two maps into one
		for (int key : edgeMapKeys) {
			std::set<int> a = edgeMap1.at(key);
			std::set<int> b = edgeMap2.at(key);
			a.insert(b.begin(), b.end());
			edgeMap.insert({ key,a });
		}


		

		
		//select starting city
		int startingCity = parent1[0];
		//The offspring route
		std::vector<int> newRoute;
		newRoute.push_back(startingCity);
		int minCity = startingCity;








			while (newRoute.size() < dotcount) {


				//Get the keyset from edgemap
				std::vector<int> edgeMapKeys;
				for (auto const& element : edgeMap) {
					edgeMapKeys.push_back(element.first);
				}





				//Delete all edges leading to this from the initial map (edgeMapCopy)

				for (int key : edgeMapKeys) {
					std::set<int> cities = edgeMap[key];
					if (cities.find(minCity) != cities.end()) {
						cities.erase(cities.find(minCity));
						edgeMap[key] = cities;

					}
				}

				//Print the edge map
				for (int key : edgeMapKeys) {
					//std::cout << "city: " << key << " has edges to ";
					auto cities = edgeMap[key];
					for (int a : cities) {
						//std::cout << a << " ";
					}
					//std::cout << "\n";
				}




				//List of the cities we can go to from this
				std::set<int> cities = edgeMap[minCity];
				
				for (int i : cities) {
					//std::cout << "Next cities: " << i << std::endl;
				}
				edgeMap.erase(minCity);
				
				//Map of all the neighbor sizes
				std::map<int, int> neighborSizes;
				for (int i : cities) {
					neighborSizes.insert({ i,edgeMap[i].size() });
					//std::cout << "Neighbor:" << i << " and their sizes: " << edgeMap[i].size() << std::endl;
				}

				//Find the neighbor with the least number of edges. Choose the first one this time
				int minNeighbors = 5;
				 minCity = -1;
				for (const auto &myPair : neighborSizes) {
					if (minNeighbors > myPair.second) {
						minNeighbors = myPair.second;
						minCity = myPair.first;

					}
				}
				//std::cout << "MinCity: " << minCity << " and minNeigh: " << minNeighbors << std::endl;
				newRoute.push_back(minCity);



			}






		std::vector<City> newTour;
		for (int a : newRoute) {
			for (City c : parent11.cintour) {
				if (c.id == a) {
					newTour.push_back(c);
				}
				
			}

		}



		

		Tour finalTour(newTour);



		//Add extras

		if (finalTour.cintour.size() != parent11.cintour.size()) {
			vector<int> missing;
			auto currents = finalTour.ids();
			std::vector<int> allints(parent11.cintour.size());
			std::iota(allints.begin(), allints.end(), 0);
			for (int i : currents) {
				allints.erase(std::remove(allints.begin(), allints.end(), i), allints.end());
				missing = allints;





			}


			for (int i : missing) {

				for (City c: parent11.cintour) {

					if (i == c.id) {
						finalTour.cintour.push_back(c);
					}


			}

		}




		}



		assert(isLegitRoute(finalTour));
		auto candidate = finalTour;
		bool isLegitCandidate = true;
		for (int a = 0; a < newgen.size(); a++) {
			if (candidate.cintour == newgen[a].cintour) {
				isLegitCandidate = false;
			}
	

		}
		if (isLegitCandidate) {
			newgen.push_back(candidate);
		}
	}
	cout << "Edge recombination crossover done" << endl;

};


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

		static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };


		int subsetLoLimit = static_cast<int>((parent1.size() ) * (std::rand() * fraction));

		int subsetHiLimit = static_cast<int>((parent1.size() + 1) * (std::rand() * fraction));


		while (subsetHiLimit >= parent1.size()) {
			subsetHiLimit = static_cast<int>((parent1.size() + 1) * (std::rand() * fraction));
		}
		while (subsetLoLimit >= subsetHiLimit) {
			subsetLoLimit = static_cast<int>((parent1.size()) * (std::rand() * fraction));
			subsetHiLimit = static_cast<int>((parent1.size() + 1) * (std::rand() * fraction));
		}



		//Parent 1 subset
		std::vector<City> citiesInSubset;
		//std::cout << "Lowlimit ja hilimit: " << subsetLoLimit << " ja " << subsetHiLimit << std::endl;
		for (int a = subsetLoLimit; a < subsetHiLimit; a++)
		{
			citiesInSubset.push_back(parent1.cintour[a]);
		}


		//std::cout << "Constructing a new tour" << std::endl;
		Tour newtour(citiesInSubset);

		//Tehd��n uudelleenj�rjestelty parent2-vektori, jossa siis loppuosa, alkuosa, cut;
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


		//K�yd��n l�pi loppuvektori. Jokainen slotti: Jos t�m� l�ytyy cutista, edet��n p2rorderia yks eteenp�in. Jos ei l�ydy, lis�t��n cuttiin. Poistetaan reorderedin eka elementti aina.
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


		//K�yd��n l�pi alkuvektori. Jokainen slotti: Jos t�m� l�ytyy cutista, edet��n p2rorderia yks eteenp�in. Jos ei l�ydy, lis�t��n cuttiin. Poistetaan reorderedin eka elementti aina.
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

		auto candidate = newtour;
		bool isLegitCandidate = true;
		for (int a = 0; a < newgen.size(); a++) {
			if (candidate.cintour == newgen[a].cintour) {
				isLegitCandidate = false;
			}

		}
		if (isLegitCandidate) {
			newgen.push_back(candidate);
		}


	}

	assert(areLegitTours(newgen));
	std::cout << "Order crossover ready" << std::endl;



};
//Valitsee crossover-metodin
void crossover(std::string identifier, std::vector<std::pair<int, int>> parentPairs)
{
	std::cout << "Starting crossover. Selected operation: " << identifier << std::endl;
	if (identifier == "OX") { orderCrossover(parentPairs); }
	if (identifier == "EX") { edgeRecombinationCrossover(parentPairs); }


}
//Ottaa tietyt kaksi reitti� gensizest�, yhdist�� n�m� pareiksi
std::vector<std::pair<int, int>> getParentPairs(int gensize)
{
	std::vector<std::pair<int, int>> parentPairs;
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };



	while (parentPairs.size()<gensize) 
	{

		int p1 = 0;
		int p2 = 0;
		while (p1 == p2) {
			 p1 = static_cast<int>((auxtours.size()) * (std::rand() * fraction));
			 p2 = static_cast<int>((auxtours.size()) * (std::rand() * fraction));
			 
			
		}
		if (!(std::find(parentPairs.begin(), parentPairs.end(), std::make_pair(p1, p2))
			!= parentPairs.end())) {


			parentPairs.push_back(std::make_pair(p1, p2));
		}
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

	std::cout << "3-opt hillclimb in progress" << std::endl;
	#pragma omp parallel for schedule(static,1)
	for (int i = 0; i < newgen.size(); i++) {
		newgen[i] = threeOpt(newgen[i]);
		cout << " Done " << i+1 << " of " << newgen.size() << endl;
	}


}
//3-opt mutate routine
Tour threeOpt(Tour currentTour)
{
	auto rettour = currentTour;
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
	std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds.";

	return rettour;
}
//Initiate 2-opt mutate
void twoOptMutate()
{
	std::cout << "2-opt hillclimb in progress" << std::endl;
	#pragma omp parallel for schedule(static,1)
	for (int i = 0; i < newgen.size(); i++) {
		newgen[i] = twoOpt(newgen[i]);
		cout << " Done " << i << " of " << newgen.size() << endl;
		
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
	std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds.";

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
			int pos1 = rand() % newgen[0].size();
			int pos2 = rand() % newgen[0].size();
			std::iter_swap(newgen[i].cintour.begin() + pos1, newgen[i].cintour.begin() + pos2);
		}
	}
}


//Routine for scramble mutate
void scrambleMutate(float mutationrate)
{
	int subsetLength = std::max((int)floor(mutationrate*newgen[0].size()), 1);
	for (auto tour : newgen) {
		//cout << "First: " << tour.representation() << endl;
		int start = rand() % newgen[0].size();
		auto rng = std::default_random_engine{};

		//If wraps around
		if (start + subsetLength > newgen[0].size()) {
			vector<City> backportion(tour.cintour.begin()+start,tour.cintour.end());
			vector<City> frontportion(tour.cintour.begin(), tour.cintour.begin() +subsetLength-backportion.size() );
			vector<City> midportion(tour.cintour.begin() + subsetLength - backportion.size(), tour.cintour.begin() + start);

			vector<City> combinePlaceholder;
			combinePlaceholder.reserve(newgen[0].size() - subsetLength);
			combinePlaceholder.insert(combinePlaceholder.end(), backportion.begin(), backportion.end());
			combinePlaceholder.insert(combinePlaceholder.end(), frontportion.begin(), frontportion.end());


			std::shuffle(std::begin(combinePlaceholder), std::end(combinePlaceholder), rng);
			std::copy_n(combinePlaceholder.begin(), backportion.size(), &tour.cintour[start]);
			std::copy_n(combinePlaceholder.begin()+backportion.size(), frontportion.size(), &tour.cintour[0]);
		}
		else {
			std::shuffle(tour.cintour.begin() + start, tour.cintour.begin() + subsetLength+start,rng);
		}

		//cout << "Last: " << tour.representation() << endl;
	}

}

//Mutation method chooser
void mutate(std::string identifier, float mutationrate)
{
	std::cout << "Mutation underway. Chosen mutation method: " << identifier << std::endl;
	if (identifier == "swap") { swapMutate(mutationrate); }
	if (identifier == "scramble") { scrambleMutate(mutationrate); }
	if (identifier == "2opt") { twoOptMutate(); }
	if (identifier == "3opt") { threeOptMutate(); }


}

bool averageChangeStopper(vector<Tour> oldgen, vector<Tour> newgen) {
	
	double oldavg = 0;
	double newavg = 0;

	for (int i = 0; i < oldgen.size(); i++) {
		oldavg += oldgen[i].dist;
	}

	for (int i = 0; i < newgen.size(); i++) {
		newavg += newgen[i].dist;
	}

	oldavg = oldavg / oldgen.size()*1.0;
	newavg = newavg / newgen.size()*1.0;

	if (newavg/oldavg > 0.98) {
		cout << "ratio:" << newavg / oldavg << endl;
		cout << "New avg: " << newavg << endl;
		cout << "Old avg: " << oldavg << endl;
		return true;
	}
	return false;


}