
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "AuxilaryClasses.h"

void initializeTexts();
void initializeButtonTexts();
void initializeDots();
void initializeShapes();
int randomCoordinates(char identifier);
Tour randomizeRoute(Tour currenttour);
void randomizeDots();

void printVector(std::vector<int> path);
void sortTours();
bool cmp(City a, City b);
void getParentTours(int gensize);
void swapMutate(float mutationrate);
void mutate(std::string identifier, float mutationrate);
void orderCrossover(std::vector<std::pair<int, int>> parentPairs);
void crossover(std::string identifier, std::vector<std::pair<int, int>> parentPairs);
std::vector<std::pair<int, int>> getParentPairs(int gensize);
void nextGeneration(int gensize, float mutationrate);
void printBestRoutes();
bool buttonPressed(sf::RectangleShape rect, sf::Event event);
#endif 