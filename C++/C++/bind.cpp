#include<iostream>
#include<functional>
#include<thread>
#include<vector>
using namespace std;
using namespace placeholders; 
/*
C++ bind绑定器=>返回的结果还是一个函数对象
bind的作用：绑定器，绑定一个可调用对象（函数，函数对象，成员

void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
class Test
{
public:
	int sum(int a,int b) { return a + b; }
};
int main()
{	//bind是函数模板 可以自动推演模板类型函数
	bind(hello, "hello bind")();
	cout<<bind(sum, 10, 20)()<<endl;
	cout << bind(&Test::sum, Test(), 20, 30)() << endl;
	//参数占位符    绑定器出了语句，无法继续使用
	//bind(hello, placeholders::_1)("hello bind2");
	bind(hello, _1)("hello bind2");
	cout << bind(sum, _1, _2)(200, 300) << endl;

	function<void(string)>func1 = bind(hello, _1);
	func1("hello ");
	func1("ho");
	func1("hi");
	return 0;
}*/

/*
muduo源码文件  threadpool.cc thread.cc bind function
*/
//线程类
class Thread
{
public:
	Thread(function<void()>func) :_func(func) {};
	thread start()
	{
		thread t(_func);
		return t;
	}
private:
	function<void()>_func;
};
//线程池类
class ThreadPool
{
public:
	ThreadPool() {};
	~ThreadPool() {
	//线程池析构时，回收线程资源
		for (int i = 0; i < _pool.size(); ++i)
		{
			delete _pool[i];
		}
	};
	//开启线程池
	void startPool(int size)
	{
		for (int i = 0; i < size; ++i)
		{
			_pool.push_back(
				new Thread(bind(&ThreadPool::runInThread,this,i)));
		}
		for (int i = 0; i < size; ++i)
		{
			_handler.push_back(_pool[i]->start());
		}
		for (thread& t : _handler)
		{
			t.join();
		}
	}
private:
	vector<Thread*> _pool;
	vector<thread>_handler;
	//把runInThread这个成员方法充当线程函数 thread pthread_create
	void runInThread(int id)
	{
		cout << "call runInThread! id:" << id << endl;
	}
};
int main()
{
	ThreadPool pool;
	pool.startPool(5);
	return 0; 
}