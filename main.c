#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

//��Ϸ��������
enum constant
{
	Edge = -1, AirPlane = 1, Space = 0, Bullet = 2, Enemy = 3, EnergyRecoveryFactor = 4,	//���Ԫ��
	SpMax = 100, HpMax = 100,	//���ֵ
	J = 3, K = 100, L = 500,	//����
	SpRecover1 = 2, SpRecover2 = 20,	//�����ظ�
	High = 27, Width = 52,	//�����С
	EnengyConsumptionK = 50, EnengyConsumptionL = 20,	//�����ظ�
	EnemyMoveSpeed = 3,	//�л�����(�ݼ�) 
	ProbabERF = 10,	//�����������ӵĸ���
};

typedef struct 
{
	int x;
	int y;
}POS;

//��ֵ
POS air, enemy;
int canvas[High][Width] = { 0 };	//����
int score = 0, hp = HpMax, sp = SpMax, p = 1;	//�÷֣�����������������
int k0 = 0, k1 = 0, k2 = 0;		//����

void Welcome(void);
void Start(void);
void Print(void);
void UpdateWithInput(void);
void UpdateWithoutInput(void);

void NewEnemy(void);
int EnemyJudge(void);

void HideCur(void);
void GoToXY(int x, int y);

//������
int main()
{
	Welcome();
	Start();
	while (1)
	{
		Print();
		UpdateWithoutInput();
		UpdateWithInput();
	}
	return 0;
}



//��� 
void Print(void)
{
	GoToXY(0, 0);
	//��ӡ��ͼ��Ԫ��
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (canvas[i][j] == Space)
			{
				printf(" ");
			}
			else if (canvas[i][j] == AirPlane)
			{
				printf("*");
			}
			else if (canvas[i][j] == Bullet)
			{
				printf("|");
			}
			else if (canvas[i][j] == Enemy)
			{
				printf("@");
			}
			else if (canvas[i][j] == EnergyRecoveryFactor)
			{
				printf("+");
			}
			else if (canvas[i][j] == Edge)
			{
				printf("#");
			}
		}
		printf("\n");
	}
	printf("\n");

	//��ӡѪ��
	for (i = 1; i <= 10; i++)
	{
		if (i <= hp / 10)
		{
			printf("\3 ");
		}
		else
		{
			printf("  ");
		}
	}
	if(k2 > 0)
	{
		printf("�ظ���...");
	}
	else
	{
		printf("              ");
	}
	printf("\nHP  = %3d\n", hp);

	//��ӡ�÷�
	printf("\t\t\tScore = %4d\n", score);

	//��ӡ����
	for (i = 1; i <= 10; i++)
	{
		if (i <= sp / 10)
		{
			printf("\4 ");
		}
		else
		{
			printf("  ");
		}
	}
	printf("\nSP  = %3d", sp);

	//��������0��������Ϸ
	if (hp <= 0)
	{
		printf("\nGame Over!\n");
		printf("press any key to continue...");
		Sleep(1500);

		getch();
		exit(0);
	}

	Sleep(1);
}

//��ʼ��
void Start(void)
{
	srand(time(0));

	//�ɻ�λ��
	air.x = 3 * High / 4;
	air.y = Width / 2;
	canvas[air.x][air.y] = AirPlane;

	NewEnemy();
	
	//��ͼ�߽�
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (i == 0 || j == 0 || i == High - 1 || j == Width - 1)
			{
				canvas[i][j] = Edge;
			}
		}
	}

}

//�������йصĸ���
void UpdateWithInput(void)
{
	if (kbhit())
	{
		char input = getch();
		//�ɻ��ƶ�
		if ( (input == 'a' || input == 'A') && air.y > 1)
		{
			canvas[air.x][air.y] = Space;
			air.y--;
			canvas[air.x][air.y] = AirPlane;
		}
		else if ( (input == 'd' || input == 'D') && air.y < Width - 2)
		{
			canvas[air.x][air.y] = Space;
			air.y++;
			canvas[air.x][air.y] = AirPlane;
		}
		else if ( (input == 'w' || input == 'W') && air.x > 1)
		{
			canvas[air.x][air.y] = Space;
			air.x--;
			canvas[air.x][air.y] = AirPlane;
		}
		else if ( (input == 's' || input == 'S') && air.x < High - 2)
		{
			canvas[air.x][air.y] = Space;
			air.x++;
			canvas[air.x][air.y] = AirPlane;
		}

		//�ɻ������������ͷ�
		else if ( (input == 'j' || input == 'J') )
		{
			k0 = J;
		}
		// k���� ɨ��
		else if ( (input == 'k' || input == 'K') && sp >= EnengyConsumptionK && k1 == 0)
		{
			sp -= EnengyConsumptionK;
			k1 = K;
		}
		// l���� �����ָ�
		else if ( (input == 'l' || input == 'L') && sp >= EnengyConsumptionL && hp < HpMax && hp > 0 && k2 == 0)
		{
			sp -= EnengyConsumptionL;
			k2 = L;
		}
		//��ͣ��Ϸ
		else if (input == 27)
		{
			GoToXY(High / 4, Width / 4);
			printf("		      Pause");
			getch();
		}
	}
}

