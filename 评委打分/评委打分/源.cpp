#include<iostream>
#include<vector>
#include<deque>
#include<ctime>
#include<algorithm>
using namespace std;
class Person
{
public:
	Person(string name,int score)
	{
		this->m_Name = name;
		this->m_Score = score;
	}
	string m_Name;
	int m_Score;
};
void createPerson(vector<Person>& v)
{
	string nameseep = "ABCDE";
	for (int i = 0;i < 5;i++)
	{
		string name = "选手姓名";
		name += nameseep[i];

		int score = 0;
		Person p(name, score);

		v.push_back(p);
	}
}
//打分
void setScore(vector<Person>& v)
{
	for (vector<Person>::iterator it = v.begin();it != v.end();it++)
	{
		deque<int>d;
		for (int i = 0;i < 10;i++)
		{
			int score = rand() % 41 + 60;
			d.push_back(score);
		}
		sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();

		int sum = 0;
		for (deque<int>::iterator dit = d.begin();dit != d.end();dit++)
		{
			sum += *dit;
		}
		int avg = sum / d.size();
		it->m_Score = avg;
	}
}
void showScore(vector<Person>& v)
{
	for (vector<Person>::iterator it = v.begin();it != v.end();it++)
	{
		cout << "姓名：" << it->m_Name << "平均分：" << it->m_Score << endl;
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	vector<Person>v;
	createPerson(v);

	setScore(v);
	showScore(v);
	return 0;
}