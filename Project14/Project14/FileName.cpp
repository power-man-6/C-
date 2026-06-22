#include<iostream>
#include<string.h>
void resever(char arr[], int size)
{
	char* p = arr;
	char* q = arr + size - 1;
	while (p < q)
	{
		char ch = *p;
		*p = *q;
		*q = ch;
		p++;
		q--;
}
int main()
{ 
	char arr[] = "hello wold";
	resever(arr, strlen(arr));
	std::cout << arr << std::endl;
	return 0;
}