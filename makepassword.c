#include <stdio.h>
#include <time.h>
#include <string.h>

void makepassword() {
	int password;
	FILE* pw = NULL;
	clock_t time;
	pw = fopen(".shadow", "w");

	//��й�ȣ�� �Է¹޴� �κ� ���� input
	//10���� �̳��� �Է¹޾Ƽ� ����

	key = (int)time;
	password = key ^ //input;
	fprintf(pw, "%d", password);
	fclose(pw);
	return;
}

int matchpassword(char *input,int key) {
	char password_origin[10];
	char temp[10];
	FILE* pw = NULL;
	pw = fopen(".shadow", "r");
	fscanf(pw, "%s", password_origin);
	fclose(pw);
	if (strcmp(password_origin , key ^ input) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}