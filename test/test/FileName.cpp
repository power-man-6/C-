#include<iostream>
using namespace std;
int main()
{
	int score = 0;
	cout << "请输入你的分数" << endl;
	cin >> score;
	cout << "您输入的分数为:" << endl;
	if (score > 600) {
		cout << "恭喜你考上一本！" << endl;
	}
	else {
		cout << "可惜！" << endl;

	}
	return 0;
}