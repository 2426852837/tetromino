#include "gameinterface.h"
#include "mainwindow.h"

GameInterface::GameInterface(QWidget *parent): QMainWindow(parent)
{
    //声明与赋予初始值
    QDesktopWidget *desktopWidget = QApplication::desktop();
    int width = (desktopWidget->width() - this->width()) / 2;
    int height = 5;
    QPalette pal = this->palette();
    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font("Microsoft YaHei", 15, 75);
    QWidget *widget = new QWidget(this);

    status = STATUS_OFF;
    nextStage = 100;
    speed = 500;
    key = Qt::Key_0;
    keytemp = key;
    mainLayout = new QGridLayout;

    //实例化部分
    //界面组件实例化
    tetris = new CTetromino;
    tetrisBox = new TetrisBox;
    nextTetrisBox = new NextTetrisBox;
    QLabel *nextTetrisLabel = new QLabel(tr("<font color = white>NEXT：</font>"));
    QLabel *controlLabel = new QLabel(tr("<font color = white>CONTROL：</font>"));
    QLabel *up_Label = new QLabel(tr("<font color = white>W/↑-ROTATE</font>"));
    QLabel *down_Label = new QLabel(tr("<font color = white>S/↓-DOWN</font>"));
    QLabel *left_Label = new QLabel(tr("<font color = white>A/←-LEFT</font>"));
    QLabel *right_Label = new QLabel(tr("<font color = white>D/→-RIGHT</font>"));
    QLabel *spaceLabel = new QLabel(tr("<font color = white>SPACE-SKIP</font>"));
    QLabel *enter_controlLabel = new QLabel(tr("<font color = white>ENTER-START</font>"));
    QLabel *pause_controlLabel = new QLabel(tr("<font color = white>P-PAUSE</font>"));
    QLabel *restart_controlLabel = new QLabel(tr("<font color = white>R-RESTART</font>"));
    QLabel *exit_controlLabel = new QLabel(tr("<font color = white>ESC-EXIT</font>"));
    QLabel *scoreTitleLabel = new QLabel(tr("<font color = white>SCORE：</font>"));
    scoreLabel = new QLabel(tr("<font color = white>0</font>"));
    QLabel *diffTitleLabel;
    if(isCus == true)
    {
        diffTitleLabel = new QLabel(tr("<font color = white>SPEED:</font>"));
        diffLabel = new QLabel(tr("<font color = white></font>"));
    }
    else
    {
        diffTitleLabel = new QLabel(tr("<font color = white>DIFFICULTY:</font>"));
        diffLabel = new QLabel(tr("<font color = white>0</font>"));
    }
    //计时器实例化
    timer = new QTimer(this);
    repeatTimer = new QTimer(this);
    //实例化部分结束

    //字体导入
    font.setFamily(fontFamilies.at(0));

    //为文字标签设置字体
    nextTetrisLabel->setFont(font);
    controlLabel->setFont(font);
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
    diffLabel->setFont(font);
    diffTitleLabel->setFont(font);
    spaceLabel->setFont(font);

    //设置游戏界面背景
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/game_bg.png")));
    setPalette(pal);

    //设置布局
    mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(15);
    mainLayout->setVerticalSpacing(20);
    mainLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(nextTetrisLabel, 15, 3);
    mainLayout->addWidget(nextTetrisBox, 16, 3, 1, 2);
    mainLayout->addWidget(controlLabel, 0, 0, 1, 1);
    mainLayout->addWidget(up_Label, 0, 1, 1, 1);
    mainLayout->addWidget(down_Label, 1, 1, 1, 1);
    mainLayout->addWidget(left_Label, 1, 0, 1, 1);
    mainLayout->addWidget(right_Label, 1, 2, 1, 1);
    mainLayout->addWidget(spaceLabel, 0, 3, 1, 1);
    mainLayout->addWidget(restart_controlLabel, 0, 2, 1, 1);
    mainLayout->addWidget(enter_controlLabel, 0, 4, 1, 1);
    mainLayout->addWidget(pause_controlLabel, 1, 3, 1, 1);
    mainLayout->addWidget(exit_controlLabel, 1, 4, 1, 1);
    mainLayout->addWidget(tetrisBox, 3, 1, 14, 2);
    mainLayout->addWidget(scoreTitleLabel, 7, 3);
    mainLayout->addWidget(scoreLabel, 7, 4);
    mainLayout->addWidget(diffTitleLabel, 8,3);
    mainLayout->addWidget(diffLabel, 8, 4);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
    setWindowIcon(QIcon(":/res/img/title.png"));

    //设置起始位置
    move(width, height);

    //初始化
    nextTetrisBox->updateNextTetris(*tetris);
    if(isCus == true)
    {
        setWindowTitle(tr("Custom mode Tetromino - OFF"));
    }
    else
    {
        setWindowTitle(tr("Tetromino - OFF"));
    }

    //链接计时器
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    connect(repeatTimer,SIGNAL(timeout()),this,SLOT(onRepeatTimer()));

}

