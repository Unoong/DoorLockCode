#include <stdio.h>
#include <time.h>
#include <string.h>

void makepassword() {
	int password;
	FILE* pw = NULL;
	clock_t time_cpu = clock();
	pw = fopen(".shadow", "w");

	//비밀번호를 입력받는 부분 인자 input
	//받은 후 정수형태로 변경

	key = (int)time_cpu;
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