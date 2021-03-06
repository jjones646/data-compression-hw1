/**
 * morse.cpp
 *
 * Jonathan Jones
 * A simple program to parse in a file and convert to morse code dots & dashes.
 */

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

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

int partOne(string& fdata) {

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
        // increment the count for this character
        charfreq[*it]++;
    }

    // create a vector holding all of the words
    stringstream ss(fdata);
    istream_iterator<string> _begin(ss);
    istream_iterator<string> _end;
    vector<string> worddata(_begin, _end);

    // count the frequency of each word
    map<string, size_t> wordfreq;
    for ( vector<string>::iterator it = worddata.begin(); it != worddata.end() - 1; ++it) {
        // increment the count for this character
        wordfreq[*it]++;
    }

    // print out the results for the frequency of each character
    double entropy_chars = 0;
    cout << "Alphabet Distribution:" << endl;
    for (auto e : charfreq) {
        cout << "\t" << e.first << "\t=>\t"
             << e.second << "\t("
             << fixed << setprecision(3) << static_cast<double>(e.second) / fdata.size() * 100 << "%)" << endl;

        const double prob = static_cast<double>(e.second) / fdata.size();
        entropy_chars += prob * log2(prob);
    }
    entropy_chars *= -1;

    LOG_MSG << "Total Dots:\t" << total_dots << endl
            << "Total Dashes:\t" << total_dashes << endl
            << "Total Intra:\t" << total_intra_gaps << endl
            << "Total Inter:\t" << total_inter_gaps << endl
            << "Total Words:\t" << total_words << endl
            << "Total All:\t" << total_all << endl;

    LOG_MSG << "Word Count:\t\t" << worddata.size() << endl;


    cout << "Mapped Distribution:" << endl
         << "\tDots   =>\t" << total_dots << "\t(" << fixed << setprecision(3) << static_cast<double>(total_dots) / total_all * 100 << "%)" << endl
         << "\tDashes =>\t" << total_dashes << "\t(" << fixed << setprecision(3) << static_cast<double>(total_dashes) / total_all * 100 << "%)" << endl
         << "\tIntra  =>\t" << total_intra_gaps << "\t(" << fixed << setprecision(3) << static_cast<double>(total_intra_gaps) / total_all * 100 << "%)" << endl
         << "\tInter  =>\t" << total_inter_gaps << "\t(" << fixed << setprecision(3) << static_cast<double>(total_inter_gaps) / total_all * 100 << "%)" << endl
         << "\tWords  =>\t" << total_words << "\t(" << fixed << setprecision(3) << static_cast<double>(total_words) / total_all * 100 << "%)" << endl;

    // create a vector holding everything
    vector<double> totals;
    totals.push_back(total_dots);
    totals.push_back(total_dashes);
    totals.push_back(total_intra_gaps);
    totals.push_back(total_inter_gaps);
    totals.push_back(total_words);

    double totals_sum = 0;
    for (auto const& t : totals)
        totals_sum += t;

    // where we'll store the entropy of the morse mapped alphabet
    double entropy_morse = 0;
    for (auto const& t : totals) {
        const double prob = static_cast<double>(t) / totals_sum;
        entropy_morse += prob * log2(prob);
    }
    entropy_morse *= -1;

    cout << "Entropy Alphabet:\t" << entropy_chars << endl
         << "Entropy Morse Alphabet:\t" << entropy_morse << endl;

    return EXIT_SUCCESS;
}

int partTwo(string& fdata) {

    // create a vector holding all of the words
    stringstream ss(fdata);
    istream_iterator<string> _begin(ss);
    istream_iterator<string> _end;
    vector<string> worddata(_begin, _end);

    // count the frequency of each character
    map<char, size_t> charfreq;
    for ( string::iterator it = fdata.begin(); it != fdata.end() - 1; ++it) {
        // increment the count for this character
        charfreq[*it]++;
    }

    // count the frequency of each word
    map<string, size_t> wordfreq;
    for ( vector<string>::iterator it = worddata.begin(); it != worddata.end() - 1; ++it) {
        // increment the count for this character
        wordfreq[*it]++;
    }

    // print out the results for the frequency of each character
    double entropy_chars = 0;
    cout << "Alphabet Distribution:" << endl;
    for (auto e : charfreq) {
        cout << "\t" << e.first << "\t=>\t"
             << e.second << "\t("
             << fixed << setprecision(3) << static_cast<double>(e.second) / fdata.size() * 100 << "%)" << endl;

        const double prob = static_cast<double>(e.second) / fdata.size();
        entropy_chars += prob * log2(prob);
    }
    entropy_chars *= -1;

    double entropy_words = 0;
    cout << "Dictionary Distribution:" << endl;
    for (auto e : wordfreq) {
        cout << "\t" << e.first << "\t=>\t"
             << e.second << "\t("
             << fixed << setprecision(3) << static_cast<double>(e.second) / worddata.size() * 100 << "%)" << endl;

        const double prob = static_cast<double>(e.second) / worddata.size();
        entropy_words += prob * log2(prob);
    }
    entropy_words *= -1;

    cout << "Entropy Alphabet:\t" << entropy_chars << endl
         << "Entropy Dictionary:\t" << entropy_words << endl;

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    // make sure we are given a file to parse
    if ( argc < 2 ) {
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

    if ( argc >= 2 ) {
        if ( argc == 2 ) {
            return partOne(fdata);
        }
        else if ( string(argv[2]).compare(string("1")) == 0 ) {
            return partOne(fdata);
        }
        else if ( string(argv[2]).compare(string("2")) == 0 ) {
            return partTwo(fdata);
        }
        else {
            cout << "usage: " << argv[0] << " <file> [part]" << endl;
            return EXIT_FAILURE;
        }
    }

    // we're all done here
    exit(EXIT_SUCCESS);
}