GameInterface::~GameInterface()
{

}

void GameInterface::refreshScore()//刷新游戏分数标签
{
    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font("Microsoft YaHei", 15, 75);
    font.setFamily(fontFamilies.at(0));

    QString str;
    QString strDiff;
    int score = tetris->getScore();
    int diff = tetris->getDiff();
    str = QString::number(score);
    strDiff = QString::number(diff);
    scoreLabel->setText(str);
    if(!isCus)
    {
        if(score>=nextStage&&speed>=100)
        {
            nextStage+=100;
            speed-=50;
            setTimer();
        }
        diffLabel->setText(strDiff);
        diffLabel->setFont(font);
        diffLabel->setStyleSheet("QLabel{color:white;}");
    }
    scoreLabel->setFont(font);
    scoreLabel->setStyleSheet("QLabel{color:white;}");
}

void GameInterface::setTimer()//设置游戏速度
{
    if(isCus == true)
        timer->start(custom.getspeed());
    else {
        timer->start(speed);
    }
}

void GameInterface::keyPressEvent(QKeyEvent *event)//设置按键事件
{
    if (event->key() == Qt::Key_D||event->key() == Qt::Key_Right)//向右移动触发右移函数并记录按键
    {
        if (status == STATUS_ON)
        {
            if (tetris->moveToRight())
            {
                tetrisBox->updateTetris(*tetris);
                if(key == Qt::Key_0)
                {
                    key = Qt::Key_D;
                }
                else if (key == Qt::Key_A) {
                    keytemp = Qt::Key_D;
                }
            }
        }
    }
    else if (event->key() == Qt::Key_A||event->key() == Qt::Key_Left)//向左移动触发左移函数并记录按键
    {
        if (status == STATUS_ON)
        {
            if (tetris->moveToLeft())
            {
                tetrisBox->updateTetris(*tetris);
                if(key == Qt::Key_0)
                {
                    key = Qt::Key_A;
                }
                else if (key == Qt::Key_D) {
                    keytemp = Qt::Key_A;
                }
            }
        }
    }

    else if (event->key() == Qt::Key_S||event->key() == Qt::Key_Down)//向下移动触发下移函数
    {
        if (status == STATUS_ON)
        {
            if (tetris->moveToBottom())
            {
                tetrisBox->updateTetris(*tetris);
                nextTetrisBox->updateNextTetris(*tetris);
                refreshScore();
            }
            else
            {
                QMediaPlayer *effect = new QMediaPlayer;
                effect->setMedia(QUrl::fromLocalFile("./sound/game_over.mp3"));
                effect->play();
                timer->stop();
                QString str;
                str +=  QString("Game Over!\nYour Score is: %1!").arg(tetris->getScore());
                QMessageBox::information(this, tr("Game Over"), str);
                status = STATUS_END;
                if(isCus == true)
                {
                    setWindowTitle(tr("Custom mode Tetromino - END"));
                }
                else
                {
                    speed = 500;
                    setWindowTitle(tr("Tetromino - END"));
                }
            }
        }
    }
    else if (event->key() == Qt::Key_W||event->key() == Qt::Key_Up)//向上进行旋转
    {
        if (tetris->rotate())
        {
            if (status == STATUS_ON)
            {
                tetrisBox->updateTetris(*tetris);
                repeatTimer->start(100);
            }
        }
    }

    else if (event->key() == Qt::Key_Space) {                      //空格直接落底
        if(status == STATUS_ON)
        {
            if(tetris->moveToEnd())
            {
                tetrisBox->updateTetris(*tetris);
            }
            else
            {
                QMediaPlayer *effect = new QMediaPlayer;
                effect->setMedia(QUrl::fromLocalFile("./sound/game_over.mp3"));
                effect->play();
                timer->stop();
                QString str;
                str +=  QString("Game Over!\nYour Score is: %1!").arg(tetris->getScore());
                QMessageBox::information(this, tr("Game Over"), str);
                status = STATUS_END;
                if(isCus == true)
                {
                    setWindowTitle(tr("Custom mode Tetromino - END"));
                }
                else
                {
                    speed = 500;
                    setWindowTitle(tr("Tetromino - END"));
                }

            }
        }
    }

    else if (event->key() == Qt::Key_Enter||event->key() == Qt::Key_Return)//开始游戏
    {
        if (status == STATUS_PAUSE)
        {
            setTimer();
            status = STATUS_ON;
            if(isCus == true)
            {
                setWindowTitle(tr("Custom mode Tetromino - ON"));
            }
            else
            {
                setWindowTitle(tr("Tetromino - ON"));
            }
        }
        else if (status == STATUS_OFF)
        {
            tetris->createBlock();
            tetrisBox->updateTetris(*tetris);
            nextTetrisBox->updateNextTetris(*tetris);
            refreshScore();
            if(isCus == true)
            {
                QString strspeed=QString::number(custom.getspeed());
                int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
                QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
                QFont font("Microsoft YaHei", 15, 75);
                font.setFamily(fontFamilies.at(0));
                diffLabel->setFont(font);
                diffLabel->setStyleSheet("QLabel{color:white;}");
                diffLabel->setText(strspeed);
                mainLayout->addWidget(diffLabel, 8, 4);
            }

            status = STATUS_ON;
            if(isCus == true)
            {
                setWindowTitle(tr("Custom mode Tetromino - ON"));
            }
            else
            {
                setWindowTitle(tr("Tetromino - ON"));
            }
            setTimer();
        }
        else if (status == STATUS_END)
        {
            tetris->clear();
            tetris->createBlock();
            tetrisBox->updateTetris(*tetris);
            nextTetrisBox->updateNextTetris(*tetris);
            refreshScore();
            status = STATUS_ON;
            if(isCus == true)
            {
                setWindowTitle(tr("Custom mode Tetromino - ON"));
            }
            else
            {
                speed = 500;
                nextStage = 100;
                setWindowTitle(tr("Tetromino - ON"));
            }
            setTimer();
        }
    }
    else if (event->key() == Qt::Key_P)
    {
        if (status == STATUS_ON)
        {
            timer->stop();
            status = STATUS_PAUSE;
            if(isCus == true)
            {
                setWindowTitle(tr("Custom mode Tetromino - PAUSE"));
            }
            else
            {
                setWindowTitle(tr("Tetromino - PAUSE"));
            }

        }
    }

    else if (event->key() == Qt::Key_R)
    {
        if(status==STATUS_ON||status==STATUS_PAUSE)
        {
            timer->stop();
            QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要重新开始游戏吗，您的分数不会被记录",
                                                                     QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                     QMessageBox::No);
            if(result==QMessageBox::No||result==QMessageBox::Cancel)
            {
                if(status==STATUS_ON)
                {
                    setTimer();
                    return;
                }
            }
        }
        tetris->clear();
        tetrisBox->updateTetris(*tetris);
        nextTetrisBox->updateNextTetris(*tetris);
        refreshScore();
        speed = 500;
        status = STATUS_OFF;
        if(isCus == true)
        {
            setWindowTitle(tr("Custom mode Tetromino - OFF"));
        }
        else
        {
            setWindowTitle(tr("Tetromino - OFF"));
        }
    }

    else if (event->key() == Qt::Key_Escape)
    {
        timer->stop();
        if(status==STATUS_ON||status==STATUS_PAUSE)
        {
            QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要关闭游戏吗?您的分数将不会被记录",
                                                                     QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                     QMessageBox::No);
            if(result==QMessageBox::No||result==QMessageBox::Cancel)
            {
                if(status==STATUS_ON)
                {
                    setTimer();
                    return;
                }
            }
        }
        status = STATUS_OFF;
        tetris->clear();
        tetrisBox->updateTetris(*tetris);
        nextTetrisBox->updateNextTetris(*tetris);
        refreshScore();
        if(isCus == true)
        {
            setWindowTitle(tr("Custom mode Tetromino - OFF"));
        }
        else
        {
            setWindowTitle(tr("Tetromino - OFF"));
        }
        setVisible(false);
        emit ExitWin();

    }
}

