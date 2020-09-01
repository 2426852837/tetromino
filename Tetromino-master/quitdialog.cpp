#include "quitdialog.h"
#include "ui_quitdialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("退出");
    this->setWindowIcon(QIcon(":/res/img/title.png"));
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/background.jpg")));
    setPalette(pal);
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_buttonBox_accepted()
{
    this->setVisible(false);
    QApplication *app;
    app->closeAllWindows();
}
