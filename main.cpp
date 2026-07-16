#include "Snake.h"
#include <iostream>

using namespace std;
using namespace SnakeSpace;

int main(int argc, char** argv)
{
    // check command line arguments
    if (argc != 3)
    {
        cerr << "Incorrect number of arguments run the application with " << argv[0] << " <TotalRows> <TotalCols>" << endl;
        exit(INVALID);
    }

    srand(time(nullptr));

    int Num_Rows = ConvertToInt(argv[1]);
    int Num_Cols = ConvertToInt(argv[2]);

    GameStructure GameWorld;

    // Initialize the game by allocating memory
    GameWorld = iniGame(Num_Rows, Num_Cols);
    bool blnCountinue = true;
    char chInput = '\0';

    // clear screen once before loop starts
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    do
    {
        // Printing the Game
        PrintGame(GameWorld, Num_Rows, Num_Cols, GameWorld.Score);

        // get user input manually again
        cout << "Enter move (W/A/S/D): ";
        cin >> chInput;
        chInput = tolower(chInput);

        // move the snake
        MoveSnake(GameWorld, Num_Rows, Num_Cols, GameWorld.Score, chInput);

        // check if we hit a wall or our own body
        if(GameWorld.enStatus == LOST)
        {
            cout << "\nLost the game! Final Score: " << GameWorld.Score << endl;
            blnCountinue = false;
        }

    } while(blnCountinue);

    // clean up memory before closing
    DeallocMem(GameWorld.arrWorld, Num_Rows);

    cout << "Game Over!" << endl;
    return RUNNING;
}
