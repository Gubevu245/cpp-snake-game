#include "Snake.h"

namespace SnakeSpace
{
    // convert string to int
    int ConvertToInt(string strNum)
    {
        int Num;
        stringstream ss {strNum};
        ss >> Num;
        if (ss.fail())
        {
            cerr << "Could not convert " << strNum << " To an integer" << endl;
            exit(ARG_CONV);
        }
        return Num;
    }

    // generate random number
    int Gen_Random(int Lowest, int Highest)
    {
        int Range = Highest - Lowest + 1;
        return (rand() % Range + Lowest);
    }

    // set up the 2D array
    TwoDarray AllocateMem(int Rows, int Cols)
    {
        TwoDarray arrGame;
        arrGame = new OneDarray[Rows];
        for (int a = 0; a < Rows; a++)
        {
            arrGame[a] = new int[Cols];
        }

        for (int a = 0; a < Rows; a++)
        {
            for (int c = 0; c < Cols; c++)
            {
                arrGame[a][c] = EMPTY;
            }
        }

        // spawn first fruit
        int FRow = Gen_Random(0, Rows - 1);
        int FCol = Gen_Random(0, Cols - 1);

        while(arrGame[FRow][FCol] != EMPTY)
        {
            FRow = Gen_Random(0, Rows - 1);
            FCol = Gen_Random(0, Cols - 1);
        }
        arrGame[FRow][FCol] = FRUIT;
        return arrGame;
    }

    // setup the game variables
    GameStructure iniGame(int Rows, int Cols)
    {
        GameStructure WorldGame;
        WorldGame.arrWorld = AllocateMem(Rows, Cols);
        WorldGame.Rows = Rows;
        WorldGame.Cols = Cols;
        WorldGame.Length = 0;
        WorldGame.Score = 0;

        // spawn snake head
        WorldGame.Prow = Gen_Random(0, Rows - 1);
        WorldGame.Pcol = Gen_Random(0, Cols - 1);

        while(WorldGame.arrWorld[WorldGame.Prow][WorldGame.Pcol] != EMPTY)
        {
            WorldGame.Prow = Gen_Random(0, Rows - 1);
            WorldGame.Pcol = Gen_Random(0, Cols - 1);
        }
        WorldGame.arrWorld[WorldGame.Prow][WorldGame.Pcol] = SNAKE_HEAD;
        WorldGame.enStatus = RUNNING;
        return WorldGame;
    }

    void Pause()
    {
        cout << "Press any key to continue " << endl;
        cin.get();
    }

    // draw the grid
    void PrintGame(GameStructure& Game, int Rows, int Cols, int& Score)
    {
        // keeping the cursor trick so it doesn't flicker when you press enter!
        cout << "\033[H";

        for (int a = 0; a < Rows; a++)
        {
            for (int c = 0; c < Cols; c++)
            {
                switch(Game.arrWorld[a][c])
                {
                case EMPTY:
                    cout << CH_EMPTY << " ";
                    break;
                case FRUIT:
                    cout << CH_FRUIT << " ";
                    break;
                case SNAKE_HEAD:
                    cout << CH_HEAD << " ";
                    break;
                default:
                    cout << BODY << " ";
                }
            }
            cout << endl;
        }
        cout << "\nControls: W, A, S, D" << endl;
        cout << "Game Score is: " << Game.Score << "   " << endl;
    }

    // check boundaries
    bool Is_In_World(int Rows, int Cols, int Dest_Row, int Dest_Col)
    {
        if (Dest_Row >= 0 && Dest_Row < Rows && Dest_Col >= 0 && Dest_Col < Cols)
        {
            return true;
        }
        return false;
    }

    // handle head logic
    void MoveHead(GameStructure& stcGame, int Dest_Row, int Dest_Col, int Current_Row, int Current_Col)
    {
        if(inBody(stcGame, Dest_Row, Dest_Col))
        {
            stcGame.enStatus = LOST;
            return;
        }
        else
        {
            stcGame.arrWorld[Dest_Row][Dest_Col] = SNAKE_HEAD;
            stcGame.arrWorld[Current_Row][Current_Col] = stcGame.Length;
            stcGame.Prow = Dest_Row;
            stcGame.Pcol = Dest_Col;
        }
    }

    // check if we crashed into ourselves
    bool inBody(GameStructure& stcGame, int Dest_Row, int Dest_Col)
    {
        bool blnBody = false;
        if (stcGame.arrWorld[Dest_Row][Dest_Col] >= START_BODY && stcGame.arrWorld[Dest_Row][Dest_Col] <= END_BODY)
        {
            blnBody = true;
        }
        return blnBody;
    }

    // age the body parts so the tail disappears
    void MoveBody(GameStructure& stcGame, int Rows, int Cols)
    {
        for (int a = 0; a < Rows; a++)
        {
            for (int c = 0; c < Cols; c++)
            {
                if(stcGame.arrWorld[a][c] >= START_BODY && stcGame.arrWorld[a][c] <= END_BODY)
                {
                    stcGame.arrWorld[a][c]--;
                }
            }
        }
    }

    // process the move
    void MoveSnake(GameStructure& Game, int Rows, int Cols, int& Score, char Input)
    {
        int DRow = Game.Prow;
        int DCol = Game.Pcol;

        switch(Input)
        {
        case 'w':
            DRow--;
            break;
        case 's':
            DRow++;
            break;
        case 'd':
            DCol++;
            break;
        case 'a':
            DCol--;
            break;
        default:
            cerr << "Wrong input, Please try again" << endl;
            Pause();
            return;
        }

        if (Is_In_World(Rows, Cols, DRow, DCol))
        {
            if (Game.arrWorld[DRow][DCol] == FRUIT)
            {
                // ate a fruit
                Game.Score++;
                Game.Length++;
                MoveHead(Game, DRow, DCol, Game.Prow, Game.Pcol);

                // spawn new fruit
                int FRow = Gen_Random(0, Rows - 1);
                int FCol = Gen_Random(0, Cols - 1);

                while(Game.arrWorld[FRow][FCol] != EMPTY)
                {
                    FRow = Gen_Random(0, Rows - 1);
                    FCol = Gen_Random(0, Cols - 1);
                }
                Game.arrWorld[FRow][FCol] = FRUIT;
            }
            else
            {
                // just moving normally
                MoveBody(Game, Rows, Cols);
                MoveHead(Game, DRow, DCol, Game.Prow, Game.Pcol);
            }
        }
        else
        {
            // hit a wall
            Game.enStatus = LOST;
        }
    }

    // free memory to stop leaks
    void DeallocMem(TwoDarray arrGame, int Rows)
    {
        for (int a = 0; a < Rows; a++)
        {
            delete[] arrGame[a];
        }
        delete[] arrGame;
        arrGame = nullptr;
    }
}
