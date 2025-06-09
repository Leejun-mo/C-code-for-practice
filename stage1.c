#include <stdio.h>
#include <string.h>

char Main_Menu_Input[10], Return[10], Yes_Or_No[10], Pass_Or_Fail_BW[20], Pass_Or_Fail_ST[20], Exit[10];
int Training_Menu_Input, One_Loop = 0, Second_Loop = 0, First_Two_Fin = 0;
void Main_Menu() {
    printf("~{마그라테아 프로그램 메뉴}~\n");
    printf("I.오디션 관리, II.훈련, III.데뷔\n");
    printf("<종료>:(0) 또는 (q)\n");
}
void Training_Menu() {
    printf("~{마그라테아 프로그램 훈련 메뉴}~\n");
    printf("(1.체력과 지식) %s, (2.자기관리 및 팀워크) %s, (3.언어 및 발음), (4.보컬)\n", Pass_Or_Fail_BW, Pass_Or_Fail_ST);
    printf("(5.댄스), (6.비주얼 및 이미지), (7.연기 및 무대 퍼포먼스), (8.팬 소통)\n");
    printf("3~8 번 메뉴는 1번과 2번을 순서대로 통과했을 경우 선택할 수 있습니다.\n");
    printf("<뒤 돌아가기 또는 종료> (아무 키)\n");
}
void Inputc(char *str) {
    printf("Input:");
    scanf("%s",str);
}
void Inputi(int *num) {
    printf("Input: ");
    scanf("%d", num);
}
void Not_Implemented_Yet() {
    printf("아직 구현되지 않은 기능\n");
    printf("\n");
}
void Unknown_Input() {
    printf("제시되지 않는 입력 오류.\n");
}

int main () {
    while (1) {
        Main_Menu();
        Inputc(Main_Menu_Input);
        if (Main_Menu_Input[0]=='0' || Main_Menu_Input[0]=='q') {
            printf("마그라테아 프로그램 종료");
            break;
        } else if (strcmp(Main_Menu_Input, "I") == 0 || strcmp(Main_Menu_Input, "III") == 0) {
            Not_Implemented_Yet();
        } else if (strcmp(Main_Menu_Input, "II") == 0){
            while (1) {
                Training_Menu();
                Inputi(&Training_Menu_Input);
                if (Training_Menu_Input == 1) {
                    if (One_Loop == 1) {
                        printf("이미 평가를 완료한 항목입니다.\n\n");
                        continue;
                    }
                    printf("평가 결과를 입력하시겠습니까? (Y/N)\n");
                    Inputc(Yes_Or_No);
                    if (strcmp(Yes_Or_No, "Y") == 0) {
                        printf("훈련을 마치고 인증에 통과했나요? (P/F)\n");
                        Inputc(Pass_Or_Fail_BW);
                        if (strcmp(Pass_Or_Fail_BW, "P") == 0) {
                            strcpy(Pass_Or_Fail_BW, "<통과>");
                            One_Loop = 1;
                        } else if (strcmp(Pass_Or_Fail_BW, "F") == 0) {
                            strcpy(Pass_Or_Fail_BW, "<실패>");
                            One_Loop = 1;
                        } else {
                            Unknown_Input();
                            continue;
                        }
                    } else if (strcmp(Yes_Or_No, "N") == 0){
                        printf("마그라테아 프로그램 훈련 메뉴 페이지로 리디렉션 중...\n\n");
                        continue;
                    } else {
                        Unknown_Input();
                        continue;
                    }
                } else if (Training_Menu_Input == 2) {
                    if (Second_Loop == 1) {
                        printf("이미 평가를 완료한 항목입니다.\n\n");
                        continue;
                    }
                    if (One_Loop != 1) {
                        printf("1번 항목을 먼저 완료해야 합니다.\n\n");
                        continue;
                    }
                    printf("평가 결과를 입력하시겠습니까? (Y/N)\n");
                    Inputc(Yes_Or_No);
                    if (strcmp(Yes_Or_No, "Y") == 0) {
                        printf("훈련을 마치고 인증에 통과했나요? (P/F)\n");
                        Inputc(Pass_Or_Fail_ST);
                        if (strcmp(Pass_Or_Fail_ST, "P") == 0) {
                            strcpy(Pass_Or_Fail_ST, "<통과>");
                            Second_Loop = 1;
                            First_Two_Fin = 1;
                        } else if (strcmp(Pass_Or_Fail_ST, "F") == 0) {
                            strcpy(Pass_Or_Fail_ST, "<실패>");
                            Second_Loop = 1;
                            First_Two_Fin = 1;
                        } else {
                            Unknown_Input();
                            continue;
                        }
                    } else if (strcmp(Yes_Or_No, "N") == 0){
                        printf("마그라테아 프로그램 훈련 메뉴 페이지로 리디렉션 중...\n\n");
                        continue;
                    } else {
                        Unknown_Input();
                        continue;
                    }
                } else if (Training_Menu_Input >= 3 && Training_Menu_Input <= 8 && First_Two_Fin != 1) {
                    printf("3~8 번 메뉴는 1번과 2번을 순서대로 통과했을 경우 선택할 수 있습니다.\n\n");
                    continue;
                } else if (Training_Menu_Input >= 3 && Training_Menu_Input <= 8 && First_Two_Fin == 1) {
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
            printf("\n");
            if (strcmp(Return, "r") == 0) {
                continue;
                printf("\n");
            } else {
                printf("마그라테아 프로그램 종료");
                break;
            }
        }

    }
    
}
