#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MEMBER_COUNT 30
#define TEST_COUNT 7
#define MAX_MENTOR 8
#define MAX_TRAUMA 30
#define MAX_COUNSELING 100
#define QUESTION_COUNT 5

char Main_Menu_Input[10], Return[10], Yes_Or_No[10];
int Training_Menu_Input;

typedef struct {
    char name[30];
    char nickname[20];
    char gender;
} Member;

Member milliways_members[MEMBER_COUNT];
float health_scores[MEMBER_COUNT][TEST_COUNT] = {0};

const char* health_items[TEST_COUNT] = {
    "1마일 러닝", "스피드 스프린트", "푸시업", "스쿼트", "팔굽혀 펴기", "수영", "무게 들기"
};

const char* exercise_types[5][3] = {
    {"러닝", "자전거", "빠른 걷기"},
    {"푸시업", "스쿼트", ""},
    {"레그 프레스", "레그 컬", ""},
    {"철봉", "풀업 바", ""},
    {"플랭크", "크런치", ""}
};

char member_routine[MEMBER_COUNT][6][30];

int member_ids[MEMBER_COUNT] = {0};
int member_ability[MEMBER_COUNT] = {0};

typedef struct {
    int id;
    char name[30];
    int mentee_id;
} Mentor;

Mentor mentors[MAX_MENTOR];

typedef struct {
    char nickname[20];
    int age;
    char trauma[100];
} TraumaMember;

typedef struct {
    int id;
    char question[200];
} CounselingQuestion;

typedef struct {
    char nickname[20];
    char question[200];
    char answer[100];
} CounselingSession;

TraumaMember traumaMembers[MAX_TRAUMA];
CounselingQuestion questions[QUESTION_COUNT] = {
    {1, "어떤 상황에서 그 트라우마를 경험하셨나요?"},
    {2, "해당 상황이 어떻게 당신의 일상생활과 감정에 어떤 영향을 미치고 있는지 말씀해주세요."},
    {3, "이 트라우마를 어떻게 극복하려고 노력하셨나요?"},
    {4, "트라우마와 관련하여 어떤 감정을 느끼고 계신가요?"},
    {5, "트라우마를 극복하기 위해 어떤 지원이 필요한 것으로 생각하시나요?"}
};

CounselingSession counselingSessions[MAX_COUNSELING];
int counselingCount = 0;

typedef struct {
    char keyword[20];
    char message[500];
} EasterEgg;

EasterEgg arthurEgg = {
    "specter",
    "나는 고백한다. 대학 졸업 후 스타트업 창업이라는 허세에 빠져 치기 어린 행동으로 친구들의 앞길을 막았다. 나는 나의 아이디어가 설득되는 사람이 나 뿐일 때 파괴적인 결과를 보게 된다는 것을 뼈저리게 경험했다. 과거의 아서는 독선과 아집의 망령이다."
};

void Inputc(char *str) { printf("Input: "); scanf("%s", str); }
void Inputi(int *num) { printf("Input: "); scanf("%d", num); }
void Not_Implemented_Yet() { printf("아직 구현되지 않은 기능\n\n"); }
void Unknown_Input() { printf("제시되지 않는 입력 오류.\n"); }

void Init_Members() {
    strcpy(milliways_members[0].name, "고은"); strcpy(milliways_members[0].nickname, "Goeun"); milliways_members[0].gender = 'F';
    strcpy(milliways_members[1].name, "원철"); strcpy(milliways_members[1].nickname, "Woncheol"); milliways_members[1].gender = 'M';
    strcpy(milliways_members[2].name, "영진"); strcpy(milliways_members[2].nickname, "Youngjin"); milliways_members[2].gender = 'M';
    strcpy(milliways_members[3].name, "혜경"); strcpy(milliways_members[3].nickname, "Hyekyung"); milliways_members[3].gender = 'F';
    strcpy(milliways_members[4].name, "아서"); strcpy(milliways_members[4].nickname, "Arthur"); milliways_members[4].gender = 'M';

    for (int i = 0; i < 5; i++) {
        strcpy(traumaMembers[i].nickname, milliways_members[i].nickname);
        traumaMembers[i].age = 20 + i;
        strcpy(traumaMembers[i].trauma, "");
    }
}

