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

#include "gameboard.hh"
#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textBrowserInfo->setText("Game Started..");

    // connect all game piece push buttons signals to the slot
    connect(ui->slot_1x1, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_1x2, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_1x3, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_1x4, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_2x2, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_3x2, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_3x3, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_4x2, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_5x1, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_5x2, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_5x3, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);
    connect(ui->slot_5x4, &QPushButton::clicked,
            this, &MainWindow::on_game_piece_clicks);

    // connect reset button signal to reset slot
    connect(ui->pushButtonReset, &QPushButton::clicked,
            this, &MainWindow::on_reset_clicked);
    // connect pause button signal to pause slot
    connect(ui->pushButtonPause, &QPushButton::clicked,
            this, &MainWindow::on_pause_clicked);
    // connect resume button signal to resume slot
    connect(ui->pushButtonResume, &QPushButton::clicked,
            this, &MainWindow::on_resume_clicked);

    // start elapsed time timer and timeout timer
    // and connect to elapsed time desplay
    connect(&timer_, &QTimer::timeout, this, [this]() {
        // Calculate elapsed time in minutes and seconds
        int elapsedSeconds = (pausedTime_ + elapsedTimer_.elapsed() ) / 1000;
        int minutes = elapsedSeconds / 60;
        int seconds = elapsedSeconds % 60;

        // Update the QLabel widget with the elapsed time in minutes and seconds
        ui->labelET->setText(QString("  %1:%2").arg(minutes,2,10,
                                                    QChar('0')).arg(seconds, 2, 10, QChar('0')));
    });
    elapsedTimer_.start();
    timer_.start(100);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_game_piece_clicks()
{
    //refresh the ui board colors at each clicks
    update_slots();
    // get name of the clicked slot
    QString buttonName = sender()->objectName();
    // convert to std string
    std::string buttonNameS = buttonName.toUtf8().constData();
    // get indexes of clicked button by button name
    char cx = buttonNameS.at(5);
    char cy = buttonNameS.at(7);
    // row number
    int x = int(cx) - int('0');
    // column number
    int y = int(cy) - int('0');

    // defining the Point which which was clicked
    //(row and column indexes to be interchanged)
    Point clickedPoint;
    clickedPoint.x = y-1;
    clickedPoint.y = x-1;

    // assigning the slot number, which starting from "1" for (0,0) point
    // upto 20 for (4,3) point
    int slotNumber = (x-1)*4 + y;

    // get slot type of clicked slot
    Slot_type clickedColor = gameBoard_.which_slot(clickedPoint);

    // select the piece to move if it is a game piece (RED or GREEN)
    if(clickedColor == RED)
    {
        start_.x = clickedPoint.x;
        start_.y = clickedPoint.y;
        ui->textBrowserInfo->setText("Red piece selected to move");
        isPieceSelected_ = true;
        // highligt the selected piece
        QString clr = "rgb(150, 0, 0)";
        set_slot_color(slotNumber, clr);
    }
    else if(clickedColor == GREEN)
    {
        start_.x = clickedPoint.x;
        start_.y = clickedPoint.y;
        ui->textBrowserInfo->setText("Green piece selected to move");
        isPieceSelected_ = true;
        // highligt the selected piece
        QString clr = "rgb(0, 150, 0)";
        set_slot_color(slotNumber, clr);
    }

    // if a piece is already selected and then an empty slot is selected,
    // then the selected piece move to the empty slot
    else if(clickedColor == EMPTY && isPieceSelected_)
    {
        dest_.x = clickedPoint.x;
        dest_.y = clickedPoint.y;

        // call the move function in game board
        bool isMoved = gameBoard_.move(start_, dest_);
        // if the move is valide and succeede
        if (isMoved)
        {
            ui->textBrowserInfo->setText("Last Move : Succeeded!");
            isPieceSelected_ = false;
            // update the UI for the new board status and increase move count by 1
            update_slots();
            noOfMoves_++;
            ui->lcdMoves->display(noOfMoves_);

            // check if the game is over
            bool isWon = gameBoard_.is_game_over();
            if(isWon)
            {
                ui->textBrowserInfo->setText("Congratulations..!!"
                                             "You won the game.!");
                timer_.stop();
                if(noOfMoves_<=31)
                {
                    // if game is over and completed with minimum number of
                    // movements (31), change the background color of the board
                    ui->centralwidget->setStyleSheet("background-color:"
                                                     "rgb(0, 0, 200)");
                    ui->textBrowserInfo->setText("Congratulations..!!"
                                                 "You won with minimum moves.!");
                }
            }
        }
        // if the move is invalid
        else
        {
            ui->textBrowserInfo->setText("Last Move : Invalid!");
            qDebug()<<"Last Move : Invalid";
            isPieceSelected_ = false;
        }
    }

}

