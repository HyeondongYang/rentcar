#include "/home/iot/study/cpp/rentcar/header/spotmanage.h"

void spotmanage::show_spot()
{
    system("clear");
    sprintf(query, "SELECT * FROM spot");
    mysql_query(&conn, query);
    sql_result = mysql_store_result(&conn);
    std::cout<<"해수욕장 목록"<<std::endl<<std::endl;  
    while(sql_row = mysql_fetch_row(sql_result))
    {
        std::cout<<"해수욕장 이름: "<<sql_row[0]<<"  해수욕장 위치: "<<sql_row[1]<<std::endl;
    }
    sleep(2);
    mysql_free_result(sql_result);
}

void spotmanage::delete_spot()
{
    show_spot();
    std::cout<<"삭제할 해수욕장 이름 입력: ";
    std::cin>>spot_name;
    sprintf(query, "delete from spot where name = '%s'", spot_name.c_str());
    if(mysql_query(&conn, query)!=0)
    {
        fprintf(stderr, "database connect error : %s\n", mysql_error(&conn));
        std::cout<<"해당 해수욕장이 없습니다"<<std::endl;
    }
    else
    {
        std::cout<<"삭제 완료"<<std::endl;
        sleep(2);
    }
}

void spotmanage::append_spot()
{
    system("clear");
    std::cout<<"추가할 해수욕장 이름 입력: ";
    std::cin>>spot_name;
    std::cout<<"해당 주소 입력: ";
    std::cin>>spot_address;
    sprintf(query, "INSERT INTO spot(name, address) VALUES('%s','%s')", spot_name.c_str(), spot_address.c_str());
    if(mysql_query(&conn, query)!=0)
    {  
        fprintf(stderr, "Failed to connect to databases: Error: %s\n",
        mysql_error(&conn));
    }
    else
    {
        std::cout<<"추가 성공"<<std::endl;
        sleep(2);
    }
}

void spotmanage::change_spot()
{
    int select;
    std::string change_name;
    show_spot();
    std::cout<<"수정할 해수욕장 이름 입력: ";
    std::cin>>spot_name;
    std::cout<<"1. 이름변경 2. 주소변경 : ";
    std::cin>>select;
    if(select == 1)
    {
        std::cout<<"이름: ";
        std::cin>>change_name;
        sprintf(query, "update spot set name = '%s' where name ='%s'", change_name.c_str(), spot_name.c_str());
        if(mysql_query(&conn, query)!=0)
        {  
            fprintf(stderr, "Failed to connect to databases: Error: %s\n",
            mysql_error(&conn));
        }
        else
        {
            std::cout<<"수정 완료"<<std::endl;
            sleep(2);
        }
    }
    else if(select == 2)
    {
        std::cout<<"주소: ";
        std::cin>>spot_address;
        sprintf(query, "update spot set address = '%s' where name ='%s'", spot_address.c_str(), spot_name.c_str());
        if(mysql_query(&conn, query)!=0)
        {  
            fprintf(stderr, "Failed to connect to databases: Error: %s\n",
            mysql_error(&conn));
        }
        else
        {
            std::cout<<"수정 완료"<<std::endl;
            sleep(2);
        }
    }
    else
    {
        std::cout<<"잘못입력했습니다"<<std::endl;
        sleep(2);
    }
}