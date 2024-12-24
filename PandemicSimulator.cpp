/*
 * PandemicSimulator.cpp
 * Created by: Lütfü Heysem Kızıloğlu
 * Section: 002
 * Student ID: 22301926
 */

#include "PandemicSimulator.h"
#include "MyQueue.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

PandemicSimulator::PandemicSimulator(string cityGridFile) {
    
    bool firstLine = true;
    city = "";
    ifstream file(cityGridFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if(firstLine){
                firstLine = false;
                m = line[0] - '0';
                n = line[2] - '0';
                continue;
            }
            else{
                city += line;
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << cityGridFile << endl;
    }

    cityAdj = new int*[m*n];
    numberOfAdj = new int[m*n];
    timeOfInfection = new int[m*n];
    cityState = new int[m*n];

    for(int i=0; i<m*n; i++)
        timeOfInfection[i] = -1;

    for(int i=0; i<(int)city.length(); i++){
        if(city[i] == '0')
            cityState[i] = 0;
        else if(city[i] == '1')
            cityState[i] = 1;
        else
            cityState[i] = 2;

        bool topLeft = false, topRight = false, bottomLeft = false, bottomRight = false;
        bool leftEdge = false, topEdge = false, rightEdge = false, bottomEdge = false;
        bool rest = false; 

        if(i == 0)                             { topLeft        = true;     numberOfAdj[i] = 2; }
        else if(i == n-1)                      { topRight       = true;     numberOfAdj[i] = 2; }
        else if (i == n * (m - 1))             { bottomLeft     = true;     numberOfAdj[i] = 2; }
        else if (i == m * n - 1)               { bottomRight    = true;     numberOfAdj[i] = 2; }
        else if (i % n == 0)                   { leftEdge       = true;     numberOfAdj[i] = 3; }
        else if (i < n)                        { topEdge        = true;     numberOfAdj[i] = 3; }
        else if ((i + 1) % n == 0)             { rightEdge      = true;     numberOfAdj[i] = 3; }
        else if (i > n * (m - 1))              { bottomEdge     = true;     numberOfAdj[i] = 3; }
        else                                   { rest           = true;     numberOfAdj[i] = 4; }

        cityAdj[i] = new int[numberOfAdj[i]];
        if(topLeft){
            cityAdj[i][0] = i+1;
            cityAdj[i][1] = i+n;
        }
        else if(topRight){
            cityAdj[i][0] = i-1;
            cityAdj[i][1] = i+n;
        }
        else if(bottomLeft){
            cityAdj[i][0] = i+1;
            cityAdj[i][1] = i-n;
        }
        else if(bottomRight){
            cityAdj[i][0] = i-1;
            cityAdj[i][1] = i-n;
        }
        else if(leftEdge){
            cityAdj[i][0] = i+1;
            cityAdj[i][1] = i+n;
            cityAdj[i][2] = i-n;
        }
        else if(rightEdge){
            cityAdj[i][0] = i-1;
            cityAdj[i][1] = i+n;
            cityAdj[i][2] = i-n;
        }
        else if(topEdge){
            cityAdj[i][0] = i+1;
            cityAdj[i][1] = i-1;
            cityAdj[i][2] = i+n;
        }
        else if(bottomEdge){
            cityAdj[i][0] = i+1;
            cityAdj[i][1] = i-1;
            cityAdj[i][2] = i-n;
        }
        else if(rest){
            cityAdj[i][0] = i+1;
            cityAdj[i][1] = i-1;
            cityAdj[i][2] = i+n;
            cityAdj[i][3] = i-n;
        }
    }

    MyQueue* q = new MyQueue();
    for(int i=0; i<m*n; i++){
        if(cityState[i] == 2){
            q->enqueue(i);
            timeOfInfection[i] = 0;
        }
    }
    while(!q->isEmpty()){
        int city = q->dequeue();
        
        for(int i=0; i<numberOfAdj[city]; i++){
            if(cityState[cityAdj[city][i]] == 1){
                cityState[cityAdj[city][i]] = 2;

                if(timeOfInfection[cityAdj[city][i]] > 0) 
                    timeOfInfection[cityAdj[city][i]] = min(timeOfInfection[city] + 1, timeOfInfection[cityAdj[city][i]]);
                else
                    timeOfInfection[cityAdj[city][i]] = timeOfInfection[city] + 1;

                q->enqueue(cityAdj[city][i]);
            }
        }
    }
    delete q;
}

PandemicSimulator::~PandemicSimulator() {
    for(int i=0; i<m*n; i++){
        delete[] cityAdj[i];
    }
    delete[] cityAdj;
    delete[] numberOfAdj;
    delete[] cityState;
    delete[] timeOfInfection;
}

void PandemicSimulator::displayCityState(const int time){
    // cout << city << endl;

    cout << "City state at day " << time << ":" << endl;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int index = i * n + j;
            if (timeOfInfection[index] == -1 || timeOfInfection[index] > time) {
                cout << city[index];
            } else {
                cout << 2;
            }
        }
        cout << endl;
    }
}

void PandemicSimulator::simulateBlock(const int row, const int col){
    cout << "Time for block (" << row << ", " << col << ") to be infected: " << timeOfInfection[row*n + col] << " days." << endl;
}

void PandemicSimulator::simulatePandemic(){
    int maxTime = 0;
    bool isTheEntireCityInfected = true;

    for(int i=0; i<m*n; i++){
        if(timeOfInfection[i] == -1 && cityState[i] != 0)
            isTheEntireCityInfected = false;
        else
            maxTime = max(maxTime, timeOfInfection[i]);
    }

    if(isTheEntireCityInfected){
        cout << "Minimum time for pandemic to spread to all blocks: " << maxTime << " days." << endl;
    }
    else{
        cout << "Pandemic cannot spread to all blocks." << endl;
    }
}