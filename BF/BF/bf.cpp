#include<iostream>
using namespace std;
#include<string>
int BF(string s, string t)
{
  int i = 0;
  int j = 0;
  while (i < s.size() && j < t.size())
  {
    if (s[i] == t[j])
    {
      i++;
      j++;
    }
    else
   {
      i = i - j + 1;
      j = 0;
   }
  }
  if (j == t.size())
  {
    return i - j;
  }
  else
  {
    return -1;
  }
}
int main()
{
  string s = "ABCDEFG";
  string t = "GDEF";
  int pos = BF(s, t);
  cout << pos << endl;
}
