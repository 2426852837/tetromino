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

namespace Ui {
class GameInterface;
}

class GameInterface: public QMainWindow
{
    Q_OBJECT
public:
    explicit GameInterface(QWidget *parent);
    ~GameInterface();
    void refreshScore();
    void setTimer();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *e);
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
public slots:
    void onTimer();
public slots:
    void onRepeatTimer();
private:
    int speed;
    int nextStage;
    Qt::Key key;
    Qt::Key keytemp;
    int status;
    CTetromino tetris;
    QTimer *timer;
    QTimer *repeatTimer;

    TetrisBox *tetrisBox;
    NextTetrisBox *nextTetrisBox;
    QGridLayout *mainLayout;

    QLabel *nextTetrisLabel;
    QLabel *controlLabel;
    QLabel *up_Label;
    QLabel *down_Label;
    QLabel *left_Label;
    QLabel *right_Label;
    QLabel *enter_controlLabel;
    QLabel *pause_controlLabel;
    QLabel *restart_controlLabel;
    QLabel *exit_controlLabel;
    QLabel *scoreTitleLabel;
    QLabel *scoreLabel;
    QLabel *diffTitleLabel;
    QLabel *diffLabel;
    QMessageBox *box1=new QMessageBox();
};

#endif // GAMEINTERFACE_H
