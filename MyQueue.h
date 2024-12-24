/*
 * MyQueue.h
 * Created by: Lütfü Heysem Kızıloğlu
 * Section: 002
 * Student ID: 22301926
 */

#ifndef MYQUEUE_H
#define MYQUEUE_H

class MyQueue {
private:
    int* cities;
    int size; 

public:
    MyQueue();
    MyQueue(int capacity);
    MyQueue(const MyQueue& other);
    MyQueue& operator=(const MyQueue& other);
    ~MyQueue();

    void enqueue(int value);
    int dequeue();
    
    bool isEmpty() const;
};

#endif