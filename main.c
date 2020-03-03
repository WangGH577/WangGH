#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define   MAX_LEN  10                	   /* 字符串最大长度 */
#define   STU_NUM 30                       /* 最多的学生人数 */
#define   COURSE_NUM 6                     /* 最多的考试科目数 */
typedef struct student
{
	long num;	/* 每个学生的学号 */
	char name[MAX_LEN];            	/* 每个学生的姓名 */
	float score[COURSE_NUM];	/* 每个学生COURSE_NUM门功课的成绩 */
	float sum;                       /* 每个学生的总成绩 */
	float aver;                   /* 每个学生的平均成绩 */
}STU;
int   Menu(void);
void  ReadScore(STU stu[], int n, int m);
void  AverSumofEveryStudent(STU stu[], int n, int m);
void  AverSumofEveryCourse(STU stu[], int n, int m);
void  SortbyScore(STU stu[], int n, int m, int (*compare)(float a, float b));
int   Ascending(float a, float b);
int   Descending(float a, float b);
void  SwapFloat(float* x, float* y);
void  SwapLong(long* x, long* y);
void  SwapChar(char x[], char y[]);
void  AsSortbyNum(STU stu[], int n, int m);
void  SortbyName(STU stu[], int n, int m);
void  SearchbyName(STU stu[], int n, int m);
void  SearchbyNum(STU stu[], int n, int m);
void  StatisticAnalysis(STU stu[], int n, int m);
void  PrintScore(STU stu[], int n, int m);
void  Swap(STU* x, STU* y);

int   main()
{
	STU stu[STU_NUM];
	int n, m;
	printf("Input student number(n<=30):\n");
	scanf("%d", &n);
	while (1)
	{
		int option = Menu();
		switch (option)
		{
		case 1:
			printf("Input course number(m<=%d):\n", 6);
			scanf("%d", &m);
			ReadScore(stu, n, m);
			break;
		case 2:
			AverSumofEveryCourse(stu, n, m);
			break;
		case 3:
			AverSumofEveryStudent(stu, n, m);
			break;
		case 4:
			SortbyScore(stu, n, m, Descending);
			printf("Sort in descending order by score:\n");
			PrintScore(stu, n, m);
			break;
		case 5:
			SortbyScore(stu, n, m, Ascending);
			printf("Sort in ascending order by score:\n");
			PrintScore(stu, n, m);
			break;
		case 6:
			AsSortbyNum(stu, n, m);
			printf("Sort in ascending order by number:\n");
			PrintScore(stu, n, m);
			break;
		case 7:
			SortbyName(stu, n, m);
			printf("Sort in dictionary order by name:\n");
			PrintScore(stu, n, m);
			break;
		case 8:
			SearchbyNum(stu, n, m);
			break;
		case 9:
			SearchbyName(stu, n, m);
			break;
		case 10:
			StatisticAnalysis(stu, n, m);
			break;
		case 11:
			PrintScore(stu, n, m);
			break;
		case 0:
			printf("End of program!");
			exit(0);
			break;
		default:
			printf("Input error!\n");
		}
	}
	return 0;
}

int   Menu(void)
{
	printf("Management for Students' scores\n"
		"1.Input record\n"
		"2.Caculate total and average score of every course\n"
		"3.Caculate total and average score of every student\n"
		"4.Sort in descending order by score\n"
		"5.Sort in ascending order by score\n"
		"6.Sort in ascending order by number\n"
		"7.Sort in dictionary order by name\n"
		"8.Search by number\n"
		"9.Search by name\n"
		"10.Statistic analysis\n"
		"11.List record\n"
		"0.Exit\n"
		"Please Input your choice:\n");
	int option;
	scanf("%d", &option);
	return option;
}

void  ReadScore(STU stu[], int n, int m)
{
	int i, j;
	printf("Input student's ID, name and score:\n");
	for (i = 0; i < n; i++)
	{
		scanf("%ld%s", &stu[i].num, stu[i].name);
		for (j = 0; j < m; j++)
		{
			scanf("%f", &stu[i].score[j]);
		}
	}
}

void  AverSumofEveryCourse(STU stu[], int n, int m)
{
	float sum_course[COURSE_NUM], ave_course[COURSE_NUM];
	int i, j;
	for (j = 0; j < m; j++)
	{
		sum_course[j] = 0;
		for (i = 0; i < n; i++)
		{
			sum_course[j] += stu[i].score[j];
		}
		ave_course[j] = sum_course[j] / n;
		printf("course %d:sum=%.0f,aver=%.0f\n", j + 1, sum_course[j], ave_course[j]);
	}
}

