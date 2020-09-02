#include "versus.h"

versus::versus(QWidget *parent)
{
    //声明与赋予初始值
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QPalette pal = this->palette();
    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font("Microsoft YaHei", 15, 75);
    QWidget *widget = new QWidget(this);

    play1Status = PLAYER_END;
    play2Status = PLAYER_END;
    status = STATUS_OFF;
    nextStage = 100;
    nextStage4p2 = 100;
    speed = 500;
    speed4p2 = 500;
    mainLayout = new QGridLayout;

    //实例化部分

    //界面组件实例化
    tetris = new CTetromino;
    tetris4p2 = new CTetromino;
    tetrisBox = new TetrisBox;
    tetrisBox4p2 = new TetrisBox;
    nextTetrisBox = new NextTetrisBox;
    nextTetrisBox4p2 = new NextTetrisBox;
    QLabel *nextTetrisLabel = new QLabel(tr("<font color = white>NEXT：</font>"));
    nextTetrisLabel4p2 = new QLabel(tr("<font color = white>NEXT：</font>"));
    QLabel *controlLabel = new QLabel(tr("<font color = white>CONTROL：</font>"));
    QLabel *w_Label = new QLabel(tr("<font color = white>W-ROTATE</font>"));
    QLabel *a_Label = new QLabel(tr("<font color = white>S-DOWN</font>"));
    QLabel *s_Label = new QLabel(tr("<font color = white>A-LEFT</font>"));
    QLabel *d_Label = new QLabel(tr("<font color = white>D-RIGHT</font>"));
    QLabel *up_Label = new QLabel(tr("<font color = white>↑-ROTATE</font>"));
    QLabel *down_Label = new QLabel(tr("<font color = white>↓-DOWN</font>"));
    QLabel *left_Label = new QLabel(tr("<font color = white>←-LEFT</font>"));
    QLabel *right_Label = new QLabel(tr("<font color = white>→-RIGHT</font>"));
    QLabel *spaceLabel = new QLabel(tr("<font color = white>SPACE-SKIP</font>"));
    QLabel *backspaceLabel = new QLabel(tr("<font color = white>BACKSPACE-SKIP</font>"));
    QLabel *enter_controlLabel = new QLabel(tr("<font color = white>ENTER-START</font>"));
    QLabel *pause_controlLabel = new QLabel(tr("<font color = white>P-PAUSE</font>"));
    QLabel *restart_controlLabel = new QLabel(tr("<font color = white>R-RESTART</font>"));
    QLabel *exit_controlLabel = new QLabel(tr("<font color = white>ESC-EXIT</font>"));
    QLabel *scoreTitleLabel = new QLabel(tr("<font color = white>P1 SCORE：</font>"));
    scoreLabel = new QLabel(tr("<font color = white>0</font>"));
    QLabel *scoreTitleLabel4p2 = new QLabel(tr("<font color = white>P2 SCORE：</font>"));
    scoreLabel4p2 = new QLabel(tr("<font color = white>0</font>"));
    QLabel *diffTitleLabel = new QLabel(tr("<font color = white>P1 DIFFICULTY:</font>"));
    diffLabel = new QLabel(tr("<font color = white>0</font>"));
    QLabel *diffTitleLabel4p2 = new QLabel(tr("<font color = white>P2 DIFFICULTY:</font>"));
    diffLabel4p2 = new QLabel(tr("<font color = white>0</font>"));
    //计时器实例化
    timer = new QTimer(this);
    timer4p2 = new QTimer(this);
    repeatTimer = new QTimer(this);
    //实例化部分结束

    //字体导入
    font.setFamily(fontFamilies.at(0));

    //为文字标签设置字体
    nextTetrisLabel->setFont(font);
    nextTetrisLabel4p2->setFont(font);
    controlLabel->setFont(font);
    w_Label->setFont(font);
    a_Label->setFont(font);
    s_Label->setFont(font);
    d_Label->setFont(font);
    up_Label->setFont(font);
    down_Label->setFont(font);
    left_Label->setFont(font);
    right_Label->setFont(font);
    enter_controlLabel->setFont(font);
    pause_controlLabel->setFont(font);
    restart_controlLabel->setFont(font);
    exit_controlLabel->setFont(font);
    scoreTitleLabel->setFont(font);
    scoreLabel->setFont(font);
    scoreTitleLabel4p2->setFont(font);
    scoreLabel4p2->setFont(font);
    diffLabel->setFont(font);
    diffTitleLabel->setFont(font);
    diffTitleLabel4p2->setFont(font);
    diffLabel4p2->setFont(font);
    spaceLabel->setFont(font);
    backspaceLabel->setFont(font);

    //设置游戏界面背景
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/game_bg.png")));
    setPalette(pal);

    //设置布局
    mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(50);
    mainLayout->setVerticalSpacing(20);
    mainLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(nextTetrisLabel, 15, 3);
    mainLayout->addWidget(nextTetrisLabel4p2, 15, 7);
    mainLayout->addWidget(nextTetrisBox, 16, 3, 1, 2);
    mainLayout->addWidget(nextTetrisBox4p2, 16, 7, 1, 2);
    mainLayout->addWidget(controlLabel, 0, 0, 1, 1);
    mainLayout->addWidget(w_Label, 0, 1, 1, 1);
    mainLayout->addWidget(s_Label, 1, 1, 1, 1);
    mainLayout->addWidget(a_Label, 1, 0, 1, 1);
    mainLayout->addWidget(d_Label, 1, 2, 1, 1);
    mainLayout->addWidget(up_Label, 0, 6, 1, 1);
    mainLayout->addWidget(down_Label, 1, 6, 1, 1);
    mainLayout->addWidget(left_Label, 1, 5, 1, 1);
    mainLayout->addWidget(right_Label, 1, 7, 1, 1);
    mainLayout->addWidget(spaceLabel, 0, 3, 1, 1);
    mainLayout->addWidget(backspaceLabel, 0, 7, 1, 1);
    mainLayout->addWidget(restart_controlLabel, 0, 2, 1, 1);
    mainLayout->addWidget(enter_controlLabel, 0, 4, 1, 1);
    mainLayout->addWidget(pause_controlLabel, 1, 3, 1, 1);
    mainLayout->addWidget(exit_controlLabel, 1, 4, 1, 1);
    mainLayout->addWidget(tetrisBox, 3, 1, 14, 2);
    mainLayout->addWidget(tetrisBox4p2, 3, 5, 14, 2);
    mainLayout->addWidget(scoreTitleLabel, 7, 3);
    mainLayout->addWidget(scoreTitleLabel4p2, 7, 7);
    mainLayout->addWidget(scoreLabel, 7, 4);
    mainLayout->addWidget(scoreLabel4p2, 7, 8);
    mainLayout->addWidget(diffTitleLabel, 8,3);
    mainLayout->addWidget(diffTitleLabel4p2, 8, 7);
    mainLayout->addWidget(diffLabel, 8, 4);
    mainLayout->addWidget(diffLabel4p2, 8, 8);

    widget->setLayout(mainLayout);
    setCentralWidget(widget);
    setWindowIcon(QIcon(":/res/img/title.png"));

    //初始化
    nextTetrisBox->updateNextTetris(*tetris);
    nextTetrisBox4p2->updateNextTetris(*tetris);
    setWindowTitle(tr("Tetromino - OFF"));

    //链接计时器
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    connect(timer4p2, SIGNAL(timeout()),this, SLOT(onTimer4p2()));
    connect(repeatTimer, SIGNAL(timeout()), this, SLOT(onRepeatTimer()));
}

