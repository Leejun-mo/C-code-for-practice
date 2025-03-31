#include <stdio.h>

int main(){

    int numberYear,numberMonth,numberDay;
    char characterYear[] = "yyyy";
    char characterMonth[] = "mm";
    char characterDay[] = "dd";
    char name;

    printf("[현재 날짜를 '%s %s %s' 형식으로 입력하세요]: ", characterYear, characterMonth, characterDay); 
    // "-"를 포함한 형식으로 코딩을 하기 어려움으로서서 "spacebar"로 형식변경함함
    scanf("%d %d %d", &numberYear, &numberMonth, &numberDay);

    printf("[당신의 이름을 입력하세요]: ");
    scanf("%s", &name);
    printf("**입력이 정상적으로 처리되었습니다~**\n");
    printf("\n");

    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("*  <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>  ******\n");
    printf("**                        [마그라테아 ver 0.1]                             *****\n");
    printf("***  풀 한 포기 없는 황무지에서 반짝이는 행성을 만들내는 곳 마그라테아,     ****\n");
    printf("****  사람들이 보지 못하는 잠재력을 찾고 전문가의 손길을 더해 보석을 빗는 곳,***\n");
    printf("*****   마그라테아에 오신걸 환영합니다~                                       **\n");
    printf("******  <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>  *\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[사용자]: %s                                    ", &name);
    printf("[실행 시간]: %d년 %d월 %d일\n", numberYear, numberMonth, numberDay);
    printf("================================================================================");

    return 0;
}

//  gcc splash.c -o splash  (컴파일)

//  .\splash    (실행)

// EUC-KR 사용 안할시 한글 깨질 수 있음.
