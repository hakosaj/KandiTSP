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
		"berlin52", "att48","bays29","rat99","kroA100","lin105","pr76","pr124","st70",
//done: berlinb att bas pr kroa lin u pr st



	};
	std::sort(instances.begin(),instances.end());
	std::cout << "Choose instance:" << std::endl;


	for (auto it = instances.begin(); it != instances.end(); it++) {
		std::cout << *it << std::endl;
	};


	std::cin >> fileEnd;
	//fileEnd = "berlin52";


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

	int xmax = 0;
	int ymax = 0;
	int xmin = 0;
	int ymin = 0;


	for (int i = 0; i < fields.size(); i++)
	{
		xmax = (fields[i][1] > xmax) ? fields[i][1] : xmax;
		ymax = (fields[i][2] > ymax) ? fields[i][2] : ymax;
		xmin = (fields[i][1] < xmin) ? fields[i][1] : xmin;
		ymin = (fields[i][2] < ymin) ? fields[i][2] : ymin;
	}
	double delta= ((xmax - xmin)+(ymax-ymin))/2 ;

	scalefactor = 370 / delta;

		for (int i = 0; i < fields.size(); i++)
		{
			float xcoord = 650+ scalefactor * fields[i][1];
			float ycoord = 100+ scalefactor * fields[i][2];
			cities.push_back(City(i, xcoord, ycoord));
		}

	
	
	return fields;
}


void runAlgorithm(Tour currenttour, int gens, std::string selecting, std::string crossovering, std::string mutating)
{
	std::vector<int> bestSolutions;
	vector<Tour> bestPaths;
	auto totalstart = std::chrono::steady_clock::now();
	int reptot = 1;
	std::string reps;
	cout << "How many iterations? " << endl;
	std::cin >> reps;
	auto iters = std::stoi(reps);


	for (int rep = 0; rep < iters; rep++) {

		initialPopulation = 70;
		cout << "Iterations: " << rep+1 << " of " << reptot << endl;
		std::cout << "Running the genetic algorithm for " << gens << " generations." << std::endl;
		std::cout << "Initial population size: " << initialPopulation << std::endl;
		std::cout << "Generation size: " << generationSize << std::endl;
		generationSize = 70;
		auto start = std::chrono::steady_clock::now();
		while (tours.size()<generationSize)
		//while (tours.size()<generationSize || !areLegitTours(tours))
			{ randomizeRoute(currenttour);
			cout << "Perusarvonta. Miten t‰ss‰ voi kusta?" << endl;
			}
		
		for (int i = 0; i < gens; i++) {
			std::cout << "Working on gen number " << i + 1 << std::endl;
			nextGeneration(generationSize, mutationRate, selecting, crossovering, mutating,currentgen);
			currentgen = i + 1;

			if (stoppingCriteriaMet) { break; }



		}
		auto end = std::chrono::steady_clock::now();
		int timer = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "Elapsed time: " << timer << " milliseconds." << std::endl;
		bestSolutions.push_back(tours[0].distance());
		bestPaths.push_back(tours[0]);
		cout << selecting << " " << crossovering << " " << mutating << endl;

	}

	auto totalend = std::chrono::steady_clock::now();
	int timer = std::chrono::duration_cast<std::chrono::milliseconds>(totalend - totalstart).count();
	float mins = timer / 60000.0;

	cout << "Elapsed: " << mins << " minutes." << endl;
	for (int i = 0; i < reptot; i++) {
		cout << bestSolutions[i] << endl;
	}
	cout << "Average: " << std::accumulate(bestSolutions.begin(), bestSolutions.end(), 0.0) / bestSolutions.size() << endl;

	bestPaths = sortTours(bestPaths);
	tours = bestPaths;



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
	return a.distance() < b.distance();
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

	for (int t = 0; t < generation.size();t++) {
		for (int r = 0; r < generation.size();r++) {

			if (t == r) {
				continue;
			}
			if (generation[t].cintour == generation[r].cintour) {
				//cout << generation[t].representation() << endl;
				//cout << generation[r].representation() << endl;
				return false;
			}
		}

	}

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
	if (tourette.cintour.size() == s.size() && tourette.cintour.size()==dotcount) { return true; }

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

	vector<double> distanceInverse;
	for (Tour t : tours) {
		distanceInverse.push_back(1.0 / (t.distance()) );
	}
	
	double inverseSum = std::accumulate(distanceInverse.begin(), distanceInverse.end(), 0.0);

	std::transform(distanceInverse.begin(), distanceInverse.end(), distanceInverse.begin(),
		[inverseSum](double d) {return d / inverseSum; });


	vector<double> cumulativeProbabilities;
	double currentSum = 0;
	for (double d : distanceInverse) {
		currentSum += d;
		cumulativeProbabilities.push_back(currentSum);
	}


	vector<int> indexes;


	tours = sortTours(tours);
	auxtours.push_back(tours[0]);
	int ind = 1;
	while (auxtours.size() < generationSize / 2 + 1) {
		try {

			float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0));
			for (int j = 0; j < cumulativeProbabilities.size(); j++) {
				if (cumulativeProbabilities[j] > r2) {
					ind = j;
					break;
				}
			}



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
		}
		catch (const std::exception& e) {
			cout << "Kaikki k‰yty l‰pi. Fuck." << endl;

		}



	}

	cout << "Roulette wheel selection done." << endl;
	assert(areLegitTours(auxtours));
}


