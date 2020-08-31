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
    tetrisBox = new TetrisBox;
    nextTetrisBox = new NextTetrisBox;
    nextTetrisLabel = new QLabel(tr("<font color = white>NEXT：</font>"));
    controlLabel = new QLabel(tr("<font color = white>CONTROL：</font>"));
    up_Label = new QLabel(tr("<font color = white>W/↑-ROTATE</font>"));
    down_Label = new QLabel(tr("<font color = white>S/↓-DOWN</font>"));
    left_Label = new QLabel(tr("<font color = white>A/←-LEFT</font>"));
    right_Label = new QLabel(tr("<font color = white>D/→-RIGHT</font>"));
    enter_controlLabel = new QLabel(tr("<font color = white>ENTER-START</font>"));
    pause_controlLabel = new QLabel(tr("<font color = white>P-PAUSE</font>"));
    restart_controlLabel = new QLabel(tr("<font color = white>R-RESTART</font>"));
    exit_controlLabel = new QLabel(tr("<font color = white>ESC-EXIT</font>"));
    scoreTitleLabel = new QLabel(tr("<font color = white>SCORE：</font>"));
    scoreLabel = new QLabel(tr("<font color = white>0</font>"));
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

    //设置游戏界面背景
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/game_bg.png")));
    setPalette(pal);

    //设置布局
    mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(15);
    mainLayout->setVerticalSpacing(20);
    mainLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(nextTetrisLabel, 10, 3);
    mainLayout->addWidget(nextTetrisBox, 11, 3, 1, 2);
    mainLayout->addWidget(controlLabel, 0, 0, 1, 1);
    mainLayout->addWidget(up_Label, 0, 1, 1, 1);
    mainLayout->addWidget(down_Label, 1, 1, 1, 1);
    mainLayout->addWidget(left_Label, 1, 0, 1, 1);
    mainLayout->addWidget(right_Label, 1, 2, 1, 1);
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
    nextTetrisBox->updateNextTetris(tetris);
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

void GameInterface::refreshScore()
{
    QString str;
    int score = tetris.getScore();

    str = QString::number(score);
    scoreLabel->setText(str);

    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font("Microsoft YaHei", 15, 75);
    font.setFamily(fontFamilies.at(0));

    scoreLabel->setFont(font);
    scoreLabel->setStyleSheet("QLabel{color:white;}");
}

void GameInterface::setTimer()
{
    if(isCus == true)
        timer->start(custom.getspeed());
    else {
        timer->start(speed);
    }
}

void GameInterface::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_D||event->key() == Qt::Key_Right)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToRight())
            {
                tetrisBox->updateTetris(tetris);
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
    else if (event->key() == Qt::Key_A||event->key() == Qt::Key_Left)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToLeft())
            {
                tetrisBox->updateTetris(tetris);
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

    else if (event->key() == Qt::Key_S||event->key() == Qt::Key_Down)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToBottom())
            {
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                refreshScore();
            }
            else
            {
                QMediaPlayer *effect = new QMediaPlayer;
                effect->setMedia(QUrl::fromLocalFile("./sound/game_over.mp3"));
                effect->play();
                timer->stop();
                QString str;
                str +=  QString("Game Over1!\nYour Score is: %1!").arg(tetris.getScore());
                QMessageBox::information(this, tr("Game Over1"), str);
                status = STATUS_END;
                if(isCus == true)
                {
                    setWindowTitle(tr("Custom mode Tetromino - END"));
                }
                else
                {
                    setWindowTitle(tr("Tetromino - END"));
                }
            }
        }
    }
    else if (event->key() == Qt::Key_W||event->key() == Qt::Key_Up)
    {
        if (tetris.rotate())
        {
            if (status == STATUS_ON)
            {
                tetrisBox->updateTetris(tetris);
                repeatTimer->start(100);
            }
        }
    }

    else if (event->key() == Qt::Key_Space) {
        if(status == STATUS_ON)
        {
            if(tetris.moveToEnd())
            {
                tetrisBox->updateTetris(tetris);
            }
            else
            {
                QMediaPlayer *effect = new QMediaPlayer;
                effect->setMedia(QUrl::fromLocalFile("./sound/game_over.mp3"));
                effect->play();
                timer->stop();
                QString str;
                str +=  QString("Game Over!\nYour Score is: %1!").arg(tetris.getScore());
                QMessageBox::information(this, tr("Game Over2"), str);
                status = STATUS_END;
                if(isCus == true)
                {
                    setWindowTitle(tr("Custom mode Tetromino - END"));
                }
                else
                {
                    setWindowTitle(tr("Tetromino - END"));
                }

            }
        }
    }

    else if (event->key() == Qt::Key_Enter||event->key() == Qt::Key_Return)
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
            tetris.createBlock();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
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
            tetris.clear();
            tetris.createBlock();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            refreshScore();
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

            box1->setWindowTitle("游戏暂停");
            box1->setText("按下enter继续游戏");
            box1->exec();
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
            else
            {
                tetris.clear();
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
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
            }
        }
        else
        {
            tetris.clear();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
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
            else
            {

                status = STATUS_OFF;
                tetris.clear();
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                refreshScore();
                if(isCus == true)
                {
                    setWindowTitle(tr("Custom mode Tetromino - OFF"));
                }
                else
                {
                    setWindowTitle(tr("Tetromino - OFF"));
                }

            }

        }

        else
        {
            status = STATUS_OFF;


            tetris.clear();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
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
        }
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
    if(tetris.moveToBottom())
    {
        tetrisBox->updateTetris(tetris);
        nextTetrisBox->updateNextTetris(tetris);
        refreshScore();
    }
    else
    {
        timer->stop();
        QString str;
        str +=  QString("Game Over!\nYour Score is: %1!").arg(tetris.getScore());
        QMessageBox::information(this, tr("Game Over"), str);
        status = STATUS_END;
        if(isCus == true)
        {
            setWindowTitle(tr("Custom mode Tetromino - END"));
        }
        else
        {
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
            if (tetris.moveToRight())
            {
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    else if (key == Qt::Key_A) {
        if (status == STATUS_ON)
        {
            if (tetris.moveToLeft())
            {
                tetrisBox->updateTetris(tetris);
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
            tetris.clear();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
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
}
