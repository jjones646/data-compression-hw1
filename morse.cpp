/**
 *  Jonathan Jones
 *  
 *  A simple program to parse in a file and convert to morse code dots & dashes.
 *  
 *  morse.cpp
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    // make sure we are given a file to parse
    if(argc != 2) {
        cout << "usage: ./morse <file>" << endl;
        return EXIT_FAILURE;
    }

    ofstream infile;
    infile.open(argv[1]);

    exit(EXIT_SUCCESS);
}
