/**
 * morse.cpp
 *
 * Jonathan Jones
 * A simple program to parse in a file and convert to morse code dots & dashes.
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
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
    const string specials = "\r\n\t(){}[]<>?\\/,.;:`~!@#$%%^&*-_'\'+=\"\a\b\f\v\x91\x92\x93\x94\x95\x96";
    for (auto c : specials)
        fdata.erase(std::remove(fdata.begin(), fdata.end(), c), fdata.end());

    // grab an object for the morse code mappings
    codemap m;

    // where we store the total duration units
    size_t total_units = 0;
    // where we track the count of total parsed characters
    size_t total_letters = 0;
    size_t total_dots = 0;
    size_t total_dashes = 0;
    size_t total_intra_gaps = 0;
    size_t total_inter_gaps = 0;
    size_t total_words = 0;

    // iterate over the contents of the file
    for (auto c : fdata) {
        // check to see if the character is a space - if it
        // is, this means that we are between words
        if ( (c == ' ') && m.m[c].compare("") == 0 ) {
            // add on the inter_word length and continue to the
            // next character
            total_units += m.inter_word_units;
            total_inter_gaps += m.inter_word_units;

            // increment our number of total letters processed
            total_words++;
            total_letters++;

            continue;

        } else {
            // if it's not a space, grab the string of its morse code
            // representation
            string mc(m.m[c]);

            // add on the number of dot units
            total_units += numDots(mc) * m.dot_units;
            total_dots += numDots(mc) * m.dot_units;

            // add on the number of dash units
            total_units += numDashes(mc) * m.dash_units;
            total_dashes += numDashes(mc) * m.dash_units;

            // add on the number of units for intra-dot/dash delimiting
            // this will be [number of dots & dashes] - 1
            total_units += (numDots(mc) + numDashes(mc) - 1) * m.intra_letter_units;
            total_intra_gaps += (numDots(mc) + numDashes(mc) - 1) * m.intra_letter_units;

            // add on the number of units to delimit a letter
            total_units += m.inter_letter_units;
            total_inter_gaps += m.inter_letter_units;

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

    size_t total_all = total_dots + total_dashes + total_inter_gaps + total_intra_gaps + total_words;

    // print out the final results for part a
    cout << "Total duration:\t" << total_units << endl
         << "Avg. duration:\t" << static_cast<double>(total_units) / total_letters << endl;

    // count the frequency of each character
    map<char, size_t> charfreq;
    for ( string::iterator it = fdata.begin(); it != fdata.end() - 1; ++it) {
        // increment the count for this pair
        charfreq[*it]++;
    }

    // print out the results for the frequency of each character
    cout << "Distribution:" << endl;
    for (auto e : charfreq)
        cout << "\t" << e.first << " => " << fixed << setprecision(3) << static_cast<double>(e.second) / total_letters * 100 << "%" << endl;

    LOG_MSG << "Total Dots:\t" << total_dots << endl
            << "Total Dashes:\t" << total_dashes << endl
            << "Total Intra:\t" << total_intra_gaps << endl
            << "Total Inter:\t" << total_inter_gaps << endl
            << "Total Words:\t" << total_words << endl
            << "Total All:\t" << total_all << endl;

    cout << "Mapped Distribution:" << endl
         << "\tDots   => " << fixed << setprecision(3) << static_cast<double>(total_dots) / total_all * 100 << "%" << endl
         << "\tDashes => " << fixed << setprecision(3) << static_cast<double>(total_dashes) / total_all * 100 << "%" << endl
         << "\tIntra  => " << fixed << setprecision(3) << static_cast<double>(total_intra_gaps) / total_all * 100 << "%" << endl
         << "\tInter  => " << fixed << setprecision(3) << static_cast<double>(total_inter_gaps) / total_all * 100 << "%" << endl
         << "\tWords  => " << fixed << setprecision(3) << static_cast<double>(total_words) / total_all * 100 << "%" << endl;

    // we're all done here
    exit(EXIT_SUCCESS);
}
