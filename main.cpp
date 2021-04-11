#include "VideoGame.h"
#include <iostream>
#include <string>

using namespace std;
using namespace Game;

int main()
{
    try
    {
        VideoGame example_1("Lineage II", "MMORPG", 2003, true);
        VideoGame example_2;

        cin >> example_2;

        VideoGame example_3("Minecraft", "Sandbox", 2011, true);
        VideoGame example_4;

        cout << example_1 << endl;
        cout << example_2 << endl;
        cout << example_3 << endl;

        cin >> example_4;

        cout << example_4 << endl;

    }
    catch(invalid_argument& error)
    {
        cerr << "Exception: invalid argument - " << error.what() << endl;
    }
    catch(logic_error& error)
    {
        cerr << "Exception: logic error - " << error.what() << endl;
    }
    catch(...)
    {
        cerr << "Exception: unknown exception catched, something's wrong!" << endl;
    }

    return 0;
}
