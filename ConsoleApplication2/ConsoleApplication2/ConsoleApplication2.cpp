#include <stdio.h>
#include <conio.h>  //kbhit() 및 _getch()와 같은 키보드 입력 관련 함수를 사용하기 위한 헤더
#include <chrono>   //시간 측정을 위한 표준 C++ 라이브러리 헤더

#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int main()
{
    char input = 0;;//입력 변수 초기화
    std::chrono::system_clock::time_point combostart;//현재 시간을 combostart에 저장

    while (input != ESC) {
        if (_kbhit()) {
            input = _getch();
            printf("%c", input);


            /*두 번 읽어야 방향키를 인식할 수 있기에 위에서 본 _getch()함수를 두 번 가져옴

            그리고 char의 범위는 - 128~127이기에 처음으로 사용할 _getch()에는 - 32가 저장되어야 함

                char c;
            c = _getch(); // 224를 받고(-32로)
            c = _getch(); // 뒤의 두 자리를 받는다.
            */
            if (input == -32) {
                input = _getch();

                switch (input) {

                case LEFT:
                    printf("←");
                    break;
                case RIGHT:
                    printf("→");
                    break;
                case UP:
                    printf("↑");
                    break;
                case DOWN:
                    printf("↓");
                    combostart = std::chrono::system_clock::now();//↓이 입력된 시간을 현재시간으로 선언

                    input = _getch();
                    if (input == -32) {
                        input = _getch();

                        //회피 콤보
                        if (input == LEFT) {
                            printf("←");
                            input = _getch();
                            if (input == 'c') {
                                printf("c");
                                std::chrono::duration<double> combotime = std::chrono::system_clock::now() - combostart;
                                //콤보가 3초 안에 끝났을때
                                if (combotime.count() <= 3.0) {
                                    printf("\n");
                                    printf("회피\n");
                                }
                                //콤보가 3초를 넘겼을때
                                else {
                                    break;
                                }


                            }
                        }

                        //어퍼컷 콤보
                        if (input == UP) {
                            printf("↑");
                            input = _getch();
                            if (input == 'a') {
                                printf("a");
                                std::chrono::duration<double> combotime = std::chrono::system_clock::now() - combostart;
                                //콤보가 3초 안에 끝났을때
                                if (combotime.count() <= 3.0) {
                                    printf("\n");
                                    printf("어퍼컷!!\n");
                                }
                                //콤보가 3초를 넘겼을때
                                else {
                                    break;
                                }

                            }
                        }

                        //장풍 콤보
                        if (input == RIGHT) {
                            printf("→");
                            input = _getch();
                            if (input == 'a') {
                                printf("a");
                                std::chrono::duration<double> combotime = std::chrono::system_clock::now() - combostart;
                                //콤보가 3초 안에 끝났을때
                                if (combotime.count() <= 3.0) {
                                    printf("\n");
                                    printf("장풍!!\n");
                                }
                                //콤보가 3초를 넘겼을때
                                else {
                                    break;
                                }

                            }
                        }

                    }
                    break;
                }
            }
        }
    }
}