#include "/home/iot/study/cpp/rentcar/header/showmenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <iostream>

#define BUF_SIZE 1024
#define NAME_SIZE 20

char msg[BUF_SIZE];

// void send_msg(int sock)
// {
//     char name_msg[NAME_SIZE + BUF_SIZE];
//     while (1)
//     {
//         fgets(msg, BUF_SIZE, stdin);
//         if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
//         {

//         }
//         sprintf(name_msg, "%s: %s", name, msg);
//         write(sock, name_msg, BUF_SIZE);
//     }
// }

void recv_msg(int sock)
{
    char name_msg[NAME_SIZE + BUF_SIZE];
    int str_len;
    while (1)
    {
        str_len = read(sock, name_msg, BUF_SIZE);
        if (str_len < 0)
        {
            std::cout<<"error"<<std::endl;
        }
        name_msg[str_len] = 0;
        if(strstr(name_msg, "!chat")!=NULL)
        {
            std::cout<<"상담요청!! 상담 페이지로 이동하세요"<<std::endl;
            // std::thread second (send_msg, sock);
            // second.join();
        }
        else if(strstr(name_msg, "!quit")!=NULL)
        {
            std::cout<<"고객이 상담을 종료했습니다"<<std::endl;
        }
        else
        {
            fputs(name_msg, stdout);
        }
    }

}

int main()
{
    int sock;
    struct sockaddr_in serv_addr;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(atoi("9051"));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect");
        return -1;
    }
    
    std::thread first (recv_msg, sock);
    // std::thread second (send_msg, sock);

    showmenu menu;
    menu.show_main(sock);
    first.join();
    // second.join();

    close(sock);
}
