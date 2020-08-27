#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QGridLayout>
#include<qgridlayout.h>
#include <QFile>
#include <QMessageBox>
#include <QObject>
#include <QTextStream>
#include <QtDebug>
#include <QIcon>
#include "cusgame.h"
#include "mainwindow.h"

namespace Ui {
class Form;
class cusgame;
}
class allnumber
{
public:
    allnumber()
    {
        ish=jsh=lsh=osh=zsh=tsh=ssh=1;
        spe=500;
    }
    void setallnumber(int ish,int jsh,int lsh,int osh,int zsh,int tsh,int ssh,int spe)
    {
        this->ish=ish;
        this->jsh=jsh;
        this->lsh=lsh;
        this->osh=osh;
        this->zsh=zsh;
        this->tsh=tsh;
        this->ssh=ssh;
        this->spe=spe;
    }
    int getspeed()
    {
        return spe;
    }
    int getish()
    {
        return ish;
    }
    int getssh()
    {
        return ssh;
    }
    int getjsh()
    {
        return jsh;
    }
    int getlsh()
    {
        return lsh;
    }
    int getosh()
    {
        return osh;
    }
    int getzsh()
    {
        return zsh;
    }
    int gettsh()
    {
        return tsh;
    }
private:
    int ish;
    int jsh;
    int lsh;
    int osh;
    int zsh;
    int tsh;
    int ssh;
    int spe;
};

extern allnumber custom;

class Form : public QWidget
{
    Q_OBJECT

public:

    explicit Form(QWidget *parent = nullptr);
    bool isDigitStr(QString src);
    ~Form();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::Form *ui;
    cusgame cusgame;
    QString ishape,jshape,lshape,oshape,zshape,tshape,sshape,speed;
signals:

};

#endif // FORM_H
