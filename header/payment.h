#ifndef __PAYMENT_H_
#define __PAYMENT_H_
#include "/home/iot/study/cpp/rentcar/header/database.h"

class payment : public Database
{
    private:
        int num;
        std::string user_grade;
        std::string car_name;
        std::string user_id;
        int day;
        int price;
        int pay_money;
        int rent_count;
    public:
        void pay();
        void show_list();
        void select_num();
        void take_user_grade();
        void take_car_price();
        void take_user_count();
};
#endif