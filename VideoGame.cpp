#include "VideoGame.h"
#include "Check.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using std::string;
using std::endl;
using std::invalid_argument;
using std::logic_error;
using std::stringstream;
using std::setw;
using std::left;
using std::istream;
using std::ostream;

using namespace Check;

namespace Game
{
    class VideoGame::InnerVideoGame
    {
        string name;
        string genre;
        unsigned int releaseYear;
        bool isMultiplayer;
        static int gamesCounter;
        unsigned int gameID;

        friend class VideoGame;
    };

    int VideoGame::InnerVideoGame::gamesCounter = 0;

    VideoGame::VideoGame()
    {
        ptr = NULL;
    }

    VideoGame::VideoGame(const string& n, const string& g, unsigned int rYear, bool isMultiP)
    {
        ptr = new InnerVideoGame();

        ++ptr->gamesCounter;
        setGameID();
        setGame(n, g, rYear, isMultiP);
    }

    VideoGame::~VideoGame()
    {
        delete ptr;
    }

    // start of setters
    void VideoGame::setGame(const string& n, const string& g, unsigned int rYear, bool isMultiP)
    {
        if(ptr == NULL)
        {
            ptr = new InnerVideoGame();
            ++ptr->gamesCounter;
        }
        setGameID();
        setName(n);
        setGenre(g);
        setReleaseYear(rYear);
        setMultiplayer(isMultiP);
    }

    void VideoGame::setName(const string& nameOfGame)
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        if(Validator::checkName(nameOfGame))
            ptr->name = nameOfGame;
        else
            throw invalid_argument(INVALID_NAME);

    }

    void VideoGame::setGenre(const string& genreOfGame)
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }

        if(Validator::checkGenre(genreOfGame))
            ptr->genre = genreOfGame;
        else
            throw invalid_argument(INVALID_GENRE);
    }

    void VideoGame::setReleaseYear(unsigned int year)
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }

        if(Validator::checkReleaseYear(year))
            ptr->releaseYear = year;
        else
            throw invalid_argument(INVALID_YEAR);
    }

    void VideoGame::setMultiplayer(bool isOnline)
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        if(isOnline)
            ptr->isMultiplayer = isOnline;
        else if(isOnline == false)
            ptr->isMultiplayer = isOnline;
        else
            throw invalid_argument(INVALID_MULTIPLAYER);
    }

    void VideoGame::setGameID()
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        ptr->gameID = ptr->gamesCounter;
    }
    // end of setters

    // start of getters
    string VideoGame::getName() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        return ptr->name;
    }

    string VideoGame::getGenre() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        return ptr->genre;
    }

    unsigned int VideoGame::getReleaseYear() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        return ptr->releaseYear;
    }

    bool VideoGame::getIsMultiplayer() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        return ptr->isMultiplayer;
    }

    unsigned VideoGame::getID() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        return ptr->gameID;
    }
    // end of getters

    string VideoGame::toString() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }

        stringstream ss;

        ss << setw(3) << left << getID();
        ss << setw(25) << left << getName();
        ss << setw(15) << left << getGenre();
        ss << setw(6) << left << getReleaseYear();
        ss << setw(2) << left << getIsMultiplayer() << endl;

        return ss.str();
    }

    bool VideoGame::operator ==(const VideoGame& game)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        if(this->getReleaseYear() == game.getReleaseYear())
            return true;
        else
            return false;
    }

    bool VideoGame::operator !=(const VideoGame& game)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        return !(*this == game);
    }

    bool VideoGame::operator <(const VideoGame& game)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        return !(*this >= game);
    }

    bool VideoGame::operator <=(const VideoGame& game)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        if(this->getReleaseYear() > game.getReleaseYear())
            return false;
        else
            return true;
    }

    bool VideoGame::operator >(const VideoGame& game)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        return !(*this <= game);
    }

    bool VideoGame::operator >=(const VideoGame& game)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        if(this->getReleaseYear() < game.getReleaseYear())
            return false;
        else
            return true;
    }

    VideoGame& VideoGame::operator =(const VideoGame& game)
    {
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        InnerVideoGame *temp = new InnerVideoGame();

        temp->name = game.getName();
        temp->genre = game.getGenre();
        temp->releaseYear = game.getReleaseYear();
        temp->isMultiplayer = game.getIsMultiplayer();
        temp->gameID = game.getID();

        delete this->ptr;
        this->ptr = temp;

        return *this;
    }

    VideoGame& VideoGame::operator++()
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);

        unsigned int year = this->getReleaseYear();
        this->setReleaseYear(++year);
        return *this;
    }

    VideoGame VideoGame::operator++(int)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);

        VideoGame temp = *this;
        unsigned int year = this->getReleaseYear();
        this->setReleaseYear(++year);
        return temp;
    }

    ostream& operator <<(ostream& output, const VideoGame& game)
    {
        output << game.toString();
        return output;
    }

    istream& operator >>(istream& input, VideoGame& game)
    {
        // temp values
        string name, genre;
        unsigned int releaseYear;
        bool isMultiplayer;
        VideoGame temp;

        getline(input, name);
        getline(input, genre);
        input >> releaseYear;
        input >> isMultiplayer;
        input.ignore();

        temp.setGame(name, genre, releaseYear, isMultiplayer);

        game = temp;

        return input;
    }
}
