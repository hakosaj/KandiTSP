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
#include "constants.h"
#include "Objects.h"
#include "AuxilaryClasses.h"




int randomCoordinates(char identifier)
{
	int output;

	if (identifier == 'X') output = 510 + (rand() % static_cast<int>(1490 - 510 + 1));
	else output = 10 + (rand() % static_cast<int>(830 - 20 + 1));
	
	return output;

}



float euclideanDistance(float x1, float x2, float y1, float y2)
{
	float dist = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
	return dist;
}


float tourDistance(std::vector <float> dotsX, std::vector <float> dotsY)
{
	float currentDist = 0;



	for (int i = 0; i < dotcount - 1; i++)
	{
		currentDist += euclideanDistance(dotsX[i], dotsX[i + 1], dotsY[i], dotsY[i + 1]);
	}
	currentDist += euclideanDistance(dotsX[0], dotsX[dotcount - 1], dotsY[0], dotsY[dotcount - 1]);


	return currentDist;
}

std::tuple<std::vector <float>, std::vector <float>> findBestRoute(std::vector <std::tuple<std::vector <float>, std::vector <float>>>)
{
	float routedistance = 1000000000;
	int bestIndex = 0;
	for (int a = 0; a < size(routes); a++)
	{
		auto vectors = routes[a];
		std::vector<float> XVector = std::get<0>(vectors);
		std::vector<float> YVector = std::get<1>(vectors);
		if (tourDistance(XVector, YVector) < routedistance)
		{
			routedistance = tourDistance(XVector, YVector);
			bestIndex = a;

		}
		
		
		
	}
	routedistance = 100000000;
	return routes[bestIndex];


}



void getBestRoutes(std::vector <std::tuple<std::vector <float>, std::vector <float>>>)
	{
	int spotcounter = 10;
	int routesDistanceIndex = 0;
	float currentSpotDistance = 100000000;
	
	

	for (int a = 0; a < routes.size(); a++)
		{
		auto vectors = routes[a];
		std::vector<float> XVector = std::get<0>(vectors);
		std::vector<float> YVector = std::get<1>(vectors);

		RouteDistances.push_back(tourDistance(XVector, YVector));
		}
	std::sort(RouteDistances.begin(),RouteDistances.end());



	}


std::tuple<std::vector <float>, std::vector <float>> randomize(std::vector <float> dotsX, std::vector <float> dotsY)
{
	srand(time(NULL));
	for (int i = 0; i < dotcount - 1; i++)
	{
		int index1 = 0;
		int index2 = 0;
		while (index1 == index2)
		{
			index1 = 1 + (rand() % static_cast<int>(dotcount-1));
			index2 = 1 + (rand() % static_cast<int>(dotcount-1));
		}

			 std::iter_swap(dotsX.begin() + index1, dotsX.begin() + index2);
			 std::iter_swap(dotsY.begin() + index1, dotsY.begin() + index2);
	}
	popsize += 1;
	routes.push_back(std::make_tuple(dotsX, dotsY));
	return std::make_tuple(dotsX, dotsY);

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
	CurrentBestText.setString("Current best distance");
	CurrentBestText.setCharacterSize(18);
	CurrentBestText.setFillColor(sf::Color::Black);
	CurrentBestText.setPosition(10, 340 + VerticalOffset);


	currentDistance.setFont(font);
	currentDistance.setString("Current distance");
	currentDistance.setCharacterSize(18);
	currentDistance.setFillColor(sf::Color::Black);
	currentDistance.setPosition(10, 290 + VerticalOffset);

	randomizerRateText.setFont(font);
	randomizerRateText.setString("Current randomizer rate (ms/member)");
	randomizerRateText.setCharacterSize(18);
	randomizerRateText.setFillColor(sf::Color::Black);
	randomizerRateText.setPosition(10, 390 + VerticalOffset);

	randomizerSpeedNumberText.setFont(font);
	randomizerSpeedNumberText.setCharacterSize(20);
	randomizerSpeedNumberText.setFillColor(sf::Color::Red);
	randomizerSpeedNumberText.setPosition(10, 410 + VerticalOffset);

	CurrentPopulationText.setFont(font);
	CurrentPopulationText.setString("Current population size");
	CurrentPopulationText.setCharacterSize(18);
	CurrentPopulationText.setFillColor(sf::Color::Black);
	CurrentPopulationText.setPosition(10, 440 + VerticalOffset);

	CurrentPopulationNumberText.setFont(font);
	CurrentPopulationNumberText.setCharacterSize(20);
	CurrentPopulationNumberText.setFillColor(sf::Color::Red);
	CurrentPopulationNumberText.setPosition(10, 460 + VerticalOffset);


	CurrentBestSolutionsText.setFont(font);
	CurrentBestSolutionsText.setString("Current best solutions");
	CurrentBestSolutionsText.setCharacterSize(18);
	CurrentBestSolutionsText.setFillColor(sf::Color::Black);
	CurrentBestSolutionsText.setPosition(20, 500 + VerticalOffset);


	bestRoutesNumber.setFont(font);
	bestRoutesNumber.setCharacterSize(18);
	bestRoutesNumber.setFillColor(sf::Color::Black);








	//BUTTONS AND THEIR TEXTS. MODIFY POSITIONS BY VerticalOffset



	RunSimulationButtonText.setFont(font);
	RunSimulationButtonText.setString("Run simulation");
	RunSimulationButtonText.setCharacterSize(18);
	RunSimulationButtonText.setFillColor(sf::Color::Black);
	RunSimulationButtonText.setPosition(buttonGridHorizontal1 + 1, buttonGridVertical1 + textButtonOffset + VerticalOffset);

	RandomizeRoutesText.setFont(font);
	RandomizeRoutesText.setString("Randomize ");
	RandomizeRoutesText.setCharacterSize(18);
	RandomizeRoutesText.setFillColor(sf::Color::Black);
	RandomizeRoutesText.setPosition(buttonGridHorizontal1 + 1, buttonGridVertical2 + textButtonOffset + VerticalOffset);


	showBestRouteText.setFont(font);
	showBestRouteText.setString("Show best");
	showBestRouteText.setCharacterSize(18);
	showBestRouteText.setFillColor(sf::Color::Black);
	showBestRouteText.setPosition(161, 101 + VerticalOffset);

	randomizeRoutesOnceText.setFont(font);
	randomizeRoutesOnceText.setString("Once ");
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



}


