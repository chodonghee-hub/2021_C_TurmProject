#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
}LECTURE;
typedef struct Student_info {
	char major[20];
	char id[20];
	char pw[20];
	int lecture_point;
	PERSON profile;
	LECTURE lecture_arr[10];		// 수강과목 배열
	char* lec_serial_arr[10];			// 수강과목 학수번호 목록 
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
STUDENT stu_arr[50] = { 0 };		// 학생 회원 목록
PROFESSOR prof_arr[50] = { 0 };	// 교수 회원 목록
LECTURE lec_arr[50] = { 0 };			// 과목 리스트 
STUDENT user_student = { 0 };			// 로그인시 학생 유저 
PROFESSOR user_professor = { 0 };	// 로그인시 교수 유저 
void do_signUp_student();
void do_signUp_professor();
STUDENT signUp_info_student();
PROFESSOR signUp_info_professor();
void login_student(char*, char*);
void login_professor(char*, char*);
void select_cmd(int);
void __init__();
void __main__Student();
void __main__Professor();
void cmd_main_Profesor(int);
void update_lecture();
void do_update_lecture_info(LECTURE*);
void do_upload_lecture();
LECTURE upload_lecture_info();
void cmd_main_Student(int);
void printFormat_lecture(LECTURE*);
void print_lec_list();
int is_my_lec_Professor(LECTURE*);
bool chk_id_in_stuArr(char[20]);
bool chk_id_in_profArr(char[20]);
bool chk_lec_in_lecArr(char[20]);
void do_select_lecture();
bool chk_lec_in_mine(char[20]);
LECTURE get_lecture_info(char[20]);
void print_my_lecture_list();

void __init__() {
	while (init_state) {
		printf("\n\n   < 한남대학교 수강신청 통합포탈 >		\n\n");
		printf(" (1)	회원가입 \n (2)	로그인 \n (3)	종료\n");
		printf("명령어를 입력해주세요 >> ");
		scanf_s("%d", &cmd);
		printf("\n\n");
		select_cmd(cmd);
	}
}
void select_cmd(int c) {
	char ent_id[40];
	char ent_pw[40];
	switch (c) {
	case 1:
		printf("▶ (1) 학생 회원가입		(2) 교수 회원가입\n >>>"); scanf_s("%d", &cmd);
		if (cmd == 1) do_signUp_student();
		else if (cmd == 2) do_signUp_professor();
		break;
	case 2:
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

void do_signUp_student() {
	STUDENT tmp_stu = signUp_info_student();
	if (chk_id_in_stuArr(tmp_stu.id)) {
		stu_arr[cnt_stu] = tmp_stu;
		cnt_stu++;
		printf("\n\n★ 회원가입 성공!\n");
		printf("** name : %s\n", tmp_stu.profile.name);
		printf("** age : %d\n", tmp_stu.profile.age);
	}
	else printf("\n※ 회원가입 실패, 존재하는 아이디 입니다.\n\n");
}

STUDENT signUp_info_student() {
	printf("\n〓〓〓〓〓 회원가입 (학생) 〓〓〓〓〓\n");
	STUDENT stu = { 0 };
	printf("▶ 학과 : "); scanf_s("%s", stu.major, sizeof(stu.major));
	printf("▶ ID : "); scanf_s("%s", stu.id, sizeof(stu.id));
	printf("▶ PW : "); scanf_s("%s", stu.pw, sizeof(stu.pw));
	printf("▶ 이름 : "); scanf_s("%s", stu.profile.name, sizeof(stu.profile.name));
	printf("▶ 나이 : "); scanf_s("%d", &stu.profile.age);
	printf("▶ 전화번호 : "); scanf_s("%s", stu.profile.phone_number, sizeof(stu.profile.phone_number));

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
		printf("\n\n★ 회원가입 성공!\n");
		printf("** name : %s\n", tmp_prof.profile.name);
		printf("** age : %d\n", tmp_prof.profile.age);
	}
	else printf("\n※ 회원가입 실패, 존재하는 아이디 입니다.\n\n");
}

PROFESSOR signUp_info_professor() {
	printf("\n〓〓〓〓〓 회원가입 (교수) 〓〓〓〓〓\n");
	PROFESSOR prof = { 0 };
	printf("▶ 학과 : "); scanf_s("%s", prof.major, sizeof(prof.major));
	printf("▶ ID : "); scanf_s("%s", prof.id, sizeof(prof.id));
	printf("▶ PW : "); scanf_s("%s", prof.pw, sizeof(prof.pw));
	printf("▶ 이름 : "); scanf_s("%s", prof.profile.name, sizeof(prof.profile.name));
	printf("▶ 나이 : "); scanf_s("%d", &prof.profile.age);
	printf("▶ 전화번호 : "); scanf_s("%s", prof.profile.phone_number, sizeof(prof.profile.phone_number));
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
	printf("\n〓〓〓〓〓 로그인 (학생) 〓〓〓〓〓\n");
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
	printf("\n〓〓〓〓〓 로그인 (교수) 〓〓〓〓〓\n");
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
	while (main_state) {
		printf("\n ▶ 사용자 : %s (%s) \n\n", user_professor.profile.name, user_professor.id);

		printf("%69s\n", "■■ 전체 과목 조회 ■■");
		print_lec_list();

		printf("	1 .		강의 등록\n	2 .		강의 수정\n	3 .		로그아웃 \n >>> ");
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
		printf("◎ 로그아웃 \n");
		main_state = false;
		break;
	default:
		printf("※ 명령어를 다시 입력해주세요 \n");
	}
}

void printForamt_lecture(LECTURE* lec) {
	printf("%13s%15s%15s%10s%15d%10s%15d%20.1f\n", lec->major, lec->serial, lec->title, lec->professor, lec->point, lec->time, lec->member, lec->succuss_rate);
}

void print_lec_list() {
	printf("\n\n%13s%15s%15s%10s%15s%10s%15s%20s\n", "학과", "학수번호", "강의명", "교수", "학점", "시간", "수강인원", "수강성공확률");
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	for (int i = 0; i < lec_num; i++) printForamt_lecture(lec_arr + i);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n\n");
}

int is_my_lec_Professor(LECTURE* lec) {
	return strcmp(user_professor.profile.name, lec->professor);
}

void do_upload_lecture() {
	LECTURE tmp_lec = upload_lecture_info();
	if (chk_lec_in_lecArr(tmp_lec.serial)) {
		lec_arr[lec_num] = tmp_lec;
		lec_num += 1;
		printf("\n● 강의 등록 성공\n");
	}
	else printf("\n○ 강의 등록 실패, 동일한 학수번호 강좌가 존재 합니다.\n");
}

LECTURE upload_lecture_info() {
	printf("\n〓〓〓〓〓 강의 등록 〓〓〓〓〓\n");
	LECTURE lec = { 0 };
	strncpy_s(lec.major, sizeof(lec.major), user_professor.major, sizeof(user_professor.major));
	strncpy_s(lec.professor, sizeof(lec.professor), user_professor.profile.name, sizeof(user_professor.profile.name));
	printf(" ▶ 학수번호	"); scanf_s("%s", lec.serial, sizeof(lec.serial));
	printf(" ▶ 강의명	"); scanf_s("%s", lec.title, sizeof(lec.title));
	printf(" ▶ 학점	"); scanf_s("%d", &lec.point);
	printf(" ▶ 시간	"); scanf_s("%s", lec.time, sizeof(lec.time));
	printf(" ▶ 수강인원	"); scanf_s("%d", &lec.member);
	return lec;
}

bool chk_lec_in_lecArr(char ent_serial[20]) {
	for (int i = 0; i < lec_num; i++) {
		if (strcmp(lec_arr[i].serial, ent_serial) == 0) return false;
	}return true;
}

void update_lecture() {

	bool chk_find = false;
	bool chk_update = false;

	char num[20];
	printf("\n\n ▶ 학수번호 조회  >>> "); scanf_s("%s", num, sizeof(num));
	for (int i = 0; i < lec_num; i++) {
		if (strncmp(lec_arr[i].serial, num, sizeof(lec_arr[i].serial)) == 0) {
			chk_find = true;
			if (is_my_lec_Professor(lec_arr + i) == 0) {
				do_update_lecture_info(lec_arr + i);
				chk_update = true;
			}
			else printf(" ※ 강의 수정 권한이 없습니다.\n");
			break;
		}
	}
	if (chk_find && chk_update) printf(" ※ 수정 완료 \n");
	else printf(" ※ 자료를 찾지 못하였습니다. \n");
}

void do_update_lecture_info(LECTURE* lec) {
	printf("\n〓〓〓〓〓 강의 수정 〓〓〓〓〓\n");

	printf(" ▶ 학점	"); scanf_s("%d", &(lec->point));
	printf(" ▶ 시간	"); scanf_s("%s", lec->time, sizeof(lec->time));
	printf(" ▶ 수강인원	"); scanf_s("%d", &(lec->member));
}

void __main__Student() {
	while (main_state) {
		printf("\n ▶ 사용자 : %s (%s) \n\n", user_student.profile.name, user_student.id);
		printf("%69s\n", "■■ 전체 과목 조회 ■■");

		print_lec_list();
		printf("	1 .		수강 신청\n	2 .		장바구니\n	3 .		로그아웃 \n >>> ");
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
		print_my_lecture_list();
		// 기능 추가 
		break;

	case 3:
		printf("◎ 로그아웃 \n");
		main_state = false;
		break;

	default:
		printf("명령어를 다시 입력해주세요.\n");
	}
}

void do_select_lecture() {
	char ent_serial[20];
	printf(" ▶ 수강 희망 과목 학수번호 입력 >>> "); scanf_s("%s", ent_serial, sizeof(ent_serial));
	if (!chk_lec_in_lecArr(ent_serial)) {
		if (chk_lec_in_mine(ent_serial)) {
			user_student.lec_serial_arr[user_student.cnt_my_lec] = ent_serial;
			user_student.cnt_my_lec++;
			printf("● 학수번호 : %s 추가 \n", ent_serial);
		}
		else printf("○ 이미 수강신청된 과목 입니다.  \n");
	}
}

bool chk_lec_in_mine(char ent_serial[20]) {
	for (int i = 0; i < user_student.cnt_my_lec; i++)
		if (strncmp(user_student.lec_serial_arr[i], ent_serial, sizeof(user_student.lec_serial_arr[i])) == 0) return false;
	return true;
}

LECTURE get_lecture_info(char serial[20]) {
	for (int i = 0; i < lec_num; i++) {
		if (strncmp(lec_arr[lec_num].serial, serial, sizeof(lec_arr[lec_num])) == 0)
			return lec_arr[i];
	}
}

void print_my_lecture_list() {
	printf("%69s\n", "■■■  장바구니  ■■■");
	printf("\n\n%13s%15s%15s%10s%15s%10s%15s%20s\n", "학과", "학수번호", "강의명", "교수", "학점", "시간", "수강인원", "수강성공확률");
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
	LECTURE tmp_lec = { 0 };
	for (int i = 0; i < user_student.cnt_my_lec; i++) {
		tmp_lec = get_lecture_info(user_student.lec_serial_arr[i]);
		printForamt_lecture(&tmp_lec);
	}
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
}

int main(void) {

	__init__();
	return 0;
}