int findMemberIndexByNickname(char* nickname) {
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}
int findTraumaIndexByNickname(char* nickname) {
    for (int i = 0; i < MAX_TRAUMA; i++) {
        if (strcmp(traumaMembers[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}

void inputTrauma() {
    while (1) {
        char nickname[20];
        printf("트라우마 입력할 닉네임 (종료: EXIT): ");
        scanf("%s", nickname);
        if (strcmp(nickname, "EXIT") == 0) break;
        int idx = findTraumaIndexByNickname(nickname);
        if (idx != -1) {
            printf("트라우마 내용: ");
            scanf(" %[^\n]", traumaMembers[idx].trauma);
        } else printf("닉네임 오류. 다시 입력하세요.\n");
    }
    printf("트라우마 입력 종료\n");
}

void counselingSession() {
    printf("트라우마 입력한 멤버 목록:\n");
    for (int i = 0; i < MAX_TRAUMA; i++) {
        if (strlen(traumaMembers[i].trauma) > 0)
            printf("%s ", traumaMembers[i].nickname);
    }
    printf("\n상담할 멤버 닉네임 입력: ");
    char nickname[20];
    scanf("%s", nickname);
    int idx = findTraumaIndexByNickname(nickname);
    if (idx == -1 || strlen(traumaMembers[idx].trauma) == 0) {
        printf("트라우마를 입력하지 않은 멤버입니다.\n");
        return;
    }
    int used[QUESTION_COUNT] = {0};
    for (int i = 0; i < 3; i++) {
        int q;
        do { q = rand() % QUESTION_COUNT; } while (used[q]);
        used[q] = 1;
        printf("[%s]\n", questions[q].question);
        char answer[200];
        while (1) {
            printf("답변 (100자 이내): ");
            scanf(" %[^\n]", answer);
            if (strlen(answer) == 0 || strlen(answer) > 100)
                printf("입력 오류. 다시 입력하세요.\n");
            else break;
        }
        strcpy(counselingSessions[counselingCount].nickname, nickname);
        strcpy(counselingSessions[counselingCount].question, questions[q].question);
        strcpy(counselingSessions[counselingCount].answer, answer);
        counselingCount++;
    }
    printf("상담 세션 완료!\n");
}

void viewCounselingResult() {
    printf("상담 진행한 멤버 목록:\n");
    char done_nickname[100][20];
    int count = 0;
    for (int i = 0; i < counselingCount; i++) {
        int exist = 0;
        for (int j = 0; j < count; j++)
            if (strcmp(done_nickname[j], counselingSessions[i].nickname) == 0)
                exist = 1;
        if (!exist) strcpy(done_nickname[count++], counselingSessions[i].nickname);
    }
    for (int i = 0; i < count; i++)
        printf("%s ", done_nickname[i]);
    printf("\n조회할 닉네임 입력: ");
    char nickname[20];
    scanf("%s", nickname);
    int idx = findTraumaIndexByNickname(nickname);
    if (idx == -1) { printf("존재하지 않는 닉네임입니다.\n"); return; }
    printf("\n닉네임: %s, 나이: %d, 트라우마: %s\n", traumaMembers[idx].nickname, traumaMembers[idx].age, traumaMembers[idx].trauma);
    for (int i = 0; i < counselingCount; i++) {
        if (strcmp(counselingSessions[i].nickname, nickname) == 0)
            printf("Q: %s\nA: %s\n", counselingSessions[i].question, counselingSessions[i].answer);
    }
}

void overcomeTrauma() {
    while (1) {
        printf("A. 트라우마 입력  B. 상담 진행  C. 상담 결과 보기  (종료: EXIT)\n");
        char input[10];
        scanf("%s", input);
        if (strcmp(input, "A") == 0) inputTrauma();
        else if (strcmp(input, "B") == 0) counselingSession();
        else if (strcmp(input, "C") == 0) viewCounselingResult();
        else if (strcmp(input, "EXIT") == 0) break;
        else Unknown_Input();
    }
}

void printBinary(char c) {
    for (int i = 7; i >= 0; i--)
        printf("%d", (c >> i) & 1);
}

void printEasterEggBinary() {
    char mixed[20];
    int len = strlen(arthurEgg.keyword);
    int idx = 0;
    for (int i = 0; i < len; i++)
        if ((i+1) % 2 == 1) mixed[idx++] = arthurEgg.keyword[i];
    for (int i = 0; i < len; i++)
        if ((i+1) % 2 == 0) mixed[idx++] = arthurEgg.keyword[i];
    mixed[len] = '\0';
    for (int i = len-1; i >= 0; i--) {
        printBinary(mixed[i]);
        printf(" ");
    }
    printf("\n");
}

int isEasterEgg(char* input) {
    return strcmp(input, arthurEgg.keyword) == 0;
}

void find_easter_egg() {
    printf("<<아서의 이스터에그>>\n");
    printEasterEggBinary();
    while (1) {
        char input[20];
        printf("이진수에 해당하는 글자를 조합해 단어 입력: ");
        scanf("%s", input);
        if (isEasterEgg(input)) {
            printf("##이스터에그 발견!$$\n");
            printf("%s\n", arthurEgg.message);
            break;
        } else {
            printf("틀렸습니다. 다시 시도하세요.\n");
        }
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
                if (Training_Menu_Input == 2) {
                    printf("A. 멘토링   B. 트라우마 관리\n");
                    Inputc(Yes_Or_No);
                    if (strcmp(Yes_Or_No, "B") == 0) overcomeTrauma();
                    else if (strcmp(Yes_Or_No, "Arthur") == 0) find_easter_egg();
                    else Unknown_Input();
                }
                else if (Training_Menu_Input >= 1 && Training_Menu_Input <= 8)
                    Not_Implemented_Yet();
                else break;
            }
        } else Not_Implemented_Yet();
    }
    printf("마그라테아 프로그램 종료\n");
}
