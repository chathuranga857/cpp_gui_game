/* This program will implement an GUI application to play a path game
 *
 * Game rules in breif:
 *
 * There are two colors for game peices. In this case, green and red
 * Initially all green pieces are at top row and red pieces are at the bottom row
 * Elapsed timer is started and show the time in mm:ss format
 * Goal is to move all the green pieces to bottom row and red peices to top row.
 * This can be achieved with minimum of 31 moves
 * Moving a game piece over another is not permitted. However,
 * it can be moved along a path of empty spaces, and the move can be as long as
 * such a path exists. App prevents illegal moves, and indicate them to user.
 *
 * implemented by:
 *
 * Student Information;
 *
 * Name: Chathuranga De Sivla (Manikkuge De Silva)
 * Student number: 150963990
 * UserID: vvmade
 * E-Mail: manikkuge.desilva@tuni.fi
 *
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QDebug>
#include <QMainWindow>
#include <vector>
#include <QElapsedTimer>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


private:
    Ui::MainWindow *ui;
    // GameBoard object to play the game
    GameBoard gameBoard_;
    // Start Point for move piece
    Point start_;
    // Destination Point for move piece
    Point dest_;
    // No of moves made so far from the start of the game
    int noOfMoves_ =0;
    // Flag for having a piece selected to move
    bool isPieceSelected_ = false;
    // Elapsed time timer object
    QElapsedTimer elapsedTimer_;
    // Time out timer for updating elapsed time
    QTimer timer_;
    // Record the paused time
    qint64 pausedTime_ = 0;
    // Flag to indicate if the game is on pause
    bool isPaused_ = false;

    // Function to handle all clicks on game pieces in ui
    void on_game_piece_clicks();
    // Function to handle reset button clicks
    void on_reset_clicked();
    // Function to handle pause button clicks
    void on_pause_clicked();
    // Function to handle resume button clicks
    void on_resume_clicked();
    // Update the ui to sync the board with actual game board status
    void update_slots();
    // Update a particular game slot in ui with a given color
    void set_slot_color(int, QString);


};
#endif // MAINWINDOW_HH
