#ifndef __USERMANAGE_H_
#define __USERMANAGE_H_
#include "/home/iot/study/cpp/rentcar/header/database.h"

class usermanage : public Database
{
    private:
        std::string user_id;
    public:
        void show_user_list();
        void change_user_grade(); 
};
#endif 
