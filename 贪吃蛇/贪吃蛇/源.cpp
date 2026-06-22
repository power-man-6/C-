#include<iostream>
#include<windows.h>
#include<ctime>
//定义方向枚举
enum Direction
{
	STOP = 0, LEFT, RIGHT, UP, DOWN
};
//定义蛇的结构体
struct Snack
{
	int x;
	int y;
	Snack* next;
};
//定义全局变量
const int width = 80;
const int height = 20;
int x, y, fruitx, fruity, score;
Direction dir;
Snack* head;//指向蛇头
Snack* tail;//指向蛇尾（管理蛇的身体链表）
//初始化游戏函数
void Setup()
{
	dir = STOP;
	score = 0;
	x = width / 2;
	y = height / 2;//蛇头的初始位置
	fruitx = rand() % width;
	fruity = rand() % height;
	head = new Snack;//为蛇头分配空间
	head->x = x;
	head->y = y;
	head->next = nullptr;//初始时游戏只有一个节点，即蛇头，所以下一个节点为空
	tail = head;
}
//绘制游戏画面
void Draw()
{
	system("cls");
	for (int i = 0;i < width + 2;i++)
		std::cout << "#";
	for (int i = 0;i < height;i++)
	{
		for (int j = 0;j < width;j++)
		{
			if (j == 0)
				std::cout << "#";
			if (i == y && j == x)
				std::cout << "0";
			else if (i == fruity && j == fruitx)
				std::cout << "x";
			else {
				Snack* temp = head;
				bool issnack = false;
				while (temp != nullptr)
				{
					if (temp->x == j && temp->y == i)
					{
						std::cout << "0";
						issnack = true;
						break;
					}
					temp = temp->next;
				}
				if (!issnack)
					std::cout << " ";
			}
			if (j == width - 1)
				std::cout << "#";
		}
	}
	for (int i = 0;i < width + 2;i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Score" << score << std::endl;
}
//获取用户输入的函数
void Input()
{
	if (GetAsyncKeyState(VK_UP) && dir != DOWN)
		dir = UP;
	else if
		(GetAsyncKeyState(VK_DOWN) && dir != UP)
		dir = DOWN;
	else if
		(GetAsyncKeyState(VK_LEFT) && dir != RIGHT)
		dir = LEFT;
	else if
		(GetAsyncKeyState(VK_RIGHT) && dir != LEFT)
		dir = RIGHT;
}
//游戏逻辑更新函数
void Logic()
{
	Snack* newHead = new Snack;
	newHead->next = head;
	switch (dir)
	{
	case UP:
		newHead->y = y - 1;
		newHead->x = x;
		break;
	case DOWN:
		newHead->y = y + 1;
		newHead->x = x;
		break;
	case LEFT:
		newHead->x = x - 1;
		newHead->y = y;
		break;
	case RIGHT:
		newHead->x = x + 1;
		newHead->y = y;
		break;
	default:
		break;
	}
	head = newHead;
	Snack* check = head->next;
	while (check != nullptr)
	{
		if (check->x == head->x && check->y == head->y)
		{
			std::cout << "Game Over!" << std::endl;
			exit(0);
		}
		check = check->next;
	}
	if (head->x >= width || head->x < 0 || head->y >= height || head->y < 0)
	{
		std::cout << "Game Over!" << std::endl;
		exit(0);
	}
	if (head->x == fruitx && head->y == fruity)
	{
		score += 10;
		fruitx = rand() % width;
		fruity = rand() % height;
	}
	else {
		Snack* temp = tail;
		tail = tail->next;
		delete temp;
	}
	x = head->x;
	x = head->y;
}
int main()
{
	srand(time(NULL));
	Setup();
	while (true) {
		Draw();
		Input();
		Logic();
		Sleep(100);

	}
	return 0;
}