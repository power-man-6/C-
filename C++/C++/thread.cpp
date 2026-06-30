#include<iostream>
#include<thread>
/*
	C++语言级别的多线程编码=》代码可以跨平台
	thread/mutex(互斥)condition_variable
	lock_quard/unique_lock
	atomic原子类型  基于CAS操作的原子类型 
	sleep_for
	C++语言层面 thread
   	windows            linux
		|                 |
	createThread      pthread_create 
*/

/*
线程内容:
一：怎么启动一个线程
std::thread定义一个线程对象，传入线程所需要的线程函数和参数，
线程自动开启
二:子线程如何结束
子线程函数运行完成，线程就结束了
三:主线程如何处理子线程
t.join:等待t线程结束，当前线程继续往下运行
t.detach:把t线程设为分离线程，主线程结束，整个进程结束，所有子线程都自动结束了

*/
void threadHandle1(int time)
{
	//让子线程睡眠2秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	std::cout << "hello thread1!" <<std::endl;
}
int main()
{
	//创建了一个线程对象  传入一个线程函数，新线程开始运行了
	std::thread t1(threadHandle1,2);
	//主线程等子线程结束，主线程继续往下运行
	//t1.join();
	//把线程设置成分离线程
	t1.detach();
	std::cout << "main thread done!" << std::endl;
	return 0;
}