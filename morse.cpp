/**
 * morse.cpp
 *
 * Jonathan Jones
 * A simple program to parse in a file and convert to morse code dots & dashes.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "morse.hpp"

using namespace std;


int main(int argc, char* argv[]) {
    // make sure we are given a file to parse
    if ( argc != 2 ) {
        cout << "usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;
    }

    // check if the given file exists
    string fn(argv[1]);

    if ( fileExists(fn) == false ) {
        cout << fn << " does not exist" << endl;
        return EXIT_FAILURE;
    }

    // if we make it here, the file exists
    // let's open the file now
    ifstream infile;
    infile.open(fn.c_str());

    // let's read in the file now
    string line;
    while ( !infile.eof() ) {
        getline(infile, line);
        cout << line;
    }

    // cout << "error opening " << fn << endl;
    // return EXIT_FAILURE;

    // close the file & terminate the program
    infile.close();
    exit(EXIT_SUCCESS);
}