void GameInterface::keyReleaseEvent(QKeyEvent *e)
{
    if((key == Qt::Key_D||key == Qt::Key_A||key == Qt::Key_Right||key == Qt::Key_Left)&&(e->key() == Qt::Key_D||e->key() == Qt::Key_A||e->key() == Qt::Key_Right||e->key() == Qt::Key_Left))
    {
        repeatTimer->stop();
        key = keytemp;
        keytemp = Qt::Key_0;
    }
}

void GameInterface::onTimer()
{
    if(tetris->moveToBottom())
    {
        tetrisBox->updateTetris(*tetris);
        nextTetrisBox->updateNextTetris(*tetris);
        refreshScore();
    }
    else
    {
        timer->stop();
        QString str;
        str =  QString("Game Over!\nYour Score is: %1!").arg(tetris->getScore());
        QMessageBox::information(this, tr("Game Over"), str);
        status = STATUS_END;
        if(isCus == true)
        {
            setWindowTitle(tr("Custom mode Tetromino - END"));
        }
        else
        {
            speed = 500;
            setWindowTitle(tr("Tetromino - END"));
        }
        QMediaPlayer *effect = new QMediaPlayer;
        effect->setMedia(QUrl::fromLocalFile("./sound/game_over.mp3"));
        effect->play();
    }
}

