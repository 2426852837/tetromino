#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>
#include <QDesktopWidget>

#include "nexttetrominobox.h"
#include "ctetromino.h"
#include "tetrominobox.h"
#include "mainwindow.h"
#include <QTimer>
#include <QPalette>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QFontDatabase>
#include <QMediaPlayer>


#define STATUS_ON 0     //游戏正常进行
#define STATUS_PAUSE 1  //游戏暂停
#define STATUS_OFF 2    //游戏未开始
#define STATUS_END 3    //游戏结束

#define NORMAL 0
#define REVERSE 1

namespace Ui {
class GameInterface;
}

class GameInterface: public QMainWindow
{
    Q_OBJECT
public:
    GameInterface(){}
    GameInterface(QWidget *parent);    //
    ~GameInterface();                           //
    void refreshScore();                        //
    void setTimer();                            //
    void keyPressEvent(QKeyEvent *event);       //
    void keyReleaseEvent(QKeyEvent *e);         //
    void changeEvent(QEvent *event);            //
    void closeEvent(QCloseEvent *event);        //
    void mousePressEvent(QMouseEvent *event);   //
    void mouseReleaseEvent(QMouseEvent *e);     //
    void mouseMoveEvent(QMouseEvent *e);        //
    void wheelEvent(QWheelEvent *e);            //
public slots:
    void onTimer();                             //
public slots:
    void onRepeatTimer();                       //
private:
    int speed;                                  //
    int nextStage;                              //
    Qt::Key key;                                //
    Qt::Key keytemp;                            //
    int status;                                 //
    int gamestatus;
    CTetromino *tetris;                         //
    QTimer *timer;                              //
    QTimer *repeatTimer;                        //

    TetrisBox *tetrisBox;                       //
    NextTetrisBox *nextTetrisBox;               //
    QGridLayout *mainLayout;                    //

    QLabel *scoreLabel;
    QLabel *diffTitleLabel;
    QLabel *diffLabel;
    QMessageBox *box1=new QMessageBox();

    QPoint start;
    QPoint movement;
    QPoint end;
signals:
    void ExitWin();
};

#endif // GAMEINTERFACE_H
