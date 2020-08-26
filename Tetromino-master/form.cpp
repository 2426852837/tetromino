#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowTitle("自定模式");
    this->setWindowIcon(QIcon(":/res/img/title.png"));
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/res/img/background.jpg")));
    setPalette(pal);
}

Form::~Form()
{
    delete ui;

}


void Form::on_pushButton_2_clicked()
{
    this->hide();
}

void Form::on_pushButton_clicked()
{
    this->hide();

    cusgame.show();
}
