/*
 * PandemicSimulator.h
 * Created by: Lütfü Heysem Kızıloğlu
 * Section: 002
 * Student ID: 22301926
 */

#ifndef PANDEMICSIMULATOR_H
#define PANDEMICSIMULATOR_H

#include <string>
#include "MyQueue.h"

using namespace std;

class PandemicSimulator {
private:
    int m;
    int n;
    int** cityAdj;
    int* numberOfAdj;
    int* cityState;
    int* timeOfInfection;
    string city;

public:
    PandemicSimulator(string cityGridFile);
    ~PandemicSimulator();
    
    void displayCityState(const int time);
    void simulateBlock(const int row, const int col);
    void simulatePandemic();
};;

#endif