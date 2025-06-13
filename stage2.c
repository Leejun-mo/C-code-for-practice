#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MEMBER_COUNT 30
#define TEST_COUNT 7
#define MAX_MENTOR 8

char Main_Menu_Input[10], Return[10], Yes_Or_No[10];
int Training_Menu_Input;

// 멤버 구조체
typedef struct {
    char name[30];
    char nickname[20];
    char gender;
} Member;

Member milliways_members[MEMBER_COUNT];
float health_scores[MEMBER_COUNT][TEST_COUNT] = {0};

// 체력 테스트 항목
const char* health_items[TEST_COUNT] = {
    "1마일 러닝", "스피드 스프린트", "푸시업", "스쿼트", "팔굽혀 펴기", "수영", "무게 들기"
};

// 운동 루틴 관련
const char* exercise_types[5][3] = {
    {"러닝", "자전거", "빠른 걷기"},  // 유산소
    {"푸시업", "스쿼트", ""},         // 전신 근력
    {"레그 프레스", "레그 컬", ""},  // 하체 근력
    {"철봉", "풀업 바", ""},         // 상체 근력
    {"플랭크", "크런치", ""}         // 코어
};

char member_routine[MEMBER_COUNT][6][30]; // 멤버 별 월~토 운동 루틴

// 능력치 및 멘토 관련
int member_ids[MEMBER_COUNT] = {0};         
int member_ability[MEMBER_COUNT] = {0};     

typedef struct {
    int id;            
    char name[30];     
    int mentee_id;     
} Mentor;

Mentor mentors[MAX_MENTOR];

// 유틸 함수
void Inputc(char *str) { printf("Input: "); scanf("%s", str); }
void Inputi(int *num) { printf("Input: "); scanf("%d", num); }
void Not_Implemented_Yet() { printf("아직 구현되지 않은 기능\n\n"); }
void Unknown_Input() { printf("제시되지 않는 입력 오류.\n"); }

// 멤버 초기화
void Init_Members() {
    strcpy(milliways_members[0].name, "고은"); strcpy(milliways_members[0].nickname, "Goeun"); milliways_members[0].gender = 'F';
    strcpy(milliways_members[1].name, "원철"); strcpy(milliways_members[1].nickname, "Woncheol"); milliways_members[1].gender = 'M';
    strcpy(milliways_members[2].name, "영진"); strcpy(milliways_members[2].nickname, "Youngjin"); milliways_members[2].gender = 'M';
    strcpy(milliways_members[3].name, "혜경"); strcpy(milliways_members[3].nickname, "Hyekyung"); milliways_members[3].gender = 'F';
    strcpy(milliways_members[4].name, "아서"); strcpy(milliways_members[4].nickname, "Arthur"); milliways_members[4].gender = 'M';
}

// 닉네임으로 멤버 찾기
int findMemberIndexByNickname(char* nickname) {
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}

// 체력 데이터 입력
void setHealth() {
    char nickname[20], input[200];
    printf("체력 데이터를 입력할 멤버 닉네임: ");
    scanf("%s", nickname);
    int memberIndex = findMemberIndexByNickname(nickname);
    if (memberIndex == -1) { printf("해당 닉네임의 멤버를 찾을 수 없습니다.\n"); return; }
    printf("7가지 체력 데이터를 ','로 구분하여 입력하세요. 예시: 8.5,7.2,30,50,40,3.2,100\n");
    printf("Input: ");
    scanf(" %[^\n]", input);
    char* token = strtok(input, ","); int i = 0;
    while (token != NULL && i < TEST_COUNT) {
        health_scores[memberIndex][i] = atof(token);
        token = strtok(NULL, ","); i++;
    }
    if (i != TEST_COUNT) printf("입력 데이터 오류.\n");
    else printf("체력 데이터 입력 완료.\n");
}

// 체력 데이터 조회
void getHealth() {
    char nickname[20];
    printf("전체 조회: 'ALL', 닉네임 조회: 닉네임 입력, 특정 항목 조회: 닉네임/항목번호\n");
    printf("예: 'ALL' 또는 'Goeun' 또는 'Goeun/3'\n");
    printf("Input: ");
    scanf("%s", nickname);
    if (strcmp(nickname, "ALL") == 0) {
        for (int i = 0; i < MEMBER_COUNT; i++) {
            if (strlen(milliways_members[i].nickname) == 0) continue;
            printf("이름: %s, 닉네임: %s\n", milliways_members[i].name, milliways_members[i].nickname);
            for (int j = 0; j < TEST_COUNT; j++) printf("%s: %.2f  ", health_items[j], health_scores[i][j]);
            printf("\n\n");
        }
    } else {
        char *slash = strchr(nickname, '/');
        if (slash != NULL) {
            *slash = '\0';
            int itemNum = atoi(slash + 1);
            int memberIndex = findMemberIndexByNickname(nickname);
            if (memberIndex == -1 || itemNum < 1 || itemNum > TEST_COUNT) {
                printf("입력 오류.\n"); return;
            }
            printf("%s: %.2f\n", health_items[itemNum - 1], health_scores[memberIndex][itemNum - 1]);
        } else {
            int memberIndex = findMemberIndexByNickname(nickname);
            if (memberIndex == -1) { printf("해당 닉네임의 멤버를 찾을 수 없습니다.\n"); return; }
            printf("이름: %s, 닉네임: %s\n", milliways_members[memberIndex].name, milliways_members[memberIndex].nickname);
            for (int j = 0; j < TEST_COUNT; j++) printf("%s: %.2f  ", health_items[j], health_scores[memberIndex][j]);
            printf("\n");
        }
    }
}

