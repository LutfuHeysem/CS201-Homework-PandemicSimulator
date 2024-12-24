/*
 * MyQueue.cpp
 * Created by: Lütfü Heysem Kızıloğlu
 * Section: 002
 * Student ID: 22301926
 */

#include "MyQueue.h"
#include <stdexcept>

using namespace std;

MyQueue::MyQueue(){
    size = 0;
    cities = new int[size];
}

MyQueue::MyQueue(const MyQueue& other) {
    size = other.size;
    cities = new int[size];
    for (int i = 0; i < size; ++i) {
        cities[i] = other.cities[i];
    }
}

MyQueue& MyQueue::operator=(const MyQueue& other) {
    if (this != &other) {
        delete[] cities;
        size = other.size;
        cities = new int[size];
        for (int i = 0; i < size; ++i) {
            cities[i] = other.cities[i];
        }
    }
    return *this;
}

MyQueue::MyQueue(int capacity){
    size = capacity;
    cities = nullptr;
}

MyQueue::~MyQueue(){
    delete[] cities;
}

void MyQueue::enqueue(int value){
    int* newCities = new int[size + 1];
    for (int i = 0; i < size; ++i) {
        newCities[i] = cities[i];
    }
    newCities[size] = value;
    delete[] cities;
    cities = newCities;
    ++size;
}

int MyQueue::dequeue(){
    if (size == 0) {
        throw out_of_range("Queue is empty");
    }
    int frontValue = cities[0];
    int* newCities = new int[size - 1];
    for (int i = 1; i < size; ++i) {
        newCities[i - 1] = cities[i];
    }
    delete[] cities;
    cities = newCities;
    --size;
    return frontValue;
}

bool MyQueue::isEmpty() const{
    return size == 0;
}
