#include "/home/iot/study/cpp/rentcar/header/payment.h"

void payment::pay()
{
    show_list();
    if(strcmp(user_grade.c_str(), "vip")==0)
    {
        pay_money=price*day*0.8;
    }
    else if(strcmp(user_grade.c_str(), "premium")==0)
    {
        pay_money=price*day*0.9;
    }
    else if(strcmp(user_grade.c_str(), "nomal")==0)
    {
        pay_money=price*day;
    }
    sprintf(query, "update reservation set payment = 'y' where num ='%d'", num);
    if(mysql_query(&conn, query)!=0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&conn));
    }
    else
    {
        sprintf(query, "INSERT INTO sales(money) VALUES('%d')", pay_money);
        if(mysql_query(&conn, query)!=0)
        {
            fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&conn));
        }
        else
        {
            sprintf(query, "update user set count = '%d' where id ='%s'", rent_count, user_id.c_str());
            if(mysql_query(&conn, query)!=0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&conn));
            }
            else
            {
                std::cout<<"결제금액: "<<pay_money<<" 승인완료"<<std::endl;
                sleep(2);
            }
        }
    }
}

void payment::show_list()
{
    system("clear");
    sprintf(query, "SELECT * FROM reservation where payment = 'n'");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout<<"예약번호: "<<sql_row[0]<<"ID: "<<sql_row[1]<<"  차량: "<<sql_row[2]<<"  대여일수: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    select_num();
}

void payment::select_num()
{
    std::cout<<"예약번호 입력: ";
    std::cin>>num;
    sprintf(query, "SELECT * FROM reservation where num = '%d'", num);
    
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    sql_row = mysql_fetch_row(sql_result);
    num=atoi(sql_row[0]);
    user_id=sql_row[1];
    car_name=sql_row[2];
    day=atoi(sql_row[4]);
    take_user_grade();
    take_car_price();
    take_user_count();    
}

void payment::take_user_grade()
{
    sprintf(query, "SELECT grade FROM user where id = '%s'", user_id.c_str());
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    sql_row = mysql_fetch_row(sql_result);
    user_grade = sql_row[0];
}

void payment::take_user_count()
{
    sprintf(query, "SELECT count FROM user where id = '%s'", user_id.c_str());
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    sql_row = mysql_fetch_row(sql_result);
    rent_count= atoi(sql_row[0])+ 1;
}

void payment::take_car_price()
{

    sprintf(query, "SELECT price FROM car where name = '%s'", car_name.c_str());
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    sql_row = mysql_fetch_row(sql_result);
    price = atoi(sql_row[0]);    
}