#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#define true 1
#define false 0

typedef struct Person_info {
	char name[20];
	char phone_number[20];
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
	double succuss_rate;
	double cnt_res_person;
}LECTURE;

typedef struct Student_info {
	char major[20];
	char id[20];
	char pw[20];
	int lecture_point;
	PERSON profile;
	char lec_serial_arr[10][20];			// 수강과목 학수번호 목록 
	int cnt_my_lec;
}STUDENT;

typedef struct Professor_info {
	char major[20];
	char id[20];
	char pw[20];
	PERSON profile;
	LECTURE lecture_arr[10];		// 수업 하는 과목 목록 기능 추가 
}PROFESSOR;

int cmd;
int cnt_stu = 0;
int cnt_prof = 0;
int init_state = true;
int main_state = false;
int chk_login = false;
int lec_num = 0;
int is_my_lec_Professor(LECTURE*);
int get_lecture_info(char[20]);
int get_length_of(char[20]);
bool state_in_res = false;
STUDENT stu_arr[50] = { 0 };		
STUDENT* user_student = { 0 };
STUDENT signUp_info_student();
PROFESSOR prof_arr[50] = { 0 };	
PROFESSOR signUp_info_professor();
PROFESSOR* user_professor = { 0 };
LECTURE lec_arr[50] = { 0 };			
LECTURE upload_lecture_info();
void do_signUp_student();
void do_signUp_professor();
void login_student(char*, char*);
void login_professor(char*, char*);
void select_cmd(int);
void clear(int);
void __init__();
void __main__Student();
void __main__Professor();
void cmd_main_Profesor(int);
void update_lecture();
void do_update_lecture_info(LECTURE*);
void do_upload_lecture();
void print_my_lecture_list();
void __reservation__();
void cmd_reservation(int);
void cancel_lec_reservation();
void do_select_lecture();
void cmd_main_Student(int);
void printFormat_lecture(LECTURE*);
void print_lec_list();
bool chk_id_in_stuArr(char[20]);
bool chk_id_in_profArr(char[20]);
bool chk_lec_in_lecArr(char[20]);
bool chk_lec_in_mine(char[20]);

void __init__() {
	while (init_state) {
		clear(100);
		chk_login = false;
		printf("\n\n%40s< 한남대학교 수강신청 통합포탈 >\n\n", " ");
		printf("%35s(1)	회원가입 \n\n%35s(2)	로그인 \n\n%35s(3)	종료\n\n", " ", " ", " ");
		printf("%35s● 명령어를 입력해주세요 >>> ", " ");
		scanf_s("%d", &cmd);
		printf("\n\n");
		select_cmd(cmd);
	}
}

void clear(int wait_s) {
	Sleep(wait_s);
	system("cls");
}

void select_cmd(int c) {
	clear(100);
	char ent_id[40];
	char ent_pw[40];
	switch (c) {
	case 1:
		printf("\n\n\n\n%65s\n", "< S I G N - U P >\n\n");
		printf("%35s(1) 학생 회원가입	    (2) 교수 회원가입\n\n%35s>>> ", " ", " "); scanf_s("%d", &cmd);
		if (cmd == 1) do_signUp_student();
		else if (cmd == 2) do_signUp_professor();
		break;
	case 2:
		printf("\n\n\n\n%65s\n", "< L O G I N >\n\n");
		printf("%35s(1) 학생 로그인	    (2) 교수 로그인 \n\n%35s>>> ", " ", " "); scanf_s("%d", &cmd);
		if (cmd == 1 || cmd == 2) {
			printf("\n%35s● ID : ", " "); scanf_s("%s", ent_id, sizeof(ent_id));
			printf("\n%35s● PW : ", " "); scanf_s("%s", ent_pw, sizeof(ent_pw));
			if (cmd == 1) login_student(ent_id, ent_pw);
			else if (cmd == 2) login_professor(ent_id, ent_pw);
			break;
		}printf("%35s※명령어를 다시 입력해주세요.\n", " ");
		break;
	case 3:
		init_state = false;
		break;
	default:
		printf("%35s명령어를 다시 입력해주세요.\n", " ");
	}clear(500);
}

