#include <stdio.h>
#include <stdlib.h>

int cmd;

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
		printf("��ɾ �ٽ� �Է����ּ���.\n");
	}

}

void login_student() { }

void login_professor() { }

int main(void) {

	__init__();

	return 0;
}
