#ifndef __RESERVATIONMANAGE_H_
#define __RESERVATIONMANAGE_H_
#include "/home/iot/study/cpp/rentcar/header/database.h"

class reservationmanage : public Database
{
    private:

    public:
        void show_reservation_list();
};
#endif