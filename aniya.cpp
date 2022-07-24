#include "aniya.h"

aniya::aniya(int facter, QWidget *parent) : QWidget(parent)
{
    for(int i = 1; i <= 30; i ++)
    {
        QString str = QString(":/aniya/aniya%1.png").arg(i);
        this->m_pixmap_aniya.load(str); // 先让他加载一遍
    }
        // 设置aniya
        this->setFixedSize(this->m_pixmap_aniya.width() / facter, this->m_pixmap_aniya.height() / facter);
        this->m_timer = new QTimer(this);
        connect(this->m_timer, &QTimer::timeout, [=](){
            QString str = QString(":/aniya/aniya%1.png").arg(this->m_i_left ++);
            this->m_pixmap_aniya.load(str);
            this->m_pixmap_aniya = this->m_pixmap_aniya.scaled(this->m_pixmap_aniya.width() / facter, this->m_pixmap_aniya.height() / facter, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            if(this->m_i_left > this->m_i_right)
                this->m_i_left = 1;
            emit this->chageImg();
        });
        this->m_menu_exit = new QMenu();
        connect(this->m_menu_exit->addAction("退出"), &QAction::triggered, [=](){
            exit(0);
        });
}


void aniya::moving(){
    this->m_timer->start(50);
}

void aniya::mousePressEvent(QMouseEvent *event){
//    ((QWidget* )this->parent())->frameGeometry().topLeft() 获取当前窗口左上角的坐标
    this->m_ponit_pos = event->globalPos() - (((QWidget* )this->parent())->frameGeometry().topLeft());
    // 设置按下事件为真
    this->m_b_mousedown = true;

    //右键弹出菜单
    if(event->button() == Qt::RightButton)
        this->m_menu_exit->popup(QCursor::pos());
    //窗口消失后的信号监听
    connect(this->m_menu_exit,&QMenu::aboutToHide,[=](){
        this->m_b_mousedown = false;
    });
}

void aniya::mouseMoveEvent(QMouseEvent *event){

    emit this->moveWindow(event->globalPos() - this->m_ponit_pos);
}

void aniya::mouseReleaseEvent(QMouseEvent *event){
    this->m_b_mousedown = false;
}

