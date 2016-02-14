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
#include "alphabet1.hpp"

using namespace std;
using namespace mcode;


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

    // make a variable that will hold the entire contents
    // of our incoming file
    string fdata;

    // if we make it here, the file exists
    // let's open the file now
    ifstream infile;
    infile.open(fn.c_str());

    // if everything goes well, we can now parse it line by line
    if ( infile.is_open() ) {
        // let's read in the file now
        string line;
        while ( !infile.eof() ) {
            getline(infile, line);
            fdata += line;
        }
    } else {
        // otherwise, exit with a failure
        cout << "error opening " << fn << endl;
        return EXIT_FAILURE;
    }

    // we no longer need to hold the file open, so let's close it
    infile.close();

    // dot_span
    // dash_span
    // intra_letter_gap
    // inter_letter_gap
    // inter_word_gap

    // iterate over the contents of the file
    for (auto const &i : fdata)
        cout << i;

    // cout << endl << endl << a.first << " => " << a.second << endl;

    // print out a final blank line to keep things neat
    cout << endl;

    // we're all done here
    exit(EXIT_SUCCESS);
}
