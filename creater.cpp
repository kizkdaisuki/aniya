#include "creater.h"
#include <QDebug>
#include <QString>

creater::creater()
{
    this->m_timer_t1 = new QTimer;
    this->m_timer_t1->start(1000);
    this->m_timer_t2 = new QTimer;
    this->m_timer_t2->start(10);
    this->m_timer_t3 = new QTimer;

    connect(m_timer_t1, QTimer::timeout, [=](){
        if(this->m_mainplay_ob.size() == 0)
             this->m_mainplay_ob.push_back(new MainPlay(4));
        else
            this->m_mainplay_ob.push_back(new MainPlay(6));
        if(this->m_mainplay_ob.size() > 1)
            this->m_mainplay_ob.back()->setStartPosition(this->m_point_lastpos.x(), this->m_point_lastpos.y());
        this->m_mainplay_ob.back()->show();
        if(this->m_mainplay_ob.size() >= 5)
        {
            this->m_timer_t1->stop();
            this->m_timer_t3->start(10);
            for(int i = 0; i < this->m_mainplay_ob.size(); i ++)
            {
                connect(this->m_mainplay_ob[i], &MainPlay::getClose, [=](){
                    this->m_mainplay_ob.erase(this->m_mainplay_ob.begin() + i);

                });
            }
        }
    });

    connect(m_timer_t2, QTimer::timeout, [=](){
        if(this->m_mainplay_ob.size() >= 1)
            this->m_point_lastpos = this->m_mainplay_ob[0]->m_point_realpos;
    });

    connect(m_timer_t3, QTimer::timeout, [=](){
        if(this->checkIsAttach() && this->m_mainplay_ob.size() > 1)
        {
            if(this->m_i_crash1 == -1 || this->m_i_crash2 == -1)
                return;
            QString str = QString("%1和%2撞到了").arg(this->m_i_crash1 + 1).arg(this->m_i_crash2 + 1);
//            this->m_mainplay_ob[this->m_i_crash1]->hide();
//            this->m_mainplay_ob[this->m_i_crash2]->hide();
//            this->m_mainplay_ob.erase(this->m_mainplay_ob.begin() + this->m_i_crash1);
//            this->m_mainplay_ob.erase(this->m_mainplay_ob.begin() + this->m_i_crash2);
            qDebug() << str;
        }
    });


}


bool creater::checkIsAttach()
{
    int n = this->m_mainplay_ob.size();
    if(n < 2)
        return false;
    int a[10], b[10];
    for(int i = 0; i < n; i ++)
    {

        a[0] = this->m_mainplay_ob[i]->m_point_realpos.y(); // up
        a[2] = this->m_mainplay_ob[i]->m_point_realpos.x(); // l
        a[3] = a[0] + this->m_mainplay_ob[i]->height(); // down
        a[1] = a[2] + this->m_mainplay_ob[i]->width(); // r
        for(int k = 0; k < 4; k ++)
        {
            QString str = QString("当前坐标:%1kizk%2").arg(a[k]).arg(k);
            qDebug().noquote() << str << " ";
        }
        for(int j = i + 1; j < n; j ++)
        {

            b[0] = this->m_mainplay_ob[j]->m_point_realpos.y();
            b[2] = this->m_mainplay_ob[j]->m_point_realpos.x();
            b[3] = b[0] + this->m_mainplay_ob[j]->height();
            b[1] = b[2] + this->m_mainplay_ob[j]->width();
            for(int k = 0; k < 4; k ++)
            {
                QString str = QString("当前坐标:%1qmt%2->%3").arg(b[k]).arg(k).arg(j);
                qDebug().noquote() << str << " ";
            }

            // a[0] < b[3] return false
            // a[3] > b[0] return false;
            // a[2] > b[1] return false;
            // a[1] < b[2] return false;
            int cnt = 0;
            for(int k = 0; k < 4; k ++)
            {
                int t = 3 - k;
                if(t > k)
                {
                    if(b[t] > a[k])
                        cnt ++ ;
                }
                else if(t < k)
                {
                    if(b[t] < a[k])
                        cnt ++ ;
                }
            }
            if(cnt < 2)
            {
                this->m_i_crash1 = i;
                this->m_i_crash2 = j;
                return true;
            }

//            bool flg = false;
//            if(a[0] >= b[3])
//            {
//                if(a[2] <= b[1]) flg = true;
//                if(a[1] >= b[2]) flg = true;
//            }
//            if(a[3] <= b[0])
//            {
//                if(a[2] <= b[1]) flg = true;
//                if(a[1] >= b[2]) flg = true;
//            }
//            if(flg)
//            {
//                this->m_i_crash1 = i;
//                this->m_i_crash2 = j;
//                return true;
//            }
        }
    }
    return false;
}
