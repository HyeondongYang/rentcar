#include "database.h"
#include <iostream>
#include <string.h>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <thread>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
// g++ clientmain.cpp client.cpp -lmysqlclient
using namespace std;

// 회워가입 : 일반회원(normal)/ 이름,id,pw
class User : public Database // << 객체를 만들어서 쓸 것
{
protected:
    string Name;
    int test;    // 실험용
    string pass; // 아무키 누를 시 다음으로 넘어감
    // id/pw/name/grade/count
    //등급
public:
    char Query[1024];
    string Id;
    string Pw;
    int mysql_num;
    //로그인, 회원가입, id찾기, 비밀번호 찾기
    void SignUp();       // 회원 가입
    void remove_infor(); // id 반환
    string Login();      // id 반환
    void FindId();
    void FindPw();
};

void User::remove_infor()
{
    cout << "회원 탈퇴를 진행합니다.\n\n";
    cout << "아이디를 입력하세요: ";
    cin >> Id;
    // strcpy(Id_copy, Id);
    cout << "비밀번호를 입력하세요: ";
    cin >> Pw;
    sprintf(Query, "select pw from user where id='%s'", Id.c_str());
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(ConnPtr));
    }
    else
    {
        Result = mysql_store_result(&Conn);
        mysql_num = mysql_num_rows(Result);
        if (mysql_num == 0) // id 잘못 입력 시
        {
            cout << "\n\tid 또는 pw를 잘못 입력했습니다.\n";
            cout << "\t확인 하신 후 아무키나 눌러주세요" << endl;
            cin >> pass;
            system("clear");
            mysql_free_result(Result);
            return;
        }
        if ((Row = mysql_fetch_row(Result)) != NULL) // 아이디 존재 시
        {
            if (Row[0] == Pw) //해당 아이디에 비밀번호와 같다면
            {
                sprintf(Query, "delete from user where id='%s'", Id.c_str());
                if (mysql_query(&Conn, Query) != 0)
                {
                    fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(ConnPtr));
                }
                else
                {
                    cout << "\t[ 회원 탈퇴가 정상적으로 처리되었습니다. ]\n\n";
                }
            }
            else
            {
                cout << "--------------------------------\n";
                cout << "비밀번호를 잘못 입력했습니다.\n";
                cout << "--------------------------------\n";
            }
            mysql_free_result(Result);
            cout << "\t확인 하신 후 아무키나 눌러주세요" << endl;
            cin >> pass;
            system("clear");
        }
    }
}

void User::SignUp()
{
    cout << "사용하실 이름을 입력하세요: ";
    cin >> Name;
    cout << "사용하실 ID를 입력하세요: ";
    cin >> Id;
    sprintf(Query, "select * from user where ID='%s'", Id.c_str());
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
    }
    else
    {
        cout << "=======ID 중복 검사를 실행합니다.=======\n";
        Result = mysql_store_result(&Conn);
        mysql_num = mysql_num_rows(Result); // 개수 반환       없으면 0    있으면 레코드 갯수 반환      
        if (mysql_num == 0)
        {
            cout << "----------------------------------------\n";
            cout << "\t사용가능한 아이디 입니다.\n";
            cout << "----------------------------------------\n";
            mysql_free_result(Result);
            cout << "사용하실 PW를 입력하세요: ";
            cin >> Pw;
            sprintf(Query, "INSERT INTO user(id,pw,name,grade,count) VALUES('%s','%s','%s','Normal','0')", Id.c_str(), Pw.c_str(), Name.c_str());
            if (mysql_query(&Conn, Query) != 0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
            }
            else
            {
                sprintf(Query, "select * from user where ID='%s'", Id.c_str());
                if (mysql_query(&Conn, Query) != 0)
                {
                    fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                }
                else
                {
                    Result = mysql_store_result(ConnPtr); // 쿼리 수행한 결과 값 모두 담음
                    if ((Row = mysql_fetch_row(Result)) != NULL)
                    {
                        cout << "회원가입하신 정보입니다.....\n";
                        cout << "NAME: " << Row[2] << endl; // 배열 상태로 출력
                        cout << " ID : " << Row[0] << endl;
                        cout << " PW : " << Row[1] << endl;
                        cout << "grade: " << Row[3] << endl;
                        cout << "rent count:" << Row[4] << endl;
                        cout << "\n확인하신 후 아무키나 누르세요...";
                        cin >> pass;
                        system("clear");
                        mysql_free_result(Result);
                    }
                }
            }
        }
        else
        {
            cout << "사용중인 아이디입니다.\n";
            cout << "\n확인하신 후 아무키나 누르세요...";
            cin >> pass;
            system("clear");
        }
    }
}

