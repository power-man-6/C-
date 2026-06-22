#include<iostream>
using namespace std;
class CPU
{
public:
	virtual void calculate() = 0;
};
class VideCard
{
public:
	virtual void display() = 0;
};
class Memory 
{
public:
	virtual void storage() = 0;
};
class Computer
{
public:
	Computer(CPU* cpu,VideCard* vc, Memory* mem)
	{
		m_cpu = cpu;
		m_vc = vc;
		m_mem = mem;
	}
	void work()
	{
		m_cpu->calculate();
		m_vc->display();
		m_mem->storage();

	}
	~Computer()
	{
		delete m_cpu;
		delete m_vc;
		delete m_mem;
	}
private:
	CPU* m_cpu;
	VideCard* m_vc;
	Memory* m_mem;
};
class Intelcpu :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Intel的CPU开始计算了" << endl;
	}
};
class IntelVideCard :public VideCard
{
public:
	virtual void display()
	{
		cout << "Intel的Videcard显示了" << endl;
	}
};
class IntelMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Intel开始储存" << endl;
	}
};
void test01()
{
	CPU* intelcpu = new Intelcpu;
	VideCard* intelcard = new IntelVideCard;
	Memory* intelMem = new IntelMemory;

	Computer* computer1 = new Computer(intelcpu, intelcard, intelMem);
	computer1->work();
	delete computer1;
}
int main()
{
	test01();
}