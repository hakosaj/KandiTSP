
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
#include <numeric>
#include <queue>
#include <tuple>
#include <math.h>
#include "Constants.h"
#include "AuxilaryClasses.h"



extern std::vector<Tour> tours;
extern std::vector<City> cities;
extern std::vector<Tour> auxtours;
extern std::vector<Tour> newgen;


/*Uuden napin lis‰‰minen:
1) Lis‰‰ Objects.h Button Texts-kohtaan tekstiolio: MyFunctionButtonText
2) Lis‰‰ Objects.h Button shapes- kohtaan rectangle nimell‰ MyFunctionButton. sitten objects.cpp
3) Lis‰‰ mainiin InitializeButtonTexts-funktioon kohta, jossa teksti ja sijainti
4) InitializeShapesiin Button positions-kohtaan suorakulmion sijainti
5) Mainiin event listeneriin referenssi uuteen nappiin
6) Mainiin window.draw()-komento MyFunctionButton ja MyFunctionButtonText
*/

//Used fonts
extern sf::Font font;


//Used color definitions
extern sf::Color windowColor;

//Title texts
extern sf::Text TSPText;
extern sf::Text NameYearText;
extern sf::Text SchoolNameText;


//Button texts
extern sf::Text SubtourOptButtonText;
extern sf::Text RunSimulationButtonText;
extern sf::Text showBestRouteText;
extern sf::Text RandomizeRoutesText;
extern sf::Text randomizeRoutesOnceText;
extern sf::Text changeDotcountText;
extern sf::Text exitButtonText;
extern sf::Text printBestRoutesButtonText;
extern sf::Text changeRandomizerRateButtonText;
extern sf::Text cycleButtonText;
extern sf::Text twoOptButtonText;


//Titles for different values
extern sf::Text CurrentDistanceText;
extern sf::Text AdjacencyRepresentationText;
extern sf::Text CityListText;
extern sf::Text CurrentBestText;
extern sf::Text randomizerRateText;
extern sf::Text CurrentPopulationText;
extern sf::Text CycleCounterText;

//Value texts

extern sf::Text currentDistance;
extern sf::Text AdjacencyRepresentation;
extern sf::Text CityList;
extern sf::Text CurrentBestNumberText;
extern sf::Text randomizerSpeedNumberText;
extern sf::Text CurrentPopulationNumberText;


//More value texts: best 4 routes
extern sf::Text bestRoutes1;
extern sf::Text bestRoutes2;
extern sf::Text bestRoutes3;
extern sf::Text bestRoutes4;
extern sf::Text bestRoutes5;
extern sf::Text bestRoutes6;
extern sf::Text bestRoutes7;
extern sf::Text bestRoutes8;

//Other or testing
extern sf::Text CurrentBestSolutionsText;







extern sf::Text bestRoutesNumber;


//std::vector <std::tuple<std::vector <float>, std::vector <float>>> routes(0);
//std::vector <std::tuple<std::vector <float>, std::vector <float>>> bestRoutes(1);
//std::vector<float> RouteDistances(1);



//form for queue: distance,x,y
//form: id, x, y




extern std::vector <int> gridlinesHorizontal;
extern std::vector <int> gridlinesVertical;
extern sf::CircleShape testicircle;
extern sf::CircleShape startcircle;
extern sf::RectangleShape reunat;
extern std::pair<int, int> crossoverIndices;

extern std::vector<City> vertices;



//Button shapes here
extern sf::RectangleShape generateButton;
extern sf::RectangleShape randomizebutton;
extern sf::RectangleShape randomizeOnceButton;
extern sf::RectangleShape showBestRouteButton;
extern sf::RectangleShape printBestRoutesButton;
extern sf::RectangleShape changeDotcountButton;
extern sf::RectangleShape changeRandomizerRateButton;
extern sf::RectangleShape exitButton;
extern sf::RectangleShape cycleButton;
extern sf::RectangleShape SubtourOptButton;
extern sf::RectangleShape twoOptButton;

#endif