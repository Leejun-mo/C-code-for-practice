#include <stdio.h>
#include <string.h>

// Function to strip newline from input strings
void strip_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Judge info struct
typedef struct {
    char name[30];
    char gender[10];
    char belong[30];
    char job[30];
    char spec[30];
    char email[40];
    char contact[40];
} Judgeinfo;

// Print judge number label
void printjudgenumber(int index) {
    printf("*심사위원 %d: ", index + 1);
}

int main() {
    char pname[100];
    char yorn;
    int judgenum, membernum;

    printf("####################################\n");
    printf("#      심사위원 명단 데이터 입력       #\n");
    printf("####################################\n");

    // Project name input
    printf("참여 프로젝트: ");
    scanf("%s", pname);

    // Judge and member numbers input
    printf("심사 총 인원: ");
    scanf("%d", &judgenum);

    printf("선발 멤버 수: ");
    scanf("%d", &membernum);

    printf("\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사위원 정보 입력을 시작합니다.\n", judgenum);
    printf("++++++++++++++++++++++++++++++++++++\n");

    // Declare the array after knowing the size
    Judgeinfo judgenumber[judgenum];

    for (int i = 0; i < judgenum; i++) {
        printjudgenumber(i);
        

        // Clear input buffer
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        printf("이름: ");
        fgets(judgenumber[i].name, sizeof(judgenumber[i].name), stdin);
        strip_newline(judgenumber[i].name);

        printf("성별: ");
        fgets(judgenumber[i].gender, sizeof(judgenumber[i].gender), stdin);
        strip_newline(judgenumber[i].gender);

        printf("소속: ");
        fgets(judgenumber[i].belong, sizeof(judgenumber[i].belong), stdin);
        strip_newline(judgenumber[i].belong);

        printf("직함: ");
        fgets(judgenumber[i].job, sizeof(judgenumber[i].job), stdin);
        strip_newline(judgenumber[i].job);

        printf("전문분야: ");
        fgets(judgenumber[i].spec, sizeof(judgenumber[i].spec), stdin);
        strip_newline(judgenumber[i].spec);

        printf("메일: ");
        fgets(judgenumber[i].email, sizeof(judgenumber[i].email), stdin);
        strip_newline(judgenumber[i].email);

        printf("전화: ");
        fgets(judgenumber[i].contact, sizeof(judgenumber[i].contact), stdin);
        strip_newline(judgenumber[i].contact);

        
    }
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("심사위원 정보 입력이 끝났습니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    // Confirm output
    printf("[%s] 심사위원 정보를 확인할까요? (Y,N) ", pname);
    scanf(" %c", &yorn);  // Note space before %c to skip newline

    if (yorn == 'Y' || yorn == 'y') {
        printf("\n===== 심사위원 전체 명단 =====\n");
        for (int i = 0; i < judgenum; i++) {
            printjudgenumber(i);
            printf("\n");
            printf("이름: %s\n", judgenumber[i].name);
            printf("성별: %s\n", judgenumber[i].gender);
            printf("소속: %s\n", judgenumber[i].belong);
            printf("직함: %s\n", judgenumber[i].job);
            printf("전문분야: %s\n", judgenumber[i].spec);
            printf("메일: %s\n", judgenumber[i].email);
            printf("전화: %s\n", judgenumber[i].contact);
            printf("-----------------------------\n");
        }
    } else {
        printf("출력을 취소했습니다.\n");
    }

    return 0;
}
