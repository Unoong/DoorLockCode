#include<stdio.h>
#include<time.h>
#include<string.h>

void main()
{
	int ft, lt; // ������ ���� �ð�, ���� �ð�
	char pass[10] = ("1234"); //password�� ����� ����
	char input[10];
	time_t nowTime = time(NULL);
	struct tm *pTmNow = localtime(&nowTime); //�ð������� ��� tm ����ü�� ����ð� ����

	scanf("%d %d", &ft, &lt); // ������ �ð� ���� �Է�

	//if (pTmNow) printf("%d�� %d�� %d��\n", pTmNow->tm_hour, pTmNow->tm_min, pTmNow->tm_sec);    --> ����ð� ��,��,�� ���

	printf("password: ");
	scanf("%s", input);

	if (pTmNow->tm_hour >= ft && pTmNow->tm_hour < lt){   // ����ð��� ���� �ð� ��

		printf("connection rejected\n");  // ���ѽð� ������� ����
	}

	else{
		if (strcmp(input, pass) == 0) printf("correct\n");
		else printf("wrong password\n");

	}

}