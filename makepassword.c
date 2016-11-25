#include <stdio.h>
#include <time.h>
#include <string.h>

void makepassword() {
	int password;
	FILE* pw = NULL;
	clock_t time;
	pw = fopen(".shadow", "w");

	//비밀번호를 입력받는 부분 인자 input
	//10글자 이내로 입력받아서 저장

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