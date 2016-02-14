

#include <cstdlib>
#include <fstream>
// #include <cstdio>

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
