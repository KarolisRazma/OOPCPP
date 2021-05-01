#ifndef CHECK_H
#define CHECK_H

#include <string>

using std::string;

#define CAPACITY 9
#define FIRST_GAME_RELEASE_YEAR 1958
#define CURRENT_YEAR 2021

// invalid_argument error messages
#define INVALID_NAME "Wrong game name!"
#define INVALID_GENRE "Wrong genre!"
#define INVALID_YEAR "Wrong release year!"
#define INVALID_MULTIPLAYER "Wrong multiplayer value!"
#define INVALID_PRICE "Price can't be negative!"
#define INVALID_SYMBOL "Symbol must be '+' or '-' only!"

// logic_error messages
#define NO_INIT "Object is not initialized!"
#define USE_OF_NO_INIT "Tried to access uninitialized object!"

namespace Check
{
    class Validator
    {
        public:
            static bool checkGenre(const string &genre);
            static bool checkName(const string &name);
            static bool checkReleaseYear(unsigned int &date);
            static void checkPointer(void *ptr, string file, int line);
    };
}

#endif // CHECK_H
