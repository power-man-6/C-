#include <iostream>
#include <cstdlib>
#include<ctime>

using namespace std;

int main()
{
    srand(time(0));
    int secretNumber = rand() % 100 +1;
    int guess;
    int attempts = 0;

    cout<<"欢迎来到猜数字游戏！/n";
    cout<<"我已经想好了一个1到100之间的数字。/n";

    do
    {
      cout<<"请输入你的猜测：";
      cin>>guess;
      attempts++;
      
      if (guess>secretNumber){
        cout<<"太大了！\n";
    } else if (guess<secretNumber){
        cout<<"太小了！\n";}
      else{
        cout<<"恭喜用了"<<attempts<<"次猜测正确！\n";
      
    } 
    }while (guess != secretNumber);
    
    return 0;
}