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
#include <algorithm>

#include "morse.hpp"
#include "alphabet.hpp"

#define LOG_MSG \
      if (debug_disabled == true) {} \
      else clog

using namespace std;

namespace {
// set to false to show debugging information
const bool debug_disabled = true;
}

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

    // convert everything to lowercase
    std::transform(fdata.begin(), fdata.end(), fdata.begin(), ::tolower);

    // remove special characters
    const string specials = "\r\n\t(){}[]\\/,.;`!@#$%%^&*-_'+=~\"";
    for (auto c : specials)
        fdata.erase(std::remove(fdata.begin(), fdata.end(), c), fdata.end());

    // grab an object for the morse code mappings
    codemap m;

    // where we store the total duration units
    size_t total_units = 0;
    // where we track the count of total parsed characters
    size_t total_letters = 0;

    // iterate over the contents of the file
    for (auto c : fdata) {
        // check to see if the character is a space - if it
        // is, this means that we are between words
        if ( c == ' ' ) {
            // add on the inter_word length and continue to the
            // next character
            total_units += m.inter_word_units;
            continue;

        } else {
            // if it's not a space, grab the string of its morse code
            // representation
            string mc(m.m[c]);

            // add on the number of dot units
            total_units += numDots(mc) * m.dot_units;

            // add on the number of dash units
            total_units += numDashes(mc) * m.dash_units;

            // add on the number of units for intra-dot/dash delimiting
            // this will be [number of dots & dashes] - 1
            total_units += numDots(mc) + numDashes(mc) - 1;

            // add on the number of units to delimit a letter
            total_units += m.inter_letter_units;

            // increment our number of total letters processed
            total_letters++;

            // Debugging
            LOG_MSG << "Letter:\t" << c << endl
                    << "\tMorse Repr:\t" << mc << endl
                    << "\tNum Dots:\t" << numDots(mc) << endl
                    << "\tNum Dashes:\t" << numDashes(mc) << endl
                    << "\tTotal Units:\t" << total_units << endl;
        }
    }

    cout << "Total duration:\t" << total_units << endl
         << "Avg. duration:\t" << static_cast<double>(total_units) / total_letters << endl;

    // we're all done here
    exit(EXIT_SUCCESS);
}
