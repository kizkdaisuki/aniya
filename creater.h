#ifndef CREATER_H
#define CREATER_H

#include "mainplay.h"
#include <QApplication>
#include <QTimer>
#include <QVector>
#include <QPoint>
class creater : QObject
{
public:

    bool checkIsAttach();

public:

    QVector<MainPlay*> m_mainplay_ob;
    int m_i_idx = 0;
    QTimer* m_timer_t1 = NULL; // 初始化
    QTimer* m_timer_t2 = NULL;
    QTimer* m_timer_t3 = NULL;
    QPoint m_point_lastpos;
    creater();
};

#endif // CREATER_H
