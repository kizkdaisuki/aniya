#include "creater.h"
#include <QDebug>

bool creater::checkIsAttach()
{
    int n = this->m_mainplay_ob.size();
    for(int i = 0; i < n; i ++)
    {
        int a[4], b[4];
        a[0] = this->m_mainplay_ob[i]->m_point_realpos.y(); // up
        a[2] = this->m_mainplay_ob[i]->m_point_realpos.x(); // l
        a[3] = a[0] + this->m_mainplay_ob[i]->height(); // down
        a[1] = a[2] + this->m_mainplay_ob[i]->width(); // r
        for(int j = i + 1; j < n; j ++)
        {

            b[0] = this->m_mainplay_ob[j]->m_point_realpos.y();
            b[2]  = this->m_mainplay_ob[j]->m_point_realpos.x();
            b[3] = b[0] + this->m_mainplay_ob[j]->height();
            b[1] = b[2] + this->m_mainplay_ob[j]->width();
//            if(b[3] > a[0]) return false;
//            if(b[0] < a[3]) return false;
//            if(b[2] > a[1]) return false;
//            if(b[1] < a[2]) return false;
            bool flg = true;
            for(int k = 0; k < 4; k ++)
            {
                int t = 3 - k;
                if(t > k)
                    if(b[t] > a[k]) flg = false;
                else
                    if(b[t] < a[k]) flg = false;
            }
            if(flg)
                return false;
        }
    }
    return false;
}

creater::creater()
{
    this->m_timer_t1 = new QTimer;
    this->m_timer_t1->start(1000);
    this->m_timer_t2 = new QTimer;
    this->m_timer_t2->start(10);
    connect(m_timer_t1, QTimer::timeout, [=](){
        if(this->m_mainplay_ob.size() == 0)
             this->m_mainplay_ob.push_back(new MainPlay(4));
        else
            this->m_mainplay_ob.push_back(new MainPlay(6));
        if(this->m_mainplay_ob.size() > 1)
            this->m_mainplay_ob.back()->setStartPosition(this->m_point_lastpos.x(), this->m_point_lastpos.y());
        this->m_mainplay_ob.back()->show();
        if(this->m_mainplay_ob.size() >= 5)
            this->m_timer_t1->stop();
    });

    connect(m_timer_t2, QTimer::timeout, [=](){
        if(this->m_mainplay_ob.size() >= 1)
            this->m_point_lastpos = this->m_mainplay_ob[0]->m_point_realpos;
    });
    this->m_timer_t3 = new QTimer;
    this->m_timer_t3->start(10);
    connect(m_timer_t3, QTimer::timeout, [=](){
        if(this->checkIsAttach())
            qDebug() << "碰到了";
    });


}
