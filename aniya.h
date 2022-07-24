#ifndef ANIYA_H
#define ANIYA_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>
#include <QMenu>
#include <QTime>
#include <QtGlobal>
#include <cmath>
#include <QImage>

class aniya : public QWidget
{
    Q_OBJECT
public:
    explicit aniya(int facter, QWidget *parent = nullptr);
    void moving();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    int m_i_left = 1;
    int m_i_right = 30;
    QPixmap m_pixmap_aniya;
    QTimer* m_timer;
    QPoint m_ponit_pos;
    QMenu* m_menu_exit;
    bool m_b_mousedown = false;

signals:
    void chageImg();
    void moveWindow(QPoint);
};

#endif // ANIYA_H