void GameInterface::onRepeatTimer()
{
    if(key == Qt::Key_D)
    {
        if (status == STATUS_ON)
        {
            if (tetris->moveToRight())
            {
                tetrisBox->updateTetris(*tetris);
            }
        }
    }
    else if (key == Qt::Key_A) {
        if (status == STATUS_ON)
        {
            if (tetris->moveToLeft())
            {
                tetrisBox->updateTetris(*tetris);
            }
        }
    }
}

void GameInterface::changeEvent(QEvent *event)
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
            status=STATUS_PAUSE;
            if(isCus == true)
            {
                setWindowTitle(tr("Custom mode Tetromino - PAUSE"));
            }
            else
            {
                setWindowTitle(tr("Tetromino - PAUSE"));
            }
        }

    }
}

void GameInterface::closeEvent(QCloseEvent *event)
{
    if(status==STATUS_ON||status==STATUS_PAUSE)
    {
        timer->stop();
        QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确认要退出游戏吗，您的分数不会被记录",
                                                                 QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                                                                 QMessageBox::No);

        if (result==QMessageBox::Yes)
        {
            tetris->clear();
            tetrisBox->updateTetris(*tetris);
            nextTetrisBox->updateNextTetris(*tetris);
            refreshScore();
            status = STATUS_OFF;
            if(isCus == true)
            {
                setWindowTitle(tr("Custom mode Tetromino - OFF"));
            }
            else
            {
                setWindowTitle(tr("Tetromino - OFF"));
            }
            emit ExitWin();
            event->accept();
        }
        else
        {
            if(status==STATUS_ON)
            {
                timer->start();
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

void GameInterface::mousePressEvent(QMouseEvent *event)
{
    if(isCus == true)
    {
        start = event->pos();
        timer->stop();
    }
}
void GameInterface::mouseReleaseEvent(QMouseEvent *e)
{
    if(isCus == true)
    {
        if(status == STATUS_ON)
            timer->start(custom.getspeed());
    }
}
void GameInterface::mouseMoveEvent(QMouseEvent *e)
{
    if(isCus == true)
    {
        movement = e->pos();
        int x = movement.x() - start.x();
        int y = movement.y() - start.y();

        if(x >= 34)
        {
            if (status == STATUS_ON)
            {
                if (tetris->moveToRight())
                {
                    start.setX(e->x());
                    tetrisBox->updateTetris(*tetris);
                }
            }
        }
        else if (x <= -34)
        {
            if (status == STATUS_ON)
            {
                if (tetris->moveToLeft())
                {
                    start.setX(e->x());
                    tetrisBox->updateTetris(*tetris);
                }
            }
        }
        if(y >= 34)
        {
            if (status == STATUS_ON)
            {
                if (tetris->moveToBottom())
                {
                    start.setY(e->y());
                    tetrisBox->updateTetris(*tetris);
                    nextTetrisBox->updateNextTetris(*tetris);
                    refreshScore();
                }
                else
                {
                    QMediaPlayer *effect = new QMediaPlayer;
                    effect->setMedia(QUrl::fromLocalFile("./sound/game_over.mp3"));
                    effect->play();
                    timer->stop();
                    QString str;
                    str +=  QString("Game Over1!\nYour Score is: %1!").arg(tetris->getScore());
                    QMessageBox::information(this, tr("Game Over1"), str);
                    status = STATUS_END;
                    setWindowTitle(tr("Tetromino - END"));
                }
            }

        }
        else if (y <= -34)
        {
            if (status == STATUS_ON)
            {
                if (tetris->moveToUp())
                {
                    start.setY(e->y());
                    tetrisBox->updateTetris(*tetris);
                }
            }
        }
    }
}
void GameInterface::wheelEvent(QWheelEvent *e)
{
    if(isCus == true)
    {
        if (tetris->rotate())
        {
            if (status == STATUS_ON)
            {
                tetrisBox->updateTetris(*tetris);
                repeatTimer->start(100);
            }
        }
        e->accept();
    }
}
