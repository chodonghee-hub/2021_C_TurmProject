#include <stdio.h>
#include <stdlib.h>

int cmd;

void select_cmd(int);
void __init__();

void __init__() {
	printf("   < 한남대학교 수강신청 통합포탈 >		\n\n");
	printf(" (1)	회원가입 \n (2)	로그인 (학생) \n (3)	로그인 (교수)\n");
	printf("명령어를 입력해주세요 >> ");
	scanf_s("%d", &cmd);
	printf("\n\n");
	select_cmd(cmd);
}

void select_cmd(int c) {
	switch (c) {
		/*
		case 1 :
			signUp_student();
			break;


		case 2 :
			login_student();
			break;

		case 3 :
			login_professor();
			break;
		*/

	default:
		printf("명령어를 다시 입력해주세요.\n");
	}

}

void login_student() { }

void login_professor() { }

int main(void) {

	__init__();

	return 0;
}
