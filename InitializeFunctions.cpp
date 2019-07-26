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

//Initialize texts
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
//Initialize button texts
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


	runAlgorithmButtonText.setFont(font);
	runAlgorithmButtonText.setString("Run algorithm");
	runAlgorithmButtonText.setCharacterSize(18);
	runAlgorithmButtonText.setFillColor(sf::Color::Black);
	runAlgorithmButtonText.setPosition(buttonGridHorizontal3 + 1, buttonGridVertical5 + textButtonOffset + VerticalOffset);





}
//Initialize dots randomly
void initializeDots() {


	for (int i = 0; i < dotcount; i++)
	{
		float xcoord = randomCoordinates('X');
		float ycoord = randomCoordinates('Y');
		cities.push_back(City(i, xcoord, ycoord));
	}


}
//Initialize dots in a circle
void initializeDotsCircle() {


	for (int i = 0; i < dotcount; i++)
	{
		cities.empty();
		float xcoord = 900 + 200 * cos((2 * 3.1415926*i) / dotcount);
		float ycoord = 300 + 200 * sin((2 * 3.1415926*i) / dotcount);
		cities.push_back(City(i, xcoord, ycoord));
	}


}
//Initialize dots in a star
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
			xcoord = 900 + 20 * (10 + rand() % 5 - 2) * cos((2 * 3.1415926*i) / dotcount);
			ycoord = 300 + 20 * (10 + rand() % 5 - 2) * cos((2 * 3.1415926*i) / dotcount);
		}
		cities.push_back(City(i, xcoord, ycoord));
	}

}
//Initialize the shapes
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



	runAlgorithmButton.setFillColor(sf::Color::Red);
	runAlgorithmButton.setPosition(buttonGridHorizontal3, buttonGridVertical5 + VerticalOffset);





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
