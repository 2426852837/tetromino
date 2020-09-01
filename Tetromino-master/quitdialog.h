#ifndef QUITDIALOG_H
#define QUITDIALOG_H

#include <QDialog>
#include <QIcon>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:


    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
};

#endif // QUITDIALOG_H
