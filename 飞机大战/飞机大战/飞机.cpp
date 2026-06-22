#include<iostream>
using namespace std;
#include<windows.h>
#include<ctime>
//游戏区域的宽与高
const int  WIDTH = 80;
const int  HEIGHT = 20;

//玩家飞机
struct Plane
{
	int x, y;
	char shape [3][3] = {
		{'<','0','>'},
		{' ','*',' '},
		{' ','^',' '}
	};
};
//子弹的结构体
struct Bullet {
	int x, y;
};
//敌机
struct Enemy {
	int x, y;
	char shape[3][3] = {
	{'^','o','^'},
	{' ','*',' '},
	{'<','v','>'}
	};
};
//绘制游戏画面
void draw(Plane player, Bullet bullet, Enemy enemy)
{
	system("cls");
	// 使用缓冲区避免闪烁
	char buffer[HEIGHT][WIDTH];
	memset(buffer, ' ', sizeof(buffer));
	for (int i=0;i < HEIGHT;i++)
	{
		for (int j=0;j < WIDTH;j++)
		{
			bool drawplayer = (i >= player.y && i < player.y + 3 && j >= player.x && j < player.x + 3);
			bool drawbullet = (i == bullet.y && j == bullet.x);
			bool drawenemy = (i >= enemy.y && i<enemy.y + 3 && j>enemy.x && j < enemy.x + 3);
			if (drawplayer)
			{
				cout << player.shape[i - player.y][j - player.x];
			}
			else if (drawbullet)
			{
				cout << "*";
			}
			else if (drawenemy)
			{
				cout << enemy.shape[i - enemy.y][j - enemy.x];
			}
			else { cout << " "; }
		}
	}
	cout << endl;
}
//控制玩家飞机移动
void morePlay(Plane& player, char input)
{
	switch (input) {
	case 'w':
		if (player.y > 0) player.y--;
		break;
	case 's':
		if (player.y < HEIGHT - 3) player.y++;
		break;
	case'a':
		if (player.x > 0)player.x--;
		break;
	case'd':
		if (player.x < WIDTH - 3) player.x++;
		break;
	}
}
//发射子弹
void fireBullet(Bullet &bullet,Plane player)
{
	bullet.x = player.x + 1;
	bullet.y = player.y + 1;
}
//移动子弹
void moveBullet(Bullet&bullet)
{
	bullet.y--;
}
//移动敌人飞机
void moveEnemy(Enemy &enemy)
{
	enemy.y++;
	if (enemy.y > HEIGHT - 1) {
		enemy.y = 0;
		enemy.x = rand() % (WIDTH - 3);
	}
}
//碰撞检测
bool isCollision(Bullet bullet, Enemy enemy)
{
	return bullet.y >= enemy.y && bullet.y < enemy.y + 3 && bullet.x >= enemy.x && bullet.x < enemy.x + 3;
}
int main()
{
	Plane player = { WIDTH / 2 - 1,HEIGHT - 3 };
	Bullet bullet = { -1,-1 };
	Enemy enemy = { rand() % (WIDTH - 3),0 };
	int score=0;
	char input;
	srand(static_cast<unsigned int>(time(nullptr)));
	while (true)
	{
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('w')) input = 'w';
		else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) input = 's';
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) input = 'a';
		else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) input = 'd';
		else if (GetAsyncKeyState(VK_SPACE)) input = ' ';
		else input = '\0';
		morePlay(player, input);
		if (input == ' ')
		{
			fireBullet(bullet, player);
		}
			moveEnemy(enemy);
			if (bullet.y >= 0) 
			{
				moveBullet(bullet);
				if (isCollision(bullet, enemy))
				{
					enemy.y = 0;
					enemy.x = rand() % (WIDTH - 3);
					bullet.x = -1;
					bullet.y = -1;
					score++;
				}
			}
			draw(player, bullet, enemy);
			cout << "Score:" << score << endl;

			Sleep(50);
	}
	return 0;
}