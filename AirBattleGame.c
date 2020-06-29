/*
	Name: AirBattleGame_2.0
	Author: WangGH577
	School: CQUPT
	Completed_Date: 02/25/2020 17:49
	Published_Date: 03/03/2020 18:04
	Last_Updated:   06/29/2020 13:20
	Description:
		仅用于交流学习，未经允许禁止用作其他商业行为
		如果想引用部分代码进行创作并上传网络, 请注明原作者
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

//游戏常数参数
enum constant
{
	Edge = -1, AirPlane = 1, Space = 0, Bullet = 2, Enemy = 3, EnergyRecoveryFactor = 4,	//对应元素
	SpMax = 100, HpMax = 100,	//最大值
	J = 3, K = 100, L = 500,	//技能
	SpRecover1 = 2, SpRecover2 = 20,	//能量回复
	High = 27, Width = 52,	//界面大小
	EnengyConsumptionK = 50, EnengyConsumptionL = 20,	//能量回复
	EnemyMoveSpeed = 3,	//敌机速率(递减) 
	ProbabERF = 10,	//产生能量因子的概率
};

typedef struct 
{
	int x;
	int y;
}POS;

//初值
POS air, enemy;
int canvas[High][Width] = { 0 };		//画布
int score = 0, hp = HpMax, sp = SpMax, p = 1;	//得分，生命，能量，概率
int k0 = 0, k1 = 0, k2 = 0;			//技能

void Welcome(void);
void Start(void);
void Print(void);
void UpdateWithInput(void);
void UpdateWithoutInput(void);

void NewEnemy(void);
int EnemyJudge(void);

void HideCur(void);
void GoToXY(int x, int y);

//主函数
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



//输出 
void Print(void)
{
	GoToXY(0, 0);
	//打印地图及元素
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

	//打印血条
	for (i = 1; i <= 10; i++)
	{
		if (i <= hp / 10)
		{
			printf("▅");
		}
		else
		{
			printf("  ");
		}
	}
	if(k2 > 0)
	{
		printf("回复中...");
	}
	else
	{
		printf("              ");
	}
	printf("\nHP  = %3d\n", hp);

	//打印得分
	printf("\t\t\tScore = %4d\n", score);

	//打印蓝条
	for (i = 1; i <= 10; i++)
	{
		if (i <= sp / 10)
		{
			printf("▅");
		}
		else
		{
			printf("  ");
		}
	}
	printf("\nSP  = %3d", sp);

	//生命低于0，结束游戏
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

//初始化
void Start(void)
{
	srand(time(0));

	//飞机位置
	air.x = 3 * High / 4;
	air.y = Width / 2;
	canvas[air.x][air.y] = AirPlane;

	NewEnemy();
	
	//地图边界
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

//与输入有关的更新
void UpdateWithInput(void)
{
	if (kbhit())
	{
		char input = getch();
		//飞机移动
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

		//飞机攻击及技能释放
		else if ( (input == 'j' || input == 'J') )
		{
			k0 = J;
		}
		// k技能 扫射
		else if ( (input == 'k' || input == 'K') && sp >= EnengyConsumptionK && k1 == 0)
		{
			sp -= EnengyConsumptionK;
			k1 = K;
		}
		// l技能 生命恢复
		else if ( (input == 'l' || input == 'L') && sp >= EnengyConsumptionL && hp < HpMax && hp > 0 && k2 == 0)
		{
			sp -= EnengyConsumptionL;
			k2 = L;
		}
		//暂停游戏
		else if (input == 27)
		{
			GoToXY(High / 4, Width / 4);
			printf("		      Pause");
			getch();
		}
	}
}

//与输入无关的更新
void UpdateWithoutInput(void)
{

	//寻找子弹  子弹飞行  
	int i, j;
	for (i = 1; i < High - 2; i++)	
	{//子弹不可能出现在最后一行，所以只需搜索到 High - 2行（High - 1行为边界）
		for (j = 1; j < Width - 1; j++)
		{
			if (canvas[i][j] == Bullet)
			{
				//子弹移动
				if (i > 1)
				{
					canvas[i - 1][j] = Bullet;
				}
				canvas[i][j] = Space;
				//子弹击中
				if ((i - 1 == enemy.x || i == enemy.x || i + 1 == enemy.x) && j == enemy.y)
				{
					score++;
					//判断能量恢复
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

	//j技能k0 普攻
	if (k0 != 0)
	{
		if (k0 % 3 != 0)
		{
			//产生子弹
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

	//k技能k1 扫射
	if (k1 != 0 )
	{
		if (k1 % 4 != 0)
		{
			//产生子弹
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

	//l技能k2 生命恢复（缓慢恢复10点） 
	if (k2 != 0)
	{
		if (k2 % 50 == 0)
		{
			hp++;
		}
		k2--;
	}

	//敌机到达底部
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

	//敌机运动更新
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
	
	//飞机与敌机相撞
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

	//保证生命和能量不越界
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

//欢迎界面  
void Welcome(void)
{
	HideCur();
	int i;
	for (i = 0; i < High / 3; i++)
	{
		printf("\n");
	}
	printf("			 飞机大战");

	for (i = 0; i < High / 3; i++)
	{
		printf("\n");
	}
	printf("	      == Press any key and begin in 1 s ==\n\n\n");
	getch();
	Sleep(1000);
	
}

//产生新敌机或能量因子
void NewEnemy(void)
{
	if (canvas[enemy.x][enemy.y] == EnemyJudge() )
	{
		canvas[enemy.x][enemy.y] = Space;
	}

	p = rand() % ProbabERF;

	enemy.x = 1;
	enemy.y = rand() % (Width - 16) + 8;	//为了游戏降低难度，敌机不会出现在靠近边界的位置
	canvas[enemy.x][enemy.y] = EnemyJudge();
}

//判断敌机类型（敌机/能量因子）
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

//隐藏光标 
void HideCur(void)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info = {1, 0};
	SetConsoleCursorInfo(handle, &info);
}
//光标移动 
void GoToXY(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
