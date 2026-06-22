#include<iostream>
using namespace std;
#include<ctime>

struct student
{
	string sName;
	int score;
};
struct Teacher
{
	string tName;
	struct student sArray[5];

};
void alloacatespace(struct Teacher tArray[], int len)
{
	string nameseed = "ABCDE";
	for (int i = 0;i < len;i++)
	{
		tArray[i].tName = "Teacher_";
		tArray[i].tName += nameseed[i];
		
		for (int j = 0;j < 5;j++)
		{
			tArray[i].sArray[j].sName = "student_";
			tArray[i].sArray[j].sName += nameseed[j];
			int random = rand() % 61 + 40;
			tArray[i].sArray[j].score = random;
		}
		
	}

}
void printofall(struct Teacher tArray[],int len)
{
	for (int i = 0;i < len;i++)
	{
		cout << "老师的姓名" << tArray[i].tName << endl;
		for (int j = 0;j < 5;j++)
		{
			cout << "\t学生的姓名" << tArray[i].sArray[j].sName
				<< "学生的分数" << tArray[i].sArray[j].score << endl;
		}
	}
	
}
int main()
{
	srand((unsigned int)time(NULL));
	struct Teacher tArray[3];
	int len = sizeof(tArray) / sizeof(tArray[0]);
	alloacatespace(tArray, len);
	printofall(tArray, len);
}