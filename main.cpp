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
#include "AuxilaryClasses.h"
#include "Functions.h"
#include "Objects.h"
#include "Constants.h"


int main()
{

	srand(time(NULL));
	std::cout << "Welcome to JH TSP simulation. Would you like to read a csv-file? (y/n)" << std::endl;

	std::string filePrompt;
	std::cin >> filePrompt;



	if (filePrompt != "y") {
		std::cout << " Randomized(r), convex(c) or nonconvex(n) vertex set? " << std::endl;
		std::string vertexSetType;
		std::cin >> vertexSetType;
		std::cout << "How many dots" << std::endl;
		std::cin >> dotcount;

		if (vertexSetType == "r") { initializeDots(); }
		if (vertexSetType == "c") { initializeDotsCircle(); }
		if (vertexSetType == "n") { initializeDotsStar(); }
	}
	
	if (filePrompt == "y") {
		auto fields = readCsv();
		dotcount = fields.size();
	}

	// create the window
	sf::RenderWindow window(sf::VideoMode(width, height), "Genetic TSP GUI - Current pointcount: " + std::to_string(dotcount));

	// init text
	font.loadFromFile("arial.ttf");

	initializeTexts();
	initializeShapes();
	initializeButtonTexts();



	Tour currentTour = Tour(cities);
	// run the program as long as the window is open
	while (window.isOpen() && !exitStatus)
	{
		window.setTitle("Genetic TSP GUI - Current pointcount: " + std::to_string(dotcount));

		float presentDistance = currentTour.dist;
		popsize = tours.size();

		//sortTours(tours);
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			// mouseclick
			if (event.type == sf::Event::MouseButtonPressed) {


				if (buttonPressed(twoOptButton, event))
				{
					runAlgorithm(currentTour);
					currentTour = tours[0];
					std::cout << "This dist:" << distance(tours[0].cintour) << std::endl;
					printVector(tours[0].cintour);
					currentDist = currentTour.dist;
					
					

				}


				if (buttonPressed(SubtourOptButton, event))
				{
					nextGeneration(generationSize, mutationRate);

				}

				if (buttonPressed(printBestRoutesButton, event))
				{
					printBestRoutesButton.setFillColor(sf::Color::Green);
					printBestRoutes();

				}

				if (buttonPressed(cycleButton, event))
				{
					if (cycleCounter == tours.size()) { cycleCounter = 0; }
					cycleButton.setFillColor(sf::Color::Green);
					currentTour = tours[cycleCounter];
					cycleCounter += 1;

				}



				if (buttonPressed(generateButton, event))
				{

					generateButton.setFillColor(sf::Color::Green);
					tours.clear();
					randomizeDots();
					cycleCounter = 1;
					tours.push_back(cities);
					currentTour = Tour(cities);
					presentDistance = 100;
					currentDist = currentTour.dist;
				}




				if (buttonPressed(exitButton, event))
				{
					initializeDotsCircle();

				}


				if (buttonPressed(randomizebutton, event))
				{


					randomizebutton.setFillColor(sf::Color::Green);
					if (RandomizeStatus)
					{
						RandomizeStatus = false;
						randomizebutton.setFillColor(sf::Color::Red);
					}
					else RandomizeStatus = true;

				}

				if (buttonPressed(randomizeOnceButton, event))
				{
					randomizeOnceButton.setFillColor(sf::Color::Green);
					currentTour = randomizeRoute(currentTour);

				}


				if (buttonPressed(showBestRouteButton, event))
				{
					showBestRouteButton.setFillColor(sf::Color::Green);
					currentTour = tours[0];
				}

				if (buttonPressed(changeDotcountButton, event))
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
				SubtourOptButton.setFillColor(sf::Color::Red);
				twoOptButton.setFillColor(sf::Color::Red);

			}




		}



		// change shapes or objects if �nteractive



		// clear the window with color
		window.clear(windowColor);

		if (currentDist < bestdist) bestdist = currentDist;
		currentDist = distance(currentTour.cintour);
		sortTours(tours);



		// Draw everything here

		//Draw dots 
		for (int a = 0; a < currentTour.size(); a++)
		{
			testicircle.setPosition(currentTour.cintour[a].x, currentTour.cintour[a].y);
			window.draw(testicircle);
		}
		startcircle.setPosition(currentTour.cintour[0].x - 4, currentTour.cintour[0].y - 4);
		window.draw(startcircle);

		//Draw lines here
		for (int a = 0; a < currentTour.size() - 1; a++)
		{

			window.draw(sfLine(sf::Vector2f(currentTour.cintour[a].x + 4, currentTour.cintour[a].y + 4), sf::Vector2f(currentTour.cintour[a + 1].x + 4, currentTour.cintour[a + 1].y + 4)));


		}
		window.draw(sfLine(sf::Vector2f(currentTour.cintour[currentTour.size() - 1].x + 4, currentTour.cintour[currentTour.size() - 1].y + 4), sf::Vector2f(currentTour.cintour[0].x + 4, currentTour.cintour[0].y + 4)));


		//asdsad
		//Draw gridlines here
		for (int a = 0; a < size(gridlinesVertical); a++)
		{

			window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical[a] + 50), sf::Vector2f(gridlinesHorizontal[2], gridlinesVertical[a] + 50)));


		};
		window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical[0] + 50), sf::Vector2f(gridlinesHorizontal[0], gridlinesVertical.back() - 10)));
		window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[1], gridlinesVertical[0] + 50), sf::Vector2f(gridlinesHorizontal[1], gridlinesVertical.back() - 10)));
		window.draw(sfLine(sf::Vector2f(gridlinesHorizontal[2], gridlinesVertical[0] + 50), sf::Vector2f(gridlinesHorizontal[2], gridlinesVertical.back() - 10)));


		//Draw static text, borders
		window.draw(reunat);
		window.draw(TSPText);
		window.draw(NameYearText);
		window.draw(SchoolNameText);

		//Draw buttons
		window.draw(generateButton);
		window.draw(randomizebutton);
		window.draw(randomizeOnceButton);
		window.draw(printBestRoutesButton);
		window.draw(changeRandomizerRateButton);
		window.draw(exitButton);
		window.draw(cycleButton);
		window.draw(SubtourOptButton);
		window.draw(changeDotcountButton);
		window.draw(showBestRouteButton);
		window.draw(twoOptButton);


		//Draw button texts
		window.draw(RunSimulationButtonText);
		window.draw(RandomizeRoutesText);
		window.draw(randomizeRoutesOnceText);
		window.draw(changeRandomizerRateButtonText);
		window.draw(SubtourOptButtonText);
		window.draw(changeDotcountText);
		window.draw(exitButtonText);
		window.draw(CurrentBestSolutionsText);
		window.draw(printBestRoutesButtonText);
		window.draw(cycleButtonText);
		window.draw(showBestRouteText);
		window.draw(twoOptButtonText);

		//Draw texts for various value labels;
		CurrentDistanceText.setString(std::to_string(currentDist));
		window.draw(CurrentDistanceText);
		randomizerSpeedNumberText.setString(std::to_string(randomizeSleep));
		CycleCounterText.setString("Cycles:" + std::to_string(cycleCounter) + "/" + std::to_string(popsize));
		window.draw(randomizerRateText);
		window.draw(randomizerSpeedNumberText);
		window.draw(CycleCounterText);
		CurrentBestNumberText.setString(std::to_string(bestdist));
		window.draw(CurrentBestNumberText);
		window.draw(currentDistance);
		window.draw(CurrentBestText);
		window.draw(CurrentPopulationText);

		//Draw best courses
		window.draw(bestRoutes1);
		window.draw(bestRoutes2);
		window.draw(bestRoutes3);
		window.draw(bestRoutes4);
		window.draw(bestRoutes5);
		window.draw(bestRoutes6);
		window.draw(bestRoutes7);
		window.draw(bestRoutes8);



		//Draw the city list
		std::string citys = "";
		citys += std::to_string(currentTour.cintour[0].id);
		for (int r = 1; r <= currentTour.size() - 1; r++)
		{
			citys += "-";
			citys += std::to_string(currentTour.cintour[r].id);

		}
		window.draw(CityListText);
		CityList.setString(citys);
		window.draw(CityList);



		CurrentPopulationNumberText.setString(std::to_string(popsize));
		window.draw(CurrentPopulationNumberText);
		if (RandomizeStatus) {
			Sleep(randomizeSleep);
			currentTour = randomizeRoute(currentTour);
		}

		if (popsize>8 && popsize % 70 == 1) { printBestRoutes(); }
		window.display();
	}

	return 0;
}