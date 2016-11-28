#include<stdio.h>
#include<time.h>
#include<string.h>

void main()
{
	int ft, lt; // 제한할 시작 시간, 나중 시간
	char pass[10] = ("1234"); //password가 저장될 공간
	char input[10];
	time_t nowTime = time(NULL);
	struct tm *pTmNow = localtime(&nowTime); //시간정보가 담긴 tm 구조체에 현재시간 지정

	scanf("%d %d", &ft, &lt); // 제한할 시간 범위 입력

	//if (pTmNow) printf("%d시 %d분 %d초\n", pTmNow->tm_hour, pTmNow->tm_min, pTmNow->tm_sec);    --> 현재시간 시,분,초 출력

	printf("password: ");
	scanf("%s", input);

	if (pTmNow->tm_hour >= ft && pTmNow->tm_hour < lt){   // 현재시간과 제한 시간 비교

		printf("connection rejected\n");  // 제한시간 범위라면 거절
	}

	else{
		if (strcmp(input, pass) == 0) printf("correct\n");
		else printf("wrong password\n");

	}

}