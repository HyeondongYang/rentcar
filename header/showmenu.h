#ifndef __SHOWMENU_H_
#define __SHOWMENU_H_

#include "database.h"
#include "carmanage.h"
#include "payment.h"
#include "reservationmanage.h"
#include "spotmanage.h"
#include "usermanage.h"


class showmenu : public Database
{
    private:
        int select;
        carmanage car;
        payment pay;
        reservationmanage reservation;
        spotmanage spot;
        usermanage user;
    public:
        void show_main();
        void show_user_page();
        void show_reservation_page();
        void show_car_page();
        void show_spot_page();
};
#endif