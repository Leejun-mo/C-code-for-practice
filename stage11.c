#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMBER_COUNT 30
#define TEST_COUNT 7

char Main_Menu_Input[10], Return[10], Yes_Or_No[10], Exit[10];
int Training_Menu_Input;

typedef struct {
    char name[30];
    char nickname[20];
    char gender;
} Member;

Member milliways_members[MEMBER_COUNT];
float health_scores[MEMBER_COUNT][TEST_COUNT] = {0};

// 테스트 항목 이름
const char* health_items[TEST_COUNT] = {
    "1마일 러닝", "스피드 스프린트", "푸시업", "스쿼트", "팔굽혀 펴기", "수영", "무게 들기"
};

void Init_Members() {
    strcpy(milliways_members[0].name, "고은");
    strcpy(milliways_members[0].nickname, "Goeun");
    milliways_members[0].gender = 'F';

    strcpy(milliways_members[1].name, "원철");
    strcpy(milliways_members[1].nickname, "Woncheol");
    milliways_members[1].gender = 'M';

    strcpy(milliways_members[2].name, "영진");
    strcpy(milliways_members[2].nickname, "Youngjin");
    milliways_members[2].gender = 'M';

    strcpy(milliways_members[3].name, "혜경");
    strcpy(milliways_members[3].nickname, "Hyekyung");
    milliways_members[3].gender = 'F';

    strcpy(milliways_members[4].name, "아서");
    strcpy(milliways_members[4].nickname, "Arthur");
    milliways_members[4].gender = 'M';
}

void Main_Menu() {
    printf("~{마그라테아 프로그램 메뉴}~\n");
    printf("I.오디션 관리, II.훈련, III.데뷔\n");
    printf("<종료>:(0) 또는 (q)\n");
}

void Training_Menu() {
    printf("~{마그라테아 프로그램 훈련 메뉴}~\n");
    printf("(1.체력과 지식), (2.자기관리 및 팀워크), (3.언어 및 발음), (4.보컬)\n");
    printf("(5.댄스), (6.비주얼 및 이미지), (7.연기 및 무대 퍼포먼스), (8.팬 소통)\n");
}

void Inputc(char *str) {
    printf("Input: ");
    scanf("%s", str);
}

void Inputi(int *num) {
    printf("Input: ");
    scanf("%d", num);
}

void Not_Implemented_Yet() {
    printf("아직 구현되지 않은 기능\n\n");
}

void Unknown_Input() {
    printf("제시되지 않는 입력 오류.\n");
}

int findMemberIndexByNickname(char* nickname) {
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}

// 체력 데이터 입력
void setHealth() {
    char nickname[20];
    char input[200];
    printf("체력 데이터를 입력할 멤버 닉네임: ");
    scanf("%s", nickname);
    int memberIndex = findMemberIndexByNickname(nickname);
    if (memberIndex == -1) {
        printf("해당 닉네임의 멤버를 찾을 수 없습니다.\n");
        return;
    }
    printf("7가지 체력 데이터를 ','로 구분하여 입력하세요.\n");
    printf("7가지 체력 테스트 항목:  1마일 러닝테스트, 스피드 스프린트, 푸시업, 스쿼트, 팔굽혀 펴기, 수영, 무게들기.\n");
    printf("예시: 8.5,7.2,30,50,40,3.2,100\n");
    printf("Input: ");
    scanf(" %[^\n]", input);  // 줄 전체 입력 받기

    char* token = strtok(input, ",");
    int i = 0;
    while (token != NULL && i < TEST_COUNT) {
        health_scores[memberIndex][i] = atof(token);
        token = strtok(NULL, ",");
        i++;
    }

    if (i != TEST_COUNT) {
        printf("입력 데이터가 부족하거나 초과되었습니다.\n");
    } else {
        printf("체력 데이터 입력 완료.\n");
    }
}

// 체력 데이터 조회 (개선 버전)
void getHealth() {
    char nickname[20];
    printf("전체 조회: 'ALL', 닉네임 조회: 닉네임 입력, 특정 항목 조회: 닉네임/항목번호\n");
    printf("예: 'ALL' 또는 'Goeun' 또는 'Goeun/3'\n");
    printf("Input: ");
    scanf("%s", nickname);

    if (strcmp(nickname, "ALL") == 0) {
        for (int i = 0; i < MEMBER_COUNT; i++) {
            if (strlen(milliways_members[i].nickname) == 0)
                continue;
            printf("이름: %s, 닉네임: %s\n", milliways_members[i].name, milliways_members[i].nickname);
            for (int j = 0; j < TEST_COUNT; j++) {
                printf("%s: %.2f  ", health_items[j], health_scores[i][j]);
            }
            printf("\n\n");
        }
    } else {
        // 닉네임/항목번호 형태인지 확인
        char *slash = strchr(nickname, '/');
        if (slash != NULL) {
            *slash = '\0';
            int itemNum = atoi(slash + 1);
            int memberIndex = findMemberIndexByNickname(nickname);
            if (memberIndex == -1 || itemNum < 1 || itemNum > TEST_COUNT) {
                printf("닉네임 또는 항목 번호가 잘못되었습니다.\n");
                return;
            }
            printf("이름: %s, 닉네임: %s\n", milliways_members[memberIndex].name, milliways_members[memberIndex].nickname);
            printf("%s: %.2f\n", health_items[itemNum - 1], health_scores[memberIndex][itemNum - 1]);
        } else {
            int memberIndex = findMemberIndexByNickname(nickname);
            if (memberIndex == -1) {
                printf("해당 닉네임의 멤버를 찾을 수 없습니다.\n");
                return;
            }
            printf("이름: %s, 닉네임: %s\n", milliways_members[memberIndex].name, milliways_members[memberIndex].nickname);
            for (int j = 0; j < TEST_COUNT; j++) {
                printf("%s: %.2f  ", health_items[j], health_scores[memberIndex][j]);
            }
            printf("\n");
        }
    }
}

int main () {
    Init_Members();

    while (1) {
        Main_Menu();
        Inputc(Main_Menu_Input);
        if (Main_Menu_Input[0]=='0' || Main_Menu_Input[0]=='q') {
            printf("마그라테아 프로그램 종료\n");
            break;
        } else if (strcmp(Main_Menu_Input, "I") == 0 || strcmp(Main_Menu_Input, "III") == 0) {
            Not_Implemented_Yet();
        } else if (strcmp(Main_Menu_Input, "II") == 0){
            while (1) {
                Training_Menu();
                Inputi(&Training_Menu_Input);
                if (Training_Menu_Input == 1) {
                    printf("A. 체력 상태 입력\n");
                    printf("B. 체력 상태 조회\n");
                    Inputc(Yes_Or_No);
                    if (strcmp(Yes_Or_No, "A") == 0 || strcmp(Yes_Or_No, "a") == 0) {
                        setHealth();
                        continue;
                    } else if (strcmp(Yes_Or_No, "B") == 0 || strcmp(Yes_Or_No, "b") == 0) {
                        getHealth();
                        continue;
                    } else {
                        Unknown_Input();
                        continue;
                    }
                } else if (Training_Menu_Input >= 2 && Training_Menu_Input <= 8) {
                    Not_Implemented_Yet();
                    continue;
                } else {
                    break;
                }
            }
        } else {
            Unknown_Input();
            printf("반환하려면'r'을 입력하십시오, 종료 하려면 'r'아닌 아무 키 입력.\n");
            Inputc(Return);
            if (strcmp(Return, "r") == 0) {
                continue;
            } else {
                printf("마그라테아 프로그램 종료\n");
                break;
            }
        }
    }
}
