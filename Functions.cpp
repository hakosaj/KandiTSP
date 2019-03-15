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
	std::string fileName;
	std::cout << "Enter path to file: C:\\Users\\jh\\Desktop\\Kandi\\Data\\berlin52" << std::endl;
	std::cin >> fileName;

	fileName = "C:\\Users\\jh\\Desktop\\Kandi\\Data\\berlin52.csv";
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
			float xcoord = fields[i][1];
			float ycoord = fields[i][2];
			cities.push_back(City(i, xcoord, ycoord));
		}

	
	
	return fields;
}

void runAlgorithm(Tour currenttour)
{
	int gens = 4;
	
	std::cout << "Running the genetic algorithm for " << gens << " generations." << std::endl;
	std::cout << "Initial population size: " << initialPopulation << std::endl;
	std::cout << "Generation size: " << generationSize << std::endl;
	auto start = std::chrono::steady_clock::now();
	for (int a = 0; a < initialPopulation; a++) { randomizeRoute(currenttour); }
	for (int i = 0; i < gens; i++) { 
		std::cout << "Working on gen number " << i+1 << std::endl;
		nextGeneration(generationSize,mutationRate);
		currentgen = i + 1;
	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << std::endl;





}


void initializeTexts()
{
	TSPText.setFont(font);
	TSPText.setString("TSP Genetic algorithms");
	TSPText.setCharacterSize(24);
	TSPText.setFillColor(sf::Color::Red);
	TSPText.setPosition(10, 10);

	NameYearText.setFont(font);
	NameYearText.setString("Jussi Hakosalo 2018");
	NameYearText.setCharacterSize(20);
	NameYearText.setFillColor(sf::Color::Black);
	NameYearText.setPosition(10, 40);


	SchoolNameText.setFont(font);
	SchoolNameText.setString("Aalto University School of Science");
	SchoolNameText.setCharacterSize(20);
	SchoolNameText.setFillColor(sf::Color::Black);
	SchoolNameText.setPosition(10, 60);


	CurrentDistanceText.setFont(font);
	CurrentDistanceText.setCharacterSize(20);
	CurrentDistanceText.setFillColor(sf::Color::Red);
	CurrentDistanceText.setPosition(10, 310 + VerticalOffset);

	CurrentBestNumberText.setFont(font);
	CurrentBestNumberText.setCharacterSize(20);
	CurrentBestNumberText.setFillColor(sf::Color::Red);
	CurrentBestNumberText.setPosition(10, 360 + VerticalOffset);

	CurrentBestText.setFont(font);
	CurrentBestText.setString("Best distance");
	CurrentBestText.setCharacterSize(18);
	CurrentBestText.setFillColor(sf::Color::Black);
	CurrentBestText.setPosition(10, 340 + VerticalOffset);


	currentDistance.setFont(font);
	currentDistance.setString("Current distance");
	currentDistance.setCharacterSize(18);
	currentDistance.setFillColor(sf::Color::Black);
	currentDistance.setPosition(10, 290 + VerticalOffset);

	randomizerRateText.setFont(font);
	randomizerRateText.setString("Randomizer rate");
	randomizerRateText.setCharacterSize(18);
	randomizerRateText.setFillColor(sf::Color::Black);
	randomizerRateText.setPosition(10, 390 + VerticalOffset);

	randomizerSpeedNumberText.setFont(font);
	randomizerSpeedNumberText.setCharacterSize(20);
	randomizerSpeedNumberText.setFillColor(sf::Color::Red);
	randomizerSpeedNumberText.setPosition(10, 410 + VerticalOffset);

	CurrentPopulationText.setFont(font);
	CurrentPopulationText.setString("Population size");
	CurrentPopulationText.setCharacterSize(18);
	CurrentPopulationText.setFillColor(sf::Color::Black);
	CurrentPopulationText.setPosition(10, 440 + VerticalOffset);

	CurrentPopulationNumberText.setFont(font);
	CurrentPopulationNumberText.setCharacterSize(20);
	CurrentPopulationNumberText.setFillColor(sf::Color::Red);
	CurrentPopulationNumberText.setPosition(10, 460 + VerticalOffset);


	CurrentBestSolutionsText.setFont(font);
	CurrentBestSolutionsText.setString("Fittest solutions");
	CurrentBestSolutionsText.setCharacterSize(18);
	CurrentBestSolutionsText.setFillColor(sf::Color::Black);
	CurrentBestSolutionsText.setPosition(20, 500 + VerticalOffset);


	/*AdjacencyRepresentationText.setFont(font);
	AdjacencyRepresentationText.setString("Adjacency repres.");
	AdjacencyRepresentationText.setCharacterSize(18);
	AdjacencyRepresentationText.setFillColor(sf::Color::Black);
	AdjacencyRepresentationText.setPosition(250, 390 + VerticalOffset);
	*/



	/*AdjacencyRepresentation.setFont(font);
	AdjacencyRepresentation.setCharacterSize(18);
	AdjacencyRepresentation.setFillColor(sf::Color::Black);
	AdjacencyRepresentation.setPosition(250, 410);
	*/

	CityListText.setFont(font);
	CityListText.setString("City list");
	CityListText.setCharacterSize(18);
	CityListText.setFillColor(sf::Color::Black);
	CityListText.setPosition(150, 390 + VerticalOffset);

	CityList.setFont(font);
	CityList.setCharacterSize(18);
	CityList.setFillColor(sf::Color::Black);
	CityList.setPosition(150, 410);


	bestRoutesNumber.setFont(font);
	bestRoutesNumber.setCharacterSize(18);
	bestRoutesNumber.setFillColor(sf::Color::Black);


	CycleCounterText.setFont(font);
	CycleCounterText.setCharacterSize(18);
	CycleCounterText.setFillColor(sf::Color::Black);
	CycleCounterText.setPosition(170, 440);


	//Best routes
	bestRoutes1.setFont(font);
	bestRoutes1.setCharacterSize(18);
	bestRoutes1.setFillColor(sf::Color::Black);

	bestRoutes2.setFont(font);
	bestRoutes2.setCharacterSize(18);
	bestRoutes2.setFillColor(sf::Color::Black);

	bestRoutes3.setFont(font);
	bestRoutes3.setCharacterSize(18);
	bestRoutes3.setFillColor(sf::Color::Black);

	bestRoutes4.setFont(font);
	bestRoutes4.setCharacterSize(18);
	bestRoutes4.setFillColor(sf::Color::Black);

	bestRoutes5.setFont(font);
	bestRoutes5.setCharacterSize(18);
	bestRoutes5.setFillColor(sf::Color::Black);

	bestRoutes6.setFont(font);
	bestRoutes6.setCharacterSize(18);
	bestRoutes6.setFillColor(sf::Color::Black);

	bestRoutes7.setFont(font);
	bestRoutes7.setCharacterSize(18);
	bestRoutes7.setFillColor(sf::Color::Black);

	bestRoutes8.setFont(font);
	bestRoutes8.setCharacterSize(18);
	bestRoutes8.setFillColor(sf::Color::Black);





}

void initializeButtonTexts()
{


	// Button texts. MODIFY POSITIONS BY VerticalOffset



	RunSimulationButtonText.setFont(font);
	RunSimulationButtonText.setString("Generate");
	RunSimulationButtonText.setCharacterSize(18);
	RunSimulationButtonText.setFillColor(sf::Color::Black);
	RunSimulationButtonText.setPosition(buttonGridHorizontal1 + 1, buttonGridVertical1 + textButtonOffset + VerticalOffset);

	RandomizeRoutesText.setFont(font);
	RandomizeRoutesText.setString("Run ");
	RandomizeRoutesText.setCharacterSize(18);
	RandomizeRoutesText.setFillColor(sf::Color::Black);
	RandomizeRoutesText.setPosition(buttonGridHorizontal1 + 1, buttonGridVertical2 + textButtonOffset + VerticalOffset);


	showBestRouteText.setFont(font);
	showBestRouteText.setString("Show shortest");
	showBestRouteText.setCharacterSize(18);
	showBestRouteText.setFillColor(sf::Color::Black);
	showBestRouteText.setPosition(161, 101 + VerticalOffset);

	randomizeRoutesOnceText.setFont(font);
	randomizeRoutesOnceText.setString("Run once ");
	randomizeRoutesOnceText.setCharacterSize(18);
	randomizeRoutesOnceText.setFillColor(sf::Color::Black);
	randomizeRoutesOnceText.setPosition(161, 161 + VerticalOffset);


	changeDotcountText.setFont(font);
	changeDotcountText.setString("Set pointcount");
	changeDotcountText.setCharacterSize(18);
	changeDotcountText.setFillColor(sf::Color::Black);
	changeDotcountText.setPosition(buttonGridHorizontal1 + 1, buttonGridVertical3 + textButtonOffset + VerticalOffset);

	exitButtonText.setFont(font);
	exitButtonText.setString("Reset route");
	exitButtonText.setCharacterSize(18);
	exitButtonText.setFillColor(sf::Color::Black);
	exitButtonText.setPosition(buttonGridHorizontal2 + 1, buttonGridVertical3 + textButtonOffset + VerticalOffset);


	printBestRoutesButtonText.setFont(font);
	printBestRoutesButtonText.setString("Print shortest");
	printBestRoutesButtonText.setCharacterSize(18);
	printBestRoutesButtonText.setFillColor(sf::Color::Black);
	printBestRoutesButtonText.setPosition(buttonGridHorizontal3 + 1, buttonGridVertical1 + textButtonOffset + VerticalOffset);

	changeRandomizerRateButtonText.setFont(font);
	changeRandomizerRateButtonText.setString("Change RRate");
	changeRandomizerRateButtonText.setCharacterSize(18);
	changeRandomizerRateButtonText.setFillColor(sf::Color::Black);
	changeRandomizerRateButtonText.setPosition(buttonGridHorizontal3 + 1, buttonGridVertical2 + textButtonOffset + VerticalOffset);

	cycleButtonText.setFont(font);
	cycleButtonText.setString("Cycle routes");
	cycleButtonText.setCharacterSize(18);
	cycleButtonText.setFillColor(sf::Color::Black);
	cycleButtonText.setPosition(buttonGridHorizontal3 + 1, buttonGridVertical3 + textButtonOffset + VerticalOffset);


	SubtourOptButtonText.setFont(font);
	SubtourOptButtonText.setString("NextGeneration");
	SubtourOptButtonText.setCharacterSize(18);
	SubtourOptButtonText.setFillColor(sf::Color::Black);
	SubtourOptButtonText.setPosition(buttonGridHorizontal3 + 1, buttonGridVertical4 + textButtonOffset + VerticalOffset);

	twoOptButtonText.setFont(font);
	twoOptButtonText.setString("Run algorithm");
	twoOptButtonText.setCharacterSize(18);
	twoOptButtonText.setFillColor(sf::Color::Black);
	twoOptButtonText.setPosition(buttonGridHorizontal3 + 1, buttonGridVertical5 + textButtonOffset + VerticalOffset);





}
void initializeDots() {


	for (int i = 0; i < dotcount; i++)
	{
		float xcoord = randomCoordinates('X');
		float ycoord = randomCoordinates('Y');
		cities.push_back(City(i, xcoord, ycoord));
	}


}


void initializeDotsCircle() {


	for (int i = 0; i < dotcount; i++)
	{
		cities.empty();
		float xcoord = 900+200*cos((2*3.1415926*i)/dotcount);
		float ycoord = 300 + 200 * sin((2 * 3.1415926*i) / dotcount);
		cities.push_back(City(i, xcoord, ycoord));
	}


}

void initializeDotsStar() {


	for (int i = 0; i < dotcount; i++)
	{
		float xcoord;
		float ycoord;
		cities.empty();
		if (i % 2 == 0) {
			xcoord = 900 + 150 * cos((2 * 3.1415926*i) / dotcount);
			ycoord = 300 + 150 * sin((2 * 3.1415926*i) / dotcount);
		}
		else {
			srand(time(NULL));
			 xcoord = 900 + 20*(10 + rand() %5 -2 ) * cos((2 * 3.1415926*i) / dotcount);
			 ycoord = 300 + 20*(10 + rand() %5 - 2) * cos((2 * 3.1415926*i) / dotcount);
		}
		cities.push_back(City(i, xcoord, ycoord));
	}

}

float euclideanDistance(float x1, float x2, float y1, float y2)
{
	float dist = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
	return dist;
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

void initializeShapes() {


	// set shape properties

	reunat.setFillColor(sf::Color::Transparent);
	reunat.setOutlineColor(sf::Color::Black);
	reunat.setPosition(leftEdge, outlinet);
	reunat.setOutlineThickness(outlinet);

	// set and calculate dots


	testicircle.setFillColor(windowColor);
	testicircle.setOutlineThickness(3);
	testicircle.setOutlineColor(sf::Color::Black);

	startcircle.setFillColor(windowColor);
	startcircle.setOutlineThickness(3);
	startcircle.setOutlineColor(sf::Color::Red);


	//Button positions
	generateButton.setFillColor(sf::Color::Red);
	generateButton.setPosition(buttonGridHorizontal1, buttonGridVertical1 + VerticalOffset);

	randomizebutton.setFillColor(sf::Color::Red);
	randomizebutton.setPosition(buttonGridHorizontal1, buttonGridVertical2 + VerticalOffset);

	randomizeOnceButton.setFillColor(sf::Color::Red);
	randomizeOnceButton.setPosition(buttonGridHorizontal2, buttonGridVertical2 + VerticalOffset);

	showBestRouteButton.setFillColor(sf::Color::Red);
	showBestRouteButton.setPosition(buttonGridHorizontal2, buttonGridVertical1 + VerticalOffset);

	changeDotcountButton.setFillColor(sf::Color::Red);
	changeDotcountButton.setPosition(buttonGridHorizontal1, buttonGridVertical3 + VerticalOffset);

	exitButton.setFillColor(sf::Color::Red);
	exitButton.setPosition(buttonGridHorizontal2, buttonGridVertical3 + VerticalOffset);

	printBestRoutesButton.setFillColor(sf::Color::Red);
	printBestRoutesButton.setPosition(buttonGridHorizontal3, buttonGridVertical1 + VerticalOffset);

	changeRandomizerRateButton.setFillColor(sf::Color::Red);
	changeRandomizerRateButton.setPosition(buttonGridHorizontal3, buttonGridVertical2 + VerticalOffset);

	cycleButton.setFillColor(sf::Color::Red);
	cycleButton.setPosition(buttonGridHorizontal3, buttonGridVertical3 + VerticalOffset);

	cycleButton.setFillColor(sf::Color::Red);
	cycleButton.setPosition(buttonGridHorizontal3, buttonGridVertical3 + VerticalOffset);

	SubtourOptButton.setFillColor(sf::Color::Red);
	SubtourOptButton.setPosition(buttonGridHorizontal3, buttonGridVertical4 + VerticalOffset);

	twoOptButton.setFillColor(sf::Color::Red);
	twoOptButton.setPosition(buttonGridHorizontal3, buttonGridVertical5 + VerticalOffset);





	//FIttest tour texts
	bestRoutes1.setPosition(gridlinesHorizontal[0], gridlinesVertical[2]);
	bestRoutes2.setPosition(gridlinesHorizontal[0], gridlinesVertical[3]);
	bestRoutes3.setPosition(gridlinesHorizontal[0], gridlinesVertical[4]);
	bestRoutes4.setPosition(gridlinesHorizontal[0], gridlinesVertical[5]);
	bestRoutes5.setPosition(gridlinesHorizontal[1], gridlinesVertical[2]);
	bestRoutes6.setPosition(gridlinesHorizontal[1], gridlinesVertical[3]);
	bestRoutes7.setPosition(gridlinesHorizontal[1], gridlinesVertical[4]);
	bestRoutes8.setPosition(gridlinesHorizontal[1], gridlinesVertical[5]);



	int mousecharter = 0;


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
void sortTours(std::vector<Tour>) {
	std::sort(tours.begin(), tours.end());
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





void threeOptMutate()
{
	for (int i = 0; i < newgen.size(); i++) {
		newgen[i] = threeOpt(newgen[i]);
	}


}

std::tuple<double,Tour> reverse_segment_if_better(Tour tour, int i, int j, int k)
{
	//std::cout << "DELTASSA!" << "i on: " << i << " j on: " << j << " k on: " << k << std::endl;
	City A = tour.cintour[i - 1];
	City B = tour.cintour[i];
	City C = tour.cintour[j - 1];
	City D = tour.cintour[j];
	City E = tour.cintour[k-1];
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
		return std::make_tuple(-d0 + d1,tour);
		}
	else if (d0 > d2){
		std::reverse(tour.cintour.begin() + j, tour.cintour.begin() + k);
		return std::make_tuple(-d0 + d2, tour);
		}
	else if (d0 > d4){
		std::reverse(tour.cintour.begin() + i, tour.cintour.begin() + k);
		return std::make_tuple(-d0 + d4, tour);
		}
	else if (d0 > d3){
		std::vector<City>  tmp1(tour.cintour.begin()+j, tour.cintour.begin() + k);
		std::vector<City>  tmp2(tour.cintour.begin() + i, tour.cintour.begin() + j);
		tmp1.insert(tmp1.end(), tmp2.begin(), tmp2.end());
		std::copy(tmp1.begin(), tmp1.end(), tour.cintour.begin()+i);
		std::make_tuple(-d0 + d3, tour);
		}
	return std::make_tuple(0,tour);
	 


}


std::vector<std::tuple<int, int, int>> all_segments(int N)
{
	std::vector<std::tuple<int, int, int>> tuples;
	for (int i = 1; i < N; i++) {
		for (int j = i + 2; j < N; j++) {
			for (int k = j + 2; k < N + (i > 0); k++) {
				auto a=std::make_tuple(i, j, k);
				tuples.push_back(a);
			}
		}
	}
	return tuples;
}

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
				for (int k = j + 2; k < N+(i>0); k++) {
					auto a  = reverse_segment_if_better(rettour, i, j, k);
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


bool isSameRoute(Tour t1, Tour t2)
{
	if (std::abs(t1.dist- t2.dist)<1) { return true; }
	return false;


}
void twoOptMutate()
{
	std::cout << "2-opt hillclimb in progress" << std::endl;

	for (int i = 0; i < newgen.size(); i++) {
		newgen[i] = twoOpt(newgen[i]);
	}


}

//Python 2Opt:

/*
def two_opt(route):
	best = route
	improved = True
	while improved:
		improved = False
		for i in range(1, len(route)-2):
			for j in range(i+1, len(route)):
				if j-i == 1: continue # changes nothing, skip then
				new_route = route[:]
				new_route[i:j] = route[j-1:i-1:-1] # this is the 2woptSwap
				if cost(new_route) < cost(best):
					best = new_route
					improved = True
		route = best
	return best

*/
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
					std::reverse(newroute.begin()+(i-1), newroute.begin() + (j - 1) );
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


//Kahden kaupungin vaihto: Swap-mutaatio. vaihdetaan dotcount* mutation rate kaupunkeja keskenään, pyöristys alaspäin
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


//Valitsee mutaatiometodin
void mutate(std::string identifier, float mutationrate)
{
	std::cout << "Mutation underway. Chosen mutation method: " << identifier << std::endl;
	if (identifier == "SWAP") { swapMutate(mutationrate); }
	if (identifier == "2opt") { twoOptMutate(); }
	if (identifier == "3opt") { threeOptMutate(); }


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
		int subsetLoLimit = rand() % dotcount - 1 +1;
		int subsetHiLimit = rand() % dotcount - 1 +1;

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

				while (std::find(st, en, rordertour.cintour.at(r-count).id) != en)
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

//Tekee adjasenssimatriisin
std::vector<std::tuple<City, City, City>> generateAdjacencyMatrix(Tour tour)
//ekan naapurit on kaksi seuraavaa: nykyinen, edellinen, seuraava
{
	auto cities = tour.cintour;
	std::vector<std::tuple<City, City, City>> neighbors;

	neighbors.push_back(std::make_tuple(cities[0], cities.back(), cities[1]));
	for (int i = 1; i < cities.size()-1; i++)
	{
		neighbors.push_back(std::make_tuple(cities[i], cities[i - 1], cities[i + 1]));
	}
	neighbors.push_back(std::make_tuple(cities.back(), cities[cities.size() - 2], cities[0]));

	return neighbors;

}
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
				return std::get< 0 >(item).id == idq;
			});

			std::tuple<City,City,City> a1 = adjacency1[i];
			std::tuple<City, City, City> a2 = *position;
			//std::cout << "Adj 1: " << std::get<0>(a1).id << std::get<1>(a1).id<< std::get<2>(a1).id << std::endl;
			//std::cout << "Adj 2: " << std::get<0>(a2).id << std::get<1>(a2).id << std::get<2>(a2).id << std::endl;
			
			
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
			std::set<City,CustomCompare> adjacentCitiesSet;
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
			adjacencyUnions=removeFromAdjacencyUnions(N,adjacencyUnions);
			//get N's neighbor list
			
			
			auto neighborListIter = std::find_if(adjacencyUnions.begin(), adjacencyUnions.end(),
				[=](auto item)
			{
				return item.first == N;
			});
			std::pair<City, std::vector<City>>neighborList=  *neighborListIter;
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
				for(int x = 0; x < NNeighborLists.size(); x++)
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



//Valitsee crossover-metodin
void crossover(std::string identifier, std::vector<std::pair<int, int>> parentPairs)
{
	std::cout << "Starting crossover. Selected operation: " << identifier << std::endl;
	if (identifier == "OX") { orderCrossover(parentPairs); }
	if (identifier == "EX") { edgeRecombinationCrossover(parentPairs); }


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
 

void select(std::string identifier, int gensize)
{
	if (identifier == "ranked") { rankedSelection(gensize); }
	if (identifier == "roulette") { rouletteSelection(gensize); }

}


void nextGeneration(int gensize, float mutationrate)
{
	newgen.clear();
	//Selectja parentpairs: käyttää tours-reittivektoria-> auxtours-reittivektori
	select("roulette", generationSize);
	std::vector<std::pair<int, int>> parentPairs = getParentPairs(generationSize);
	assert(areLegitTours(auxtours));
	//Crossover: auxtours-> newgen7
	crossover("OX", parentPairs);
	assert(areLegitTours(newgen));
	//Mutate käyttää newgeniä
	mutate("3opt", mutationrate);
	std::cout << "Asserting: dotcount is " << dotcount << std::endl;
	assert(areLegitTours(newgen));
	std::cout << "New generation initialized" << std::endl;
	tours = newgen;
	assert(areLegitTours(tours));
	auxtours.clear();
	newgen.clear();
	sortTours(tours);
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
