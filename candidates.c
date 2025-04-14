#include <stdio.h>

#define CANDIDATES 6

typedef struct {
    char name[50];
    char birthday[11];  // Format: YYYY/MM/DD
    char gender;
    char email[100];
    char nationality[50];
    float bmi;
    char mainSkill[50];
    char subSkill[50];
    int topik; // 0 = 원어민
    char mbti[5];
    char intro[300];
} Candidate;

void printCandidateOrder(int index) {
    switch(index) {
        case 0: printf("첫 번째 "); break;
        case 1: printf("두 번째 "); break;
        case 2: printf("세 번째 "); break;
        case 3: printf("네 번째 "); break;
        case 4: printf("다섯 번째 "); break;
        case 5: printf("여섯 번째 "); break;
    }
}

int main() {
    Candidate candidates[CANDIDATES];

    printf("####################################\n");
    printf("     오디션 후보자 데이터 입력\n");
    printf("####################################\n");

    for (int i = 0; i < CANDIDATES; i++) {
        printCandidateOrder(i);
        printf("후보자의 정보를 입력합니다.\n", i + 1);
        printf("---------------------------------\n");

        printf("1. 성명: ");
        scanf("%s", candidates[i].name);

        printf("2. 생일(YYYY/MM/DD 형식): ");
        scanf("%s", candidates[i].birthday);

        printf("3. 성별(여성이면 F 또는 남성이면 M): ");
        scanf(" %c", &candidates[i].gender);

        printf("4. 메일 주소: ");
        scanf("%s", candidates[i].email);

        printf("5. 국적: ");
        scanf("%s", candidates[i].nationality);

        printf("6. BMI: ");
        scanf("%f", &candidates[i].bmi);

        printf("7. 주 스킬: ");
        scanf("%s", candidates[i].mainSkill);

        printf("8. 보조 스킬: ");
        scanf("%s", candidates[i].subSkill);

        printf("9. 한국어 등급(TOPIK, 원어민은 0 입력): ");
        scanf("%d", &candidates[i].topik);

        printf("10. MBTI: ");
        scanf("%s", candidates[i].mbti);

        printf("11. 소개: ");
        scanf(" %[^\n]s", candidates[i].intro); // reads until newline, including spaces

        printf("=================================\n");
    }

    // 출력
    printf("\n####################################\n");
    printf("     오디션 후보자 데이터 조회 \n");
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("성   명 | 생   일 | 성별 | 메   일            | 국적 | BMI  | 주스킬 | 보조스킬 | TOPIK  | MBTI |\n");
    printf("=============================================================================================\n");

    for (int i = 0; i < CANDIDATES; i++) {
        char topikStr[20];
        if (candidates[i].topik == 0) {
            sprintf(topikStr, "원어민");
        } else {
            sprintf(topikStr, "%d급", candidates[i].topik);
        }

        // Format birthday without slashes
        char birthNoSlash[9];
        sscanf(candidates[i].birthday, "%4c/%2c/%2c", &birthNoSlash[0], &birthNoSlash[4], &birthNoSlash[6]);
        birthNoSlash[8] = '\0';

        printf("%-6s |%-8s| %-3s | %-18s |%-5s| %-4.1f | %-6s | %-7s | %-6s | %-4s |\n",
            candidates[i].name,
            birthNoSlash,
            candidates[i].gender == 'F' ? "여" : "남",
            candidates[i].email,
            candidates[i].nationality,
            candidates[i].bmi,
            candidates[i].mainSkill,
            candidates[i].subSkill,
            topikStr,
            candidates[i].mbti
        );
        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[i].intro);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}