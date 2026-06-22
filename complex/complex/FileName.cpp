#include<iostream>

using namespace std;
/*
String
实现一个字符串类

*/

class String
{
public:
  String(const char* p = nullptr)
  {
    if (p != nullptr)
    {
      _pstr = new char[strlen(p) + 1];
      strcpy(_pstr, p);
    }
    else
    {
      _pstr = new char[1];
      *_pstr = '\0';
    }
  }
  ~String()
  {
    delete[]_pstr;
    _pstr == nullptr;
  }
  //重载拷贝构造函数
  String(const String& str)
  {
    _pstr = new char[strlen(str._pstr) + 1];
    strcpy(_pstr, str._pstr);
  }
  //赋值运算符重载
  String& operator=(const String& src)
  {
    if (this == &src)
    {
      return *this;
    }
    delete[]_pstr;
    _pstr = new char[strlen(src._pstr) + 1];
    strcpy(_pstr, src._pstr);
    return *this;
  }
  bool operator>(const String& str)const
  {
    return strcmp(_pstr, str._pstr) > 0;
  }
private:
  char* _pstr;
};
int main()
{
  string str1;
  string str2 = "aaa";//string str2("aaa");
  string str3(str2);
  string str9(str2, 1, 90);
  cout << "str9:" << str9 << endl;
  string str4 = str2 + str3; 
  string str5 = str2 + "bbb";
  string str6 = "ddd" + str2;
  
  cout << "str6:" << str6 << endl;
  if (str5 > str6)
  {
    cout << str5 << ">" << str6 << endl;
  }
  int len = str5.length();
  for (int i = 0; i < len; i++)
  {
    cout << str5[i] << " ";
  }
  //char buff[100] = {0};
  //strcpy(buff, str6.c_str());
  //cout << "buff:" << buff << endl;
  return 0;
}