void select(std::string identifier, int gensize)
{
	if (identifier == "ranked") { rankedSelection(gensize); }
	if (identifier == "roulette") { rouletteSelection(gensize); }

}


void nextGeneration(int gensize, float mutationrate,std::string selecting, std::string crossovering, std::string mutating, int currentgen)
{
	newgen.clear();
	auto copyt = tours;
	//Selectja parentpairs: k‰ytt‰‰ tours-reittivektoria-> auxtours-reittivektori
	//assert(areLegitTours(tours));

	select(selecting, generationSize);
/*
	cout << "Originals: \n";
	for (auto r : tours) {
		cout << r.representation() << endl;
	}
	cout << "After selection: \n";
	for (auto r : auxtours) {
		cout << r.representation() << endl;
	}
	*/


	std::vector<std::pair<int, int>> parentPairs = getParentPairs(generationSize);


	assert(areLegitTours(auxtours));
	//Crossover: auxtours-> newgen

	crossover(crossovering, parentPairs);
	assert(areLegitTours(newgen));
	//Mutate k‰ytt‰‰ newgeni‰
	mutate(mutating, mutationrate);


	if (areLegitTours(newgen)) {
		std::cout << "New generation initialized" << std::endl;
		if (averageChangeStopper(tours, newgen)) {
			stoppingCriteriaMet = true;
			cout << "Stopping criteria met." << endl;
		}
		else {
			stoppingCriteriaMet = false;
		}


		tours = newgen;

		auxtours.clear();
		newgen.clear();
		for (Tour t : tours) {
			t.dist = t.distance();
		}
		tours = sortTours(tours);
		printBestRoutes(tours);
		cycleCounter = 0;
	}
	else if (currentgen > 4) {
		stoppingCriteriaMet = true;
		cout << "Stopping due to convergent behavior." << endl;
		auxtours.clear();
		newgen.clear();
		for (Tour t : tours) {
			t.dist = t.distance();
		}
		tours = sortTours(tours);
		printBestRoutes(tours);
		cycleCounter = 0;
	}
	else {/*
		cout << "Stopping due to early convergence" << endl;
		stoppingCriteriaMet = true;
		tours = copyt;
		auxtours.clear();
		newgen.clear();
		for (Tour t : tours) {
			t.dist = t.distance();
		}
		tours = sortTours(tours);
		printBestRoutes(tours);
		cycleCounter = 0;

	}*/
		std::cout << "New generation initialized" << std::endl;
		if (averageChangeStopper(tours, newgen)) {
			stoppingCriteriaMet = true;
			cout << "Stopping criteria met." << endl;
		}
		else {
			stoppingCriteriaMet = false;
		}


		tours = newgen;

		auxtours.clear();
		newgen.clear();
		for (Tour t : tours) {
			t.dist = t.distance();
		}
		tours = sortTours(tours);
		printBestRoutes(tours);
		cycleCounter = 0;
	}

	}



void printBestRoutes(vector<Tour> tours) {


	bestRoutes1.setString(std::to_string(tours[0].distance()));
	assert(isLegitRoute(tours[0]));
	bestRoutes2.setString(std::to_string(tours[1].distance()));
	bestRoutes3.setString(std::to_string(tours[2].distance()));
	bestRoutes4.setString(std::to_string(tours[3].distance()));
	bestRoutes5.setString(std::to_string(tours[4].distance()));
	bestRoutes6.setString(std::to_string(tours[5].distance()));
	bestRoutes7.setString(std::to_string(tours[6].distance()));
	bestRoutes8.setString(std::to_string(tours[7].distance()));
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
