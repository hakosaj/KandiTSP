#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <Windows.h> 
#include <string>
#include <tuple>
#include <math.h>
#include <queue>
#include "constants.h"
#include "Objects.h"
#include "AuxilaryClasses.h"

std::vector<Tour> tours;
std::vector<City> cities;
std::vector<Tour> auxtours;

int randomCoordinates(char identifier)
{
	int output;

	if (identifier == 'X') output = 510 + (rand() % static_cast<int>(width-10 - 510 + 1));
	else output = 10 + (rand() % static_cast<int>(height - 20 + 1));

	return output;

}
void initializeElements()
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


	AdjacencyRepresentationText.setFont(font);
	AdjacencyRepresentationText.setString("Adjacency repres.");
	AdjacencyRepresentationText.setCharacterSize(18);
	AdjacencyRepresentationText.setFillColor(sf::Color::Black);
	AdjacencyRepresentationText.setPosition(250, 390 + VerticalOffset);



	AdjacencyRepresentation.setFont(font);
	AdjacencyRepresentation.setCharacterSize(18);
	AdjacencyRepresentation.setFillColor(sf::Color::Black);
	AdjacencyRepresentation.setPosition(250, 410);

	CityListText.setFont(font);
	CityListText.setString("City list");
	CityListText.setCharacterSize(18);
	CityListText.setFillColor(sf::Color::Black);
	CityListText.setPosition(250, 340 + VerticalOffset);

	CityList.setFont(font);
	CityList.setCharacterSize(18);
	CityList.setFillColor(sf::Color::Black);
	CityList.setPosition(250, 360);


	bestRoutesNumber.setFont(font);
	bestRoutesNumber.setCharacterSize(18);
	bestRoutesNumber.setFillColor(sf::Color::Black);


	CycleCounterText.setFont(font);
	CycleCounterText.setCharacterSize(18);
	CycleCounterText.setFillColor(sf::Color::Black);
	CycleCounterText.setPosition(300, 260);


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
	








	// TEXTS. MODIFY POSITIONS BY VerticalOffset



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





}


void initializeDots() {


	for (int i = 0; i < dotcount; i++)
	{
		float xcoord = randomCoordinates('X');
		float ycoord = randomCoordinates('Y');
		cities.push_back(City(i,xcoord,ycoord));
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



//Cities on siis nykyiset pisteet
//cintour on tourin member
void randomizeDots()
{
	cities.resize(dotcount, City(0, 0, 0));
	for (int i = 0; i <= dotcount - 1; i++)
	{
		popsize = 0;
		cities[i].x  = randomCoordinates('X');
		cities[i].y = randomCoordinates('Y');
		cities[i].id = i;
		bestdist = 100000;
	}

}



Tour randomizeRoute(Tour currenttour)
{
	std::vector<City> a = currenttour.cintour;
	std::random_shuffle(a.begin() + 1, a.end());
	tours.push_back(a);
	return a;

}



void sortTours() {
	std::sort(tours.begin(), tours.end());
}

/*
Tour optimizeSubtour(Tour auxtour)
{
	Tour bestTour = auxtour;
	float currentFitness = 10000000;
	do {
		if (currentFitness > bestTour.dist) {
			currentFitness = bestTour.dist;
		}
	} while (std::next_permutation(bestTour.cintour.begin(), bestTour.cintour.end()));

	return bestTour;
}
*/

/*
void KLHeuristic(int splits = 3) 
{
	int split1 = 1;
	int split2 = 5;
	int split3 = 10;
	int split4 = 14;
	

}
*/

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
		return true;
	}
	return false;

}

