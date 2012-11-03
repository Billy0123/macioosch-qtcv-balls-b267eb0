#include <QPainter>
#include "matwidget.h"

MatWidget::MatWidget(QWidget *parent) :
    QWidget(parent)
{
}

void MatWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QImage mat_qi = mat2qimage(matrix);
    mat_qi = mat_qi.scaled(size(), Qt::KeepAspectRatio);

    painter.translate((width()-mat_qi.width())/2,
                      (height()-mat_qi.height())/2);

    painter.drawImage(mat_qi.rect(), mat_qi);
}
