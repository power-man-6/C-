#include<iostream>
using namespace std;
#include<string>
#include<stack>
//中缀转后缀
bool Pri(char ch, char top)
{
	if ((ch == '*' || ch == '/') && (top == '+' || top == '-'))
		return true;
	if(top=='('&&ch!=')')
		return true;
	return false;
}
string MiddleToEndExpr(string expr)
{
	stack<char> s;
	string result;
	for (char ch : expr)
	{
		if (ch >= '0' && ch <= '9')
		{
			result.push_back(ch);
		}
		else
		{
			for (;;)
			{
				if (s.empty() || ch == '(')
				{
					s.push(ch);
					break;
				}
				else
					//比较当前符号与栈顶符号的优先级
				{
					char top = s.top();
					if (Pri(ch, top))//ch>top return true ch<=top return false
					{
						s.push(ch);
						break;
					}
					else
					{
						s.pop();
						if (top == '(')
							break;
						result.push_back(top);
					}
				}
			}
		}
	}
	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}
	return result;
}
int main()
{
	cout << MiddleToEndExpr("(1+2)*(3-4)") << endl;
	cout << MiddleToEndExpr("2+6/(4-2)+(4+6)/2") << endl;
}