//�������޹صĸ���
void UpdateWithoutInput(void)
{

	//Ѱ���ӵ�  �ӵ�����  
	int i, j;
	for (i = 1; i < High - 2; i++)	
	{//�ӵ������ܳ��������һ�У�����ֻ�������� High - 2�У�High - 1��Ϊ�߽磩
		for (j = 1; j < Width - 1; j++)
		{
			if (canvas[i][j] == Bullet)
			{
				//�ӵ��ƶ�
				if (i > 1)
				{
					canvas[i - 1][j] = Bullet;
				}
				canvas[i][j] = Space;
				//�ӵ�����
				if ((i - 1 == enemy.x || i == enemy.x || i + 1 == enemy.x) && j == enemy.y)
				{
					score++;
					//�ж������ָ�
					if (p == 0)
					{
						sp += SpRecover2;
					}
					else
					{
						sp += SpRecover1;
					}
					NewEnemy();
				}
			}
		}
	}

	//j����k0 �չ�
	if (k0 != 0)
	{
		if (k0 % 3 != 0)
		{
			//�����ӵ�
			int d;
			for (d = -1; d <= 1; d++)
			{
				if (air.y + d >= 1 && air.y + d <= Width - 2 && air.x - 1 > 1)
				{
					canvas[air.x - 1][air.y + d] = Bullet;
				}
			}
		}
		k0--;
	}

	//k����k1 ɨ��
	if (k1 != 0 )
	{
		if (k1 % 4 != 0)
		{
			//�����ӵ�
			int d;
			for (d = -3; d <= 3; d++)
			{
				if (air.y + d >= 1 && air.y + d <= Width - 2 && air.x - 1 > 1)
				{
					canvas[air.x - 1][air.y + d] = Bullet;
				}
			}
		}
		k1--;
	}

	//l����k2 �����ָ��������ָ�10�㣩 
	if (k2 != 0)
	{
		if (k2 % 50 == 0)
		{
			hp++;
		}
		k2--;
	}

	//�л�����ײ�
	if (enemy.x >= High - 2) 
	{
		if (p == 0)
		{
			sp += SpRecover1;
		}
		else
		{
			hp -= 10;
		}
		NewEnemy();
	}

	//�л��˶�����
	static int speed = 0;
	if (speed <= EnemyMoveSpeed)
	{
		speed++;
		if (speed == EnemyMoveSpeed)
		{
			canvas[enemy.x][enemy.y] = Space;
			enemy.x++;
			canvas[enemy.x][enemy.y] = EnemyJudge();
			speed = 0;
		}
	}
	
	//�ɻ���л���ײ
	if ( (enemy.x == air.x && enemy.y == air.y))
	{
		if (p == 0)
		{
			sp += SpRecover2;
			canvas[air.x][air.y] = AirPlane; 
			NewEnemy();
		}
		else
		{
			if (hp >= HpMax / 2)
			{
				hp = 1;
				canvas[air.x][air.y] = AirPlane;
				NewEnemy();
			}
			else
			{
				hp = 0;
			}
		}
	}

	//��֤������������Խ��
	if (sp < 0 || sp > SpMax || hp < 0 || hp > HpMax)
	{
		if (hp < 0)
		{
			hp = 0;
		}
		else if (hp > HpMax)
		{
			hp = HpMax;
		}
		if (sp < 0)
		{
			sp = 0;
		}
		else if (sp > SpMax)
		{
			sp = SpMax;
		}
	}

}

//��ӭ����  
void Welcome(void)
{
	HideCur();
	int i;
	for (i = 0; i < High / 3; i++)
	{
		printf("\n");
	}
	printf("			 �ɻ���ս");

	for (i = 0; i < High / 3; i++)
	{
		printf("\n");
	}
	printf("	      == Press any key and begin in 1 s ==\n\n\n");
	getch();
	Sleep(1000);
	
}

//�����µл�����������
void NewEnemy(void)
{
	if (canvas[enemy.x][enemy.y] == EnemyJudge() )
	{
		canvas[enemy.x][enemy.y] = Space;
	}

	p = rand() % ProbabERF;

	enemy.x = 1;
	enemy.y = rand() % (Width - 16) + 8;	//Ϊ����Ϸ�����Ѷȣ��л���������ڿ����߽��λ��
	canvas[enemy.x][enemy.y] = EnemyJudge();
}

//�жϵл����ͣ��л�/�������ӣ�
int EnemyJudge(void)
{
	if (p == 0)
	{
		return EnergyRecoveryFactor;
	}
	else
	{
		return Enemy;
	}
}

//���ع�� 
void HideCur(void)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(handle, &cursor_info);
}
//����ƶ� 
void GoToXY(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