void versus::refreshScore()//刷新游戏分数标签
{
    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font("Microsoft YaHei", 15, 75);
    font.setFamily(fontFamilies.at(0));

    QString str4p1;
    QString strDiff4p1;
    int score4p1 = tetris->getScore();
    int diff4p1 = tetris->getDiff();
    str4p1 = QString::number(score4p1);
    strDiff4p1 = QString::number(diff4p1);
    scoreLabel->setText(str4p1);
    if(score4p1>=nextStage&&speed>=100)
    {
        nextStage+=100;
        speed-=50;
        timer->start(speed);
    }
    diffLabel->setText(strDiff4p1);
    diffLabel->setFont(font);
    diffLabel->setStyleSheet("QLabel{color:white;}");
    scoreLabel->setFont(font);
    scoreLabel->setStyleSheet("QLabel{color:white;}");

    QString str4p2;
    QString strDiff4p2;
    int score4p2 = tetris4p2->getScore();
    int diff4p2 = tetris4p2->getDiff();
    str4p2 = QString::number(score4p2);
    strDiff4p2 = QString::number(diff4p2);
    scoreLabel4p2->setText(str4p2);
    if(score4p2 >= nextStage4p2 && speed4p2 >= 100)
    {
        nextStage4p2+=100;
        speed4p2-=50;
        timer4p2->start(speed4p2);
    }
    diffLabel4p2->setText(strDiff4p2);
    diffLabel4p2->setFont(font);
    diffLabel4p2->setStyleSheet("QLabel{color:white;}");
    scoreLabel4p2->setFont(font);
    scoreLabel4p2->setStyleSheet("QLabel{color:white;}");
}


