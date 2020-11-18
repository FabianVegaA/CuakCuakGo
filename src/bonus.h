#ifndef KNAPSACK_H
#define KNAPSACK_H
#define SIZE 20


typedef struct
{
    int data;
    int key;
} DataItem;

DataItem *hashArray[SIZE];
DataItem *dummyItem;
DataItem *item;

int hashCode(int key);

DataItem *search(int key);

void insert(int key, int data);

void display();



#endif