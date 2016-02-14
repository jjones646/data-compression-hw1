
#include <string>
#include <sys/stat.h>


/**
    Check if a file exists
@param[in] filename - the name of the file to check

@return    true if the file exists, else false

*/
bool fileExists(const std::string& filename)
{
    struct stat buf;

    if (stat(filename.c_str(), &buf) != -1)
        return true;

    return false;
}

// Returns the number of dots in a string
size_t numDots(const std::string& s) {
    return std::count(s.begin(), s.end(), '.');
}

// Returns the number of dashes in a string
size_t numDashes(const std::string& s) {
    return std::count(s.begin(), s.end(), '-');
}
