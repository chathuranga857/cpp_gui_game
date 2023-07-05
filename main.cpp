
#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


/*
#include "gameboard.hh"
#include <iostream>
#include <vector>

using namespace std;

const string INPUT_TEXT = "Enter start point (x, y) and destination point (x, y), or q to quit: ";
const string INVALID_POINT = "Invalid start/destination point.";
//const string BUTTON_MISSING = "Button missing in start point.";
//const string NOT_EMPTY = "Destination point is not empty.";
const string IDENTICAL_POINTS = "Given points are the same.";   // Actually useless
const string CANNOT_MOVE = "There is no path between start point and destination point.";
const string GAME_OVER = "Game over. Congratulations!";
const string MOVES_MADE = " move(s) made.";


// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid point later).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Enables the user to play the game.
// Until the game is over, reads user commands and moves the buttons,
// the user desires, if such is possible.
// After each move, prints the game board again.
// When the game is over or the user gives the quit command,
// prints the number of moves made.
void play_game(GameBoard& g)
{
    Point p1 = {0, 0};
    Point p2 = {0, 0};
    string command = "";
    unsigned int total_moves = 0;
    g.print();
    while(not g.is_game_over())
    {
        cout << INPUT_TEXT;
        cin >> command;
        if(command == "q" or command == "Q")
        {
            cout << total_moves << MOVES_MADE << endl;
            return;
        }
        p1.x = stoi_with_check(command) - 1;
        cin >> command;
        p1.y = stoi_with_check(command) - 1;
        cin >> command;
        p2.x = stoi_with_check(command) - 1;
        cin >> command;
        p2.y = stoi_with_check(command) - 1;
        if(not g.is_valid_point(p1) or not g.is_valid_point(p2))
        {
            cout << INVALID_POINT << endl;
            continue;
        }
        //if(g.at(p1.y).at(p1.x) != GREEN and g.at(p1.y).at(p1.x) != RED)
        Slot_type slot_p1 = g.which_slot(p1);
        if(slot_p1 != GREEN and slot_p1 != RED)
        {
            //cout << BUTTON_MISSING << endl;
            cout << INVALID_POINT << endl;
            continue;
        }
        //if(g.at(p2.y).at(p2.x) != EMPTY)
        if(g.which_slot(p2) != EMPTY)
        {
            //cout << NOT_EMPTY << endl;
            cout << INVALID_POINT << endl;
            continue;
        }
        if(p1 == p2)
        {
            // This is never reached
            cout << IDENTICAL_POINTS << endl;
            continue;
        }
        if(g.move(p1, p2))
        {
            ++total_moves;
            g.print();
        }
        else
        {
            cout << CANNOT_MOVE << endl;
        }
    }
    cout << GAME_OVER << endl;
    cout << total_moves << MOVES_MADE << endl;
}

int main()
{
    GameBoard grid;
    //grid.init_grid(grid);
    play_game(grid);

    return 0;
}
*/
