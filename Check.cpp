#include "Check.h"
#include <sstream>
#include <stdexcept>

using std::string;
using std::stringstream;
using std::logic_error;

namespace Check
{
    const static string possibleGenres[CAPACITY] =
    {
        "Action", "FPS", "MMORPG", "Simulation", "Sports", "Adventure", "Strategy", "Sandbox", "RPG"
    };

    bool Validator::checkGenre(const string &genre)
    {
        for(int i = 0; i < CAPACITY; ++i)
        {
            if(genre == possibleGenres[i])
                return true;
        }
        return false;
    }

    bool Validator::checkName(const string &name)
    {
        int nLength = name.length();
        for(int i = 0; i < nLength; ++i)
        {
            if((!isalpha(name[i]) && name[i] != ' ') || !(isupper(name[0])) || name.length() < 3)
            {
                return false;
            }
        }
        return true;
    }

    bool Validator::checkReleaseYear(unsigned int &date)
    {
        if(date >= FIRST_GAME_RELEASE_YEAR && date <= CURRENT_YEAR)
            return true;
        else
            return false;
    }

    void Validator::checkPointer(void *ptr, string file, int line)
    {
        if(ptr == NULL)
        {
            stringstream ss;
            ss << USE_OF_NO_INIT << " In " << file << " : at " << line << " line\n";
            throw logic_error(ss.str());
        }
    }
}

