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
             this->m_mainplay_ob.push_back(new MainPlay(4)), this->m_mainplay_ob.back()->m_i_id = this->m_mainplay_ob.size();
        else
            this->m_mainplay_ob.push_back(new MainPlay(6)), this->m_mainplay_ob.back()->m_i_id = this->m_mainplay_ob.size();
        if(this->m_mainplay_ob.size() > 1)
            this->m_mainplay_ob.back()->setStartPosition(this->m_point_lastpos.x(), this->m_point_lastpos.y());
        this->m_mainplay_ob.back()->show();
        if(this->m_mainplay_ob.size() >= 5)
        {
            this->m_timer_t1->stop();
            this->m_timer_t3->start(2000);
        }
    });

    connect(m_timer_t2, QTimer::timeout, [=](){
        if(this->m_mainplay_ob.size() >= 1)
            this->m_point_lastpos = this->m_mainplay_ob[0]->m_point_realpos;
    });

    connect(m_timer_t3, QTimer::timeout, [=](){
        if(this->m_mainplay_ob.size() == 1)
            exit(0);
        if(!this->m_b_flg)
        {
            this->m_timer_t3->stop();
            this->m_timer_t3->start(30);
            this->m_b_flg = true;
        }
        if(this->checkIsAttach() && this->m_mainplay_ob.size() > 1)
        {

//            this->m_mainplay_ob[this->m_i_crash1]->hide();
//            this->m_mainplay_ob[this->m_i_crash2]->hide();

            int id1 = this->m_mainplay_ob[this->m_i_crash1]->m_i_id;
            int id2 = this->m_mainplay_ob[this->m_i_crash2]->m_i_id;
            if(id1 == 1 || id2 == 1)
            {
                id1 = max(id1, id2);
                // 将1到的删除

                int idx = -1;
                for(int i = 0; i < (int)this->m_mainplay_ob.size(); i ++)
                    if(this->m_mainplay_ob[i]->m_i_id == id1)
                    {
                        idx = i;
                        break;
                    }
                if(idx != -1)
                {
                    this->m_mainplay_ob[idx]->close();
                    this->m_mainplay_ob.erase(this->m_mainplay_ob.begin() + idx);
                }
            }

//            qDebug() << str;
            // 拿到对应的速度分量
            double vx1 = this->m_mainplay_ob[this->m_i_crash1]->m_point_v.x(), vy1 = this->m_mainplay_ob[this->m_i_crash1]->m_point_v.y();
            double vx2 = this->m_mainplay_ob[this->m_i_crash2]->m_point_v.x(), vy2 = this->m_mainplay_ob[this->m_i_crash2]->m_point_v.y();
            double vx = (vx1 + vx2) / 2;
            double vy = (vy1 + vy2) / 2;
            qDebug() << "1对应的速度分量为: " << vx1 << " " << vy1 << " " << vx2 << " " << vy2;
            vx1 = 2 * vx - vx1;
            vx2 = 2 * vx - vx2;
            vy1 = 2 * vy - vy1;
            vy2 = 2 * vy - vy2;
            this->m_mainplay_ob[this->m_i_crash1]->m_point_v.setX(vx1);
            this->m_mainplay_ob[this->m_i_crash1]->m_point_v.setY(vy1);
            this->m_mainplay_ob[this->m_i_crash2]->m_point_v.setX(vx2);
            this->m_mainplay_ob[this->m_i_crash2]->m_point_v.setY(vy2);
//            this->m_mainplay_ob[this->m_i_crash1]->m_b_iscrash = true;
//            this->m_mainplay_ob[this->m_i_crash2]->m_b_iscrash = true;
//            this->m_mainplay_ob[this->m_i_crash1]->m_point_realpos += this->m_mainplay_ob[this->m_i_crash1]->m_point_v;
//            this->m_mainplay_ob[this->m_i_crash1]->move(this->m_mainplay_ob[this->m_i_crash1]->m_point_realpos);
//            this->m_mainplay_ob[this->m_i_crash2]->m_point_realpos += this->m_mainplay_ob[this->m_i_crash1]->m_point_v;
//            this->m_mainplay_ob[this->m_i_crash2]->move(this->m_mainplay_ob[this->m_i_crash2]->m_point_realpos);
            QString str = QString("%1和%2碰到了").arg(id1).arg(id2);
            qDebug() << str << "对应的速度分量为: " << vx1 << " " << vy1 << " " << vx2 << " " << vy2;
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
        for(int j = i + 1; j < n; j ++)
        {

            b[0] = this->m_mainplay_ob[j]->m_point_realpos.y();
            b[2] = this->m_mainplay_ob[j]->m_point_realpos.x();
            b[3] = b[0] + this->m_mainplay_ob[j]->height();
            b[1] = b[2] + this->m_mainplay_ob[j]->width();

           bool flg = false;
           if(a[0] <= b[3] && a[3] >= b[0])
           {
                if(a[1] >= b[2] && a[2] <= b[1]) flg = true;
                if(a[2] <= b[1] && a[1] >= b[2]) flg = true;
           }
           if(a[3] >= b[0] && a[0] <= b[3])
           {
                if(a[1] >= b[2] && a[2] <= b[1]) flg = true;
                if(a[2] <= b[1] && a[1] >= b[2]) flg = true;
           }
           if(flg)
           {
               this->m_i_crash1 = i;
               this->m_i_crash2 = j;
               return true;
           }
        }
    }
    return false;
}
