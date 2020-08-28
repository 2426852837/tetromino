#include "cusgame.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFontDatabase>
#include "mainwindow.h"
#include "form.h"

Cusgame::Cusgame(QWidget *parent) : QMainWindow(parent)
{
    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    tetrisBox = new TetrisBox;
    nextTetrisBox = new NextTetrisBox;
    nextTetrisLabel = new QLabel(tr("<font color = white>NEXT：</font>"));
    controlLabel = new QLabel(tr("<font color = white>CONTROL：</font>"));
    w_controlLabel = new QLabel(tr("<font color = white>W-ROTATE</font>"));
    s_controlLabel = new QLabel(tr("<font color = white>S-DOWN</font>"));
    a_controlLabel = new QLabel(tr("<font color = white>A-UP</font>"));
    d_controlLabel = new QLabel(tr("<font color = white>D-RIGHT</font>"));
    enter_controlLabel = new QLabel(tr("<font color = white>ENTER-START</font>"));
    p_controlLabel = new QLabel(tr("<font color = white>P-PAUSE</font>"));
    r_controlLabel = new QLabel(tr("<font color = white>R-RESTART</font>"));
    esc_controlLabel = new QLabel(tr("<font color = white>ESC-END</font>"));
    spaceLabel = new QLabel(tr("<font color = white>Space-SKIP</font>"));
    scoreTitleLabel = new QLabel(tr("<font color = white>SCORE：</font>"));
    scoreLabel = new QLabel(tr("<font color = white>0</font>"));

    diffTitleLabel = new QLabel(tr("<font color = white>SPEED:</font>"));
    diffLabel = new QLabel(tr("<font color = white></font>"));
    QFont font("Microsoft YaHei", 15, 75);
    font.setFamily(fontFamilies.at(0));

    nextTetrisLabel->setFont(font);
    controlLabel->setFont(font);
    w_controlLabel->setFont(font);
    s_controlLabel->setFont(font);
    a_controlLabel->setFont(font);
    d_controlLabel->setFont(font);
    enter_controlLabel->setFont(font);
    p_controlLabel->setFont(font);
    r_controlLabel->setFont(font);
    esc_controlLabel->setFont(font);
    spaceLabel->setFont(font);
    scoreTitleLabel->setFont(font);
    scoreLabel->setFont(font);
    diffLabel->setFont(font);
    diffTitleLabel->setFont(font);



    mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(15);
    mainLayout->setVerticalSpacing(20);
    mainLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(nextTetrisLabel, 6, 3);
    mainLayout->addWidget(nextTetrisBox, 7, 3, 1, 2);
    mainLayout->addWidget(controlLabel, 0, 0, 1, 1);
    mainLayout->addWidget(w_controlLabel, 0, 1, 1, 1);
    mainLayout->addWidget(s_controlLabel, 1, 1, 1, 1);
    mainLayout->addWidget(a_controlLabel, 1, 0, 1, 1);
    mainLayout->addWidget(d_controlLabel, 1, 2, 1, 1);
    mainLayout->addWidget(r_controlLabel, 0, 2, 1, 1);
    mainLayout->addWidget(spaceLabel, 0, 3, 1, 1);
    mainLayout->addWidget(enter_controlLabel, 0, 4, 1, 1);
    mainLayout->addWidget(p_controlLabel, 1, 3, 1, 1);
    mainLayout->addWidget(esc_controlLabel, 1, 4, 1, 1);
    mainLayout->addWidget(tetrisBox, 3, 1, 14, 2);
    mainLayout->addWidget(scoreTitleLabel, 12, 3);
    mainLayout->addWidget(scoreLabel, 12, 4);
    mainLayout->addWidget(diffTitleLabel, 13,3);


    QWidget *widget = new QWidget(this);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
    setWindowIcon(QIcon(":/res/img/title.png"));

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/game_bg.png")));
    setPalette(pal);

    QDesktopWidget *desktopWidget = QApplication::desktop();
    int w = (desktopWidget->width() - this->width()) / 2;
    int h = 5;
    move(w, h);

    QMediaPlaylist *playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("./sound/bgm.mp3"));
    playlist->setCurrentIndex(0);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    QMediaPlayer *sound = new QMediaPlayer;
    sound->setMedia(playlist);
    sound->play();

    key = Qt::Key_0;
    keytemp = key;

    speed = custom.getspeed();

    status = STATUS_OFF;
    nextTetrisBox->updateNextTetris(tetris);
    setWindowTitle(tr("Custom mode Tetromino - OFF"));
    timer = new QTimer(this);
    repeatTimer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    connect(repeatTimer,SIGNAL(timeout()),this,SLOT(onrepeatTimer()));

}

Cusgame::~Cusgame()
{

}

void Cusgame::setTimer(){
    timer->start(custom.getspeed());
}



