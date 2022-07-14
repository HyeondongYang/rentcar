#include "/home/iot/study/cpp/rentcar/header/reservationmanage.h"

void reservationmanage::show_reservation_list()
{
    system("clear");
    sprintf(query, "SELECT * FROM reservation");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"예약 명단"<<std::endl<<std::endl;  
    while(sql_row = mysql_fetch_row(sql_result))
    {
        std::cout<<"ID: "<< sql_row[1]<<"  차량: "<<sql_row[2]<<"  계산: "<<sql_row[3]<<"  대여일수: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}