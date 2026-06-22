#include<iostream>
#include<string.h>
void Resever(char arr[], int size)
{
	char* q = arr;
	char* p = arr + size - 1;
	while (q<p)
	{
		char ch = *q;
		*q = *p;
		*p = ch;
		q++;
		p--;
	}
	
}
int main()
{
	char arr[] = "zhangyongbozhangjingqi";

	std::cout << "交换前：";
	std::cout << arr << std::endl;
	std::cout << "交换后：" << std::endl;
	Resever(arr, strlen(arr));
	std::cout << arr << std::endl;
}