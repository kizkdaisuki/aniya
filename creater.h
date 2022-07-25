#ifndef CREATER_H
#define CREATER_H

#include "mainplay.h"
#include <QApplication>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <algorithm>
class creater : QObject
{
public:

    bool checkIsAttach();

public:

    QVector<MainPlay*> m_mainplay_ob;
    int m_i_idx = 0;
    QTimer* m_timer_t1 = NULL; // 初始化
    QTimer* m_timer_t2 = NULL; // 保存主aniya的最后一次的位置
    QTimer* m_timer_t3 = NULL; // 检测碰撞
    QTimer* m_timer_t4 = NULL; // 检测是否退出
    QPoint m_point_lastpos;
    int m_i_crash1 = -1;
    int m_i_crash2 = -1;
    creater();
};

#endif // CREATER_H
