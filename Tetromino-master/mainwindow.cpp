#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameinterface.h"
#include "quitdialog.h"
#include "ui_quitdialog.h"
#include <QDialog>
#include "form.h"

bool isCus;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("俄罗斯方块");
    this->setWindowIcon(QIcon(":/res/img/title.png"));
    QPalette pal;
    QPixmap pixmap(":/res/img/background.jpg");
    pal.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(pal);
    setAutoFillBackground(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    quit = new Dialog(this);
    quit->setModal(true);
    quit->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    myform = new Form();
    this->show();
    myform->setWindowModality(Qt::ApplicationModal);
    myform->show();
    connect(myform,SIGNAL(ExitWin()),this,SLOT(show()));
}


void MainWindow::on_pushButton_clicked()
{
    isCus = false;
    gi = new GameInterface(this);
    gi->setWindowModality(Qt::ApplicationModal);
    gi->show();
    connect(gi,SIGNAL(ExitWin()),this,SLOT(show()));
}

void MainWindow::on_pushButton_4_clicked()
{
    vs = new versus(this);
    vs->setWindowModality(Qt::ApplicationModal);
    vs->showMaximized();
    connect(vs,SIGNAL(ExitWin()),this,SLOT(show()));
}