// Implementation of game reset slot function
void MainWindow::on_reset_clicked()
{
    gameBoard_.reset_game();
    isPieceSelected_ = false;
    ui->centralwidget->setStyleSheet("");
    update_slots();
    noOfMoves_ = 0;
    ui->lcdMoves->display(noOfMoves_);
    pausedTime_ = 0;
    elapsedTimer_.restart();
    timer_.start(100);
    ui->labelET->setText("  00:00");

    // In case if reset is clicked while the game is on pause,
    // connect all disconneted signals and slots
    if(isPaused_)
    {
        connect(ui->slot_1x1, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_1x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_1x3, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_1x4, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_2x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_3x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_3x3, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_4x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_5x1, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_5x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_5x3, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_5x4, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
    }

    isPaused_ = false;

    ui->textBrowserInfo->setText("Game Reset!");

}

void MainWindow::on_pause_clicked()
{
    if(not isPaused_)
    {
        pausedTime_ += elapsedTimer_.elapsed();
        timer_.stop();

        disconnect(ui->slot_1x1, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_1x2, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_1x3, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_1x4, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_2x2, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_3x2, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_3x3, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_4x2, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_5x1, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_5x2, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_5x3, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);
        disconnect(ui->slot_5x4, &QPushButton::clicked,
                   this, &MainWindow::on_game_piece_clicks);

        ui->textBrowserInfo->setText("Game Paused!");
    }

    isPaused_ = true;

}

void MainWindow::on_resume_clicked()
{
    if(isPaused_)
    {
        elapsedTimer_.restart();
        timer_.start();

        // connect all disconnected signals and slots
        connect(ui->slot_1x1, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_1x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_1x3, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_1x4, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_2x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_3x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_3x3, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_4x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_5x1, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_5x2, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_5x3, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);
        connect(ui->slot_5x4, &QPushButton::clicked,
                this, &MainWindow::on_game_piece_clicks);

        ui->textBrowserInfo->setText("Game Resumed..");
    }

    isPaused_ = false;
}

// Implementation of updating ui board to sync with new game board update
void MainWindow::update_slots()
{
    int slotNumber = 0;

    // looping row number
    for (int i = 0; i<5; i++)
    {
        // inner loop for column number
        for (int j = 0; j<4; j++)
        {
            // assigning the slot number based on the point
            slotNumber = i*4 + j + 1;
            Point point;
            point.x = j;
            point.y = i;

            Slot_type slotType = gameBoard_.which_slot(point);
            QString slotColor="";

            switch (slotType) {
            case GREEN:
                slotColor = "rgb(0, 255, 0)";
                break;
            case RED:
                slotColor = "rgb(255, 0, 0)";
                break;
            case EMPTY:
                slotColor = "rgb(255, 255, 255)";
                break;
            default:
                break;
            }
            if (slotColor != "")
            {
                set_slot_color(slotNumber, slotColor);
            }

        }
    }
}

// Implementation of function for setting the slot color.
// inputs are the slot number and the color in QString
void MainWindow::set_slot_color(int slotNo, QString slotColor)
{
    switch (slotNo) {
    case 1:
        ui->slot_1x1->setStyleSheet("Height:50; Width : 50;border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 2:
        ui->slot_1x2->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 3:
        ui->slot_1x3->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 4:
        ui->slot_1x4->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 6:
        ui->slot_2x2->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 10:
        ui->slot_3x2->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 11:
        ui->slot_3x3->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 14:
        ui->slot_4x2->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 17:
        ui->slot_5x1->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 18:
        ui->slot_5x2->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 19:
        ui->slot_5x3->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    case 20:
        ui->slot_5x4->setStyleSheet("Height:50; Width : 50; border-radius: 25%;"
                                    "background-color:" + slotColor);
        break;
    default:
        break;
    }
}

