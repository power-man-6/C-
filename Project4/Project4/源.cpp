#include<iostream>
#include<cwchar>

using namespace std;
int main() 
{
	setlocale(LC_ALL, "");  // 使用系统默认区域设置
	wchar_t mr = L'张';
	wchar_t mar[] = L"我喜欢你";
	wcout << mr << endl;
	wcout << mar << endl;
	return  0 ;
}