void do_signUp_student() {
	STUDENT tmp_stu = signUp_info_student();
	if (chk_id_in_stuArr(tmp_stu.id)) {
		stu_arr[cnt_stu] = tmp_stu;
		cnt_stu++;
		printf("\n\n%35s※★ 회원가입 성공!\n", " ");
		printf("%35s** name : %s\n", " ", tmp_stu.profile.name);
		printf("%35s** age : %d\n", " ", tmp_stu.profile.age);
	}
	else printf("\n\n%35s※ 회원가입 실패, 존재하는 아이디 입니다.\n\n", " ");
	clear(500);
}

STUDENT signUp_info_student() {
	clear(100);
	printf("\n\n%40s〓〓〓〓〓 Sign-up Student 〓〓〓〓〓\n", " ");
	STUDENT stu = { 0 };
	printf("\n%35s▶ 학과 : ", " "); scanf_s("%s", stu.major, sizeof(stu.major));
	printf("\n%35s▶ ID : ", " "); scanf_s("%s", stu.id, sizeof(stu.id));
	printf("\n%35s▶ PW : ", " "); scanf_s("%s", stu.pw, sizeof(stu.pw));
	printf("\n%35s▶ 이름 : ", " "); scanf_s("%s", stu.profile.name, sizeof(stu.profile.name));
	printf("\n%35s▶ 나이 : ", " "); scanf_s("%d", &stu.profile.age);
	printf("\n%35s▶ 전화번호 : ", " "); scanf_s("%s", stu.profile.phone_number, sizeof(stu.profile.phone_number));

	return stu;
}

bool chk_id_in_stuArr(char ent_id[20]) {
	for (int i = 0; i < cnt_stu; i++) {
		if (strncmp(stu_arr[i].id, ent_id, sizeof(stu_arr[i])) == 0)
			return false;
	}
	return true;
}

void do_signUp_professor() {
	PROFESSOR tmp_prof = signUp_info_professor();
	if (chk_id_in_profArr(tmp_prof.id)) {
		prof_arr[cnt_prof] = tmp_prof;
		cnt_prof++;
		printf("\n\n%35s★ 회원가입 성공!\n", " ");
		printf("%35s** name : %s\n", " ", tmp_prof.profile.name);
		printf("%35s** age : %d\n", " ", tmp_prof.profile.age);
	}
	else printf("\n※ 회원가입 실패, 존재하는 아이디 입니다.\n\n");
	clear(500);
}

PROFESSOR signUp_info_professor() {
	clear(100);
	printf("\n\n%40s〓〓〓〓〓 Sign-up Professor 〓〓〓〓〓\n", " ");
	PROFESSOR prof = { 0 };
	printf("\n%35s▶ 학과 : ", " "); scanf_s("%s", prof.major, sizeof(prof.major));
	printf("\n%35s▶ ID : ", " "); scanf_s("%s", prof.id, sizeof(prof.id));
	printf("\n%35s▶ PW : ", " "); scanf_s("%s", prof.pw, sizeof(prof.pw));
	printf("\n%35s▶ 이름 : ", " "); scanf_s("%s", prof.profile.name, sizeof(prof.profile.name));
	printf("\n%35s▶ 나이 : ", " "); scanf_s("%d", &prof.profile.age);
	printf("\n%35s▶ 전화번호 : ", " "); scanf_s("%s", prof.profile.phone_number, sizeof(prof.profile.phone_number));
	return prof;
}

bool chk_id_in_profArr(char ent_id[20]) {
	for (int i = 0; i < cnt_prof; i++) {
		if (strncmp(prof_arr[i].id, ent_id, sizeof(prof_arr[i].id)) == 0)
			return false;
	}
	return true;
}

