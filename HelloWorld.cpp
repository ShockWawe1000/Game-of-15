#include <iostream>
#include <array>
#include <random>

/*
15 tile game

Goals:

Create Display
Create Board Generator
Create Controls
Create Win/Lose logic

*/


class Tile
{
    int tile{};
    bool m_isEmpty{ true };
public:
    Tile(int a): tile{a} {if (tile>0){m_isEmpty=false;} }
    
    bool isEmpty()
    {
        return m_isEmpty;
    }

    int getNum()
    {
        return tile;
    }
    friend std::ostream& operator<<(std::ostream& out, const Tile& a);
    friend class Board;
    operator int() const { return tile; }
};


class Board
{
    std::array <std::array<Tile, 4>, 4> solvedBoard{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 };
    std::array <std::array<Tile,4>,4> board {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    
public:
    bool checkGameState()
    {
        for (int x = 0; x < board.size(); ++x)
        {
            for (int y = 0; y < board.size(); ++y)
            {

                if (static_cast<int>(board[x][y]) != solvedBoard[x][y])
                {
                    return false;
                }
            }
        }
        return true;
    }

    void randomBoard()
    {
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution direction{ 1, 4 };
        for (int i=0;i<1000;++i)
            {                
                    if (direction(mt) == 1)   { moveW();}
                    else if (direction(mt) == 2){moveA();}
                    else if (direction(mt) == 3){moveS();}
                    else { moveD(); }
            }
    }

    friend std::ostream& operator<<(std::ostream& out, const Board& a);

    void moveW()
    {
        for (int x = 1; x < board.size(); ++x)
        {
            for (int y = 0; y < board.size(); ++y)
            {

                if (static_cast<int>(board[x][y]) == 0)
                {
                    std::swap(board[x - 1][y], board[x][y]);
                    break;
                }
            }
        }
    }

    void moveA()
    {
        for (int x = 0; x < board.size(); ++x)
        {
            for (int y = 1; y < board.size(); ++y)
            {

                if (static_cast<int>(board[x][y]) == 0)
                {
                    std::swap(board[x][y - 1], board[x][y]);
                    break;
                }
            }
        }
    }

    void moveS()
    {
        for (int y = 0; y < board.size(); ++y)
        {
            for (int x = 0; x < board.size() - 1; ++x)
            {



                if (static_cast<int>(board[x][y]) == 0)
                {
                    std::swap(board[x][y], board[x + 1][y]);
                    break;
                }

            }

        }
    }

    void moveD()
    {
        for (int x = 0; x < board.size(); ++x)
        {
            for (int y = 0; y < board.size() - 1; ++y)
            {

                if (static_cast<int>(board[x][y]) == 0)
                {
                    std::swap(board[x][y + 1], board[x][y]);
                    break;
                }
            }
        }
    }

    void getUserInput()
    {
        bool loop = true;
        static char prevInput{ 'q' };
       

        while (loop == true)
        {
                char input;
                std::cin >> input;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (input == 'q')
                {
                    std::cout << "Valid command: " << input;
                    loop = false;
                    prevInput = input;
                 }
                        {
                                if (input == 'a' || input == 'A')
                                {
                                    std::cout << "Valid command: " << input;
                                    loop = false;
                                    prevInput = input;
                                    moveD();
                                   

                                }
                                else if (input == 'w' || input == 'W')
                                {
                                    std::cout << "Valid command: " << input;
                                    loop = false;
                                    prevInput = input;
                                    moveS();

                                }
                                else if (input == 'd' || input == 'D')
                                {
                                    std::cout << "Valid command: " << input;
                                    loop = false;
                                    prevInput = input;
                                    moveA();
                                }
                                else if (input == 's' || input == 'S')
                                {
                                    std::cout << "Valid command: " << input;
                                    loop = false;
                                    prevInput = input;
                                    moveW();
                                }
                                
                                else
                                    std::cout << "Invalid input";
                        }
            
                
        }
         
    }
};

std::ostream& operator<<(std::ostream& out, const Board& a)
{
    system("CLS");
    out << "\t   Game of 15! \n";
    out << "\n\t- - - - - - - - - \n";
    out << "\t|";
    for (int x = 0; x < a.board.size(); ++x)
    {

        for (int y = 0; y < a.board.size(); ++y)
        {
            
            out << a.board[x][y];
            if (y == 3)
            {
                out << '|';
                if (x == 0)
                    std::cout << "\t\t Control Schema:    W";

                    if (x == 1)
                        std::cout << "\t\t                  A S D";

                    if(x==3)
                        std::cout << "\t\t    Sort it so the numbers go 1-15";

                    out << "\n";
                    if(x!=3)
                    out << "\t|";
            }

        }
    }
    out << "\t- - - - - - - - -  ";
    std::cout << "\n\nEnter your move: ";
   
    return out;
}


std::ostream& operator<<(std::ostream& out, const Tile& a)
{
    if (a.tile > 9)
        out << " " << a.tile << " ";
    else if (a.tile > 0)
        out << "  " << a.tile << " ";
    else
        out << "    ";
    return out;
}



int main()
{
    Board board{};
    std::cout << board;
    board.randomBoard();
    std::cout << board;
    bool win = board.checkGameState();
    while (win == false)
    {
        board.getUserInput();
        std::cout << board;
        win = board.checkGameState();
    }
    std::cout << "\n\n\tYou won\n";
   
    return 0;
}
