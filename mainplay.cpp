#include "mainplay.h"
#include "ui_mainplay.h"
#include <QIcon>
#include <QDesktopWidget>
#include <QDebug>
#include <QScreen>
#include <QPushButton>
#include <QMessageBox>

MainPlay::MainPlay(int facter, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPlay)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/aniya/aniya20.png"));
    this->initMoveWay(); // 初始化运动方向
    this->m_aniya_bo = new aniya(facter);
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
    this->m_d_heightmax = desk.height();
    this->m_d_widthmax = desk.width();
    this->m_timer->start(30);
    connect(this->m_timer, &QTimer::timeout, [=](){
        if(!this->m_aniya_bo->m_b_mousedown)
            this->m_point_realpos += this-> m_point_v;
        int flg = this->checkHit(this->m_point_realpos);
        if(flg)// check 是否碰壁
        {    // this->m_point_realpos.setX(-this->width()); // 反弹
            // 改变速度方向

            if(flg == 1) // 碰到顶部
            {
                this->m_d_angle = 2 * this->m_PI - this->m_d_angle;
                this->m_point_v.setX(cos(this->m_d_angle) * 5.0);
                this->m_point_v.setY(sin(this->m_d_angle) * 5.0);
            }
            else
            {
                double dv = this->m_PI;
                if(this->m_d_angle > this->m_PI)
                    dv *= 3;
                this->m_d_angle = dv - this->m_d_angle;
                this->m_point_v.setX(cos(this->m_d_angle) * 5.0);
                this->m_point_v.setY(sin(this->m_d_angle) * 5.0);
            }
            this->m_point_realpos += this->m_point_v;
        }
//        qDebug() << "brid pos = " << this->m_point_realpos.x();
        this->move(this->m_point_realpos);
    });

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
//    掉标题栏
       this->setWindowFlags(Qt::FramelessWindowHint);

       //设置透明窗体  120号属性
       this->setAttribute(Qt::WA_TranslucentBackground);

       //设置窗口顶层
       this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    this->m_point_realpos.setY(this->m_d_heightmax * 0.5 - this->height());
    this->m_point_realpos.setX(this->m_d_widthmax * 0.5 - this->width());
}

int MainPlay::checkHit(QPoint q){
    double w = q.x();
    double h = q.y();
    if(w + this->width() >= this->m_d_widthmax || w <= 0)
        return 2;
    if(h + this->height() >= this->m_d_heightmax || h <= 0)
        return 1;
    return 0;
}

void MainPlay::initMoveWay(){
    this->m_d_angle = this->getRandValue(0.001, 0.999) * 2 * this->m_PI;
    this->m_point_v.setX(cos(this->m_d_angle) * 5.0);
    this->m_point_v.setY(sin(this->m_d_angle) * 5.0);
}

float MainPlay::getRandValue(float min, float max){
    static bool seedStatus;
    if (!seedStatus)
    {
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    seedStatus = true;
    }
    if(min > max)
    {
    float temp = min;
    min = max;
    max = temp;
    }
    double diff = fabs(max-min);
    double m1 = (double)(qrand() % 100) / 100;
    double retval = min + m1 * diff;
    return retval;
}

void MainPlay::setStartPosition(int w, int h){
    //       设置起始Y位置
           this->m_point_realpos.setY(h);
    this->m_point_realpos.setX(w);
}

void MainPlay::closeEvent(QCloseEvent *event){
    // TODO

    qDebug() << "close";
    emit this->getClose();
    event->accept();
}
