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
	fprintf(pw, "%d %d",key,password);
	fclose(pw);
	return;
}

int matchpassword(int input) {
	int password_origin = 0;
	int key = 0;
	FILE* pw = NULL;
	pw = fopen(".shadow", "r");
	fscanf(pw, "%d %d",&key,&password_origin);
	fclose(pw);
	if (password_origin == key ^ input) {
		return 1;
	}
	else {
		return 0;
	}
}