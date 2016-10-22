// Kacey Price
// krp9da
// Prelab 6
// wordPuzzle.cpp

// Big theta (for large input (row/columns > 22)) ==> big-theta(num_rows * num_columns * num_words_in_dictionary)
// 300x300 grid with words2.txt dictionary ==>27409 words found Found all words in 23.0886 seconds
// 300x300 grid with words.txt dict ==>  2855 words found Found all words in 19.644 seconds


#include "hashTable.h"
#include "timer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <map>
using namespace std;

#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];

hashTable* dictionaryTable;
list<string> buffer;

int getMaxDiagnol(int rows, int cols);
bool readDictionary(string filename);
int hash(string word);
bool readInGrid (string filename, int &rows, int &cols);
char* getWordInGrid (int startRow, int startCol, int dir, int len, int numRows, int numCols);

int main(int argc, char* argv[]){
    readDictionary(argv[1]);
    int totalWordsFound = 0;
    int rows, cols;
    bool result = readInGrid (argv[2], rows, cols);
    if ( !result ) {
        cout << "Error reading in file!" << endl;
        exit(1); 
    }
    cout << endl;
    string dir = "";
    timer t;
    t.start();
    for ( int direction = 0; direction < 8; direction++ ){
      for( int startRow = 0; startRow < rows; startRow++){
	for( int startCol = 0 ; startCol < cols; startCol++){
	  int len;
	   switch (direction) { // assumes grid[0][0] is in the upper-left
            case 0:
                len = startRow + 1;
		if(len > 22){
		  len = 22;
		}
		dir = "N  ";
                break; // north
	    case 1:
	        len = getMaxDiagnol(cols - startCol, startRow+1);
	        if(len > 22){
		  len = 22;
	        }
	        dir = "NE";
                break; // north-east
            case 2:
	        len = cols - startCol;
	        if(len > 22){
		  len = 22;
		}
	        dir = "E  ";
                break; // east
            case 3:
	       len = getMaxDiagnol(cols - startCol, rows - startRow);
	       if(len > 22){
	         len = 22;
	       }
	       dir = "SE";
               break; // south-east
            case 4:
               len = rows - startRow;
	       if(len > 22){
	         len = 22;
	       }
	       dir = "S  ";
               break; // south
            case 5:
	      len = getMaxDiagnol(startCol+1, rows-startRow);
	      if(len > 22){
		len = 22;
	      }
	      dir = "SW";
              break; // south-west
            case 6:
              len = startCol+1;
	      if(len > 22){
	        len = 22;
	      }
	      dir = "W  ";
              break; // west
            case 7:
	      len = getMaxDiagnol(startCol+1, startRow+1);
	      if(len > 22){
		len = 22;
	      }
	      dir = "NW";
              break; // north-west
	  }
	  for(int i = len ; i >= 3; i--){
	    char* tempWord = getWordInGrid (startRow, startCol, direction, i, rows, cols);
	    string result = dictionaryTable->searchWord(tempWord);
	    if(result != ""){
	       stringstream streamRow;
	      streamRow << startRow;
	      string stringRow = streamRow.str();
	      stringstream streamCol;
	      streamCol << startCol;
	      string stringCol = streamCol.str();
	      buffer.push_back(dir + " (" + stringRow +  "," + stringCol + ")" + ":            " +  result);
	      totalWordsFound++;
	    }
          }
        }
      }	
    }
    t.stop();
     for (list<string>::const_iterator iterator = buffer.begin(); iterator != buffer.end(); ++iterator) {
    cout << *iterator << endl;
    }
    cout << totalWordsFound << " words found" << endl;
    cout << "Found all words in " << t.getTime() << " seconds" << endl;
    cout << int(t.getTime() * 1000)  << endl;
    return 0;
}

int getMaxDiagnol(int rows, int cols){
  int diagnolMax;
    if( rows > cols){
      diagnolMax = cols;
    }else{
      diagnolMax = rows;
    }
   return diagnolMax;
}

bool readDictionary(string filename){
  string line;
  int count = 0;
  ifstream file(filename.c_str());
  if( !file.is_open() ){
    return false;
  }
  while(getline(file, line)){
    count++;
  }
  file.close();
  dictionaryTable = new hashTable(count);
  ifstream file2(filename.c_str());
  while(getline(file2, line)){
    dictionaryTable->insert(line);
  }
  file.close();
  return true;
}


    

//From getWordInGrid.cpp provided
bool readInGrid (string filename, int &rows, int &cols) {
    // a C++ string to hold the line of data that is read in
    string line;
    // set up the file stream to read in the file (takes in a C-style
    // char* string, not a C++ string object)
    ifstream file(filename.c_str());
    // upon an error, return false
    if ( !file.is_open() )
        return false;
    // the first line is the number of rows: read it in
    file >> rows;
     cout << "There are " << rows << " rows." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the second line is the number of cols: read it in and parse it
    file >> cols;
    cout << "There are " << cols << " cols." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the third and last line is the data: read it in
    getline (file,line);
    // close the file
    file.close();
    // convert the string read in to the 2-D grid format into the
    // grid[][] array.  In the process, we'll print the grid to the
    // screen as well.
    int pos = 0; // the current position in the input data
    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            grid[r][c] = line[pos++];
	         cout << grid[r][c];
        }
	  cout << endl;
    }
    // return success!
    return true;
}

//From getWordInGrid.cpp
char* getWordInGrid (int startRow, int startCol, int dir, int len,
                    int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocataion.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static char output[256];
    // make sure the length is not greater than the array size.
    if ( len >= 255 )
        len = 255;
    // the position in the output array, the current row, and the
    // current column
    int pos = 0, r = startRow, c = startCol;
    // iterate once for each character in the output
    for ( int i = 0; i < len; i++ ) {
        // if the current row or column is out of bounds, then break
        if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) )
            break;
        // set the next character in the output array to the next letter
        // in the grid
        output[pos++] = grid[r][c];
        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }
    // set the next character to zero (end-of-string)
    output[pos] = 0;
    // return the string (a C-style char* string, not a C++ string
    // object)
    return output;
}