int main()
{




	// create the window
	sf::RenderWindow window(sf::VideoMode(width, height), "Genetic TSP GUI - Current pointcount: "+ std::to_string(dotcount));

	// init text
	font.loadFromFile("arial.ttf");

	initializeElements();
	initializeShapes();
	initializeDots();
	
	


	Tour currentTour = Tour(cities);
	// run the program as long as the window is open
	while (window.isOpen() && !exitStatus)
	{
		window.setTitle("Genetic TSP GUI - Current pointcount: " + std::to_string(dotcount));

		float presentDistance = currentTour.dist;
		popsize = tours.size();

		sortTours();
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			// mouseclick
			if (event.type == sf::Event::MouseButtonPressed) {




				if (buttonPressed(printBestRoutesButton, event))
				{
					printBestRoutesButton.setFillColor(sf::Color::Green);
					printBestRoutes();
					
					}

				if (buttonPressed(cycleButton, event))
				{
					cycleButton.setFillColor(sf::Color::Green);
					currentTour = tours[cycleCounter];
					cycleCounter += 1;

				}



					if (buttonPressed(generateButton,event))
					{

						generateButton.setFillColor(sf::Color::Green);
						tours.clear();
						randomizeDots();
						cycleCounter = 1;
						tours.push_back(cities);
						currentTour = Tour(cities);
						presentDistance = 100;
					}




					if (buttonPressed(exitButton,event))
					{
						return 0;
						window.close();
						
					}


					if (buttonPressed(randomizebutton,event))
					{


						randomizebutton.setFillColor(sf::Color::Green);
						if (RandomizeStatus)
						{
							RandomizeStatus = false;
							randomizebutton.setFillColor(sf::Color::Red);
						}
						else RandomizeStatus = true;

					}

					if (buttonPressed(randomizeOnceButton,event))
					{
						randomizeOnceButton.setFillColor(sf::Color::Green);
						currentTour = randomizeRoute(currentTour);

					}


					if (buttonPressed(showBestRouteButton,event))
					{
						showBestRouteButton.setFillColor(sf::Color::Green);
						currentTour = tours[0];
					}

					if (buttonPressed(changeDotcountButton,event))
					{
						std::cout << "Set amount of points" << std::endl;
						std::cin >> dotcount;
						tours.clear();
						cities.clear();
						randomizeDots();
						tours.push_back(cities);
						currentTour = Tour(cities);

						std::cout << "alkapakka" << std::endl;

					}

					if (buttonPressed(changeRandomizerRateButton, event))
					{
						std::cout << "Set randomizer rate" << std::endl;
						std::cin >> randomizeSleep;

					}




					if (buttonGridHorizontal2 < event.mouseButton.x &&  event.mouseButton.x < buttonGridHorizontal2 + buttonwidth && buttonGridVertical3 + VerticalOffset < event.mouseButton.y && event.mouseButton.y < buttonGridVertical3 + buttonheight + VerticalOffset)
					{
						window.close();
						return 0;
					}

				}


				if (event.type == sf::Event::MouseButtonReleased) {

					generateButton.setFillColor(sf::Color::Red);
					randomizeOnceButton.setFillColor(sf::Color::Red);
					showBestRouteButton.setFillColor(sf::Color::Red);
					printBestRoutesButton.setFillColor(sf::Color::Red);
					cycleButton.setFillColor(sf::Color::Red);

				}




			}



			// change shapes or objects if �nteractive



			// clear the window with color
			window.clear(windowColor);


			// draw everything here...

			//Draw dots here
			for (int a = 0; a < dotcount; a++)
			{
				testicircle.setPosition(currentTour.cintour[a].x,currentTour.cintour[a].y);
				window.draw(testicircle);

			}

			//Draw lines here
			for (int a = 0; a < dotcount - 1; a++)
			{

				window.draw(sfLine(sf::Vector2f(currentTour.cintour[a].x + 4, currentTour.cintour[a].y + 4), sf::Vector2f(currentTour.cintour[a + 1].x + 4, currentTour.cintour[a + 1].y + 4)));


			}
			window.draw(sfLine(sf::Vector2f(currentTour.cintour[dotcount - 1].x + 4, currentTour.cintour[dotcount - 1].y + 4), sf::Vector2f(currentTour.cintour[0].x + 4, currentTour.cintour[0].y + 4)));


			//Draw gridlines here
			for (int a = 0; a < size(gridlinesVertical); a++)
			{

				window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical[a] + 50), sf::Vector2f(gridlinesHorizontal[2], gridlinesVertical[a] + 50)));


			};

			window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical[0] + 50), sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical.back()-10  )));
			window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[1], gridlinesVertical[0] + 50), sf::Vector2f(gridlinesHorizontal[1], gridlinesVertical.back()-10  )));
			window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[2], gridlinesVertical[0] + 50), sf::Vector2f(gridlinesHorizontal[2], gridlinesVertical.back()-10  )));


			if (popsize>8 && popsize % 70 ==1) {printBestRoutes();}

			startcircle.setPosition(cities[0].x - 4, cities[0].y - 4);
			window.draw(startcircle);

			window.draw(reunat);
			window.draw(TSPText);
			window.draw(NameYearText);
			window.draw(SchoolNameText);

			window.draw(generateButton);
			window.draw(randomizebutton);
			window.draw(randomizeOnceButton);
			window.draw(RunSimulationButtonText);
			window.draw(RandomizeRoutesText);
			window.draw(randomizeRoutesOnceText);
			window.draw(printBestRoutesButton);
			window.draw(randomizerRateText);
			randomizerSpeedNumberText.setString(std::to_string(randomizeSleep));
			window.draw(randomizerSpeedNumberText);


			window.draw(changeRandomizerRateButton);
			window.draw(changeRandomizerRateButtonText);

			window.draw(exitButton);
			window.draw(exitButtonText);


			window.draw(CurrentBestSolutionsText);
			window.draw(printBestRoutesButtonText);

			//CycleCounterText.setString(std::to_string(cycleCounter));
			CycleCounterText.setString("Cycles:"+std::to_string(cycleCounter)+"/"+std::to_string(popsize));
			window.draw(CycleCounterText);


			window.draw(cycleButton);
			window.draw(cycleButtonText);


			window.draw(bestRoutes1);
			window.draw(bestRoutes2);
			window.draw(bestRoutes3);
			window.draw(bestRoutes4);
			window.draw(bestRoutes5);
			window.draw(bestRoutes6);
			window.draw(bestRoutes7);
			window.draw(bestRoutes8);



			window.draw(changeDotcountButton);
			window.draw(changeDotcountText);


			window.draw(showBestRouteButton);
			window.draw(showBestRouteText);
			currentDist = currentTour.dist;
			CurrentDistanceText.setString(std::to_string(presentDistance));
			window.draw(CurrentDistanceText);


			window.draw(AdjacencyRepresentationText);
			AdjacencyRepresentation.setString("1231243");
			window.draw(AdjacencyRepresentation);



			std::string citys = "";
			for (int r = 0; r <= dotcount - 1; r++)
			{
				citys += std::to_string(currentTour.cintour[r].id);
				citys += "-";
			}
			citys += "0";


			window.draw(CityListText);
			CityList.setString(citys);
			window.draw(CityList);


			if (currentDist < bestdist) bestdist = currentDist;
			CurrentBestNumberText.setString(std::to_string(bestdist));
			window.draw(CurrentBestNumberText);

			window.draw(currentDistance);
			window.draw(CurrentBestText);

			window.draw(CurrentPopulationText);
			CurrentPopulationNumberText.setString(std::to_string(popsize));
			window.draw(CurrentPopulationNumberText);



			if (RandomizeStatus) {
				Sleep(randomizeSleep);
				currentTour = randomizeRoute(currentTour);
			}


			/*
			if (RouteDistances.size() > 0) {
				for (int a = 0; a < 3; a++)
				{
					bestRoutesNumber.setPosition(30, gridlinesVertical[a]);
					bestRoutesNumber.setString(std::to_string(RouteDistances[a]));
					window.draw(bestRoutesNumber);

				}
			}*/




			// end the current frame
			window.display();
		}

		return 0;
	}
