#include "/home/iot/study/cpp/rentcar/header/carmanage.h"

void carmanage::show_car_list()
{
    system("clear");
    sprintf(query, "SELECT * FROM car");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"차량 정보"<<std::endl<<std::endl;
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout << "이름: " << sql_row[0] << "  구분: " << sql_row[1] << "  연료: " << sql_row[2] << "  가격: " << sql_row[3] <<"  수량: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}

void carmanage::show_sedan_car_list()
{
    sprintf(query, "SELECT * FROM car where car_type = 'sedan'");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"차량 정보"<<std::endl<<std::endl;
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout << "이름: " << sql_row[0] << "  구분: " << sql_row[1] << "  연료: " << sql_row[2] << "  가격: " << sql_row[3] <<"  수량: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);    
}

void carmanage::show_suv_car_list()
{
    sprintf(query, "SELECT * FROM car where car_type = 'suv'");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"차량 정보"<<std::endl<<std::endl;
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout << "이름: " << sql_row[0] << "  구분: " << sql_row[1] << "  연료: " << sql_row[2] << "  가격: " << sql_row[3] <<"  수량: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}

void carmanage::show_gasoline_car_list()
{
    sprintf(query, "SELECT * FROM car where fuel_type = 'gasoline'");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"차량 정보"<<std::endl<<std::endl;
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout << "이름: " << sql_row[0] << "  구분: " << sql_row[1] << "  연료: " << sql_row[2] << "  가격: " << sql_row[3] <<"  수량: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}

void carmanage::show_disel_car_list()
{
    sprintf(query, "SELECT * FROM car where fuel_type = 'disel'");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"차량 정보"<<std::endl<<std::endl;
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout << "이름: " << sql_row[0] << "  구분: " << sql_row[1] << "  연료: " << sql_row[2] << "  가격: " << sql_row[3] <<"  수량: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}

void carmanage::show_lpg_car_list()
{
    sprintf(query, "SELECT * FROM car where fuel_type = 'lpg'");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"차량 정보"<<std::endl<<std::endl;
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout << "이름: " << sql_row[0] << "  구분: " << sql_row[1] << "  연료: " << sql_row[2] << "  가격: " << sql_row[3] <<"  수량: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}

void carmanage::show_electric_car_list()
{
    sprintf(query, "SELECT * FROM car where fuel_type = 'electric'");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"차량 정보"<<std::endl<<std::endl;
    while (sql_row = mysql_fetch_row(sql_result))
    {
        std::cout << "이름: " << sql_row[0] << "  구분: " << sql_row[1] << "  연료: " << sql_row[2] << "  가격: " << sql_row[3] <<"  수량: "<<sql_row[4]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}

void carmanage::show_total_car_amount()
{
    system("clear");
    int total = 0;
    sprintf(query, "SELECT amount FROM car");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    while (sql_row = mysql_fetch_row(sql_result))
    {
        total+=atoi(sql_row[0]);
    }
    std::cout<<"잔여 차량 수: "<<total<<std::endl;
    sleep(2);
    mysql_free_result(sql_result);
}