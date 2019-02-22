#include "Functions.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <Windows.h> 
#include <string>
#include <chrono>
#include <time.h> 
#include <thread>
#include <tuple>
#include <math.h>
#include <utility>
#include <queue>
#include "Constants.h"
#include "Objects.h"
#include "AuxilaryClasses.h"



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
	exitButtonText.setString("Quit program");
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





}
void initializeDots() {


	for (int i = 0; i < dotcount; i++)
	{
		float xcoord = randomCoordinates('X');
		float ycoord = randomCoordinates('Y');
		cities.push_back(City(i, xcoord, ycoord));
	}


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
		bestdist = 14600000;
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

void sortTours() {
	std::sort(tours.begin(), tours.end());
}

bool cmp(City a, City b)
{
	return a.id < b.id;
}


//Ottaa parhaimmat gensize reittiä, nämä ovat uuden generaation pohja
void getParentTours(int gensize)
{
	auxtours.clear();
	for (int i = 0; i < generationSize; i++)
	{
		auxtours.push_back(tours[i]);
		//std::cout << tours[i].representation() << std::endl;
	}
}


//Kahden kaupungin vaihto: Swap-mutaatio. vaihdetaan dotcount* mutation rate kaupunkeja keskenään, pyöristys alaspäin

void swapMutate(float mutationrate)
{
	std::cout << "Doing swap mutation. Mutation rate: " << mutationrate << std::endl;
	int swaps = std::max((int)floor(mutationrate*dotcount), 1);
	for (int i = 0; i < generationSize; i++) {
		for (int s = 0; s < swaps; s++);
		{
			int pos1 = rand() % 8 + 1;
			int pos2 = rand() % 8 + 1;
			std::iter_swap(newgen[i].cintour.begin() + pos1, newgen[i].cintour.begin() + pos2);
		}
	}
}


//Valitsee mutaatiometodin
void mutate(std::string identifier, float mutationrate)
{
	if (identifier == "SWAP") { swapMutate(mutationrate); }


}

/*Order crossover.
1) Valitaan subset jälkimmäisestä parentista.
2) Täytetään subsetin osuus järjestykseen, sitten loput järjestyksessä
Esim:
p1 1 2 |5 6 4| 3 8 7
p2 1 4 |2 3 6| 5 7 8

o1 - -  5 6 4  - - -
o2 2 3  5 6 4  7 8 1
*/

void orderCrossover(std::vector<std::pair<int, int>> parentPairs)
{
	std::cout << "Doing order crossover. Crossover subset from " << std::get<0>(crossoverIndices) << " to " << std::get<1>(crossoverIndices) << std::endl;
	for (int g = 0; g < generationSize; g++)
	{
		//std::cout << "Doing order crossover for parent pair: " << std::get<0>(parentPairs[g]) << " , " << std::get<1>(parentPairs[g]) << std::endl;
		//std::cout << "Original pairs are:" << std::endl;
		Tour parent1 = auxtours[std::get<0>(parentPairs[g])];
		Tour parent2 = tours[std::get<1>(parentPairs[g])];

		int subsetLoLimit = std::get<0>(crossoverIndices);
		int subsetHiLimit = std::get<1>(crossoverIndices);
		//Parent 1 subset
		std::vector<City> citiesInSubset;
		//std::cout << "debuggausta" << std::endl;
		for (int a = 5; a < 12; a++)
		{
			citiesInSubset.push_back(parent1.cintour[a]);
		}
		//std::cout << "Constructing a new tour" << std::endl;
		Tour newtour(citiesInSubset);
		std::cout << "Cut from parent 1: " << std::endl;
		//newtour.printTour();
		//std::cout << "Parent2: " << std::endl;
		//parent2.printTour();
		//std::vector<int> points;
		//std::cout << "First and last cut elements: " << parent2.cintour[5].id << "and " << parent2.cintour[11].id << std::endl;
		//std::cout << "Parent 2-mukaiseen jarjestykseen:" << std::endl;
		//std::cout << "P2-alkupiste: " << parent2.cintour[12].id<< std::endl;

		//Tehdään uudelleenjärjestelty parent2-vektori, jossa siis loppuosa, alkuosa, cut;
		std::vector<City> parent2rorder;
		for (int a = subsetHiLimit; a < parent2.size(); a++)
		{
			parent2rorder.push_back(parent2.cintour[a]);
		}
		for (int a = 1; a < subsetHiLimit; a++)
		{
			parent2rorder.push_back(parent2.cintour[a]);
		}
		Tour rordertour(parent2rorder);
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
			//std::cout << "current newtour: " << std::endl;
			//printVector(newtour.ids());

		}

		//Käydään läpi alkuvektori. Jokainen slotti: Jos tämä löytyy cutista, edetään p2rorderia yks eteenpäin. Jos ei löydy, lisätään cuttiin. Poistetaan reorderedin eka elementti aina.
		int insertIterator = 0;
		for (int a = subsetLoLimit - 1; a > 0; a--)
		{
			int r = 0 + count;
			const std::vector<int> jada = newtour.ids();
			std::vector<int>::const_iterator st = jada.begin();
			std::vector<int>::const_iterator en = jada.end();
			while (std::find(st, en, rordertour.cintour[r - count].id) != en)
			{
				r++;

			}
			newtour.cintour.insert(newtour.cintour.begin() + insertIterator, rordertour.cintour[r - count]);
			insertIterator++;
			//std::cout << "current newtour: " << std::endl;
			//printVector(newtour.ids());
			count++;


		}
		newtour.cintour.insert(newtour.cintour.begin(), parent1.cintour[0]);


		newgen.push_back(newtour);
		std::cout << "Added " << newtour.representation() << " to new generation" << std::endl;
	}

	std::cout << "Order crossover ready" << std::endl;



};


//Valitsee crossover-metodin
void crossover(std::string identifier, std::vector<std::pair<int, int>> parentPairs)
{
	std::cout << "Starting crossover. Selected operation: " << identifier << std::endl;
	if (identifier == "OX") { orderCrossover(parentPairs); }


}


//Ottaa tietyt kaksi reittiä kymmenestä, yhdistää nämä pareiksi
std::vector<std::pair<int, int>> getParentPairs(int gensize)
{
	std::vector<std::pair<int, int>> parentPairs;
	for (int i = 0; i < gensize; i++)
	{
		int p1 = rand() % 10;
		int p2 = rand() % 10;
		parentPairs.push_back(std::make_pair(p1, p2));
		//std::cout << p1 << '+' << p2 <<  std::endl;
	}
	return parentPairs;

}

void nextGeneration(int gensize, float mutationrate)
{
	newgen.clear();
	getParentTours(generationSize);
	std::vector<std::pair<int, int>> parentPairs = getParentPairs(generationSize);
	crossover("OX", parentPairs);
	mutate("SWAP", mutationrate);
	tours = newgen;
	cycleCounter = 0;
}



void printBestRoutes() {


	bestRoutes1.setString(std::to_string(tours[0].dist));
	bestRoutes2.setString(std::to_string(tours[1].dist));
	bestRoutes3.setString(std::to_string(tours[2].dist));
	bestRoutes4.setString(std::to_string(tours[3].dist));
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