string User::Login()
{
    cout << "<로그인 페이지>"
         << "\nID: ";
    cin >> Id;
    cout << "PW: ";
    cin >> Pw;


    sprintf(Query, "select pw from user where id='%s'", Id.c_str());
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
    }
    else
    {
        Result = mysql_store_result(&Conn);
        mysql_num = mysql_num_rows(Result); // 개수 반환       없으면 0    있으면 레코드 갯수 반환      
        if (mysql_num == 0)
        {
            cout << "아이디나 비밀번호를 잘못입력했습니다.\n"; // id..틀리면
            mysql_free_result(Result);
        }
        else
        {
            Row = mysql_fetch_row(Result); // 배열 형태로 바꿈
            if (Row[0] == Pw)
            {
                cout << "로그인 되었습니다.\n";
                cout << "\n확인하신 후 아무키나 누르세요...";
                cin >> pass;
                system("clear");
                return string(Id);
            }
            else
            {
                cout << "아이디나 비밀번호를 잘못입력했습니다.\n"; // pw..틀리면
            }
        }
        cout << "\n확인하신 후 아무키나 누르세요...";
        cin >> pass;
        system("clear");
        return string("no");
    }
}

void User::FindId()
{
    cout << "<아이디 찾기 페이지>\n";
    cout << "등록된 이름 입력: ";
    cin >> Name;

    sprintf(Query, "select id,pw from user where name='%s'", Name.c_str()); //// 동일한 이름 포함하여 쿼리문 실행
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
    }
    else
    {
        cout << "등록된 PW 입력: ";
        cin >> Pw;
        Result = mysql_store_result(&Conn); // 결과 값 담음

        while ((Row = mysql_fetch_row(Result)) != NULL) // 한행 씩 출력 Row[0],[1]
        {
            if (Row[1] == Pw) // // 회원일 때만 사용했던 ID 제공
            {
                cout << "사용자의 ID는 [ " << Row[0] << " ] 입니다." << endl;
                cout << "\n확인하신 후 아무키나 누르세요...";
                cin >> pass;
                system("clear");
                mysql_free_result(Result); // 결과 값 담은 것을 메모리 해체
                return;
            }
        }
        cout << "\n\t가입하신 이름 또는 pw를 잘못입력했습니다.\n"; // Row값에 아무 것도 없을 시 출력문
        cout << "\n확인하신 후 아무키나 누르세요...";
        cin >> pass;
        system("clear");
        mysql_free_result(Result);
    }
}

void User::FindPw()
{
    cout << "<비밀번호 찾기 페이지>" << endl;
    cout << "등록된 이름 입력: ";
    cin >> Name;
    sprintf(Query, "select id,pw from user where Name='%s'", Name.c_str()); // 동일한 이름 포함하여 쿼리문 실행
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
    }
    else
    {
        cout << "본인의 ID 입력: "; // 동일한 이름 중 ID 통해 pw가 명확해짐
        cin >> Id;
        Result = mysql_store_result(&Conn);             // 결과 값을 모두 담음
        while ((Row = mysql_fetch_row(Result)) != NULL) // 배열 형태로 바꿈
        {
            if (Row[0] == Id) // id가 존재하며, 회원일 때
            {
                cout << "사용자의 PW는 [ " << Row[1] << " ] 입니다." << endl;
                cout << "\n확인하신 후 아무키나 누르세요...";
                cin >> pass;
                system("clear");
                mysql_free_result(Result); // 결과 값 메모리 해체
                return;
            }
        }
        cout << "가입하신 이름 또는 ID를 잘못입력했습니다.\n";
        cout << "\n확인하신 후 아무키나 누르세요...";
        cin >> pass;
        system("clear");
        mysql_free_result(Result);
    }
}

