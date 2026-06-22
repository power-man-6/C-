#pragma once
#include<easyx.h>
//图形窗口的大小
#define BGWEIGHT 400//宽
#define BGHEIGHT 600//高


//1.打开窗口，加载图片，链表结构的体现，变量的定义。
//2.生成我方飞机，加移动。
//3.子弹的生成，发射。释放。

IMAGE img[4];//图片数组
//初始化函数
void init()
{
	//加载图片
	loadimage(&img[0], "res\\背景.jpg", BGWEIGHT, BGHEIGHT);
}


//开始函数
void start()
{
	initgraph(BGWEIGHT, BGHEIGHT);
	while (1);
	closegraph();
}