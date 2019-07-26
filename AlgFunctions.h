#ifndef AFUNCTIONS_H
#define AFUNCTIONS_H

#include "AuxilaryClasses.h"

//Functions for selection methods 
void rankedSelection(int gensize);

//Functions for crossovers
std::vector<std::pair<City, std::vector<City>>> removeFromAdjacencyUnions(City N, std::vector<std::pair<City, std::vector<City>>> adjacencyUnions);
void edgeRecombinationCrossover(std::vector<std::pair<int, int>> parentPairs);
std::vector<std::tuple<City, City, City>> generateAdjacencyMatrix(Tour tour);
void orderCrossover(std::vector<std::pair<int, int>> parentPairs);
void crossover(std::string identifier, std::vector<std::pair<int, int>> parentPairs);
std::vector<std::pair<int, int>> getParentPairs(int gensize);


//Functions for mutates
std::tuple<double, Tour> reverse_segment_if_better(Tour tour, int i, int j, int k);
std::vector<std::tuple<int, int, int>> all_segments(int N);
void threeOptMutate();
Tour threeOpt(Tour currentTour);
void twoOptMutate();
Tour twoOpt(Tour currentTour);
void swapMutate(float mutationrate);
void mutate(std::string identifier, float mutationrate);


#endif 