class Spot : public Database // 관광지 조회
{
private:
    string Name;
    string likeName;
    string pass;
    int sltNum;
    int mysql_num; // mysql_num_rows () 반환값 받기
    char Query[1024];

public:
    void Search();
};
void Spot::Search()
{
    while (1)
    {
        cout << "<제주도 관광지 조회 페이지>" << endl;
        cout << "1) 전체 조회  2) 지역명으로 조회   3) 주소로 조회  0) 그만 조회\n>>";
        cin >> sltNum;

        if (sltNum == 1)
        {
            sprintf(Query, "select * from spot");
            if (mysql_query(&Conn, Query) != 0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
            }
            else
            {
                cout << "--------------------------------------------\n";
                Result = mysql_store_result(&Conn);
                while ((Row = mysql_fetch_row(Result)) != NULL)
                {
                    cout << "\tname: " << Row[0];
                    cout << "\n\taddress: " << Row[1];
                    cout << "\n--------------------------------------------\n"
                         << endl;
                }
                mysql_free_result(Result);
            }
        }
        else if (sltNum == 2)
        {
            cout << "지역명을 입력하세요(일부 단어만 입력 가능): ";
            cin >> Name;
            likeName = "%" + Name + "%";
            sprintf(Query, "select * from spot where name like '%s'", likeName.c_str());
            if (mysql_query(&Conn, Query) != 0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
            }
            else
            {
                Result = mysql_store_result(&Conn);
                mysql_num = mysql_num_rows(Result);
                cout << "--------------------------------------\n"
                     << endl;
                if (mysql_num == 0)
                {
                    mysql_free_result(Result);
                    cout << "\t조회한 결과가 없습니다.\n";
                    cout << "--------------------------------------\n"
                         << endl;
                }
                else
                {
                    while ((Row = mysql_fetch_row(Result)) != NULL)
                    {
                        cout << "\tname: " << Row[0];
                        cout << "\n\taddress: " << Row[1];
                        cout << "\n--------------------------------------\n"
                             << endl;
                    }
                    mysql_free_result(Result);
                }
            }
        }
        else if (sltNum == 3)
        {
            cout << "주소를 입력하세요(일부 단어만 입력가능): ";
            cin >> Name;
            likeName = "%" + Name + "%";
            sprintf(Query, "select * from spot where address like '%s'", likeName.c_str());
            if (mysql_query(&Conn, Query) != 0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
            }
            else
            {
                Result = mysql_store_result(&Conn);
                mysql_num = mysql_num_rows(Result);
                cout << "--------------------------------------\n"
                     << endl;
                if (mysql_num == 0)
                {
                    cout << "\t조회한 결과가 없습니다.\n";
                    cout << "--------------------------------------\n"
                         << endl;
                }
                else
                {
                    while ((Row = mysql_fetch_row(Result)) != NULL)
                    {
                        cout << "\tname: " << Row[0];
                        cout << "\n\taddress: " << Row[1];
                        cout << "\n--------------------------------------\n"
                             << endl;
                    }
                }
                mysql_free_result(Result);
            }
        }
        else if (sltNum == 0)
        {
            cout << "그만 조회합니다.\n";
            cout << "\n확인하신 후 아무키나 누르세요...";
            cin >> pass;
            system("clear");
            break;
        }
        else
        {
            cout << "잘못 선택했습니다.\n";
        }
        cout << "\n확인하신 후 아무키나 누르세요...";
        cin >> pass;
        system("clear");
    }
}

class Reservation : public Database // 예약
{                                   // id, car_name, payment, day
                                    //지불여부(y,n)
private:
    int changeInt;
    int sltNum; // 고유번호 입력
    int day;
    int mysql_num;
    string car;
    string str; //  char형 포인터 id   >> string 변환
    string Name;
    string likeName;
    string pass;
    char fuel[20];
    char Query[1024];

public:
    void Search();                           // 조회
    void Confirmation(string Id, int count); // 예약 확정  (로그인 하면서 아이디 반환하여 하기)
    void Cancel(string Id);                  // 취소
    void Cancellation(string Id);            // 변경
};

