#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include <string>

using std::string;
using std::istream;
using std::ostream;

namespace Game
{
    /**@brief
    * This class stores data about video games.
    * VideoGame consists of these fields: name, genre, release year, single/multi player
    */
    class VideoGame
    {
        private:
            class InnerVideoGame;
            InnerVideoGame *ptr;
            friend class InnerVideoGame;

        public:
            /**@brief
            * Lazy initialization of the VideoGame.
            */
            VideoGame();
            VideoGame(const string& n, const string& g, unsigned int rYear, bool isMultiP);
            ~VideoGame();

            /**@brief
            * This function will set all video game data with given parametres.
            */
            void setGame(const string& n, const string& g, unsigned int rYear, bool isMultiP);
            void setName(const string& nameOfGame);
            void setGenre(const string& genreOfGame);
            void setReleaseYear(unsigned int year);
            void setMultiplayer(bool isOnline);
            void setGameID();

            string getName() const;
            string getGenre() const;
            unsigned int getReleaseYear() const;
            bool getIsMultiplayer() const;
            unsigned int getID() const;
            /**@brief
            * This function returns class object data converted into string.
            * @return string in format: gameID name genre releaseYear isMultiplayer (5 fields, separated by whitespace)
            */
            string toString() const;

            /**@brief
            * This function checks if release year of 2 games are equal.
            * @retval TRUE both games released in the same year
            * @retval FALSE both games are released in different years
            */
            bool operator ==(const VideoGame& game);
            bool operator !=(const VideoGame& game);
            bool operator <(const VideoGame& game);
            bool operator <=(const VideoGame& game);
            bool operator >(const VideoGame& game);
            bool operator >=(const VideoGame& game);

            VideoGame& operator =(const VideoGame& game);

            VideoGame& operator++();
            VideoGame operator++(int);

            friend ostream& operator <<(ostream& output, const VideoGame& game);
            friend istream& operator >>(istream& input, VideoGame& game);
    };
}

#endif // VIDEOGAME_H
