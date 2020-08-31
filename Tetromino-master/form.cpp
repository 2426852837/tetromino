#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"

allnumber custom;
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
    isCus = false;
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


    ishape=ui->ishape->text();
    jshape=ui->jshape->text();
    lshape=ui->lshape->text();
    oshape=ui->oshape->text();
    zshape=ui->zshape->text();
    tshape=ui->tshape->text();
    sshape=ui->sshape->text();
    speed=ui->speed->text();
    isCus = true;

    if((isDigitStr(ishape))&&(isDigitStr(jshape))&&(isDigitStr(lshape))&&(isDigitStr(oshape))&&(isDigitStr(zshape))&&(isDigitStr(tshape))&&(isDigitStr(sshape))&&(isDigitStr(speed)))
    {
        int len = 0;
        int ish=ishape.toInt();
        int jsh=jshape.toInt();
        int lsh=lshape.toInt();
        int osh=oshape.toInt();
        int zsh=zshape.toInt();
        int tsh=tshape.toInt();
        int ssh=sshape.toInt();
        int spe=speed.toInt();
        len= ish+jsh+lsh+osh+zsh+tsh+ssh;
        if(len == 0)
        {
            QMessageBox::information(this,"错误","方块数目不能全为0，请重新输入");
            return;
        }
        custom.setallnumber(ish,jsh,lsh,osh,zsh,tsh,ssh,spe);
        gi = new GameInterface(this);
        this->hide();
        gi->show();
    }
    else
    {
        QMessageBox::information(this,"错误","输入错误，请重新输入");
        return;
    }

}
bool Form::isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;
    if (*s)
    {
        return false;
    }
    else
    {
        return true;
    }
}