void login_student(char* ent_id, char* ent_pw) {
	clear(100);
	printf("\n\n%40s〓〓〓〓〓 Login Student 〓〓〓〓〓\n", " ");
	for (int i = 0; i < cnt_stu; i++) {
		if (strcmp(stu_arr[i].id, ent_id) == 0) {
			if (strcmp(stu_arr[i].pw, ent_pw) == 0) {
				user_student = stu_arr + i;
				main_state = true;
				chk_login = true;
				printf("\n%35s★ 로그인 성공 : %s\n", " ", user_student->profile.name);
				__main__Student();
			}
			else printf("\n%35s▶ 비밀번호가 일치하지 않습니다. \n", " ");
			break;
		}
	} if (chk_login == false) printf("\n%35s※ 로그인 실패 !", " ");
	clear(500);
}

void login_professor(char* ent_id, char* ent_pw) {
	clear(100);
	printf("\n\n%40s〓〓〓〓〓 Login Professor 〓〓〓〓〓\n", " ");
	for (int i = 0; i < cnt_prof; i++) {
		if (strcmp(prof_arr[i].id, ent_id) == 0) {
			if (strcmp(prof_arr[i].pw, ent_pw) == 0) {
				user_professor = prof_arr + i;
				main_state = true;
				chk_login = true;
				printf("\n%35s★ 로그인 성공 : %s\n", " ", user_professor->profile.name);
				__main__Professor();
			}
			else printf("\n%35s▶ 비밀번호가 일치하지 않습니다. \n", " ");
			break;
		}
	} if (chk_login == false) printf("\n%35s※▶ 로그인 실패 !", " ");
	clear(500);
}

void __main__Professor() {
	while (main_state) {
		clear(100);
		printf("\n\n ▶ 사용자 : %s (%s) \n\n", user_professor->profile.name, user_professor->id);

		printf("%69s\n", "■■ 전체 과목 조회 ■■");
		print_lec_list();

		printf("\n\n%42s(1)  강의 등록\n\n%42s(2)  강의 수정\n\n%42s(3)  로그아웃 \n\n%42s● 명령어를 입력해주세요 >>> ", " ", " ", " ", " ");
		scanf_s("%d", &cmd);
		cmd_main_Profesor(cmd);
	}
}

void cmd_main_Profesor(int c) {
	switch (c) {
	case 1:
		do_upload_lecture();
		break;
	case 2:
		update_lecture();
		break;
	case 3:
		printf("\n\n\n%42s◎ 로그아웃 \n", " ");
		main_state = false;
		break;
	default:
		printf("※ 명령어를 다시 입력해주세요 \n");
	}
}

void printForamt_lecture(LECTURE* lec) {
	if (lec->member >= lec->cnt_res_person) lec->succuss_rate = 100;
	else lec->succuss_rate = (lec->member / lec->cnt_res_person) * 100;
	printf("%13s%15s%15s%10s%15d%10s%15d%20.f%s\n", lec->major, lec->serial, lec->title, lec->professor, lec->point, lec->time, lec->member, lec->succuss_rate, "%");
}

void print_lec_list() {
	printf("\n\n%13s%15s%15s%10s%15s%10s%15s%20s\n", "학과", "학수번호", "강의명", "교수", "학점", "시간", "수강인원", "수강성공확률");
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	for (int i = 0; i < lec_num; i++) printForamt_lecture(lec_arr + i);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n\n");
}

int is_my_lec_Professor(LECTURE* lec) {
	return strcmp(user_professor->profile.name, lec->professor);
}

void do_upload_lecture() {
	LECTURE tmp_lec = upload_lecture_info();
	if (chk_lec_in_lecArr(tmp_lec.serial)) {
		lec_arr[lec_num] = tmp_lec;
		lec_num += 1;
		printf("\n\n%35s● 강의 등록 성공\n", " ");
	}
	else printf("\n\n%35s○ 강의 등록 실패, 동일한 학수번호 강좌가 존재 합니다.\n", " ");
	clear(500);
}

