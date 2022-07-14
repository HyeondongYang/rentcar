#ifndef __DATABASE_H_
#define __DATABASE_H_
#include "/usr/include/mysql/mysql.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

class Database
{
protected:
    
public:
    MYSQL *connection = NULL, conn;
    MYSQL_RES *sql_result;
    MYSQL_ROW sql_row;
    char query[1024];
    
    Database()
    {
        mysql_init(&conn);
        mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "utf8");
        connection = mysql_real_connect(&conn, "10.10.20.43", "root", "1234", "rentcar", 3306, NULL, 0);
        if(connection==NULL)
        {
            fprintf(stderr, "Failed to connect to databases: Error: %s\n",
            mysql_error(&conn));
            return;
        }
        else
        {
            puts("Database connect!");
        }
    }
};
#endif