void versus::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W||event->key() == Qt::Key_Up||event->key() == Qt::Key_S||event->key() == Qt::Key_Down||event->key() == Qt::Key_A||event->key() == Qt::Key_Left||event->key() == Qt::Key_Right||event->key() == Qt::Key_D||event->key() == Qt::Key_Space||event->key() == Qt::Key_Backspace)
    {
        pressedKeyS.append(static_cast<Qt::Key>(event->key()));
        if(!repeatTimer->isActive())
        {
            repeatTimer->start(100);
        }
    }
    else if (event->key() == Qt::Key_Enter||event->key() == Qt::Key_Return)//开始游戏
    {
        if (status == STATUS_PAUSE)
        {
            if(play1Status == PLAYER_START)
                timer->start(speed);
            if(play2Status == PLAYER_START)
                timer4p2->start(speed4p2);
            setWindowTitle(tr("Tetromino - ON"));
        }
        else if (status == STATUS_OFF)
        {
            tetris->createBlock();
            tetrisBox->updateTetris(*tetris);
            nextTetrisBox->updateNextTetris(*tetris);
            tetris4p2->createBlock();
            tetrisBox4p2->updateTetris(*tetris4p2);
            nextTetrisBox4p2->updateNextTetris(*tetris4p2);
            play1Status = PLAYER_START;
            play2Status = PLAYER_START;
            refreshScore();
            status = STATUS_ON;
            setWindowTitle(tr("Tetromino - ON"));
            timer->start(speed);
            timer4p2->start(speed4p2);
        }
        else if (status == STATUS_END)
        {
            tetris->clear();
            tetris->createBlock();
            tetrisBox->updateTetris(*tetris);
            nextTetrisBox->updateNextTetris(*tetris);
            tetris4p2->clear();
            tetris4p2->createBlock();
            tetrisBox4p2->updateTetris(*tetris4p2);
            nextTetrisBox4p2->updateNextTetris(*tetris4p2);
            refreshScore();
            status = STATUS_ON;
            play1Status = PLAYER_START;
            play2Status = PLAYER_START;
            speed = 500;
            speed4p2 = 500;
            nextStage = 100;
            nextStage4p2 = 100;
            setWindowTitle(tr("Tetromino - ON"));
            timer->start(speed);
            timer4p2->start(speed4p2);
        }
        else if (status == STATUS_ON)
        {

        }
    }
    else if (event->key() == Qt::Key_P)
    {
        if (status == STATUS_ON)
        {
            timer->stop();
            timer4p2->stop();
            status = STATUS_PAUSE;
            setWindowTitle(tr("Tetromino - PAUSE"));
        }
    }

    else if (event->key() == Qt::Key_R)
    {
        if(status==STATUS_ON||status==STATUS_PAUSE)
        {
            timer->stop();
            timer4p2->stop();
            QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要重新开始游戏吗，您的分数不会被记录",
                                                                     QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                     QMessageBox::No);


            if(result==QMessageBox::No||result==QMessageBox::Cancel)
            {
                if(status==STATUS_ON)
                {
                    if(play1Status == PLAYER_START)
                        timer->start(speed);
                    if(play2Status == PLAYER_START)
                        timer4p2->start(speed4p2);
                    return;
                }

            }
        }
        tetris->clear();
        tetrisBox->updateTetris(*tetris);
        nextTetrisBox->updateNextTetris(*tetris);
        tetris4p2->clear();
        tetrisBox4p2->updateTetris(*tetris4p2);
        nextTetrisBox4p2->updateNextTetris(*tetris4p2);
        refreshScore();
        speed = 500;
        speed4p2 = 500;
        nextStage = 100;
        nextStage4p2 = 100;
        status = STATUS_OFF;
        play1Status = PLAYER_END;
        play2Status = PLAYER_END;
        setWindowTitle(tr("Tetromino - OFF"));
    }

    else if (event->key() == Qt::Key_Escape)
    {
        timer->stop();
        timer4p2->stop();
        if(status==STATUS_ON||status==STATUS_PAUSE)
        {
            QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要关闭游戏吗?您的分数将不会被记录",
                                                                     QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                     QMessageBox::No);
            if(result==QMessageBox::No||result==QMessageBox::Cancel)
            {
                if(status==STATUS_ON)
                {
                    if(play1Status == PLAYER_START)
                        timer->start(speed);
                    if(play2Status == PLAYER_START)
                        timer4p2->start(speed4p2);
                    return;
                }
            }

        }

        status = STATUS_OFF;
        play1Status = PLAYER_END;
        play2Status = PLAYER_END;
        tetris->clear();
        tetrisBox->updateTetris(*tetris);
        nextTetrisBox->updateNextTetris(*tetris);
        tetris4p2->clear();
        tetrisBox4p2->updateTetris(*tetris4p2);
        nextTetrisBox4p2->updateNextTetris(*tetris4p2);
        refreshScore();
        setWindowTitle(tr("Tetromino - OFF"));
        setVisible(false);
        emit ExitWin();
    }
}

