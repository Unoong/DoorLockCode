#include <stdio.h>
#include <time.h>

void makepassword() {
	int password;
	FILE* pw = NULL;

	pw = fopen(".shadow", "w");

	//비밀번호를 입력받는 부분 인자 input

	clock_t key;
	password = ((int)key) ^ input;
	fprintf(pw, "%d", password);
	return;
}