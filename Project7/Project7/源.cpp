#include<iostream>
#include<windows.h>
int main()
{
	std::cout << "hellow C++" << std::endl;
	MessageBox(NULL, TEXT("hello C++"), TEXT("БъЬт"), MB_OK);
	system("pause");
	return 0;
}