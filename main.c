#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>

#define true 1
#define false 0

typedef struct Person_info {
	char name[40];
	char phone_number[40];
	int age;
}PERSON;

typedef struct Lecture_info {
	char major[20];
	char serial[20];
	char title[20];
	char professor[20];
	int point;
	char time[20];
	int member;
}LECTURE;

typedef struct Student_info {
	char job[20];
	char id[40];
	char pw[40];
	int lecture_point;
	PERSON profile;
	LECTURE lecture_arr[10];		// 수강과목 배열

}STUDENT;

typedef struct Professor_info {
	char id[40];
	char pw[40];
	PERSON profile;
	//LECTURE lecture_arr[10];		// 수업 하는 과목 목록 기능 추가 

}PROFESSOR;


int cmd;
int cnt_stu = 0;
int cnt_prof = 0;
int init_state = true;
int main_state = false;
int chk_login = false;
int lec_num = 0;

STUDENT stu_arr[50] = { 0 };		// 학생 회원 목록
PROFESSOR prof_arr[50] = { 0 };	// 교수 회원 목록
LECTURE lec_arr[50] = { 0 };			// 과목 리스트 

STUDENT user_student = { 0 };			// 로그인시 학생 유저 
PROFESSOR user_professor = { 0 };	// 로그인시 교수 유저 

STUDENT signUp_student();			// test
//STUDENT signUp_student(char*[20], char*[20], char*[20], char*[20], int*);

PROFESSOR signUp_professor();		// test
//PROFESSOR signUp_professor(char* [20], char* [20], char* [20], char* [20], int*);

void clear();
void login_student(char*, char*);
void login_professor(char*, char*);
void select_cmd(int);
void __init__();
void __main__Student();
void __main__Professor();
void cmd_main_Profesor(int);
void update_lecture();
void do_update_lecture_info(LECTURE*);
LECTURE upload_lecture_info();
void cmd_main_Student(int);
void print_format_lec_info(LECTURE);
void search_lecture_list();

//test method
void print_prof_arr();


void __init__() {

	
	//prof_arr[cnt_prof] = test_prof;
	cnt_prof++;

	while (init_state) {

		clear();
		printf("\n\n   < 한남대학교 수강신청 통합포탈 >		\n\n");
		printf(" (1)	회원가입 \n (2)	로그인 \n (3)	종료\n");
		printf("명령어를 입력해주세요 >> ");
		scanf_s("%d", &cmd);
		printf("\n\n");
		select_cmd(cmd);
	}
}

void select_cmd(int c) {
	clear();
	char ent_id[40];
	char ent_pw[40];

	switch (c) {
		case 1:
			printf("▶ (1) 학생 회원가입		(2) 교수 회원가입\n >>>"); scanf_s("%d", &cmd);

			if (cmd == 1) {
				stu_arr[cnt_stu] = signUp_student();
				cnt_stu++;
			}
			else if (cmd == 2) {
				prof_arr[cnt_prof] = signUp_professor();
				cnt_prof++;
			}

			
			
			/*char _ent_id[20], _ent_pw[20], _ent_name[20], _ent_phone_number[20];
			int _ent_age;
			printf("▶ ID : "); scanf_s("%s", _ent_id, sizeof(_ent_id));
			printf("▶ PW : "); scanf_s("%s", _ent_pw, sizeof(_ent_pw));
			printf("▶ 이름 : "); scanf_s("%s", _ent_name, sizeof(_ent_name));
			printf("▶ 나이 : "); scanf_s("%d", &_ent_age);
			printf("▶ 전화번호 : "); scanf_s("%s", _ent_phone_number, sizeof(_ent_phone_number));
			
			if (cmd == 1) {
				stu_arr[cnt_stu] = signUp_student(&_ent_id, &_ent_pw, &_ent_name, &_ent_phone_number, &_ent_age);
				cnt_stu++;
			}
			else if (cmd == 2) {
				prof_arr[cnt_prof] = signUp_professor(&_ent_id, &_ent_pw, &_ent_name, &_ent_phone_number, &_ent_age);
				cnt_prof++;
			}*/

			
			break;

		case 2:

			printf("** prof : %d	stu : %d\n\n", cnt_prof, cnt_stu);
			print_prof_arr();

			printf("▶ (1) 학생 로그인	(2) 교수 로그인\n >>> "); scanf_s("%d", &cmd);

			printf("▶ ID : "); scanf_s("%s", ent_id, sizeof(ent_id));
			printf("▶ PW : "); scanf_s("%s", ent_pw, sizeof(ent_pw));

			if (cmd == 1) login_student(ent_id, ent_pw);
			else if (cmd == 2) login_professor(ent_id, ent_pw);

			break;

		case 3:
			init_state = false;
			break;

		default:
			printf("명령어를 다시 입력해주세요.\n");
	}

}

