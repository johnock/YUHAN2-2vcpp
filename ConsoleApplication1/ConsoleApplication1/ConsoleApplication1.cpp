#include <iostream>
#include <conio.h>
#define ESC 27
#define CR 13



int main()
{
    printf("이은석의 행복한 VC++\n\n");

    printf("command>");

    char a;


    while (1) {

        a = _getch();

        printf("%c", a);



        //esc를 누르면 프로그램 종료
        if (a == ESC) {
            break;
        }

        //q를 눌렀을때 문장 출력
        if (a == 'q') {
            a = _getch();
            if (a == CR) {
                printf("\n");
                printf("qwer 화이팅\ncommand>");

            }

        }

        //w를 눌렀을때 문장 출력
        else if (a == 'w') {
            a = _getch();
            if (a == CR) {
                printf("\n");
                printf("과제 너무 좋다\ncommand>");
            }

            
        }
        //e를 눌렀을때 문장 출력
        else if (a == 'e') {
            a = _getch();
            if (a == CR) {
                printf("\n");
                printf("다음주부턴 과제량 3배다\ncommand>");
            }
            
        }
        //r를 눌렀을때 문장 출력
        else if (a == 'r') {
            a = _getch();
            if (a == CR) {
                printf("\n");
                printf("행복합니다.\ncommand>");
            }
            
        }
        //qwer외에 다른 키를 입력시 오류문장 출력
        else {
            a = _getch();
            if (a == CR) {

                printf("\n오류입니다 형식에 맞게 입력해주세요.\ncommand>");
            }
            
        }


    }



}
