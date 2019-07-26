
#ifndef OBJECTS_H
#define OBJECTS_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <Windows.h> 
#include <string>
#include <queue>
#include <tuple>
#include <math.h>
#include "Constants.h"
#include "Objects.h"
#include "AuxilaryClasses.h"

std::vector<Tour> tours;
std::vector<City> cities;
std::vector<Tour> auxtours;
std::vector<Tour> newgen;


 sf::Font font;


//Used color definitions
 sf::Color windowColor(200, 200, 200);

//Title texts
 sf::Text TSPText;
 sf::Text NameYearText;
 sf::Text SchoolNameText;


//Button texts
 sf::Text RunSimulationButtonText;
 sf::Text showBestRouteText;
 sf::Text RandomizeRoutesText;
 sf::Text randomizeRoutesOnceText;
 sf::Text changeDotcountText;
 sf::Text exitButtonText;
 sf::Text printBestRoutesButtonText;
 sf::Text changeRandomizerRateButtonText;
 sf::Text cycleButtonText;
 sf::Text runAlgorithmButtonText;


//Titles for different values
 sf::Text CurrentDistanceText;
 sf::Text AdjacencyRepresentationText;
 sf::Text CityListText;
 sf::Text CurrentBestText;
 sf::Text randomizerRateText;
 sf::Text CurrentPopulationText;
 sf::Text CycleCounterText;

//Value texts

 sf::Text currentDistance;
 sf::Text AdjacencyRepresentation;
 sf::Text CityList;
 sf::Text CurrentBestNumberText;
 sf::Text randomizerSpeedNumberText;
 sf::Text CurrentPopulationNumberText;


//More value texts: best 4 routes
 sf::Text bestRoutes1;
 sf::Text bestRoutes2;
 sf::Text bestRoutes3;
 sf::Text bestRoutes4;
 sf::Text bestRoutes5;
 sf::Text bestRoutes6;
 sf::Text bestRoutes7;
 sf::Text bestRoutes8;

//Other or testing
 sf::Text CurrentBestSolutionsText;







 sf::Text bestRoutesNumber;

 std::vector <int> gridlinesHorizontal{ 20,200,380 };
 std::vector <int> gridlinesVertical{ 470,500,530,560,590,620,650 };
 sf::CircleShape testicircle(circlesize);
 sf::CircleShape startcircle(startcirclesize);
 sf::RectangleShape reunat(sf::Vector2f(width - leftEdge - outlinet, height - outlinet * 2));
 std::pair<int, int> crossoverIndices = std::make_pair(5, 10);

 std::vector<City> vertices;



//Button shapes here
 sf::RectangleShape generateButton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape randomizebutton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape randomizeOnceButton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape showBestRouteButton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape printBestRoutesButton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape changeDotcountButton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape changeRandomizerRateButton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape exitButton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape cycleButton(sf::Vector2f(buttonwidth, buttonheight));
 sf::RectangleShape runAlgorithmButton(sf::Vector2f(buttonwidth, buttonheight));

#endif