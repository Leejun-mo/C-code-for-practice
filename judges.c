#include <stdio.h>
#include <string.h>

void strip_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}


typedef struct {
    char name[30];
    char gender[10];
    char belong[30];
    char job[30];
    char spec[30];
    char email[40];
    char contact[40];
} Judgeinfo;

void printjudgenumber(int index) {
    switch(index) {
        case 0: printf("*심사위원 1: "); break;
        case 1: printf("*심사위원 2: "); break;
        case 2: printf("*심사위원 3: "); break;
        case 3: printf("*심사위원 4: "); break;
        case 4: printf("*심사위원 5: "); break;
        case 5: printf("*심사위원 6: "); break;
        case 6: printf("*심사위원 7: "); break;
        case 7: printf("*심사위원 8: "); break;
        case 8: printf("*심사위원 9: "); break;
        
    }
}


int main() {
    char buffer[512];
    char pname;
    int judgenum, membernum;

    Judgeinfo judgenumber [judgenum];

    printf("####################################\n");
    printf("#      심사위원 명단 데이터 입력       #\n");
    printf("####################################\n");
    printf("\n");
    printf("참여 프로젝트: ");
    scanf("%s", &pname);
    printf("심사 총 인원: ");
    scanf("%d", &judgenum);
    printf("선발 멤버 수: ");
    scanf("%d", &membernum);
    printf("\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사위원 정보 입력을 시작합니다.\n", judgenum);
    printf("++++++++++++++++++++++++++++++++++++\n");


    for (int i = 0; i < judgenum; i++) {
    printjudgenumber(i);

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("\"이름:");
    fgets(judgenumber[i].name, 30, stdin);
    strip_newline(judgenumber[i].name);

    printf(",성별:");
    fgets(judgenumber[i].gender, 10, stdin);
    strip_newline(judgenumber[i].gender);

    printf(",소속:");
    fgets(judgenumber[i].belong, 30, stdin);
    strip_newline(judgenumber[i].belong);

    printf(",직함:");
    fgets(judgenumber[i].job, 30, stdin);
    strip_newline(judgenumber[i].job);

    printf(",전문분야:");
    fgets(judgenumber[i].spec, 30, stdin);
    strip_newline(judgenumber[i].spec);

    printf(",메일:");
    fgets(judgenumber[i].email, 40, stdin);
    strip_newline(judgenumber[i].email);

    printf(",전화:");
    fgets(judgenumber[i].contact, 40, stdin);
    strip_newline(judgenumber[i].contact);

    printf("\"\n");
}
    return 0;
}
