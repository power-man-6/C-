#include<iostream>
using namespace std;
#include <graphics.h>


constexpr auto swidth = 600;
constexpr auto sheight = 1100;
bool PointInRect(int x, int y, RECT& r)
{
	return(r.left <= x&&x<=r.right && x <= r.top <= y && y <= r.bottom);
}
//一个开始界面
void Welcome()
{
	LPCTSTR title = _T("飞机大战");
	LPCTSTR tplay = _T("开始游戏");
	LPCTSTR texit = _T("退出游戏");

	RECT tplayr, texitr;
	BeginBatchDraw();
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(60, 0, _T("黑体"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 5, title);

	settextstyle(40, 0, _T("黑体"));
	tplayr.left = swidth / 2 - textwidth(tplay) / 2;
	tplayr.right = tplayr.left + textwidth(tplay);
	tplayr.top = sheight / 5 * 2.5;
	tplayr.bottom = tplayr.top + textheight(tplay);

	texitr.left = swidth / 2 - textwidth(texit) / 2;
	texitr.right = texitr.left + textwidth(texit);
	texitr.top = sheight / 5 * 3;
	texitr.bottom = texitr.top + textheight(texit);

	outtextxy(tplayr.left, tplayr.top, tplay);
	outtextxy(texitr.left, texitr.top, texit);

	EndBatchDraw();
	while (true)
	{
		ExMessage mess;
		getmessage(&mess, EM_MOUSE);
			if (mess.lbutton)
			{
				if (PointInRect(mess.x, mess.y, tplayr))
				{
					return;
				}
				else if (PointInRect(mess.x, mess.y, texitr))
				{
					exit(0);
				}
			}
	}
}
//背景，敌机，英雄，子弹
class BK
{
public:BK(IMAGE& img)
	:img(img)
{
}
private:
	IMAGE& img;
	int x, y;
};

bool Play()
{
	setbkcolor(WHITE);
	cleardevice();
	bool is_play = true;
	IMAGE heroimg, enemyimg, bkimg, bulletimg;
	loadimage(&heroimg, _T("E:\\图片\\res\\minas"));
	loadimage(&enemyimg, _T("E:\\图片\\res\\aaa"));
	loadimage(&bkimg, _T("E:\\图片\\res\\背景2.jpg"));
	loadimage(&bulletimg, _T("E:\\图片\\res\\bbb"));
	while (is_play)
	{

	}
	return true;
}
int main()
{
	initgraph(swidth, sheight, EW_NOMINIMIZE | EW_SHOWCONSOLE);
	bool is_live = true;
	while (is_live)
	{
		Welcome();
		is_live = Play();
	}
	return 0;
}