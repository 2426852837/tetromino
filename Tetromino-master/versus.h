#ifndef VERSUS_H
#define VERSUS_H

#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QList>

#include "nexttetrominobox.h"
#include "ctetromino.h"
#include "tetrominobox.h"
#include <QTimer>
#include <QPalette>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QFontDatabase>
#include "gameinterface.h"

#define STATUS_ON 0     //游戏正常进行
#define STATUS_PAUSE 1  //游戏暂停
#define STATUS_OFF 2    //游戏未开始
#define STATUS_END 3    //游戏结束

#define PLAYER_START 0
#define PLAYER_END 1

namespace Ui {
class versus;
}

class versus: public QMainWindow
{
    Q_OBJECT
public:
    explicit versus(QWidget *parent);
    ~versus(){}
    void refreshScore();                        //
    void keyPressEvent(QKeyEvent *event);       //
    void keyReleaseEvent(QKeyEvent *e);         //
    void changeEvent(QEvent *event);            //
    void closeEvent(QCloseEvent *event);        //
    void gameOver();
public slots:
    void onTimer();                             //
public slots:
    void onTimer4p2();
public slots:
    void onRepeatTimer();
private:
    int speed4p2;
    int nextStage4p2;
    CTetromino *tetris4p2;
    QTimer *timer4p2;
    TetrisBox *tetrisBox4p2;
    NextTetrisBox *nextTetrisBox4p2;
    QLabel *scoreTitleLabel4p2;
    QLabel *scoreLabel4p2;
    QLabel *diffTitleLabel4p2;
    QLabel *diffLabel4p2;
    QLabel *nextTetrisLabel4p2;
    QList<Qt::Key> pressedKeyS;

    int speed;                                  //
    int nextStage;                              //
    int status;                                 //
    int play1Status;
    int play2Status;

    CTetromino *tetris;                         //
    QTimer *timer;                              //
    QTimer *repeatTimer;                        //

    TetrisBox *tetrisBox;                       //
    NextTetrisBox *nextTetrisBox;               //
    QGridLayout *mainLayout;                    //

    QLabel *nextTetrisLabel;                    //
    QLabel *controlLabel;                       //
    QLabel *w_Label;                           //
    QLabel *s_Label;                         //
    QLabel *a_Label;                         //
    QLabel *d_Label;
    QLabel *up_Label;                           //
    QLabel *down_Label;                         //
    QLabel *left_Label;                         //
    QLabel *right_Label;
    QLabel *enter_controlLabel;
    QLabel *pause_controlLabel;
    QLabel *restart_controlLabel;
    QLabel *exit_controlLabel;
    QLabel *scoreTitleLabel;
    QLabel *scoreLabel;
    QLabel *diffTitleLabel;
    QLabel *diffLabel;
    QLabel *spaceLabel;
    QLabel *backspaceLabel;
    QMessageBox *box1=new QMessageBox();
signals:
    void ExitWin();
};

#endif // VERSUS_H