LECTURE upload_lecture_info() {
	clear(100);
	printf("\n\n%40s〓〓〓〓〓 Upload Lecture 〓〓〓〓〓\n", " ");
	LECTURE lec = { 0 };
	strncpy_s(lec.major, sizeof(lec.major), user_professor->major, sizeof(user_professor->major));
	strncpy_s(lec.professor, sizeof(lec.professor), user_professor->profile.name, sizeof(user_professor->profile.name));
	printf("\n%35s▶ 학수번호 : ", " "); scanf_s("%s", lec.serial, sizeof(lec.serial));

	while (get_length_of(lec.serial) != 4) {
		printf("\n%35s▷ error : 학수번호 4자리를 입력해주세요 : ", " ");
		scanf_s("%s", lec.serial, sizeof(lec.serial));
	}

	printf("\n%35s▶ 강의명 : ", " "); scanf_s("%s", lec.title, sizeof(lec.title));
	printf("\n%35s▶ 학점 : ", " "); scanf_s("%d", &lec.point);
	printf("\n%35s▶ 시간 : ", " "); scanf_s("%s", lec.time, sizeof(lec.time));
	printf("\n%35s▶ 수강인원 : ", " "); scanf_s("%d", &lec.member);
	return lec;
}

bool chk_lec_in_lecArr(char ent_serial[20]) {
	for (int i = 0; i < lec_num; i++) {
		if (strcmp(lec_arr[i].serial, ent_serial) == 0) return false;
	}return true;
}

int get_length_of(char num[20]) {
	int length = 0;
	for (int i = 0; num[i] != '\0'; i++) length++;
	return length;
}

void update_lecture() {
	clear(100);
	bool chk_find = false;
	bool chk_update = false;

	char num[20];
	printf("\n\n\n\n%35s▶ 학수번호 조회 (4자리) >>> ", " "); scanf_s("%s", num, sizeof(num));

	while (get_length_of(num) != 4) {
		printf("\n%35s▷ error : 학수번호 4자리를 입력해주세요 : ", " ");
		scanf_s("%s", num, sizeof(num));
	}

	for (int i = 0; i < lec_num; i++) {
		if (strncmp(lec_arr[i].serial, num, 4) == 0) {
			chk_find = true;
			if (is_my_lec_Professor(lec_arr + i) == 0) {
				do_update_lecture_info(lec_arr + i);
				chk_update = true;
			}
			else printf("\n%35s※ 강의 수정 권한이 없습니다.\n", " ");
			break;
		}
	}
	if (chk_find && chk_update) printf("\n%35s※ 수정 완료 \n", " ");
	else printf("%35s※ 자료를 찾지 못하였습니다. \n", " ");
	clear(500);
}

void do_update_lecture_info(LECTURE* lec) {
	clear(10);
	printf("\n\n%40s〓〓〓〓〓 Update Lecture 〓〓〓〓〓\n", " ");
	printf("\n\n%35s▶ 학점 : ", " "); scanf_s("%d", &(lec->point));
	printf("\n\n%35s▶ 시간 : ", " "); scanf_s("%s", lec->time, sizeof(lec->time));
	printf("\n\n%35s▶ 수강인원 : ", " "); scanf_s("%d", &(lec->member));
}

void __main__Student() {
	while (main_state) {
		clear(10);
		printf("\n\n ▶ 사용자 : %s (%s) \n\n", user_student->profile.name, user_student->id);
		printf("%69s\n", "■■ 전체 과목 조회 ■■");

		print_lec_list();
		printf("\n\n%42s(1)  수강 신청\n\n%42s(2)  장바구니\n\n%42s(3)  로그아웃 \n\n%42s● 명령어를 입력해주세요 >>> ", " ", " ", " ", " ");
		scanf_s("%d", &cmd);
		cmd_main_Student(cmd);
	}
}

void cmd_main_Student(int c) {
	switch (c) {
	case 1:
		do_select_lecture();
		break;

	case 2:
		__reservation__();
		break;

	case 3:
		printf("\n\n\n%42s◎ 로그아웃 \n", " ");
		main_state = false;
		break;

	default:
		printf("명령어를 다시 입력해주세요.\n");
	}
}

