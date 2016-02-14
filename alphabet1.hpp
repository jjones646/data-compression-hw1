/**
 * Defines a morse code alphabet mapping.
 */

#include <utility>
#include <string>

using std::pair;
using std::string;

// Keep things in a different namespace since the variable names
// are simple.
namespace mcode {

// Define the 5 symbols in the morse code alphabet
size_t dot_span         ( 1 );
size_t dash_span        ( 3 );
size_t intra_letter_gap ( 1 );
size_t inter_letter_gap ( 3 );
size_t inter_word_gap   ( 7 );

// Define what each letter corresponds to in terms
// of dots and dashes
pair<char, string> a        ( 'a',   ".-"    );
pair<char, string> b        ( 'b',   "-..."  );
pair<char, string> c        ( 'c',   "-.-."  );
pair<char, string> d        ( 'd',   "-.."   );
pair<char, string> e        ( 'e',   "."     );
pair<char, string> f        ( 'f',   "..-."  );
pair<char, string> g        ( 'g',   "--."   );
pair<char, string> h        ( 'h',   "...."  );
pair<char, string> i        ( 'i',   ".."    );
pair<char, string> j        ( 'j',   ".---"  );
pair<char, string> k        ( 'k',   "-.-"   );
pair<char, string> l        ( 'l',   ".-.."  );
pair<char, string> m        ( 'm',   "--"    );
pair<char, string> n        ( 'n',   "-."    );
pair<char, string> o        ( 'o',   "---"   );
pair<char, string> p        ( 'p',   ".--."  );
pair<char, string> q        ( 'q',   "--.-"  );
pair<char, string> r        ( 'r',   ".-."   );
pair<char, string> s        ( 's',   "..."   );
pair<char, string> t        ( 't',   "-"     );
pair<char, string> u        ( 'u',   "..-"   );
pair<char, string> v        ( 'v',   "...-"  );
pair<char, string> w        ( 'w',   ".--"   );
pair<char, string> x        ( 'x',   "-..-"  );
pair<char, string> y        ( 'y',   "-.--"  );
pair<char, string> z        ( 'z',   "--.."  );
pair<char, string> one      ( '1',   ".----" );
pair<char, string> two      ( '2',   "..---" );
pair<char, string> three    ( '3',   "...--" );
pair<char, string> four     ( '4',   "....-" );
pair<char, string> five     ( '5',   "....." );
pair<char, string> six      ( '6',   "-...." );
pair<char, string> seven    ( '7',   "--..." );
pair<char, string> eight    ( '8',   "---.." );
pair<char, string> nine     ( '9',   "----." );
pair<char, string> zero     ( '0',   "-----" );

// Possibly unused?
pair<char, string> space    ( ' ',   ""      );
pair<char, string> tab      ( '\t',  ""      );
pair<char, string> cret     ( '\r',  ""      );
pair<char, string> nline    ( '\n',  ""      );

} // mcode namespace
