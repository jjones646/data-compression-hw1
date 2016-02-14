/**
 * Defines a morse code alphabet mapping.
 */

#include <map>
#include <string>

using std::map;
using std::string;

// A simple class that defines the morse code mappings
class codemap {
public:
    codemap() :
        dot_units           ( 1 ),
        dash_units          ( 3 ),
        intra_letter_units  ( 1 ),
        inter_letter_units  ( 3 ),
        inter_word_units    ( 0 )
    {
        m['a'] = ".-"   ;
        m['b'] = "-..." ;
        m['c'] = "-.-." ;
        m['d'] = "-.."  ;
        m['e'] = "."    ;
        m['f'] = "..-." ;
        m['g'] = "--."  ;
        m['h'] = "...." ;
        m['i'] = ".."   ;
        m['j'] = ".---" ;
        m['k'] = "-.-"  ;
        m['l'] = ".-.." ;
        m['m'] = "--"   ;
        m['n'] = "-."   ;
        m['o'] = "---"  ;
        m['p'] = ".--." ;
        m['q'] = "--.-" ;
        m['r'] = ".-."  ;
        m['s'] = "..."  ;
        m['t'] = "-"    ;
        m['u'] = "..-"  ;
        m['v'] = "...-" ;
        m['w'] = ".--"  ;
        m['x'] = "-..-" ;
        m['y'] = "-.--" ;
        m['z'] = "--.." ;
        m['1'] = ".----";
        m['2'] = "..---";
        m['3'] = "...--";
        m['4'] = "....-";
        m['5'] = ".....";
        m['6'] = "-....";
        m['7'] = "--...";
        m['8'] = "---..";
        m['9'] = "----.";
        m['0'] = "-----";
        m[' '] = "-.-.-";
    };

    // Holds the morse code mappings from
    // characters to dots/dashes
    map<char, string> m;

    // Define the 5 symbols in the morse code alphabet
    size_t dot_units, dash_units, intra_letter_units,
           inter_letter_units, inter_word_units;
};