void do_select_lecture() {
	char ent_serial[20];
	printf("\n\n\n%42s● 수강 희망 과목 학수번호 입력 >>> ", " "); scanf_s("%s", ent_serial, sizeof(ent_serial));
	if (!chk_lec_in_lecArr(ent_serial)) {
		if (chk_lec_in_mine(ent_serial)) {
			strcpy_s(user_student->lec_serial_arr[user_student->cnt_my_lec], sizeof(ent_serial), ent_serial);
			lec_arr[get_lecture_info(ent_serial)].cnt_res_person++;
			printf("\n%42s● 학수번호 : %s 추가 \n", " ", user_student->lec_serial_arr[user_student->cnt_my_lec]);
			user_student->cnt_my_lec++;
		}
		else printf("\n%42s○ 이미 수강신청된 과목 입니다.  \n", " ");
	}
	clear(500);
}

bool chk_lec_in_mine(char ent_serial[20]) {
	for (int i = 0; i < user_student->cnt_my_lec; i++)
		if (strncmp(user_student->lec_serial_arr[i], ent_serial, sizeof(user_student->lec_serial_arr[i])) == 0) return false;
	return true;
}

int get_lecture_info(char serial[20]) {
	for (int i = 0; i < lec_num; i++) {
		if (strncmp(lec_arr[i].serial, serial, sizeof(lec_arr[i])) == 0) return i;
	}
}

void __reservation__() {
	state_in_res = true;

	while (state_in_res) {
		clear(10);
		print_my_lecture_list();
		printf("\n\n%42s(1)  항목 삭제\n\n%42s(2)  메뉴로 돌아가기\n\n%42s● 명령어를 입력해주세요 >> ", " ", " ", " "); scanf_s("%d", &cmd);
		cmd_reservation(cmd);
	}
}

void cmd_reservation(int c) {
	switch (c) {
	case 1:
		cancel_lec_reservation();
		break;
	case 2:
		state_in_res = false;
		printf("\n%42s※ 장바구니 종료\n\n", " ");
		break;

	default:
		printf("\n%42s※ 명령어를 다시 입력해주세요 \n", " ");
	}
}

void cancel_lec_reservation() {
	clear(10);
	printf("\n\n%40s〓〓〓〓〓 Cancel Reservation 〓〓〓〓〓\n", " ");
	char ent_serial[20];
	int del_p = 0;
	printf("\n%37s● 취소할 학수번호를 입력해주세요 >>> ", " "); scanf_s("%s", ent_serial, sizeof(ent_serial));
	if (!chk_lec_in_mine(ent_serial)) {

		lec_arr[get_lecture_info(ent_serial)].cnt_res_person--;

		for (int i = 0; i < user_student->cnt_my_lec; i++) {
			if (strcmp(user_student->lec_serial_arr[i], ent_serial) == 0) {
				del_p = i;
				break;
			}
		}
		for (int i = del_p; i < user_student->cnt_my_lec; i++)
			strcpy_s(user_student->lec_serial_arr[i], sizeof(user_student->lec_serial_arr[i + 1]), user_student->lec_serial_arr[i + 1]);

		for (int i = 0; i < 4; i++)
			user_student->lec_serial_arr[user_student->cnt_my_lec][i] = '\0';
		user_student->cnt_my_lec--;
	}
}

void print_my_lecture_list() {
	printf("\n\n\n%69s\n", "■■■  장바구니  ■■■");
	printf("\n\n%13s%15s%15s%10s%15s%10s%15s%20s\n", "학과", "학수번호", "강의명", "교수", "학점", "시간", "수강인원", "수강성공확률");
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	LECTURE tmp_lec = { 0 };
	char tmp_serial[20];
	for (int i = 0; i < user_student->cnt_my_lec; i++) {
		strcpy_s(tmp_serial, sizeof(tmp_serial), user_student->lec_serial_arr[i]);
		tmp_lec = lec_arr[get_lecture_info(tmp_serial)];
		printForamt_lecture(&tmp_lec);
	}
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
}

int main(void) {
	system("mode con cols=122 lines=30 | title 불타는 수강 신청");
	__init__();
	return 0;
}