void print_Student(STUDENT s) {
	printf("** name : %s\n", s.profile.name);
	printf("** age : %d\n", s.profile.age);
}

STUDENT signup_student() {
	clear();
	printf("〓〓〓〓〓 회원가입 (학생) 〓〓〓〓〓\n");

	STUDENT stu = { 0 };

	printf("▶ id : "); scanf_s("%s", stu.id, sizeof(stu.id));
	printf("▶ pw : "); scanf_s("%s", stu.pw, sizeof(stu.pw));
	printf("▶ 이름 : "); scanf_s("%s", stu.profile.name, sizeof(stu.profile.name));
	printf("▶ 나이 : "); scanf_s("%d", &stu.profile.age);
	printf("▶ 전화번호 : "); scanf_s("%s", stu.profile.phone_number, sizeof(stu.profile.phone_number));
	
	printf("\n\n★ 회원가입 성공!\n");
	print_student(stu);

	return stu;
}


//STUDENT signUp_student(char* _id[20], char* _pw[20], char* _name[20], char* _phone_number[20], int* _age) {
//	
//	STUDENT stu = { .id = *_id, .pw = *_pw, .profile = {.name = *_name, .phone_number = *_phone_number, .age = *_age} };
//
//	return stu;
//}


PROFESSOR signUp_professor() {
	clear();
	printf("〓〓〓〓〓 회원가입 (교수) 〓〓〓〓〓\n");

	PROFESSOR prof = { 0 };

	printf("▶ ID : "); scanf_s("%s", prof.id, sizeof(prof.id));
	printf("▶ PW : "); scanf_s("%s", prof.pw, sizeof(prof.pw));
	printf("▶ 이름 : "); scanf_s("%s", prof.profile.name, sizeof(prof.profile.name));
	printf("▶ 나이 : "); scanf_s("%d", &prof.profile.age);
	printf("▶ 전화번호 : "); scanf_s("%s", prof.profile.phone_number, sizeof(prof.profile.phone_number));

	return prof;
}


//PROFESSOR test_prof = { .id = "4444", .pw = "1234", .profile = {.name = "이승환", .phone_number = "01047822616", .age = 24 } };

//PROFESSOR signUp_professor(char* _id[20], char* _pw[20], char* _name[20], char* _phone_number[20], int* _age ) {
//
//	PROFESSOR prof = {.id = *_id, .pw = *_pw, .profile = {.name = *_name, .phone_number = *_phone_number, .age = *_age}};
//
//	return prof;
//}

// test _case 
void print_prof_arr() {

	PROFESSOR prof = { 0 };

	for (int i = 0; i < cnt_prof; i++) {
		prof = prof_arr[i];
		printf("→ NAME : %s,  ID : %s,  PW : %s\n", prof.profile.name, prof.id, prof.pw);
	}
}


void login_student(char* ent_id, char* ent_pw) {
	clear();
	printf("〓〓〓〓〓 로그인 (학생) 〓〓〓〓〓\n");

	for (int i = 0; i < cnt_stu; i++) {
		if (strcmp(stu_arr[i].id, ent_id) == 0) {
			// pw 확인
			if (strcmp(stu_arr[i].pw, ent_pw) == 0) {
				user_student = stu_arr[i];		// 로그인 성공 
				main_state = true;
				chk_login = true;
				printf("★ 로그인 성공 : %s\n", user_student.profile.name);
				__main__Student();
			}
			else printf("▶ 비밀번호가 일치하지 않습니다. \n");		// 비밀번호 오류
			break;
		}
	} if (chk_login == false) printf("▶ 로그인 실패 !");
}

void login_professor(char* ent_id, char* ent_pw) {
	clear();
	printf("〓〓〓〓〓 로그인 (교수) 〓〓〓〓〓\n");

	for (int i = 0; i < cnt_prof; i++) {
		if (strcmp(prof_arr[i].id, ent_id) == 0) {

			if (strcmp(prof_arr[i].pw, ent_pw) == 0) {
				user_professor = prof_arr[i];		// 로그인 성공 
				main_state = true;
				chk_login = true;
				printf("★ 로그인 성공 : %s\n", user_professor.profile.name);
				__main__Professor();				// 메인 실행 (교수) 
			}
			else printf("▶ 비밀번호가 일치하지 않습니다. \n");		// 비밀번호 오류
			break;
		}
	} if (chk_login == false) printf("▶ 로그인 실패 !");

}

