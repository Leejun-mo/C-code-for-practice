#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMBER_COUNT 30
#define TEST_COUNT 7
#define DAYS 6  // 월~토요일

char Main_Menu_Input[10], Return[10], Yes_Or_No[10], Exit[10];
int Training_Menu_Input;

typedef struct {
    char name[30];
    char nickname[20];
    char gender;
} Member;

Member milliways_members[MEMBER_COUNT];
float health_scores[MEMBER_COUNT][TEST_COUNT] = {0};

// 운동 루틴 관련 추가
const char* days_of_week[DAYS] = {"월요일", "화요일", "수요일", "목요일", "금요일", "토요일"};

const char* exercise_types[][3] = {
    {"러닝", "자전거", "빠른 걷기"},        // 유산소
    {"푸시업", "스쿼트", ""},             // 전신 근력
    {"레그 프레스", "레그 컬", ""},       // 하체 근력
    {"철봉", "풀업 바", ""},             // 상체 근력
    {"플랭크", "크런치", ""}             // 코어
};

char member_routine[MEMBER_COUNT][DAYS][30] = {{{0}}}; // 운동 루틴 저장

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

void printMemberList() {
    printf("멤버 목록:\n");
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strlen(milliways_members[i].nickname) == 0) continue;
        printf("%d. %s (%s)\n", i+1, milliways_members[i].name, milliways_members[i].nickname);
    }
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

int findMemberIndexByName(char* name) {
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(milliways_members[i].name, name) == 0)
            return i;
    }
    return -1;
}

int findMemberIndexByNickname(char* nickname) {
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}

void setExerciseRoutine() {
    printMemberList();
    char name[30];
    printf("운동 루틴을 설정할 멤버 이름 입력: ");
    scanf("%s", name);

    int memberIndex = findMemberIndexByName(name);
    if (memberIndex == -1) {
        printf("해당 이름의 멤버를 찾을 수 없습니다.\n");
        return;
    }

    int core_used = 0;
    for (int day = 0; day < DAYS; day++) {
        printf("[%s]\n", days_of_week[day]);

        // 유산소 운동 입력
        printf("유산소 선택 (1.러닝 2.자전거 3.빠른 걷기): ");
        int cardio;
        scanf("%d", &cardio);
        if (cardio < 1 || cardio > 3) {
            printf("잘못된 입력. 기본값 러닝 선택.\n");
            cardio = 1;
        }
        strcpy(member_routine[memberIndex][day], exercise_types[0][cardio-1]);

        // 근력 or 코어 선택
        printf("운동 종류 선택 (1.전신 근력 2.하체 근력 3.상체 근력 4.코어): ");
        int type;
        scanf("%d", &type);
        if (type == 4 && core_used >= 1) {
            printf("코어 운동은 주 1회만 선택할 수 있습니다. 다른 종류를 선택하세요.\n");
            type = 1;
        }

        int choice = 1;
        if (type != 4) {
            printf("세부 종목 선택 (1 또는 2): ");
            scanf("%d", &choice);
            if (choice < 1 || choice > 2) choice = 1;
        }

        strcat(member_routine[memberIndex][day], " + ");
        strcat(member_routine[memberIndex][day], exercise_types[type][choice-1]);

        if (type == 4) core_used++;
    }
    printf("운동 루틴 설정 완료.\n");
}

void getExerciseRoutine() {
    printMemberList();
    char name[30];
    printf("운동 루틴을 조회할 멤버 이름 입력: ");
    scanf("%s", name);

    int memberIndex = findMemberIndexByName(name);
    if (memberIndex == -1) {
        printf("해당 이름의 멤버를 찾을 수 없습니다.\n");
        return;
    }
    printf("이름: %s, 닉네임: %s\n", milliways_members[memberIndex].name, milliways_members[memberIndex].nickname);
    for (int i = 0; i < DAYS; i++) {
        printf("%s: %s\n", days_of_week[i], member_routine[memberIndex][i]);
    }
}

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
    printf("예시: 8.5,7.2,30,50,40,3.2,100\n");
    printf("Input: ");
    scanf(" %[^\n]", input);

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
                    printf("C. 기초 운동 루틴 설정\n");
                    printf("D. 기초 운동 루틴 조회\n");
                    Inputc(Yes_Or_No);
                    if (strcmp(Yes_Or_No, "A") == 0 || strcmp(Yes_Or_No, "a") == 0) {
                        setHealth();
                    } else if (strcmp(Yes_Or_No, "B") == 0 || strcmp(Yes_Or_No, "b") == 0) {
                        getHealth();
                    } else if (strcmp(Yes_Or_No, "C") == 0 || strcmp(Yes_Or_No, "c") == 0) {
                        setExerciseRoutine();
                    } else if (strcmp(Yes_Or_No, "D") == 0 || strcmp(Yes_Or_No, "d") == 0) {
                        getExerciseRoutine();
                    } else {
                        Unknown_Input();
                    }
                    continue;
                } else if (Training_Menu_Input >= 2 && Training_Menu_Input <= 8) {
                    Not_Implemented_Yet();
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
