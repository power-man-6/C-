//飞机大战
#include<iostream>
#include<graphics.h>
using namespace std;

constexpr auto swidth = 600;
constexpr auto sheight = 1100;

//开始界面
void Welcome()
{
	LPCTSTR title = _T("飞机大战");
	LPCTSTR	tplay = _T("开始游戏");
	LPCTSTR	texit = _T("退出游戏");

	RECT tplay, texitr;
	outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 10, title);
}
int main()
{//easyx初始化
	initgraph(swidth, sheight, EW_NOMINIMIZE | EW_SHOWCONSOLE);
	bool is_live = true;
	while (is_live)
	{
		Welcome();
	}
	return 0;
}