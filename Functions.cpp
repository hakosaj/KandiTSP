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
#include "InitializeFunctions.h"
#include "Objects.h"
#include "AlgFunctions.h"
#include "AuxilaryClasses.h"




bool operator== (const City &c1, const City &c2)
{
	return (c1.id == c2.id);
}

bool operator!= (const City &c1, const City &c2)
{
	return !(c1 == c2);
}


std::vector<std::vector<int>> readCsv()
{
	std::string fileEnd;
	std::vector<std::string> instances = {
		"berlin52", "att48","bays29","gr96","kroA100","lin105","pr76","pr107","st70","u159"



	};
	std::sort(instances.begin(),instances.end());
	std::cout << "Choose instance:" << std::endl;


	for (auto it = instances.begin(); it != instances.end(); it++) {
		std::cout << *it << std::endl;
	};


	std::cin >> fileEnd;

	while (!(std::find(instances.begin(), instances.end(), fileEnd) != instances.end()))
	{
		std::cout << "Required instance not found. Try again:" << std::endl;
		std::cin >> fileEnd;
	}

	std::string fileName = "C:\\Users\\jh\\Desktop\\Kandi\\VisualSFMLtesti1\\VisualSFMLtesti1\\Data\\"+fileEnd+".csv";
	std::cout << "File read. Path to file: " << fileName << std::endl;
	std::vector<std::vector<int>> fields;

	std::ifstream inputFile(fileName);

	if (!inputFile.is_open()) {
		std::cout << "File not opened." << std::endl;
	}
	

	if (inputFile) {
		std::string line;

		while (std::getline(inputFile, line)) {
			std::stringstream sep(line);
			std::string field;

			fields.push_back(std::vector<int>());
			while (std::getline(sep, field, ',')) {


				fields.back().push_back(std::stoi(field));


			}


		}
	}


	for (auto row : fields) {
		for (auto field : row) {
			std::cout << field <<' ';
		}
		std::cout << '\n';
	}


		for (int i = 0; i < fields.size(); i++)
		{
			float xcoord = 350+ scalefactor * fields[i][1];
			float ycoord = 100+ scalefactor * fields[i][2];
			cities.push_back(City(i, xcoord, ycoord));
		}

	
	
	return fields;
}


void runAlgorithm(Tour currenttour, int gens, std::string selecting, std::string crossovering, std::string mutating)
{
	std::vector<int> bestSolutions;
	//for (int rep = 0; rep < 4; rep++) {

		std::cout << "Running the genetic algorithm for " << gens << " generations." << std::endl;
		std::cout << "Initial population size: " << initialPopulation << std::endl;
		std::cout << "Generation size: " << generationSize << std::endl;
		auto start = std::chrono::steady_clock::now();
		for (int a = 0; a < initialPopulation; a++) { randomizeRoute(currenttour); }
		for (int i = 0; i < gens; i++) {
			std::cout << "Working on gen number " << i + 1 << std::endl;
			nextGeneration(generationSize, mutationRate, selecting, crossovering, mutating);
			currentgen = i + 1;
			bestSolutions.push_back(tours[0].dist);
		}
		auto end = std::chrono::steady_clock::now();
		std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << std::endl;
	//}
	//std::cout << "Best solutions: " << std::endl;
	//std::sort(bestSolutions.begin(),bestSolutions.end());
	//for (auto i : bestSolutions)
		//std::cout << i << ' ';




}


float euclideanDistance(float x1, float x2, float y1, float y2)
{
	float dist = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
	return dist / scalefactor;
}


float distanceTwoCities(City c1, City c2) {  return euclideanDistance(c1.x, c2.x, c1.y, c2.y); }


float distance(std::vector<City> cits)
{
	float currentDist = 0;

	for (int i = 0; i < cits.size() - 1; i++)
	{
		currentDist += euclideanDistance(cits[i].x, cits[i + 1].x, cits[i].y, cits[i + 1].y);
	}
	currentDist += euclideanDistance(cits[0].x, cits[cits.size() - 1].x, cits[0].y, cits[cits.size() - 1].y);

	return currentDist;
}


int randomCoordinates(char identifier)
{
	int output;

	if (identifier == 'X') output = 510 + (rand() % static_cast<int>(width - 10 - 510 + 1));
	else output = 10 + (rand() % static_cast<int>(height - 20 + 1));

	return output;

}

void randomizeDots()
{
	cities.resize(dotcount, City(0, 0, 0));
	for (int i = 0; i <= dotcount - 1; i++)
	{
		popsize = 0;
		cities[i].x = randomCoordinates('X');
		cities[i].y = randomCoordinates('Y');
		cities[i].id = i;
		bestdist = INT_MAX;
	}

}

Tour randomizeRoute(Tour currenttour)
{
	std::vector<City> a = currenttour.cintour;
	std::random_shuffle(a.begin() + 1, a.end());
	tours.push_back(a);
	return a;

}

