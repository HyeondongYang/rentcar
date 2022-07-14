#ifndef __SPOTMANAGE_H_
#define __SOPTMANAGE_H_
#include "/home/iot/study/cpp/rentcar/header/database.h"

class spotmanage : public Database
{
    private:
        std::string spot_name;
        std::string spot_address;
    public:
        void show_spot();
        void delete_spot();
        void append_spot();
        void change_spot();
};
#endif 