void Cusgame::keyPressEvent(QKeyEvent *event)
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
                updateScore();
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
                setWindowTitle(tr("Tetromino - END"));
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
                effect->setMedia(QUrl::fromLocalFile("./sound/so_good.mp3"));
                effect->play();
                timer->stop();
                QString str;
                str +=  QString("Game Over2!\nYour Score is: %1!").arg(tetris.getScore());
                QMessageBox::information(this, tr("Game Over2"), str);
                status = STATUS_END;
                setWindowTitle(tr("Custom mode Tetromino - END"));

            }
        }
    }

    else if (event->key() == Qt::Key_Enter||event->key() == Qt::Key_Return)
    {
        if (status == STATUS_PAUSE)
        {
            timer->start(custom.getspeed());
            status = STATUS_ON;
            setWindowTitle(tr("Custom mode Tetromino - ON"));
        }
        else if (status == STATUS_OFF)
        {
            tetris.createBlock();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            QString strspeed=QString::number(custom.getspeed());


            int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
            QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

            QFont font("Microsoft YaHei", 15, 75);
            font.setFamily(fontFamilies.at(0));
            diffLabel->setFont(font);
            diffLabel->setStyleSheet("QLabel{color:white;}");
            diffLabel->setText(strspeed);
            mainLayout->addWidget(diffLabel, 13, 4);
            status = STATUS_ON;
            setWindowTitle(tr("Custom mode Tetromino - ON"));
            timer->start(custom.getspeed());
        }
        else if (status == STATUS_END)
        {
            tetris.clear();
            tetris.createBlock();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            status = STATUS_ON;
            setWindowTitle(tr("Custom mode Tetromino - ON"));
            timer->start(custom.getspeed());
        }
    }
    else if (event->key() == Qt::Key_P)
    {
        if (status == STATUS_ON)
        {
            timer->stop();
            status = STATUS_PAUSE;
            setWindowTitle(tr("Custom mode Tetromino - PAUSE"));

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
                    timer->start(speed);
                    return;
                }

            }
            else
            {
                tetris.clear();
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                updateScore();
                status = STATUS_OFF;
                setWindowTitle(tr("Custom mode Tetromino - OFF"));
            }
        }
        else
        {
            tetris.clear();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            status = STATUS_OFF;
            setWindowTitle(tr("Custom mode Tetromino - OFF"));

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
                    timer->start(custom.getspeed());
                    return;
                }
            }
            else
            {

                status = STATUS_OFF;
                tetris.clear();
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                updateScore();
                setWindowTitle(tr("Custom mode Tetromino - OFF"));

            }

        }

        else
        {
            status = STATUS_OFF;


            tetris.clear();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            setWindowTitle(tr("Custom mode Tetromino - OFF"));
            setVisible(false);
        }
    }
}

void Cusgame::keyReleaseEvent(QKeyEvent *e)
{
    if((key == Qt::Key_D||key == Qt::Key_A||key == Qt::Key_Right||key == Qt::Key_Left)&&(e->key() == Qt::Key_D||e->key() == Qt::Key_A||e->key() == Qt::Key_Right||e->key() == Qt::Key_Left))
    {
        repeatTimer->stop();

        key = keytemp;
        keytemp = Qt::Key_0;

    }

}

void Cusgame::onrepeatTimer()
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

void Cusgame::onTimer()
{
    if(tetris.moveToBottom())
    {
        tetrisBox->updateTetris(tetris);
        nextTetrisBox->updateNextTetris(tetris);
        updateScore();
    }
    else
    {
        timer->stop();
        QString str;
        str +=  QString("Game Over!\nYour Score is: %1!").arg(tetris.getScore());
        QMessageBox::information(this, tr("Game Over"), str);
        status = STATUS_END;
        setWindowTitle(tr("Custom mode Tetromino - END"));
        QMediaPlayer *effect = new QMediaPlayer;
        effect->setMedia(QUrl::fromLocalFile("./sound/game_over.mp3"));
        effect->play();
    }
}

void Cusgame::mousePressEvent(QMouseEvent *event)
{
    start = event->pos();
    timer->stop();
}

void Cusgame::mouseMoveEvent(QMouseEvent *e)
{
    movement = e->pos();
    int x = movement.x() - start.x();
    int y = movement.y() - start.y();

    if(x >= 34)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToRight())
            {
                start.setX(e->x());
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    else if (x <= -34)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToLeft())
            {
                start.setX(e->x());
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    if(y >= 34)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToBottom())
            {
                start.setY(e->y());
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                updateScore();
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
                setWindowTitle(tr("Tetromino - END"));
            }
        }

    }
    else if (y <= -34)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToUp())
            {
                start.setY(e->y());
                tetrisBox->updateTetris(tetris);
            }
        }
    }
}

void Cusgame::mouseReleaseEvent(QMouseEvent *e)
{
    timer->start(custom.getspeed());
}

void Cusgame::wheelEvent(QWheelEvent *e)
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

void Cusgame::updateScore()
{
    QString str;
    int score = tetris.getScore();

    str += QString("%1").arg(score);

    scoreLabel->setText(str);
    int fontId = QFontDatabase::addApplicationFont(":/res/font/8bit.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    scoreLabel->setText(str);

    QFont font("Microsoft YaHei", 15, 75);
    font.setFamily(fontFamilies.at(0));
    scoreLabel->setFont(font);
    scoreLabel->setStyleSheet("QLabel{color:white;}");

}

void Cusgame::changeEvent(QEvent *event)
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
            setWindowTitle("Custom mode Tetromino - PAUSE");
        }

    }
}

void Cusgame::closeEvent(QCloseEvent *event)
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
            updateScore();
            status = STATUS_OFF;
            setWindowTitle(tr("Custom mode Tetromino - OFF"));
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
