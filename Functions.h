
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "AuxilaryClasses.h"

bool operator== (const City &c1, const City &c2);
bool operator!= (const City &c1, const City &c2);
void runAlgorithm(Tour currenttour);
void initializeTexts();
void initializeButtonTexts();
void initializeDots();
void initializeDotsCircle();
void initializeDotsStar();
std::vector<std::pair<City, std::vector<City>>> removeFromAdjacencyUnions(City N, std::vector<std::pair<City, std::vector<City>>> adjacencyUnions);
void initializeShapes();
float euclideanDistance(float x1, float x2, float y1, float y2);
float distanceTwoCities(City c1, City c2);
float distance(std::vector<City> cits);
int randomCoordinates(char identifier);
Tour randomizeRoute(Tour currenttour);
void randomizeDots();
void edgeRecombinationCrossover(std::vector<std::pair<int, int>> parentPairs);
std::vector<std::tuple<City, City, City>> generateAdjacencyMatrix(Tour tour);
void printVector(std::vector<int> path);
void printVector(std::vector<City> path);
void sortTours();
bool cmp(City a, City b);
void rankedSelection(int gensize);
double reverse_segment_if_better(Tour tour, int i, int j, int k);
std::vector<std::tuple<int, int, int>> all_segments(int N);
void threeOptMutate();
Tour threeOpt(Tour currentTour);
void twoOptMutate();
Tour twoOpt(Tour currentTour);
void swapMutate(float mutationrate);
void mutate(std::string identifier, float mutationrate);
void orderCrossover(std::vector<std::pair<int, int>> parentPairs);
void crossover(std::string identifier, std::vector<std::pair<int, int>> parentPairs);
std::vector<std::pair<int, int>> getParentPairs(int gensize);
void nextGeneration(int gensize, float mutationrate);
void printBestRoutes();
bool buttonPressed(sf::RectangleShape rect, sf::Event event);
#endif 