void Reservation::Search()
{
    while (1)
    {
        cout << "\t<렌터카 조회 페이지>\n";
        cout << "1) 전체 조회  2) 이름으로 조회 3) 연료 타입으로 조회  0) 그만 조회\n>>";
        cin >> sltNum;
        if (sltNum == 1)
        {
            sprintf(Query, "select * from car");
            if (mysql_query(&Conn, Query) != 0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
            }
            else
            {
                cout << "---------------------------------\n"
                     << endl;
                Result = mysql_store_result(&Conn);
                while ((Row = mysql_fetch_row(Result)) != NULL)
                {
                    cout << "\tname: " << Row[0];
                    cout << "\n\ttype: " << Row[1];
                    cout << "\n\tfuel_type: " << Row[2];
                    cout << "\n\tprice: " << Row[3];
                    cout << "\n\tamount: " << Row[4];
                    cout << "\n---------------------------------\n"
                         << endl;
                }
                mysql_free_result(Result);
            }
        }
        else if (sltNum == 2)
        {
            cout << "렌터카 이름을 입력하세요(일부 단어만 입력가능): ";
            cin >> Name;
            likeName = "%" + Name + "%";
            sprintf(Query, "select * from car where name like '%s'", likeName.c_str());
            if (mysql_query(&Conn, Query) != 0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
            }
            else
            {
                Result = mysql_store_result(&Conn);
                mysql_num = mysql_num_rows(Result); // 개수 반환       없으면 0    있으면 레코드 갯수 반환      
                cout << "---------------------------------" << endl;
                if (mysql_num > 0)
                {
                    while ((Row = mysql_fetch_row(Result)) != NULL)
                    {
                        cout << "\tname: " << Row[0];
                        cout << "\n\ttype: " << Row[1];
                        cout << "\n\tfuel_type: " << Row[2];
                        cout << "\n\tprice: " << Row[3];
                        cout << "\n\tamount: " << Row[4];
                        cout << "\n---------------------------------" << endl;
                    }
                    mysql_free_result(Result);
                }
                else
                {
                    cout << "\t조회한 결과가 없습니다.\n";
                    cout << "---------------------------------" << endl;
                    mysql_free_result(Result);
                }
            }
        }
        else if (sltNum == 3)
        {
            cout << "연료 타입을 입력하세요: ";
            cin >> fuel;
            sprintf(Query, "select * from car where fuel_type='%s'", fuel);
            if (mysql_query(&Conn, Query) != 0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
            }
            else
            {
                Result = mysql_store_result(&Conn);
                mysql_num = mysql_num_rows(Result); // 개수 반환       없으면 0    있으면 레코드 갯수 반환      
                cout << "---------------------------------" << endl;
                if (mysql_num > 0)
                {
                    while ((Row = mysql_fetch_row(Result)) != NULL)
                    {
                        cout << "\tname: " << Row[0];
                        cout << "\n\ttype: " << Row[1];
                        cout << "\n\tfuel_type: " << Row[2];
                        cout << "\n\tprice: " << Row[3];
                        cout << "\n\tamount: " << Row[4];
                        cout << "\n---------------------------------" << endl;
                    }
                    mysql_free_result(Result);
                }
                else
                {
                    cout << "\t조회한 결과가 없습니다.\n";
                    cout << "---------------------------------" << endl;
                    mysql_free_result(Result);
                }
            }
        }
        else if (sltNum == 0)
        {
            cout << "그만 조회합니다.\n";
            cout << "\n확인하신 후 아무키나 누르세요..";
            cin >> pass;
            system("clear");
            break;
        }
        else
        {
            cout << "잘못 선택했습니다.\n";
        }
        cout << "\n확인하신 후 아무키나 누르세요...";
        cin >> pass;
        system("clear");
    }
}

