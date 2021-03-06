#include "/home/iot/study/cpp/rentcar/header/showmenu.h"

#define BUF_SIZE 1024
#define NAME_SIZE 20

char name[NAME_SIZE] = "store";

void showmenu::show_main(int sock)
{
    while (1)
    {
        system("clear");
        std::cout << "1. 회원정보 2. 예약현황 3. 렌터카현황 4. 관광지수정 5. 상담 6. 종료" << std::endl;
        std::cin >> select;
        switch (select)
        {
        case 1:
            show_user_page();
            break;
        case 2:
            show_reservation_page();
            break;
        case 3:
            show_car_page();
            break;
        case 4:
            show_spot_page();
            break;
        case 5:
            send_msg(sock);
            break;
        case 6:
            close(sock);
            exit(0);
            break;
        default:
            break;
        }
    }
}

void showmenu::show_user_page()
{
    while (1)
    {
        system("clear");
        std::cout << "1. 조회 2. 등급변경 3. 돌아가기" << std::endl;
        std::cin >> select;
        switch (select)
        {
        case 1:
            user.show_user_list();
            break;
        case 2:
            user.change_user_grade();
            break;
        case 3:
            return;
            break;
        }
    }
}

void showmenu::show_reservation_page()
{
    while (1)
    {
        system("clear");
        std::cout << "1. 조회 2. 결제 3.돌아가기" << std::endl;
        std::cin >> select;
        switch (select)
        {
        case 1:
            reservation.show_reservation_list();
            break;
        case 2:
            pay.pay();
            break;
        case 3:
            return;
            break;
        }
    }
}

void showmenu::show_car_page()
{
    while (1)
    {
        system("clear");
        std::cout << "1. 조회 2. 수량 3.돌아가기" << std::endl;
        std::cin >> select;
        switch (select)
        {
        case 1:
            car.show_car_list();
            break;
        case 2:
            car.show_total_car_amount();
            break;
        case 3:
            return;
            break;
        }
    }
}

void showmenu::show_spot_page()
{
    while (1)
    {
        system("clear");
        std::cout << "1. 추가 2. 수정 3. 삭제 4.돌아가기" << std::endl;
        std::cin >> select;
        switch (select)
        {
        case 1:
            spot.append_spot();
            break;
        case 2:
            spot.change_spot();
            break;
        case 3:
            spot.delete_spot();
            break;
        case 4:
            return;
            break;
        }
    }
}

void showmenu::send_msg(int sock)
{
    system("clear");
    std::cout<<"상담 (종료: q or Q)"<<std::endl;
    char msg[BUF_SIZE];
    char name_msg[NAME_SIZE + BUF_SIZE];
    sprintf(name_msg, "%s님이 입장했습니다", name);
    write(sock, name_msg, BUF_SIZE);
    while (1)
    {
        fgets(msg, BUF_SIZE, stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
        {
            sprintf(name_msg, "%s님이 퇴장했습니다", name);
            write(sock, name_msg, BUF_SIZE);
            break;
        }
        sprintf(name_msg, "%s: %s", name, msg);
        write(sock, name_msg, BUF_SIZE);
    }
}