#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "VideoGame.h"
#include "Check.h"
#include <sstream>
#include <fstream>

using namespace Game;
using namespace std;

TEST_CASE("#AUTO ID")
{
    VideoGame test_1("Lineage II", "MMORPG", 2003, true, 10.15);
    CHECK(test_1.getID() == 1);

    VideoGame test_2("Runescape", "MMORPG", 2001, true, 9.47);
    CHECK(test_2.getID() == 2);

    VideoGame test_3("Half Life", "FPS", 1998, false, 15.15);
    CHECK(test_3.getID() == 3);

    VideoGame test_4("Random game", "RPG", 2000, true, 99.99);
    CHECK(test_4.getID() == 4);
}

TEST_CASE("#SET")
{
    VideoGame test_1("Lineage II", "MMORPG", 2003, true, 22.15);

    // check getters
    CHECK("Lineage II" == test_1.getName());
    CHECK("MMORPG" == test_1.getGenre());
    CHECK(2003 == test_1.getReleaseYear());
    CHECK(true == test_1.getIsMultiplayer());
    CHECK(22.15 == test_1.getPrice());

    // check setters
    test_1.setName("Minecraft");
    test_1.setGenre("Sandbox");
    test_1.setReleaseYear(2011);
    test_1.setMultiplayer(false);
    test_1.setPrice(4.99);

    // check getters
    CHECK("Minecraft" == test_1.getName());
    CHECK("Sandbox" == test_1.getGenre());
    CHECK(2011 == test_1.getReleaseYear());
    CHECK(false == test_1.getIsMultiplayer());
    CHECK(4.99 == test_1.getPrice());
}

TEST_CASE("#CMP")
{
    VideoGame test_1("Skyrim", "RPG", 2020, false, 2.22);
    VideoGame test_2("Terraria", "Adventure", 2014, true, 1.59);
    VideoGame test_3("Random game", "Action", 2007, false, 4.99);
    VideoGame test_4("Random game II", "Simulation", 2014, true, 22.56);

    // compares release year
    CHECK(test_4 == test_2);    // 2014 == 2014
    CHECK(test_1 != test_2);    // 2020 != 2014
    CHECK(test_1 > test_2);     // 2020 > 2014
    CHECK(test_3 < test_4);     // 2007 < 2014
    CHECK(test_2 <= test_4);    // 2014 <= 2014
    CHECK(test_2 >= test_4);    // 2014 >= 2014
    CHECK(test_3 <= test_1);    // 2007 <= 2020
    CHECK(test_4 >= test_3);    // 2014 >= 2007

    CHECK_FALSE(test_2 == test_1);  // 2014 == 2020
    CHECK_FALSE(test_3 != test_3);  // 2007 != 2007
    CHECK_FALSE(test_3 > test_1);   // 2007 > 2020
    CHECK_FALSE(test_1 < test_2);   // 2020 < 2014
    CHECK_FALSE(test_3 >= test_1);  // 2007 >= 2020
    CHECK_FALSE(test_4 <= test_3);  // 2014 <= 2007

}

TEST_CASE("#STREAM")
{
    VideoGame test_1;
    VideoGame test_2("Random", "RPG", 2014, true, 14.59);

    stringstream ss;

    ss << test_2;
    ss >> test_1;

    CHECK(test_2.getName() == test_1.getName());
    CHECK(test_2.getGenre() == test_1.getGenre());
    CHECK(test_2.getReleaseYear() == test_1.getReleaseYear());
    CHECK(test_2.getIsMultiplayer() == test_1.getIsMultiplayer());
    CHECK(test_2.getPrice() == test_1.getPrice());
}

TEST_CASE("#PRE_POST")
{
    VideoGame test_1("Random", "RPG", 2014, true, 22.14);
    VideoGame test_2("Random", "RPG", 2014, true, 22.13);
    VideoGame test_3("Random", "RPG", 2015, true, 22.12);

    // post increment
    CHECK(test_3 != test_1++); // 2015 != 2014++
    CHECK(test_1 == test_3); //  2015 == 2015

    // pre increment
    CHECK(test_3 == ++test_2); // 2015 == ++2014

    // post decrement
    CHECK(test_3 == test_1--); // 2015 == 2015--
    CHECK(test_1 != test_3); //  2014 != 2015

    // pre decrement
    CHECK(test_1 == --test_2); // 2014 == --2015
}

TEST_CASE("#THROW")
{
    VideoGame test_1("Random", "RPG", 2014, true, 22.15);
    VideoGame test_2(test_1);

    CHECK_THROWS(test_1.setGenre("BadGenre"));
    CHECK_THROWS_AS(test_1.setGenre("BadGenre"), invalid_argument);
    CHECK(test_1.isCopy(test_2));

    stringstream ss;
    ss << "Crazy,MMORPG,-152,1,-45454";
    CHECK_THROWS(ss >> test_2);

    CHECK(test_2.isCopy(test_1));
}

TEST_CASE("#COPY")
{
    VideoGame test_1("Random", "RPG", 2014, true, 4.99);
    VideoGame test_2(test_1);

    CHECK(test_1 == test_2);
    ++test_1;
    CHECK(test_1 != test_2);

    VideoGame test_3 = test_2;

    CHECK(test_3 == test_2);
    ++test_3;
    CHECK(test_3 != test_2);
}

TEST_CASE("#LEAK")
{
    CHECK(VideoGame::getLiveInstances() == 0);
    {
        VideoGame test_1("Random", "RPG", 2014, true, 4.99);
        VideoGame test_2 = test_1;
        CHECK(VideoGame::getLiveInstances() == 2);
        VideoGame test_3(test_1);
        VideoGame test_4;
        CHECK(VideoGame::getLiveInstances() == 3);
    }
    CHECK(VideoGame::getLiveInstances() == 0);
}

TEST_CASE("CUSTOM / CHANGE PRICE (increase or decrease game price)")
{
    VideoGame test_1("Random", "RPG", 2014, true, 4.99);

    test_1.changePrice('+', 15.01);
    CHECK(test_1.getPrice() == 20.00);

    test_1.changePrice('-', 7.77);
    CHECK(test_1.getPrice() == 12.23);

    CHECK_NOTHROW(test_1.changePrice('-', 12.23));
    test_1.changePrice('+', 12.23);
    CHECK_NOTHROW(test_1.changePrice('+', -12.23));

    CHECK_THROWS(test_1.changePrice('-', 12.24));
    CHECK_THROWS(test_1.changePrice('+', -12.24));
}


