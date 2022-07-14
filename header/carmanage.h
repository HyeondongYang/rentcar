#ifndef __CARMANAGE_H_
#define __CARMANAGE_H_
#include "/home/iot/study/cpp/rentcar/header/database.h"

class carmanage : public Database
{
    private:
        std::string car_name;
        std::string car_type;
        std::string fuel_type;
    public:
        void show_car_list();
        void show_sedan_car_list();
        void show_suv_car_list();
        void show_gasoline_car_list();
        void show_disel_car_list();
        void show_lpg_car_list();
        void show_electric_car_list();
        void show_total_car_amount();
};
#endif