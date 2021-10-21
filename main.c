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
	printf("   < �ѳ����б� ������û ������Ż >		\n\n");
	printf(" (1)	ȸ������ \n (2)	�α��� (�л�) \n (3)	�α��� (����)\n");
	printf("��ɾ �Է����ּ��� >> ");
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
		printf("��ɾ �ٽ� �Է����ּ���.\n");
	}

}

void print_Student(STUDENT s) {
	printf("** name : %s\n", s.profile.name);
	printf("** age : %d\n", s.profile.age);
}

STUDENT signUp_student() {

	printf("===== ȸ������ (�л�) =====\n");

	STUDENT stu = { 0 };

	printf("�� ID : "); scanf_s("%s", stu.id, sizeof(stu.id));
	printf("�� PW : "); scanf_s("%s", stu.pw, sizeof(stu.pw));
	printf("�� �̸� : "); scanf_s("%s", stu.profile.name, sizeof(stu.profile.name));
	printf("�� ���� : "); scanf_s("%d", &stu.profile.age);
	printf("�� ��ȭ��ȣ : "); scanf_s("%s", stu.profile.phone_number, sizeof(stu.profile.phone_number));

	return stu;
}

void login_student() { }

void login_professor() { }

int main(void) {

	__init__();

	return 0;
}
