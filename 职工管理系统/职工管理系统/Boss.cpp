#include"Boss.h"


//构造函数
Boss::Boss(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}
//显示个人信息
void Boss::showInFo()
{
	cout << "员工编号：" << this->m_Id
		<< "\t员工姓名：" << this->m_Name
		<< "\t岗位：" << this->GetDeptName()
		<< "\t岗位职责：给经理安排任务" << endl;


}
//获取岗位名称
string Boss::GetDeptName()
{
	return string("老板");
}