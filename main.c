#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

typedef struct Person_info {
	char name[40];
	char phone_number[40];
	int age;
}PERSON;

typedef struct Student_info {
	char id[40];
	char pw[40];
	PERSON profile;

	// 수강 목록 기능 추가 

}STUDENT;

typedef struct Professor_info {
	char id[40];
	char pw[40];
	PERSON profile;

	// 수업 하는 과목 목록 기능 추가 

}PROFESSOR;

int cmd;
int cnt_stu = 0;
int cnt_prof = 0;
int state = true;
int chk_login = false;

STUDENT stu_arr[50] = { 0 };		// 학생 회원 목록
PROFESSOR prof_arr[50] = { 0 };	// 교수 회원 목록

STUDENT user_student = { 0 };			// 로그인시 학생 유저 

STUDENT signUp_student();
PROFESSOR signUp_professor();
void login_student();
void select_cmd(int);
void __init__();

void __init__() {
	while (state) {
		printf("\n\n   < 한남대학교 수강신청 통합포탈 >		\n\n");
		printf(" (1)	회원가입 \n (2)	로그인 (학생) \n (3)	로그인 (교수)\n (4)	종료\n");
		printf("명령어를 입력해주세요 >> ");
		scanf_s("%d", &cmd);
		printf("\n\n");
		select_cmd(cmd);
	}
}

void select_cmd(int c) {
	switch (c) {
	case 1:

		stu_arr[cnt_stu] = signUp_student();
		cnt_stu++;
		break;

	case 2:
		login_student();
		// login에 성공하여 chk_login이 true가 되면 메인 기능 실행 
		break;

		/*case 3 :
			login_professor();
			break;
		*/
	case 4:
		state = false;
		break;

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

	printf("\n\n★ 회원가입 성공!\n");
	print_Student(stu);

	return stu;
}
//
//PROFESSOR signUp_professor() {
//
//	printf("===== 회원가입 (교수) =====\n");
//
//	PROFESSOR prof = { 0 };
//
//	printf("▶ ID : "); scanf_s("%s", prof.id, sizeof(prof.id));
//	printf("▶ PW : "); scanf_s("%s", prof.pw, sizeof(prof.pw));
//	printf("▶ 이름 : "); scanf_s("%s", prof.profile.name, sizeof(prof.profile.name));
//	printf("▶ 나이 : "); scanf_s("%d", &prof.profile.age);
//	printf("▶ 전화번호 : "); scanf_s("%s", prof.profile.phone_number, sizeof(prof.profile.phone_number));
//
//	return prof;
//}

void login_student() {

	char ent_id[40];
	char ent_pw[40];

	printf("try login... \n");

	printf("===== 로그인 (학생) =====\n");
	printf("▶ ID : "); scanf_s("%s", ent_id, sizeof(ent_id));
	printf("▶ PW : "); scanf_s("%s", ent_pw, sizeof(ent_pw));

	for (int i = 0; i < cnt_stu; i++) {
		if (strcmp(stu_arr[i].id, ent_id) == 0) {
			// pw 확인
			if (strcmp(stu_arr[i].pw, ent_pw) == 0) {
				user_student = stu_arr[i];		// 로그인 성공 
				chk_login = true;
			}
			else printf("▶ 비밀번호가 일치하지 않습니다. \n");		// 비밀번호 오류
			break;
		}
	}
	if (chk_login == false) printf("▶ 로그인 실패 !");
}

void login_professor() { }

int main(void) {

	__init__();
	return 0;
}