void initializeShapesDots() {


	// set shape properties

	reunat.setFillColor(sf::Color::Transparent);
	reunat.setOutlineColor(sf::Color::Black);
	reunat.setPosition(leftEdge, outlinet);
	reunat.setOutlineThickness(outlinet);

	// set and calculate dots

	dots.reserve(dotcount);
	dots.resize(dotcount);
	dotsX.reserve(dotcount);
	dotsY.reserve(dotcount);

	for (int i = 0; i < dotcount; i++)
	{
		dotsX[i] = randomCoordinates('X');
		dotsY[i] = randomCoordinates('Y');
	}


	
		testicircle.setFillColor(windowColor);
		testicircle.setOutlineThickness(3);
		testicircle.setOutlineColor(sf::Color::Black);

		startcircle.setFillColor(windowColor);
		startcircle.setOutlineThickness(3);
		startcircle.setOutlineColor(sf::Color::Cyan);



		runbutton.setFillColor(sf::Color::Red);
		runbutton.setPosition(20, 90 + VerticalOffset);

		randomizebutton.setFillColor(sf::Color::Red);
		randomizebutton.setPosition(20, 150 + VerticalOffset);

		randomizeOnceButton.setFillColor(sf::Color::Red);
		randomizeOnceButton.setPosition(160, 150 + VerticalOffset);

		showBestRouteButton.setFillColor(sf::Color::Red);
		showBestRouteButton.setPosition(160, 90 + VerticalOffset);

		changeDotcountButton.setFillColor(sf::Color::Red);
		changeDotcountButton.setPosition(20, 210 + VerticalOffset);

		exitButton.setFillColor(sf::Color::Red);
		exitButton.setPosition(buttonGridHorizontal2, buttonGridVertical3 + VerticalOffset);



		int mousecharter = 0;


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
	sf::RenderWindow window(sf::VideoMode(width, height), "Hakosalo_Genetic_TSP");

	// init text
	font.loadFromFile("arial.ttf");

	initializeElements();
	initializeShapesDots();



	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			// mouseclick
			if (event.type == sf::Event::MouseButtonPressed) {



					if (buttonPressed(runbutton,event))
					{


						runbutton.setFillColor(sf::Color::Green);
						routes.clear();

						for (int i = 0; i < dotcount - 1; i++)
						{
							popsize = 0;
							dotsX[i] = randomCoordinates('X');
							dotsY[i] = randomCoordinates('Y');
							bestdist = 100000;
						}
						routes.push_back(std::make_tuple(dotsX, dotsY));


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
						auto vectors = randomize(dotsX, dotsY);
						dotsY = std::get<1>(vectors);
						dotsX = std::get<0>(vectors);

					}


					if (buttonPressed(showBestRouteButton,event))
					{


						showBestRouteButton.setFillColor(sf::Color::Green);
						auto vectors = findBestRoute(routes);
						dotsY = std::get<1>(vectors);
						dotsX = std::get<0>(vectors);

					}

					if (buttonPressed(changeDotcountButton,event))
					{
						std::cout << "Set amount of points" << std::endl;
						std::cin >> dotcount;
						dots.clear();
						dotsX.clear();
						dotsY.clear();
						dots.reserve(dotcount);
						dots.resize(dotcount);
						dotsX.resize(dotcount);
						dotsY.resize(dotcount);
						routes.clear();
						for (int i = 0; i < dotcount; i++)
						{
							popsize = 0;
							dotsX[i] = randomCoordinates('X');
							dotsY[i] = randomCoordinates('Y');
							bestdist = 10000000;
						}
						routes.push_back(std::make_tuple(dotsX, dotsY));



					}




					if (buttonGridHorizontal2 < event.mouseButton.x &&  event.mouseButton.x < buttonGridHorizontal2 + buttonwidth && buttonGridVertical3 + VerticalOffset < event.mouseButton.y && event.mouseButton.y < buttonGridVertical3 + buttonheight + VerticalOffset)
					{
						window.close();
						return 0;
					}

				}


				if (event.type == sf::Event::MouseButtonReleased) {

					runbutton.setFillColor(sf::Color::Red);
					randomizeOnceButton.setFillColor(sf::Color::Red);
					showBestRouteButton.setFillColor(sf::Color::Red);

				}




			}



			// change shapes or objects if �nteractive



			RouteDistances.resize(routes.size());
			// clear the window with color
			window.clear(windowColor);


			// draw everything here...


			for (int a = 0; a < dotcount; a++)
			{

				testicircle.setPosition(dotsX[a], dotsY[a]);
				window.draw(testicircle);


			}


			for (int a = 0; a < dotcount - 1; a++)
			{

				window.draw(sfLine(sf::Vector2f(dotsX[a] + 4, dotsY[a] + 4), sf::Vector2f(dotsX[a + 1] + 4, dotsY[a + 1] + 4)));


			}
			window.draw(sfLine(sf::Vector2f(dotsX[dotcount - 1] + 4, dotsY[dotcount - 1] + 4), sf::Vector2f(dotsX[0] + 4, dotsY[0] + 4)));



			for (int a = 0; a < size(gridlinesVertical); a++)
			{

				window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical[a] + 50), sf::Vector2f(gridlinesHorizontal[1], gridlinesVertical[a] + 50)));


			};

			window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical[0] + 50), sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical.back() + 50)));
			window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[1], gridlinesVertical[0] + 50), sf::Vector2f(gridlinesHorizontal[1], gridlinesVertical.back() + 50)));


			/*getBestRoutes(routes);*/

			startcircle.setPosition(dotsX[0] - 4, dotsY[0] - 4);
			window.draw(startcircle);

			window.draw(reunat);
			window.draw(TSPText);
			window.draw(NameYearText);
			window.draw(SchoolNameText);

			window.draw(runbutton);
			window.draw(randomizebutton);
			window.draw(randomizeOnceButton);
			window.draw(RunSimulationButtonText);
			window.draw(RandomizeRoutesText);
			window.draw(randomizeRoutesOnceText);
			window.draw(randomizerRateText);
			randomizerSpeedNumberText.setString(std::to_string(randomizeSleep));
			window.draw(randomizerSpeedNumberText);

			window.draw(exitButton);
			window.draw(exitButtonText);


			window.draw(CurrentBestSolutionsText);



			window.draw(changeDotcountButton);
			window.draw(changeDotcountText);


			window.draw(showBestRouteButton);
			window.draw(showBestRouteText);
			currentDist = tourDistance(dotsX, dotsY);
			CurrentDistanceText.setString(std::to_string(currentDist));
			window.draw(CurrentDistanceText);


			;


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
				auto vectors = randomize(dotsX, dotsY);
				dotsY = std::get<1>(vectors);
				dotsX = std::get<0>(vectors);
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
