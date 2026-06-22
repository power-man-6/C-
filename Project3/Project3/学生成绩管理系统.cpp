#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAXSIZE 3
typedef struct student
{
	char stuno[20];//学号
	char name[20];//学生姓名
	int score[3];//M门课程的分数
	int total;//存储学生的总成绩
}student, * stdo;
stdo g_stus[MAXSIZE+1];
void PrintMenu();//打印菜单
void Input();//输入学生信息
void Delete();//删除学生信息
void Modify();//修改学生信息
void Query();//查询学生信息
void Sort();//计算总分并排序
void Display();//显示全部学生信息
void Exit();//退出系统
int Partition();//一次快速排序
int QSort();//快速排序
//打印菜单
void PrintMenu()
{
	system("cls");//清屏
	system("title 学生成绩管理系统");
	system("color 03");
	system("date/T");
	system("time/T");
	printf("*----------------------------------------------------*\n");
	printf("*               欢迎使用学生成绩管理系统             *\n");
	printf("*----------------------------------------------------*\n");
	printf("*               1： 录入成绩                         *\n");
	printf("*               2： 删除成绩                         *\n");
	printf("*               3： 修改成绩                         *\n");
	printf("*               4： 成绩查询                         *\n");
	printf("*               5： 成绩计算并排名                   *\n");
	printf("*               6： 显示成绩信息                     *\n");
	printf("*               0： 退出系统                         *\n");
	printf("*----------------------------------------------------*\n");
	printf("选择操作<0-6>                                         \n");
	return;
}
int main()
{
	PrintMenu();
	return 0;
}
