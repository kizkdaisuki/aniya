#ifndef MAINPLAY_H
#define MAINPLAY_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPoint>
#include "aniya.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainPlay; }
QT_END_NAMESPACE

class MainPlay : public QWidget
{
    Q_OBJECT

public:
    MainPlay(QWidget *parent = nullptr);
    ~MainPlay();

    void paintEvent(QPaintEvent *event);
    void setTransparent();
public:
    aniya* m_aniya_bo = NULL;
    QTimer* m_timer;
    QPoint m_point_realpos;

private:
    Ui::MainPlay *ui;
};
#endif // MAINPLAY_H
