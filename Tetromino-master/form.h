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

namespace Ui {
class Form;
class cusgame;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Form *ui;
    cusgame cusgame;

};

#endif // FORM_H
