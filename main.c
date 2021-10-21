#include <stdio.h>
#include <stdlib.h>

typedef struct Person_info {
	char name[40];
	char phone_number[40];
	int age;
}PERSON;

typedef struct Student_info {
	char id[40];
	char pw[40];
	PERSON profile;

}STUDENT;

int cmd;
int cnt = 0;
STUDENT stu_arr[50] = { 0 };

STUDENT signUp_student();
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
	case 1:
		stu_arr[cnt] = signUp_student();
		cnt++;
		break;

		/*
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

void print_Student(STUDENT s) {
	printf("** name : %s\n", s.profile.name);
	printf("** age : %d\n", s.profile.age);
}

STUDENT signUp_student() {

	printf("===== 회원가입 (학생) =====\n");

	STUDENT stu = { 0 };

	printf("▶ ID : "); scanf_s("%s", stu.id, sizeof(stu.id));
	printf("▶ PW : "); scanf_s("%s", stu.pw, sizeof(stu.pw));
	printf("▶ 이름 : "); scanf_s("%s", stu.profile.name, sizeof(stu.profile.name));
	printf("▶ 나이 : "); scanf_s("%d", &stu.profile.age);
	printf("▶ 전화번호 : "); scanf_s("%s", stu.profile.phone_number, sizeof(stu.profile.phone_number));

	return stu;
}

void login_student() { }

void login_professor() { }

int main(void) {

	__init__();

	return 0;
}