void  AverSumofEveryStudent(STU stu[], int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		stu[i].sum = 0;
		for (j = 0; j < m; j++)
		{
			stu[i].sum += stu[i].score[j];
		}
		stu[i].aver = stu[i].sum / m;
		printf("student %d: sum=%.0f,aver=%.0f\n", i + 1, stu[i].sum, stu[i].aver);
	}
}

void  SortbyScore(STU stu[], int n, int m, int (*compare)(float a, float b))
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 1; j < n - i; j++)
		{
			if (compare(stu[j].sum, stu[j - 1].sum))
			{
				Swap(&stu[j], &stu[j - 1]);
			}
		}
	}
}

void  AsSortbyNum(STU stu[], int n, int m)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 1; j < n - i; j++)
		{
			if (stu[j].num < stu[j - 1].num)
			{
				Swap(&stu[j], &stu[j - 1]);
			}
		}
	}
}

void  SortbyName(STU stu[], int n, int m)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 1; j < n - i; j++)
		{
			if (strcmp(stu[j].name, stu[j - 1].name) < 0)
			{
				Swap(&stu[j], &stu[j - 1]);
			}
		}
	}
}

int   Descending(float a, float b)
{
	return a > b;
}

int   Ascending(float a, float b)
{
	return a < b;
}

void  Swap(STU* x, STU* y)
{
	STU temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void  SwapFloat(float* x, float* y)
{
	float temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void  SwapLong(long* x, long* y)
{
	long temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void  SwapChar(char x[], char y[])
{
	char temp[MAX_LEN];
	strcpy(temp, x);
	strcpy(x, y);
	strcpy(y, temp);
}

void  SearchbyNum(STU stu[], int n, int m)
{
	long num;
	printf("Input the number you want to search:\n");
	scanf("%ld", &num);
	int i, j, flag = -1;
	for (i = 0; i < n; i++)
	{
		if (stu[i].num == num)
		{
			flag = i;
		}
	}
	if (flag == -1)
	{
		printf("Not found!\n");
	}
	else
	{
		printf("%ld\t%s\t", stu[flag].num, stu[flag].name);
		for (j = 0; j < m; j++)
		{
			printf("%.0f\t", stu[flag].score[j]);
		}
		printf("%.0f\t%.0f\n", stu[flag].sum, stu[flag].aver);
	}
}

void  SearchbyName(STU stu[], int n, int m)
{
	char name[MAX_LEN];
	printf("Input the name you want to search:\n");
	scanf(" %s", name);
	int i, j, flag = -1;
	for (i = 0; i < n; i++)
	{
		if (strcmp(stu[i].name, name) == 0)
		{
			flag = i;
		}
	}
	if (flag == -1)
	{
		printf("Not found!\n");
	}
	else
	{
		printf("%ld\t%s\t", stu[flag].num, stu[flag].name);
		for (j = 0; j < m; j++)
		{
			printf("%.0f\t", stu[flag].score[j]);
		}
		printf("%.0f\t%.0f\n", stu[flag].sum, stu[flag].aver);
	}
}

void  StatisticAnalysis(STU stu[], int n, int m)
{
	int i, j;
	for (j = 0; j < m; j++)
	{
		int cnt[6] = { 0 };
		printf("For course %d:\n", j + 1);
		for (i = 0; i < n; i++)
		{
			int x = stu[i].score[j] / 10;
			if (x >= 0 && x < 6)
			{
				cnt[0]++;
			}
			else
			{
				cnt[x - 5]++;
			}
		}
		printf("<60\t%d\t%.2f%%\n", cnt[0], 100.0 * cnt[0] / n);
		for (i = 1; i < 5; i++)
		{
			printf("%d-%d\t%d\t%.2f%%\n", (5 + i) * 10, (5 + i) * 10 + 9, cnt[i], 100.0 * cnt[i] / n);
		}
		printf("%d\t%d\t%.2f%%\n", 100, cnt[5], 100.0 * cnt[5] / n);
	}
}

void  PrintScore(STU stu[], int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		printf("%ld\t%s\t", stu[i].num, stu[i].name);
		for (j = 0; j < m; j++)
		{
			printf("%.0f\t", stu[i].score[j]);
		}
		printf("%.0f\t%.0f\n", stu[i].sum, stu[i].aver);
	}
}