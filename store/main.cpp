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

char name[NAME_SIZE] = "store";
char msg[BUF_SIZE];

void send_msg(int sock)
{
    char name_msg[NAME_SIZE + BUF_SIZE];
    while (1)
    {
        fgets(msg, BUF_SIZE, stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
        {

        }
        sprintf(name_msg, "%s: %s", name, msg);
        write(sock, name_msg, BUF_SIZE);
    }
}

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
        if(strstr(name_msg, "chat")!=NULL)
        {
            fputs(name_msg, stdout);
            // std::thread second (send_msg, sock);
            // second.join();
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
    serv_addr.sin_port = htons(atoi("9050"));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect");
        return -1;
    }
    
    std::thread first (recv_msg, sock);
    // std::thread second (send_msg, sock);

    showmenu menu;
    menu.show_main();
    first.join();
    // second.join();

    close(sock);
}