// 운동 루틴 설정
void setExerciseRoutine() {
    char nickname[20];
    printf("운동 루틴을 설정할 멤버 닉네임: ");
    scanf("%s", nickname);
    int memberIndex = findMemberIndexByNickname(nickname);
    if (memberIndex == -1) { printf("해당 닉네임의 멤버를 찾을 수 없습니다.\n"); return; }

    int core_used = 0;
    for (int day = 0; day < 6; day++) {
        int cardio = rand() % 3;
        int strength_type = rand() % 4; 
        int strength = rand() % 2;

        strcpy(member_routine[memberIndex][day], exercise_types[0][cardio]);
        strcat(member_routine[memberIndex][day], " + ");

        if (strength_type == 4 && !core_used) {
            strcat(member_routine[memberIndex][day], exercise_types[4][rand()%2]);
            core_used = 1;
        } else {
            strcat(member_routine[memberIndex][day], exercise_types[strength_type+1][strength]);
        }
    }
    printf("운동 루틴 설정 완료!\n");
}

// 운동 루틴 조회
void getExerciseRoutine() {
    char nickname[20];
    printf("운동 루틴 조회할 멤버 닉네임: ");
    scanf("%s", nickname);
    int memberIndex = findMemberIndexByNickname(nickname);
    if (memberIndex == -1) { printf("해당 닉네임의 멤버를 찾을 수 없습니다.\n"); return; }
    printf("이름: %s, 닉네임: %s\n", milliways_members[memberIndex].name, milliways_members[memberIndex].nickname);
    for (int day = 0; day < 6; day++) {
        printf("Day %d: %s\n", day + 1, member_routine[memberIndex][day]);
    }
}

// ---------- 멘토링 시스템 ----------

// 닉네임을 ASCII 코드 합으로 변환
int parseIntMember(char *nickname) {
    int sum = 0;
    for (int i = 0; i < strlen(nickname); i++) sum += (int)nickname[i];
    return sum;
}
int getRandomAbility() { return rand() % 901 + 100; }
void initAbilityData() {
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strlen(milliways_members[i].nickname) == 0) continue;
        member_ids[i] = parseIntMember(milliways_members[i].nickname);
        member_ability[i] = getRandomAbility();
    }
    printf("연습생 능력치 초기화 완료.\n");
}
void registerMentors() {
    printf("멘토 명단 입력 (최대 %d명):\n", MAX_MENTOR);
    for (int i = 0; i < MAX_MENTOR; i++) {
        mentors[i].id = i + 1;
        printf("%d번째 멘토 이름 입력: ", i + 1);
        scanf("%s", mentors[i].name);
        mentors[i].mentee_id = -1;
    }
    printf("멘토 등록 완료.\n");
}
void matchMentoring() {
    initAbilityData();
    int mentor_used[MAX_MENTOR] = {0};
    printf("===== 멘토링 매칭 결과 =====\n");
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strlen(milliways_members[i].nickname) == 0) continue;
        int mentee_num = member_ids[i];
        int mentor_index = (mentee_num % MAX_MENTOR);
        while (mentor_used[mentor_index]) mentor_index = (mentor_index + 1) % MAX_MENTOR;
        mentor_used[mentor_index] = 1;
        mentors[mentor_index].mentee_id = member_ids[i];
        printf("연습생: %s (%s), ID: %d, 능력치: %d -> 멘토: %s (ID:%d)\n",
            milliways_members[i].name, milliways_members[i].nickname,
            member_ids[i], member_ability[i], mentors[mentor_index].name, mentors[mentor_index].id);
    }
}

// ---------- 메인 메뉴 ----------
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

int main () {
    srand(time(NULL));
    Init_Members();
    while (1) {
        Main_Menu();
        Inputc(Main_Menu_Input);
        if (Main_Menu_Input[0]=='0' || Main_Menu_Input[0]=='q') break;
        else if (strcmp(Main_Menu_Input, "II") == 0) {
            while (1) {
                Training_Menu();
                Inputi(&Training_Menu_Input);
                if (Training_Menu_Input == 1) {
                    printf("A. 체력 상태 입력\nB. 체력 상태 조회\nC. 기초 운동 루틴 설정\nD. 기초 운동 루틴 조회\n");
                    Inputc(Yes_Or_No);
                    if (strcmp(Yes_Or_No, "A") == 0) setHealth();
                    else if (strcmp(Yes_Or_No, "B") == 0) getHealth();
                    else if (strcmp(Yes_Or_No, "C") == 0) setExerciseRoutine();
                    else if (strcmp(Yes_Or_No, "D") == 0) getExerciseRoutine();
                    else Unknown_Input();
                }
                else if (Training_Menu_Input == 2) {
                    printf("A. 멘토 등록\nB. 멘토링 매칭\n");
                    Inputc(Yes_Or_No);
                    if (strcmp(Yes_Or_No, "A") == 0) registerMentors();
                    else if (strcmp(Yes_Or_No, "B") == 0) matchMentoring();
                    else Unknown_Input();
                }
                else if (Training_Menu_Input >= 3 && Training_Menu_Input <= 8) Not_Implemented_Yet();
                else break;
            }
        } else Not_Implemented_Yet();
    }
    printf("마그라테아 프로그램 종료\n");
}
