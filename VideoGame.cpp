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
            static int liveInstances;
            double price;

        friend class VideoGame;

        public:
             ~InnerVideoGame();

    };

    int VideoGame::InnerVideoGame::gamesCounter = 0;
    int VideoGame::InnerVideoGame::liveInstances = 0;

    VideoGame::InnerVideoGame::~InnerVideoGame()
    {
        --VideoGame::InnerVideoGame::liveInstances;
    }

    VideoGame::VideoGame()
    {
        ptr = NULL;
    }

    VideoGame::VideoGame(const string& n, const string& g, unsigned int rYear, bool isMultiP, double price)
    {
        ptr = new InnerVideoGame();

        ++ptr->gamesCounter;
        setGameID();
        setGame(n, g, rYear, isMultiP, price);
        ++ptr->liveInstances;
    }

    VideoGame::VideoGame(const VideoGame& game)
    {
        if(game.ptr == NULL)
            this->ptr = NULL;
        else
        {
            this->ptr = new InnerVideoGame();
            setGameID();
            setGame(game.getName(), game.getGenre(), game.getReleaseYear(), game.getIsMultiplayer(), game.getPrice());
            ++ptr->liveInstances;
        }
    }

    VideoGame::~VideoGame()
    {
        delete ptr;
    }

    // start of setters
    void VideoGame::setGame(const string& n, const string& g, unsigned int rYear, bool isMultiP, double price)
    {
        if(ptr == NULL)
        {
            ptr = new InnerVideoGame();
            ++ptr->gamesCounter;
            ++ptr->liveInstances;
        }
        setGameID();
        setName(n);
        setGenre(g);
        setReleaseYear(rYear);
        setMultiplayer(isMultiP);
        setPrice(price);
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

    void VideoGame::setPrice(double price)
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        if(price < 0)
        {
            throw invalid_argument(INVALID_PRICE);
        }
        ptr->price = price;
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

    unsigned int VideoGame::getID() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        return ptr->gameID;
    }

    int VideoGame::getLiveInstances()
    {
        return VideoGame::InnerVideoGame::liveInstances;
    }

    double VideoGame::getPrice() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }
        return ptr->price;
    }

    // end of getters

    string VideoGame::toString() const
    {
        if(ptr == NULL)
        {
            throw logic_error(NO_INIT);
        }

        stringstream ss;

        ss << getName() << ",";
        ss << getGenre() << ",";
        ss << getReleaseYear() << ",";
        ss << getIsMultiplayer() << ",";
        ss << getPrice() << ",";
        ss << getID();

        return ss.str();
    }

    void VideoGame::changePrice(const char symbol, const double number)
    {
        if(symbol != '+' && symbol != '-')
            throw invalid_argument(INVALID_SYMBOL);
        if(symbol == '+')
        {
            setPrice(getPrice() + number);
        }
        if(symbol == '-')
        {
            setPrice(getPrice() - number);
        }
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

        if(this->getReleaseYear() < game.getReleaseYear())
            return true;
        else
            return false;
    }

    bool VideoGame::operator <=(const VideoGame& game)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        return ((*this < game) || (*this == game));
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

        return !(*this < game);
    }

    VideoGame& VideoGame::operator =(const VideoGame& game)
    {
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        if(this == &game)
            return *this;

        InnerVideoGame *temp = new InnerVideoGame();

        temp->name = game.getName();
        temp->genre = game.getGenre();
        temp->releaseYear = game.getReleaseYear();
        temp->isMultiplayer = game.getIsMultiplayer();
        temp->price = game.getPrice();
        temp->gameID = game.getID();
        ++temp->liveInstances;

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

    VideoGame& VideoGame::operator--()
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);

        unsigned int year = this->getReleaseYear();
        this->setReleaseYear(--year);
        return *this;
    }

    VideoGame VideoGame::operator--(int)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);

        VideoGame temp = *this;
        unsigned int year = this->getReleaseYear();
        this->setReleaseYear(--year);
        return temp;
    }

    bool VideoGame::isCopy(const VideoGame& game)
    {
        Validator::checkPointer(this->ptr, __FILE__, __LINE__);
        Validator::checkPointer(game.ptr, __FILE__, __LINE__);

        bool equal = true;
        equal &= (this->getName() == game.getName());
        equal &= (this->getGenre() == game.getGenre());
        equal &= (this->getReleaseYear() == game.getReleaseYear());
        equal &= (this->getIsMultiplayer() == game.getIsMultiplayer());
        equal &= (this->getPrice() == game.getPrice());
        equal &= (this->getID() == game.getID());

        return equal;
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
        char comma;
        double price;
        VideoGame temp;

        getline(input, name, ',');
        getline(input, genre, ',');
        input >> releaseYear;
        input >> comma;
        input >> isMultiplayer;
        input >> comma;
        input >> price;
        input >> comma;
        input.ignore();

        temp.setGame(name, genre, releaseYear, isMultiplayer, price);

        game = temp;

        return input;
    }
}