void Reservation::Confirmation(string Id, int count) // 확정    (로그인 하면서 아이디 반환하여 받기)
{
    cout << "\t<예약 페이지>" << endl;
    cout << "차량 이름 입력: ";
    cin >> Name;
    sprintf(Query, "select num,id,car_name,day from reservation where id = '%s'", Id.c_str()); // 해당 아이디에 차량 예약있는지
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
    }
    else // 동일 아이디 예약 불가
    {
        Result = mysql_store_result(&Conn);
        mysql_num = mysql_num_rows(Result); // 개수 반환       없으면 0    있으면 레코드 갯수 반환      
        if (mysql_num > 1)                  // 해당 아이디에 차량 예약이 있다면
        {
            cout << "----------------------------------------\n";
            cout << "이미 1대의 차량이 예약되어있습니다. \n";
            cout << "동일 ID로 예약 불가 합니다.\n";
            cout << "----------------------------------------\n";
            mysql_free_result(Result);
            cout << "\n확인하신 후 아무키나 누르세요...";
            cin >> pass;
            system("clear");
            return;
        }
    }

    sprintf(Query, "select name,amount from car where name = '%s'", Name.c_str()); // 차량 이름이 있는지
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
    }
    else
    {
        Result = mysql_store_result(&Conn);
        mysql_num = mysql_num_rows(Result);
        if (mysql_num > 0) // 검색이 되면
        {
            if ((Row = mysql_fetch_row(Result)) != NULL) // 쿼리문 수행으로 DB의 한 행만 가져옴
            {
                cout << "\tname: " << Row[0] << endl;
                changeInt = atoi(Row[1]); // 정수로 변환
                if (changeInt < 1)        // 남은 차량이 없으면
                {
                    mysql_free_result(Result);
                    cout << "---------------------------------------------------\n";
                    cout << "해당 " << Name << " 차량은 예약 마감되었습니다.\n";
                    cout << "---------------------------------------------------\n";
                    cout << "\n확인하신 후 아무키나 누르세요...";
                    cin >> pass;
                    system("clear");
                    return;
                }
                else // 남은 차량이 있으면
                {
                    cout << "\n\n   한대만 예약을 할 수 있습니다.\n 숫자 1을 입력: ";
                    cin >> sltNum;

                    if (sltNum == 0 || sltNum > 1)
                    {
                        cout << "\n1대의 차량만 랜트할 수 있습니다." << endl;
                        cout << "\n확인하신 후 아무키나 누르세요...";
                        cin >> pass;
                        system("clear");
                        return;
                    }
                    cout << "------------------------------------" << endl;
                    mysql_free_result(Result);
                    sprintf(Query, "update car set amount='%d' where name = '%s'", changeInt - sltNum, Name.c_str()); // car 테이블 업데이트
                    if (mysql_query(&Conn, Query) != 0)
                    {
                        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                    }
                    else
                    {
                        cout << "\n빌릴기간을 입력하세요: ";
                        cin >> day;
                        sprintf(Query, "insert into reservation(num, id, car_name, payment,day) values ('%d','%s','%s','n','%d')", count, Id.c_str(), Name.c_str(), day); // reservation 테이블 삽입
                        if (mysql_query(&Conn, Query) != 0)
                        {
                            fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                        }
                        else
                        {
                            cout << "\n    예약이 완료 되었습니다.\n";
                            cout << "------------------------------------" << endl;
                            cout << "\n확인하신 후 아무키나 누르세요...";
                            cin >> pass;
                            system("clear");
                            return; // 쿠폰 접립 하기 //////////////////
                        }
                    }
                }
            }
        }
        else // 검색 안되면
        {
            cout << Name << "차량은 존재하지 않습니다.\n";
            cout << "------------------------------------" << endl;
            cout << "\n확인하신 후 아무키나 누르세요...";
            cin >> pass;
            system("clear");
            mysql_free_result(Result);
        }
    }
}

