#ifndef MATWIDGET_H
#define MATWIDGET_H

#include <QWidget>
#include "matqimage.h"

class MatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MatWidget(QWidget *parent = 0);
    Mat matrix;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MATWIDGET_H
