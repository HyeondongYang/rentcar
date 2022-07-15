#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <pthread.h>
#include "/home/iot/study/cpp/rentcar/header/database.h"

#define BUF_SIZE 1024
#define MAX_CLNT 256

void *handle_clnt(void *arg);
void send_msg(char *msg, int clnt_sock);
void save_msg(char* msg);

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];

Database db;

int main(int argc, char **argv)
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    pthread_t tid;

    if (argc != 2)
    {
        printf("usage : %s <port>\n", argv[0]);
        return -1;
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock < 0)
    {
        perror("socket");
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind");
        return -1;
    }

    if (listen(serv_sock, 5) < 0)
    {
        perror("listen");
        return -1;
    }

    while (1)
    {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock < 0)
        {
            perror("accept");
            return -1;
        }

        clnt_socks[clnt_cnt++] = clnt_sock;

        pthread_create(&tid, NULL, handle_clnt, (void *)&clnt_sock);
        pthread_detach(tid);
        printf("Connected client IP : %s\n", inet_ntoa(clnt_addr.sin_addr));
    }

    close(serv_sock);
    return 0;
}

void *handle_clnt(void *arg)
{
    int clnt_sock = *((int *)arg);
    int str_len = 0;
    char msg[BUF_SIZE];

    memset(msg, 0, BUF_SIZE);
    while (str_len = read(clnt_sock, msg, BUF_SIZE) != 0)
    {
        send_msg(msg, clnt_sock);
        save_msg(msg);
    }
    for (int i = 0; i < clnt_cnt; i++)
    {
        if (clnt_sock == clnt_socks[i])
        {
            while (++i < clnt_cnt)
            {
                clnt_socks[i - 1] = clnt_socks[i];
            }
            break;
        }
    }
    clnt_cnt--;

    close(clnt_sock);
    return NULL;
}

void send_msg(char *msg, int clnt_sock)
{
    std::cout<<msg<<std::endl;
    for (int i = 0; i < clnt_cnt; i++)
    {
        if(clnt_sock!=clnt_socks[i])
            write(clnt_socks[i], msg, BUF_SIZE);
    }

}

void save_msg(char* msg)
{
    std::cout<<msg<<std::endl;
    sprintf(db.query, "INSERT INTO chat(chatlog) VALUES('%s')", msg);
    if(mysql_query(&db.conn, db.query)!=0)
    {  
        fprintf(stderr, "Failed to connect to databases: Error: %s\n",
        mysql_error(&db.conn));
    }
    else
    {
        std::cout<<"추가 성공"<<std::endl;
    }
}