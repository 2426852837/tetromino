#ifndef NEXTTETRISBOX_H
#define NEXTTETRISBOX_H

#include <QWidget>
#include <QWidget>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QColor>
#include "ctetromino.h"

#define FIXX (MAXX - NEXTMAXX) / 2     //方块x坐标的转换常数
#define FIXY 4                         //方块y坐标的转换常数

class NextTetrisBox : public QWidget
{
    Q_OBJECT
public:
    explicit NextTetrisBox(QWidget *parent = nullptr);
    void updateNextTetris(CTetromino tetris);   //更新“下一个”的数据和视图
    void paintEvent(QPaintEvent *event);    //绘制视图
private:
    Block nextBlock;    //“下一个”方块
};


#endif // NEXTTETRIS_H