void printVector(std::vector<int> path)
{
	for (std::vector<int>::const_iterator i = path.begin(); i != path.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
}

void printVector(std::vector<City> path)
{
	for (std::vector<City>::const_iterator i = path.begin(); i != path.end(); ++i)
		std::cout << i->id << ' ';
	std::cout << std::endl;
}


bool comp(Tour a, Tour b)
{
	return a.dist < b.dist;
}
std::vector<Tour> sortTours(std::vector<Tour> tours) {
	std::sort(tours.begin(), tours.end(),comp);
	return tours;
}

bool cmp(City a, City b)
{
	return a.id < b.id;
}


bool areLegitTours(std::vector<Tour> generation)
{

	if (generation.size() != generationSize) {
		std::cout << "Invalid generation size! Size of this generation is: " << generation.size() << " ,whereas it should be: " << generationSize << std::endl;
	}
	for (int i = 0; i < generation.size(); i++)
		if (!isLegitRoute(generation[i]))
		{
			return false;
		}
	return true;
}

bool isLegitRoute(Tour tourette)
{
	auto vec = tourette.ids();
	std::set<int>s(vec.begin(), vec.end());
	vec = std::vector<int>(s.cbegin(), s.cend());
	if (tourette.cintour.size() == dotcount) { return true; }
	std::cout << "Not legit route!"  << std::endl;
	printVector(tourette.cintour);
	return false;
}


bool isSameRoute(Tour t1, Tour t2)
{
	if (std::abs(t1.dist- t2.dist)<1) { return true; }
	return false;


}


//Fitness proportionate-rulettiselection
void rouletteSelection(int gensize)
{
	std::cout << "Doing roulette wheel selection" << std::endl;
	auxtours.clear();
	//std::cout << "debug 2. tours size: " << tours.size() << std::endl;

	float totalDist = 0;
	for (int i = 0; i < tours.size(); i++)
	{
		totalDist += tours[i].dist;
	}

	std::vector<std::pair<int,float>> probvector;
	float probDistInterval = 0;
	for (int i = 0; i < tours.size(); i++)
	{
		probDistInterval += tours[i].dist / totalDist;
		probvector.push_back(std::make_pair(i, probDistInterval));
	}



	std::random_device rd;  
	std::mt19937 gen(rd());
	std::vector<int> lotteryIndexVector;
	std::uniform_real_distribution<> dis(0.0, 1.0);
	for (int i = 0; i < 20; i++) {
		double prob = dis(gen);
		
		int a = 0;
		while (prob > probvector[a].second) 
		{

			if (a < tours.size()) {
				a++;
			}
			else {
				a = tours.size();
				break;
			}
			
			
		}
		lotteryIndexVector.push_back(probvector[a].first);
	}
	for (int i = 0; i < generationSize; i++)
	{
		auxtours.push_back(tours[lotteryIndexVector[i]]);
	}
}


void select(std::string identifier, int gensize)
{
	if (identifier == "ranked") { rankedSelection(gensize); }
	if (identifier == "roulette") { rouletteSelection(gensize); }

}


void nextGeneration(int gensize, float mutationrate,std::string selecting, std::string crossovering, std::string mutating)
{
	newgen.clear();
	//Selectja parentpairs: k‰ytt‰‰ tours-reittivektoria-> auxtours-reittivektori
	select(selecting, generationSize);
	std::vector<std::pair<int, int>> parentPairs = getParentPairs(generationSize);
	assert(areLegitTours(auxtours));
	//Crossover: auxtours-> newgen7
	crossover(crossovering, parentPairs);
	assert(areLegitTours(newgen));
	//Mutate k‰ytt‰‰ newgeni‰
	mutate(mutating, mutationrate);
	std::cout << "Asserting: dotcount is " << dotcount << std::endl;
	assert(areLegitTours(newgen));
	std::cout << "New generation initialized" << std::endl;
	tours = newgen;
	assert(areLegitTours(tours));
	auxtours.clear();
	newgen.clear();
	tours=sortTours(tours);
	printBestRoutes();
	cycleCounter = 0;
}



void printBestRoutes() {


	bestRoutes1.setString(std::to_string(tours[0].dist));
	std::cout << "Tours 0 is :" << tours[0].representation() << std::endl;
	std::cout << "Dist is:  " << distance(tours[0].cintour) << std::endl;
	bestRoutes2.setString(std::to_string(tours[1].dist));
	bestRoutes3.setString(std::to_string(tours[2].dist));
	bestRoutes4.setString(std::to_string(tours[3].dist));
	std::cout << "Tours 3 is :" << tours[3].representation() << std::endl;
	std::cout << "Dist is:  " << distance(tours[3].cintour) << std::endl;
	bestRoutes5.setString(std::to_string(tours[4].dist));
	bestRoutes6.setString(std::to_string(tours[5].dist));
	bestRoutes7.setString(std::to_string(tours[6].dist));
	bestRoutes8.setString(std::to_string(tours[7].dist));
}


bool buttonPressed(sf::RectangleShape rect, sf::Event event)

{

	auto x = rect.getPosition().x;
	auto y = rect.getPosition().y;

	if (x < event.mouseButton.x &&  event.mouseButton.x < x + buttonwidth && y < event.mouseButton.y && event.mouseButton.y < y + buttonheight) {
		rect.setFillColor(sf::Color::Green);
		return true;
	}
	return false;
}
