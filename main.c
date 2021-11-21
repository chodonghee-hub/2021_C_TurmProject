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
	LECTURE lecture_arr[10];		// �������� �迭

}STUDENT;

typedef struct Professor_info {
	char job[20];
	char id[40];
	char pw[40];
	PERSON profile;
	LECTURE lecture_arr[10];		// ���� �ϴ� ���� ��� ��� �߰� 

}PROFESSOR;

int cmd;
int cnt_stu = 0;
int cnt_prof = 0;
int init_state = true;
int main_state = false;
int chk_login = false;

STUDENT stu_arr[50] = { 0 };		// �л� ȸ�� ���
PROFESSOR prof_arr[50] = { 0 };	// ���� ȸ�� ���

STUDENT user_student = { 0 };			// �α��ν� �л� ���� 
PROFESSOR user_professor = { 0 };	// �α��ν� ���� ���� 

STUDENT signUp_student();
PROFESSOR signUp_professor();
void login_student(char*, char*);
void login_professor(char*, char*);
void select_cmd(int);
void __init__();
void __main__Student();
void __main__Professor();
void cmd_main_Profesor(int);

void __init__() {
	while (init_state) {
		printf("\n\n   < �ѳ����б� ������û ������Ż >		\n\n");
		printf(" (1)	ȸ������ \n (2)	�α��� \n (3)	����\n");
		printf("��ɾ �Է����ּ��� >> ");
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
			printf("�� (1) �л� ȸ������		(2) ���� ȸ������\n >>>"); scanf_s("%d", &cmd);

			if (cmd == 1) {
				stu_arr[cnt_stu] = signUp_student();
				cnt_stu++;
			}
			else if (cmd == 2) {
				prof_arr[cnt_prof] = signUp_professor();
				cnt_prof++;
			}
			break;

		case 2:

			printf("�� (1) �л� �α���	(2) ���� �α���\n >>> "); scanf_s("%d", &cmd);

			printf("�� ID : "); scanf_s("%s", ent_id, sizeof(ent_id));
			printf("�� PW : "); scanf_s("%s", ent_pw, sizeof(ent_pw));

			if (cmd == 1) login_student(ent_id, ent_pw);
			else if (cmd == 2) login_professor(ent_id, ent_pw);

			break;

		case 3:
			init_state = false;
			break;

		default:
			printf("��ɾ �ٽ� �Է����ּ���.\n");
	}

}

void print_Student(STUDENT s) {
	printf("** name : %s\n", s.profile.name);
	printf("** age : %d\n", s.profile.age);
}

STUDENT signUp_student() {

	printf("������ ȸ������ (�л�) ������\n");

	STUDENT stu = { 0 };

	printf("�� ID : "); scanf_s("%s", stu.id, sizeof(stu.id));
	printf("�� PW : "); scanf_s("%s", stu.pw, sizeof(stu.pw));
	printf("�� �̸� : "); scanf_s("%s", stu.profile.name, sizeof(stu.profile.name));
	printf("�� ���� : "); scanf_s("%d", &stu.profile.age);
	printf("�� ��ȭ��ȣ : "); scanf_s("%s", stu.profile.phone_number, sizeof(stu.profile.phone_number));
	
	printf("\n\n�� ȸ������ ����!\n");
	print_Student(stu);

	return stu;
}

PROFESSOR signUp_professor() {

	printf("������ ȸ������ (����) ������\n");

	PROFESSOR prof = { 0 };

	printf("�� ID : "); scanf_s("%s", prof.id, sizeof(prof.id));
	printf("�� PW : "); scanf_s("%s", prof.pw, sizeof(prof.pw));
	printf("�� �̸� : "); scanf_s("%s", prof.profile.name, sizeof(prof.profile.name));
	printf("�� ���� : "); scanf_s("%d", &prof.profile.age);
	printf("�� ��ȭ��ȣ : "); scanf_s("%s", prof.profile.phone_number, sizeof(prof.profile.phone_number));

	return prof;
}

void login_student(char* ent_id, char* ent_pw) {

	printf("������ �α��� (�л�) ������\n");

	for (int i = 0; i < cnt_stu; i++) {
		if (strcmp(stu_arr[i].id, ent_id) == 0) {
			// pw Ȯ��
			if (strcmp(stu_arr[i].pw, ent_pw) == 0) {
				user_student = stu_arr[i];		// �α��� ���� 
				main_state = true;
				chk_login = true;
				printf("�� �α��� ���� : %s\n", user_student.profile.name);
				__main__Student();
			}
			else printf("�� ��й�ȣ�� ��ġ���� �ʽ��ϴ�. \n");		// ��й�ȣ ����
			break;
		}
	} if (chk_login == false) printf("�� �α��� ���� !");
}

void login_professor(char* ent_id, char* ent_pw) {

	printf("������ �α��� (����) ������\n");

	for (int i = 0; i < cnt_prof; i++) {
		if (strcmp(prof_arr[i].id, ent_id) == 0) {

			if (strcmp(prof_arr[i].pw, ent_pw) == 0) {
				user_professor = prof_arr[i];		// �α��� ���� 
				main_state = true;
				chk_login = true;
				printf("�� �α��� ���� : %s\n", user_professor.profile.name);
				__main__Professor();				// ���� ���� (����) 
			}
			else printf("�� ��й�ȣ�� ��ġ���� �ʽ��ϴ�. \n");		// ��й�ȣ ����
			break;
		}
	} if (chk_login == false) printf("�� �α��� ���� !");

}

void __main__Professor() {
	while(main_state) {
		printf("\n�� ����� : %s (%s) \n\n", user_professor.profile.name, user_professor.id);
		printf("	1 .		���� ���\n	2 .		���� ����\n	3 .		�α׾ƿ� \n >>> ");
		scanf_s("%d", &cmd);
		cmd_main_Profesor(cmd);
	}
}

void cmd_main_Profesor(int c) {

	switch (c) {
		case 1 :
			// upload_lecture_info()
			break;

		case 2 : 
			// update_lecture_info()
			break;

		case 3 : 
			printf("�� �α׾ƿ� \n");
			main_state = false;
			break;

		default : 
			printf("�� ��ɾ �ٽ� �Է����ּ��� \n");
	}
}

LECTURE upload_lecture_info() {
	LECTURE lec = { 0 };
	printf(" �� �а�	"); scanf_s("%s", lec.major, sizeof(lec.major));
	printf(" �� �м���ȣ	"); scanf_s("%s", lec.serial, sizeof(lec.serial));
	printf(" �� ���Ǹ�	"); scanf_s("%s", lec.title, sizeof(lec.title));
	printf(" �� ���Ǹ�	"); scanf_s("%s", lec.title, sizeof(lec.title));
	printf(" �� ������	"); scanf_s("%s", lec.professor, sizeof(lec.professor));
	printf(" �� ����	"); scanf_s("%d", lec.point, sizeof(lec.point));
	printf(" �� �ð�	"); scanf_s("%s", lec.time, sizeof(lec.time));
	printf(" �� �����ο�	"); scanf_s("%d", lec.member, sizeof(lec.member));
	return lec;
}

void __main__Student() {

	while(main_state){
		printf("������ ������û ��� ������\n");
		printf("");
		printf("������������������\n");
	}
}

int main(void) {

	__init__();
	return 0;
}
