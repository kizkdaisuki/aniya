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
#include <QDebug>

class aniya : public QWidget
{
    Q_OBJECT
public:
    explicit aniya(int facter, QWidget *parent = nullptr);
    void moving();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void getExit();

public:
    int m_i_left = 1;
    int m_i_right = 30;
    QPixmap m_pixmap_aniya;
    QTimer* m_timer;
    QPoint m_ponit_pos;
    QPoint m_ponit_tempPos;
    QMenu* m_menu_exit;
    bool m_b_mousedown = false;
    bool m_b_mouseMidDown = false;
    double m_d_angle;
    int m_i_mouseMidDown = 0;
    int m_i_timeD = 0;

signals:
    void chageImg();
    void moveWindow(QPoint);
    void mouseMidPress();
};

#endif // ANIYA_H