void __main__Professor() {
	while(main_state) {
		clear();
		printf("\n▶ 사용자 : %s (%s) \n\n", user_professor.profile.name, user_professor.id);
		printf("	1 .		강의 등록\n	2 .		강의 수정\n	3 .		로그아웃 \n >>> ");
		scanf_s("%d", &cmd);
		cmd_main_Profesor(cmd);
	}
}

void cmd_main_Profesor(int c) {
	clear();
	switch (c) {
		case 1 :
			lec_arr[lec_num] = upload_lecture_info();
			lec_num += 1;
			break;

		case 2 : 
			update_lecture();
			break;

		case 3 : 
			printf("◎ 로그아웃 \n");
			main_state = false;
			break;

		default : 
			printf("※ 명령어를 다시 입력해주세요 \n");
	}
}

LECTURE upload_lecture_info() {
	clear();
	printf("〓〓〓〓〓 강의 등록 〓〓〓〓〓\n");
	LECTURE lec = { 0 };
	printf(" ▶ 학과	"); scanf_s("%s", lec.major, sizeof(lec.major));
	printf(" ▶ 학수번호	"); scanf_s("%s", lec.serial, sizeof(lec.serial));
	printf(" ▶ 강의명	"); scanf_s("%s", lec.title, sizeof(lec.title));
	printf(" ▶ 교수명	"); scanf_s("%s", lec.professor, sizeof(lec.professor));
	printf(" ▶ 학점	"); scanf_s("%d", &lec.point);
	printf(" ▶ 시간	"); scanf_s("%s", lec.time, sizeof(lec.time));
	printf(" ▶ 수강인원	"); scanf_s("%d", &lec.member);
	return lec;
}

void update_lecture() {
	clear();
	printf("〓〓〓〓〓 강의 수정 〓〓〓〓〓\n");
	bool chk_update = false;
	int num;
	printf(" ▶ 학수번호 조회	"); scanf_s("%d", &num);

	for (int i = 0; i < lec_num; i++) {
		if (num == i) {
			do_update_lecture_info(lec_arr + num);
			chk_update = true;
		}
	} 

	if (chk_update) printf("	※ 수정 완료 \n");
	else printf("	※ 자료를 찾지 못하였습니다. \n");
}

void do_update_lecture_info(LECTURE* lec) {
	clear();
	printf(" ▶ 학점	"); scanf_s("%d", &(lec->point));
	printf(" ▶ 시간	"); scanf_s("%s", lec->time, sizeof(lec->time));
	printf(" ▶ 수강인원	"); scanf_s("%d", &(lec->member));
}

void __main__Student() {

	while(main_state){
		clear();
		printf("〓〓〓〓〓 수강신청 목록 〓〓〓〓〓\n");

		search_lecture_list();

		printf("	1 .		수강 조회\n	2 .		수강 신청\n	3 .		장바구니\n	4. 로그아웃 \n >>> ");
		scanf_s("%d", &cmd);
		cmd_main_Student(cmd);
		printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	}
}

void cmd_main_Student(int c) {
	switch (c) {
		case 1: 
			search_lecture_list();
			break;

		case 2 : 
			//
			break;
		
		case 3 :
			//
			break;
		
		case 4 : 
			printf("◎ 로그아웃 \n");
			main_state = false;
			break;

		default :
			printf("명령어를 다시 입력해주세요.\n");
	}
}

void print_format_lec_info(LECTURE lec) {
	printf("%-20s%-10s%-20s%-10s%-5d%-20s%-5d\n", lec.major, lec.serial, lec.title, lec.professor, lec.point, lec.time, lec.member);	
}

void search_lecture_list() {
	printf("%-20s%-10s%-20s%-10s%-5s%-20s%-5s\n", "학과", "학수번호", "과목명", "교수", "학점", "시간", "인원");
	for (int i = 0; i < lec_num; i++) print_format_lec_info(lec_arr[i]);
	printf("\n");
}

void clear() {
	Sleep(100);
	system("cls");
}

int main(void) {

	__init__();
	return 0;
}
