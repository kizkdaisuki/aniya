#include "mainplay.h"
#include "ui_mainplay.h"
#include <QIcon>
#include <QDesktopWidget>
#include <QDebug>
#include <QScreen>

MainPlay::MainPlay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPlay)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/aniya/aniya20.png"));
    this->m_aniya_bo = new aniya;
    this->m_aniya_bo->setParent(this);
    this->setFixedSize(this->m_aniya_bo->width(), this->m_aniya_bo->height());
    // 让小鸟飞起来
    this->m_aniya_bo->moving();
    connect(this->m_aniya_bo, &aniya::chageImg, [=](){
        this->update();
    });
    connect(this->m_aniya_bo, &aniya::moveWindow, [=](QPoint point){
        this->move(point);
        this->m_point_realpos = point;
    });
    this->m_timer = new QTimer(this);
    auto desk =  QGuiApplication::primaryScreen()->geometry(); // 获取桌面属性
    this->m_timer->start(30);
    connect(this->m_timer, &QTimer::timeout, [=](){
        if(!this->m_aniya_bo->m_b_mousedown)
            this->m_point_realpos.setX(this->m_point_realpos.x() + 5);

        if(this->m_point_realpos.x() > desk.width())
            this->m_point_realpos.setX(-this->width());
        qDebug() << "brid pos = " << this->m_point_realpos.x();
        this->move(this->m_point_realpos);
    });
    qDebug() << "desk width = " << desk.width();
    this->setTransparent();
}

MainPlay::~MainPlay()
{
    delete ui;
}

void MainPlay::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->m_aniya_bo->m_pixmap_aniya);
}

void MainPlay::setTransparent(){
    //去掉标题栏
       this->setWindowFlags(Qt::FramelessWindowHint);

       //设置透明窗体  120号属性
       this->setAttribute(Qt::WA_TranslucentBackground);

       //设置窗口顶层
       this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

       //设置起始Y位置
      //this->m_Auto_Pos.setY(desk->height()*0.5 -this->m_Bird->height());
}

