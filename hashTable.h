// Kacey Price
// krp9da
// Prelab 6
// hashTable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <string>
using namespace std;


class hashTable {
public:
    hashTable(unsigned int size);	// Constructor
    ~hashTable();			// Destructor
    unsigned int hash(string word, float prime);              // Hash Function
    bool insert(string word);
    list<string> lookup(int key);
    string searchWord(string word);
    
private:
    //list<string>* table;
    string* table;
    int size;
};

// Prime number generation code prototypes
// written by Aaron Bloomfield, 2014
bool checkprime(unsigned int p);
int getNextPrime(unsigned int n);

#endif

