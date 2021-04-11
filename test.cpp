#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "VideoGame.h"
#include "Check.h"

using namespace Game;

TEST_CASE("Class 'VideoGame' simple test")
{
    VideoGame game("World of Warcraft", "MMORPG", 2004, true);
    CHECK(game.getID() == 1);
    VideoGame game_2("Call of Duty", "FPS", 2011, false);
    CHECK(game.getName() != game_2.getName());
}
