#ifndef MAINPLAY_H
#define MAINPLAY_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPoint>
#include "aniya.h"
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainPlay; }
QT_END_NAMESPACE

class MainPlay : public QWidget
{
    Q_OBJECT

public:
    MainPlay(int facter, QWidget *parent = nullptr);
    ~MainPlay();

    void paintEvent(QPaintEvent *event);
    void setTransparent();
    int checkHit(QPoint);
    void initMoveWay();
    float getRandValue(float, float);
    void setStartPosition(int w, int h);
public:
    aniya* m_aniya_bo = NULL;
    QTimer* m_timer;
    QPoint m_point_realpos;
    QPoint m_point_v; // 速度方向
    double m_d_angle; // 角度
    const double m_PI = acos(-1.0);
    const double EPS = 1e-6;
    double m_d_widthmax;
    double m_d_heightmax;
private:
    Ui::MainPlay *ui;
};
#endif // MAINPLAY_H