void Reservation::Cancel(string Id) // 취소
{
    sprintf(Query, "select num,id,car_name,day from reservation where id = '%s'", Id.c_str());
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
    }
    else
    {
        Result = mysql_store_result(&Conn);
        mysql_num = mysql_num_rows(Result); // 개수 반환       없으면 0    있으면 레코드 갯수 반환      
        if (mysql_num == 0)
        {
            cout << "----------------------------------------";
            cout << "\t예약된 차량이 없습니다. \n";
            cout << "----------------------------------------";
            mysql_free_result(Result);
            cout << "\n확인하신 후 아무키나 누르세요...";
            cin >> pass;
            system("clear");
            return;
        }

        cout << "---------------------------------\n";
        cout << Id << "님의 예약 목록입니다.\n";
        if ((Row = mysql_fetch_row(Result)) != NULL)
        {
            cout << "\t고유번호: " << Row[0] << endl;
            cout << "\n\t차량이름: " << Row[2] << endl;
            str = Row[2]; // 복사
            cout << "\n\t기간: " << Row[3] << "일" << endl;
            cout << "---------------------------------\n";
            cout << "고유번호 입력: ";
            cin >> sltNum;
            if (atoi(Row[0]) == sltNum)
            {
                mysql_free_result(Result);
                sprintf(Query, "delete from  reservation where id  = '%s'", Id.c_str()); // 예약테이블에서 레코드 삭제
                if (mysql_query(&Conn, Query) != 0)
                {
                    fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                }
                else // 예약 취소 완료
                {
                    sprintf(Query, "select amount from car where name = '%s'", str.c_str()); // 차 테이블에서 레코드 검색
                    if (mysql_query(&Conn, Query) != 0)
                    {
                        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                    }
                    else
                    {
                        Result = mysql_store_result(&Conn);
                        if ((Row = mysql_fetch_row(Result)) != NULL)
                        {
                            changeInt = atoi(Row[0]);
                            changeInt++;
                            mysql_free_result(Result);
                            sprintf(Query, "update car set amount='%d' where name = '%s'", changeInt, str.c_str()); // car 테이블 업데이트
                            if (mysql_query(&Conn, Query) != 0)
                            {
                                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                            }
                            else
                            {
                                cout << "예약이 취소 되었습니다.\n";
                                cout << "\n확인하신 후 아무키나 누르세요...";
                                cin >> pass;
                                system("clear");
                            }
                        }
                    }
                }
            }
            else
            {
                mysql_free_result(Result);
                cout << "고유번호를 잘못 입력하여 예약취소가 되지않았습니다.\n";
                cout << "\n확인하신 후 아무키나 누르세요...";
                cin >> pass;
                system("clear");
            }
        }
    }
}

