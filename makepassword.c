#include <stdio.h>
#include <time.h>

void makepassword() {
	int password;
	FILE* pw = NULL;

	pw = fopen(".shadow", "w");

	//��й�ȣ�� �Է¹޴� �κ� ���� input

	clock_t key;
	password = ((int)key) ^ input;
	fprintf(pw, "%d", password);
	return;
}