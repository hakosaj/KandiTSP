#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits.h>
#include "Constants.h"

float width = 1200;
float height = 700;
float outlinet = 6;
float leftEdge = 500;
float circlesize = 4;
float buttonwidth = 120;
float buttonheight = 40;
float startcirclesize = 8;
int generationSize = 20;
int initialPopulation = 50;
int currentgen = 0;

double mutationRate = 0.2;
int dotcount = 16;
float currentDist = INT_MAX;
float bestdist = INT_MAX;
int randomizeSleep = 10;
int popsize = 0;
bool Finished = true;
bool RandomizeStatus = false;
bool exitStatus = false;
bool drawState = false;
int cycleCounter = 1;


int VerticalOffset = -5;
int HorizontalOffset = 0;




int buttonGridVertical1 = 90;
int buttonGridVertical2 = 150;
int buttonGridVertical3 = 210;
int buttonGridVertical4 = 270;
int buttonGridVertical5 = 330;
int buttonGridHorizontal1 = 20;
int buttonGridHorizontal2 = 160;
int buttonGridHorizontal3 = 300;
int textButtonOffset = 11;


#endif