void Reservation::Cancellation(string Id) //  변경
{
    sprintf(Query, "select num,car_name,day from reservation where id = '%s'", Id.c_str());
    if (mysql_query(&Conn, Query) != 0)
    {
        fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
    }
    else
    {
        Result = mysql_store_result(&Conn);
        mysql_num = mysql_num_rows(Result); // 개수 반환       없으면 0    있으면 레코드 갯수 반환      
        if (mysql_num == 0)                 // 해당 아이디로 등록딘 차량 없으면
        {
            cout << "----------------------------------------\n";
            cout << "\t예약된 차량이 없습니다. \n";
            cout << "----------------------------------------\n";
            mysql_free_result(Result);
            cout << "\n확인하신 후 아무키나 누르세요...";
            cin >> pass;
            system("clear");
            return;
        }

        cout << "---------------------------------\n";
        cout << Id << "님의 예약 목록입니다.\n";
        if ((Row = mysql_fetch_row(Result)) != NULL)
        {
            cout << "\t고유번호: " << Row[0] << endl;
            cout << "\t차량이름: " << Row[1] << endl;
            cout << "\t기간: " << Row[2] << "일" << endl;
            cout << "---------------------------------\n";
            mysql_free_result(Result);
            cout << "1)  차량변경    2)  기간변경\n입력:";
            cin >> sltNum;
            if (sltNum == 1)
            {
                cout << "예약하신 차량이름을 입력: ";
                cin >> car;
                sprintf(Query, "select car_name from reservation where id = '%s'", Id.c_str());
                if (mysql_query(&Conn, Query) != 0)
                {
                    fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                }
                else
                {
                    Result = mysql_store_result(&Conn);
                    if ((Row = mysql_fetch_row(Result)) != NULL)//////////////
                    {
                        str = Row[0];
                        mysql_free_result(Result);
                        if (str == car)
                        {
                            cout << "변경하실 차량이름을 입력: ";
                            cin >> car;
                            sprintf(Query, "select name, amount from car where name = '%s'", car.c_str());
                            if (mysql_query(&Conn, Query) != 0)
                            {
                                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                            }
                            else
                            {
                                Result = mysql_store_result(&Conn);
                                mysql_num = mysql_num_rows(Result); // 개수 반환       없으면 0    있으면 레코드 갯수 반환      
                                if (mysql_num == 0)                 // 차량이름 잘못 입력 시
                                {
                                    cout << "----------------------------------------\n";
                                    cout << "\t" << car << " 차량은 존재하지 없습니다. \n";
                                    cout << "    공백을 포함하여 다시 입력하십시오.\n";
                                    cout << "----------------------------------------\n";
                                    cout << "\n확인하신 후 아무키나 누르세요...";
                                    cin >> pass;
                                    system("clear");
                                    mysql_free_result(Result);
                                    return;
                                }
                                if ((Row = mysql_fetch_row(Result)) != NULL)
                                {
                                    changeInt = atoi(Row[1]);
                                    if (changeInt < 1) // 예약 불가
                                    {
                                        mysql_free_result(Result);
                                        cout << "해당 " << car << " 차량은 예약 마감되었습니다.\n";
                                    }
                                    else // 예약가능
                                    {
                                        changeInt--;
                                        mysql_free_result(Result);
                                        sprintf(Query, "update car set amount='%d' where name = '%s'", changeInt, car.c_str()); // 현재에 빌린차량으로 감소
                                        if (mysql_query(&Conn, Query) != 0)
                                        {
                                            fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                                        }
                                        else
                                        {
                                            sprintf(Query, "update reservation set car_name='%s' where id = '%s'", Name.c_str(), Id.c_str()); // reservation 테이블 변경
                                            if (mysql_query(&Conn, Query) != 0)
                                            {
                                                fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                                            }
                                            else
                                            {
                                                cout << Query;
                                                cout << Name << "차량으로 변경이 되었습니다.\n";
                                            }
                                        }
                                        sprintf(Query, "select amount from car where name = '%s'", str.c_str());
                                        if (mysql_query(&Conn, Query) != 0)
                                        {
                                            fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                                        }
                                        else
                                        {
                                            Result = mysql_store_result(&Conn);
                                            if ((Row = mysql_fetch_row(Result)) != NULL)
                                            {
                                                changeInt = atoi(Row[0]);
                                                changeInt++;
                                                mysql_free_result(Result);
                                                sprintf(Query, "update car set amount='%d' where name = '%s'", changeInt, str.c_str()); // 과거에 빌에 차량 증가
                                                if (mysql_query(&Conn, Query) != 0)
                                                {
                                                    fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            cout << "예약하신 차량과 불일치 합니다.\n";
                        }
                    }
                }
            }
            else if (sltNum == 2)
            {
                cout << "기존 기간 입력: ";
                cin >> day;
                sprintf(Query, "select num,car_name,day from reservation where id = '%s'", Id.c_str());
                if (mysql_query(&Conn, Query) != 0)
                {
                    fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                }
                else
                {
                    Result = mysql_store_result(&Conn);
                    Row = mysql_fetch_row(Result);
                    changeInt = atoi(Row[2]);
                    if (changeInt == day)
                    {
                        cout << "변경할 기간 입력: ";
                        cin >> day;
                        sprintf(Query, "update reservation set day='%d' where id = '%s'", day, Id.c_str()); // car 테이블 업데이트
                        if (mysql_query(&Conn, Query) != 0)
                        {
                            fprintf(stderr, "Failed to connect to databases: Error: %s\n", mysql_error(&Conn));
                        }
                        else
                        {
                            cout << "기간 변경이 완료되었습니다.\n";
                        }
                    }
                    else
                    {
                        cout << "예약을 하셨던 기간이 틀렸습니다.\n";
                    }
                    mysql_free_result(Result);
                }
            }
            cout << "\n확인하신 후 아무키나 누르세요...";
            cin >> pass;
            system("clear");
        }
    }
}

char name[20] = "[DEFAULT]";

void send_msg(int sock) // send main
{
    char name_msg[1024]; //크기를 이름과 버퍼사이즈로 넣어준다
    char msg[1024];

    while (1)
    {
        fgets(msg, 1024, stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
        {
            memset(msg, 0, 1024);
            strcpy(msg, "!quit");
            write(sock, msg, 1024);
            break;
        }
        sprintf(name_msg, "%s: %s", name, msg);
        write(sock, name_msg, 1024);
    }
}

void recv_msg(int sock) // read thread main
{

    char name_msg[1024];
    int str_len;

    while (1)
    {
        memset(name_msg, 0, 1024);
        str_len = read(sock, name_msg, 1024);
        if (str_len < 0)
        {
            cout << "error" << endl;
        } // printf("길이 : %d\n", str_len);
        name_msg[str_len] = 0;
        if (strstr(name_msg, "Clear") != NULL)
        {
            system("clear");
            continue;
        }
        else if (str_len == -1) // read 실패시
        {
            printf("메세지를 읽어오지 못했습니다.\n");
        }
        fputs(name_msg, stdout);
    }
}

int main()
{
    // db, user, spot;
    // user,reservation;
    User user;
    Spot spot;
    Reservation reser;
    int slt;
    string id;
    string pass;
    int count = 0;

    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    char msg[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("10.10.20.33");
    serv_addr.sin_port = htons(atoi("9050"));
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect");
        return -1;
    }
    thread first(recv_msg, sock);

    while (1)
    {
        cout << "1)  회원가입   2) 로그인   3) ID/PW찾기  4) 회원탈퇴  5) 종료\n";
        cin >> slt;
        switch (slt)
        {
        case 1:
            user.SignUp();
            break;
        case 2:
            id = user.Login();
            if (id != "no")
            {
                while (1)
                {
                    cout << "1) 관광지 조회  2) 렌터카 조회  3) 렌터카 예약  4)  렌터카 취소  5) 렌터카 변경  6) 채팅  0) 홈으로\n입력:";
                    cin >> slt;
                    if (slt == 1)
                    {
                        spot.Search();
                    }
                    else if (slt == 2)
                    {
                        reser.Search();
                    }
                    else if (slt == 3)
                    {
                        reser.Confirmation(id, count);
                        count++;
                    }
                    else if (slt == 4)
                    {
                        reser.Cancel(id);
                    }
                    else if (slt == 5)
                    {
                        reser.Cancellation(id);
                    }
                    else if (slt == 6)
                    {
                        system("clear");
                        memset(msg, 0, 1024);
                        strcpy(msg, "!chat");
                        write(sock, msg, 1024);
                        sprintf(name, "%s", id.c_str());
                        cout << "        <상담요청 페이지>\n";
                        cout << "q 입력 시 채팅방 종료됩니다.\n";
                        send_msg(sock);
                    }
                    else if (slt == 0)
                    {
                        cout << "홈 버튼을 눌렀습니다.\n";
                        break;
                    }
                }
            }
            else
            {
                cout << "다시 로그인해주세요.\n";
            }
            break;
        case 3:
            cout << "1) id 찾기  2) 비밀번호 찾기\n";
            cin >> slt;
            if (slt == 1)
            {
                user.FindId();
            }
            else if (slt == 2)
            {
                user.FindPw();
            }
            else
            {
                cout << "잘못눌렀습니다.\n";
            }
            break;
        case 4:
            user.remove_infor(); // id 반환
            break;
        case 5:
            system("clear");
            cout << "종료합니다.\n";
            return 0;
        default:
            cout << "잘못눌렀습니다.\n";
            break;
        }
    }
    first.join();
    return 0;
}