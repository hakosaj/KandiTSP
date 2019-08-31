
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "AuxilaryClasses.h"

//Operators
bool operator== (const City &c1, const City &c2);
bool operator!= (const City &c1, const City &c2);

//Auxiliary general functions
void runAlgorithm(Tour currenttour, int gens, std::string selecting, std::string crossovering, std::string mutating);
float euclideanDistance(float x1, float x2, float y1, float y2);
int randomCoordinates(char identifier);
void randomizeDots();
bool buttonPressed(sf::RectangleShape rect, sf::Event event);
void printBestRoutes(std::vector<Tour> tours);
void nextGeneration(int gensize, float mutationrate, std::string selecting, std::string crossovering, std::string mutating, int currentgen);

//Tour-specific functions
bool comp(Tour a, Tour b);
bool isSameRoute(Tour t1, Tour t2);
bool areLegitTours(std::vector<Tour> generation);
bool isLegitRoute(Tour tourette);
float distanceTwoCities(City c1, City c2);
float distance(std::vector<City> cits);
Tour randomizeRoute(Tour currenttour);
void printVector(std::vector<int> path);
void printVector(std::vector<City> path);
std::vector<Tour> sortTours(std::vector<Tour> tours);
bool cmp(City a, City b);


#endif 