void versus::keyReleaseEvent(QKeyEvent *e)
{

    if(!repeatTimer->isActive()&&pressedKeyS.isEmpty())
    {
        repeatTimer->stop();
    }
    pressedKeyS.removeAll(static_cast<Qt::Key>(e->key()));
}

void versus::onRepeatTimer()
{
    if(pressedKeyS.contains(Qt::Key_W))
    {
        if (status == STATUS_ON&&play1Status == PLAYER_START)
        {
            if (tetris->rotate())
            {
                tetrisBox->updateTetris(*tetris);
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_Up))
    {

        if (status == STATUS_ON&&play2Status == PLAYER_START)
        {
            if (tetris4p2->rotate())
            {
                tetrisBox4p2->updateTetris(*tetris4p2);
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_A))
    {
        if (status == STATUS_ON&&play1Status == PLAYER_START)
        {
            if (tetris->moveToLeft())
            {
                tetrisBox->updateTetris(*tetris);
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_Left))
    {
        if (status == STATUS_ON&&play2Status == PLAYER_START)
        {
            if (tetris4p2->moveToLeft())
            {
                tetrisBox4p2->updateTetris(*tetris4p2);
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_D))
    {
        if (status == STATUS_ON&&play1Status == PLAYER_START)
        {
            if (tetris->moveToRight())
            {
                tetrisBox->updateTetris(*tetris);
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_Right))
    {
        if (status == STATUS_ON&&play2Status == PLAYER_START)
        {
            if (tetris4p2->moveToRight())
            {
                tetrisBox4p2->updateTetris(*tetris4p2);
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_S))
    {
        if (status == STATUS_ON&&play1Status == PLAYER_START)
        {
            if (tetris->moveToBottom())
            {
                tetrisBox->updateTetris(*tetris);
                nextTetrisBox->updateNextTetris(*tetris);
                refreshScore();
            }
            else
            {
                nextStage = 100;
                speed = 500;
                play1Status = PLAYER_END;
                if(play2Status == PLAYER_START)
                {
                    timer->stop();
                }
                else
                {
                    timer->stop();
                    status = STATUS_END;
                    gameOver();
                    setWindowTitle(tr("Tetromino - END"));
                }
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_Down))
    {
        if (status == STATUS_ON&&play2Status == PLAYER_START)
        {
            if (tetris4p2->moveToBottom())
            {
                tetrisBox4p2->updateTetris(*tetris4p2);
                nextTetrisBox4p2->updateNextTetris(*tetris4p2);
                refreshScore();
            }
            else
            {
                nextStage4p2 = 100;
                speed4p2 = 500;
                play2Status = PLAYER_END;
                if(play1Status == PLAYER_START)
                {
                    timer4p2->stop();
                }
                else
                {
                    timer4p2->stop();
                    status = STATUS_END;
                    gameOver();
                    setWindowTitle(tr("Tetromino - END"));
                }
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_Space))
    {
        if(status == STATUS_ON&&play1Status == PLAYER_START)
        {
            if(tetris->moveToEnd())
            {
                tetrisBox->updateTetris(*tetris);
                refreshScore();
            }
            else
            {
                nextStage = 100;
                speed = 500;
                play1Status = PLAYER_END;
                if(play2Status == PLAYER_START)
                {
                    timer->stop();
                }
                else
                {
                    timer->stop();
                    status = STATUS_END;
                    gameOver();
                    setWindowTitle(tr("Tetromino - END"));
                }
            }
        }
    }
    if(pressedKeyS.contains(Qt::Key_Backspace))
    {
        if(status == STATUS_ON&&play2Status == PLAYER_START)
        {
            if(tetris4p2->moveToEnd())
            {
                tetrisBox4p2->updateTetris(*tetris4p2);
                refreshScore();
            }
            else
            {
                nextStage4p2 = 100;
                speed4p2 = 500;
                play2Status = PLAYER_END;
                if(play1Status == PLAYER_START)
                {
                    timer4p2->stop();
                }
                else
                {
                    timer4p2->stop();
                    status = STATUS_END;
                    gameOver();
                    setWindowTitle(tr("Tetromino - END"));
                }
            }
        }
    }
}

void versus::onTimer()
{
    if(tetris->moveToBottom())
    {
        tetrisBox->updateTetris(*tetris);
        nextTetrisBox->updateNextTetris(*tetris);
        refreshScore();
    }
    else
    {
        nextStage = 100;
        speed = 500;
        play1Status = PLAYER_END;
        if(play2Status == PLAYER_START)
        {
            timer->stop();
        }
        else
        {
            timer->stop();
            status = STATUS_END;
            gameOver();
            setWindowTitle(tr("Tetromino - END"));
        }
    }
}

void versus::onTimer4p2()
{
    if(tetris4p2->moveToBottom())
    {
        tetrisBox4p2->updateTetris(*tetris4p2);
        nextTetrisBox4p2->updateNextTetris(*tetris4p2);
        refreshScore();
    }
    else
    {
        nextStage4p2 = 100;
        speed4p2 = 500;
        play2Status = PLAYER_END;
        if(play1Status == PLAYER_START)
        {
            timer4p2->stop();
        }
        else
        {
            timer4p2->stop();
            status = STATUS_END;
            gameOver();
            setWindowTitle(tr("Tetromino - END"));
        }
    }
}

void versus::changeEvent(QEvent *event)
{
    if (event->type() != QEvent::WindowStateChange)
    {
        return;
    }
    if (windowState() == Qt::WindowMinimized)
    {
        if(status==STATUS_ON)
        {
            timer->stop();
            timer4p2->stop();
            status=STATUS_PAUSE;
            setWindowTitle(tr("Tetromino - PAUSE"));
        }
    }
}

void versus::closeEvent(QCloseEvent *event)
{
    if(status==STATUS_ON||status==STATUS_PAUSE)
    {
        timer->stop();
        timer4p2->stop();
        QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要退出游戏吗，您的分数不会被记录",
                                                                 QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                 QMessageBox::No);

        if (result==QMessageBox::Yes)
        {
            tetris->clear();
            tetris4p2->clear();
            tetrisBox->updateTetris(*tetris);
            tetrisBox4p2->updateTetris(*tetris4p2);
            nextTetrisBox->updateNextTetris(*tetris);
            nextTetrisBox4p2->updateNextTetris(*tetris4p2);
            refreshScore();
            status = STATUS_OFF;
            setWindowTitle(tr("Tetromino - OFF"));
            emit ExitWin();
            event->accept();
        }
        else
        {
            if(status==STATUS_ON)
            {
                timer->start();
                timer4p2->stop();
            }
            event->ignore();
        }
    }
    else
    {
        emit ExitWin();
        event->accept();
    }
}

void versus::gameOver()
{
    QString str;
    int score4p1 = tetris->getScore();
    int score4p2 = tetris4p2->getScore();
    if(score4p1 > score4p2)
    {
        str = QString("GAME OVER!\nWINNER IS PLAYER ONE!");
    }
    else if (score4p1 < score4p2)
    {
        str = QString("GAME OVER!\nWINNER IS PLAYER TWO!");
    }
    else{
        str = QString("GAME OVER!\nDRAW!");
    }
    QMessageBox::information(this, tr("Game Over"), str);
}
