#include "/home/iot/study/cpp/rentcar/header/usermanage.h"

void usermanage::show_user_list()
{
    system("clear");
    sprintf(query, "SELECT * FROM user");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"유저 목록"<<std::endl<<std::endl;
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout << "이름: " << sql_row[2] << "  ID: " << sql_row[0] << "  PW: " << sql_row[1] << "  회원등급: " << sql_row[3] <<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}

void usermanage::change_user_grade()
{
    int select;
    show_user_list();
    std::cout << "변경할 유저 ID 입력: ";
    std::cin >> user_id;
    sprintf(query, "SELECT id FROM user where id = '%s'", user_id.c_str());
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    sql_row = mysql_fetch_row(sql_result);
    if(sql_row<=0)
    {
        std::cout<<"해당 유저 없음"<<std::endl;
        sleep(2);
        return;
    }   
    else
    {
    std::cout << "변경할 등급을 선택하세요" << std::endl;
    std::cout << " 1.VIP 2.프리미엄 3.일반 : ";
    std::cin >> select;
    if (select == 1)
    {
        sprintf(query, "update user set grade= 'vip' where id ='%s'", user_id.c_str());
        if (mysql_query(&conn, query) != 0)
        {
            std::cout << "query error" << std::endl;
        }
        else
        {
            std::cout << "변경 완료" << std::endl;
            sleep(2);
        }
    }
    else if (select == 2)
    {
        sprintf(query, "update user set grade = 'premium' where id ='%s'", user_id.c_str());
        if (mysql_query(&conn, query) != 0)
        {
            std::cout << "query error" << std::endl;
        }
        else
        {
            std::cout << "변경 완료" << std::endl;
            sleep(2);
        }
    }
    else if (select == 3)
    {
        sprintf(query, "update user set grade = 'nomal' where id ='%s'", user_id.c_str());
        if (mysql_query(&conn, query) != 0)
        {
            std::cout << "query error" << std::endl;
        }
        else
        {
            std::cout << "변경 완료" << std::endl;
            sleep(2);
        }
    }
    else
    {
        std::cout<<"잘못 입력했습니다"<<std::endl;
        sleep(2);
    }
    }
}