#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <iostream>
#include <ctime>
#include <cctype>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace SnakeSpace
{
    // error codes for exiting
    enum Errors
    {
        INVALID = -1,
        FAIL = -2,
        ARG_CONV = -3,
        DATA_CONV = -4
    };

    // game states
    enum Game
    {
        RUNNING,
        QUIT,
        LOST
    };

    typedef int* OneDarray;
    typedef int** TwoDarray;

    // structure holding everything about the game
    struct GameStructure
    {
        TwoDarray arrWorld;
        int Rows;
        int Cols;
        int Length;
        int Prow;
        int Pcol;
        Game enStatus;
        int Score;
    };

    const int EMPTY = 0;
    const int SNAKE_HEAD = 3004;
    const int START_BODY = 1;
    const int END_BODY = 1002;
    const int FRUIT = 1025;

    const char CH_EMPTY = '.';
    const char CH_HEAD = 'O';
    const char BODY = '#';
    const char CH_FRUIT = '*';

    // function prototypes
    int ConvertToInt(string strNum);
    GameStructure iniGame(int Rows, int Cols);
    TwoDarray AllocateMem(int Rows, int Cols);
    int Gen_Random(int Highest, int Lowest);
    void PrintGame(GameStructure& Game, int Rows, int Cols, int& Score);
    void Pause();
    void MoveSnake(GameStructure& Game, int Rows, int Cols, int& Score, char Input);
    bool Is_In_World(int Rows, int Cols, int Dest_Row, int Dest_Col);
    void MoveHead(GameStructure& stcGame, int Dest_Row, int Dest_Col, int Current_Row, int Current_Col);
    bool inBody(GameStructure& stcGame, int Dest_Row, int Dest_Col);
    void MoveBody(GameStructure& stcGame, int Rows, int Cols);
    void DeallocMem(TwoDarray arrGame, int Rows); // keeping the memory cleanup
}

#endif // SNAKE_H_INCLUDED
