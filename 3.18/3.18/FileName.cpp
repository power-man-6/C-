#include<iostream>
using namespace std;
#include<ctime>
int main()
{
	srand((unsigned int)time(NULL));
	int num = rand() % 100 + 1;
	int val = 0;
	while (1)
	{
		cout << "请输入你猜测的数字" << endl;
		cin >> val;
		if (val > num)
		{
			cout << "猜大了" << endl;
		}
		else if (val < num)
		{
			cout << "猜小了" << endl;
		}
		else
		{
			cout << "猜对了" << endl;
			break;
		}
	}
	return 0;
}