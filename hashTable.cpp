// Kacey Price
// krp9da
// Prelab 6
// hashTable.cpp

#include "hashTable.h"
#include <math.h>
#include <iostream>
using namespace std;


hashTable::hashTable(unsigned int tableSize){
  int primeSize = getNextPrime(tableSize * 5);
  //table = new list<string>[primeSize];
  table = new string[primeSize];
  for(int i = 0; i < primeSize; i++){
    table[i] = "";
  }
  size = primeSize;
}

hashTable::~hashTable(){
}

unsigned int hashTable::hash(string word, float prime){
  unsigned int key = 0;
  double counter = 0;
  for(char& letter : word){
    key += (unsigned int)letter * (unsigned int)pow(prime,counter);
    counter++;
  }
  return (unsigned int) (key % size);
} 

bool hashTable::insert(string word){
  unsigned int key = hash(word,619.0);
  unsigned int key2 = hash(word, 37.0);
  unsigned int original = key;
  if(table[key] == ""){
    table[key] = word;
  }else{
    unsigned int i = 1;
    while(table[key] != ""){
      key = (original + int(pow(i * 1.0, 2.0))) % size;
      i++;
    }
    table[key] = word;
  }
  return true;
  /*table[key].push_back(word);
    return true;*/
}

/*list<string> hashTable::lookup(int key){
  return table[key];
  }*/

string hashTable::searchWord(string word){
  unsigned int key = hash(word,619.0);
  unsigned int original = key;
  if(table[key] == word){
    return word;
  }else{
    unsigned int i = 1;
    while(table[key] != ""){
      key = (original + int(pow(i * 1.0, 3.0))) % size;
      i++;
      if(table[key] == word){
	  return word;
	}
    }
  }
    return "";
  /*list<string> listValues = lookup(hash(word));
  for (list<string>::const_iterator iterator = listValues.begin(); iterator != listValues.end(); ++iterator) {
    if(*iterator == word){
      return *iterator;
    }
  }
  return "";*/
}


// Prime number generation code
// written by Aaron Bloomfield, 2014
bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}
// Prime number generation code
// written by Aaron Bloomfield, 2014
int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}
