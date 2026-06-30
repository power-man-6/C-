#include<iostream>
#include<thread>
#include<list>
#include<mutex>
/*
* 多线程程序
* 竞态条件:多线程程序执行的结果是一致的，不会随着CPU对线程不同的调用顺序，
而产生不同的运行效果 ，
*/
/*
C++ thread 模拟车站三个窗口卖票的程序
*/
int Ticketcount = 100;//车站有100张票，由三个窗口一起卖票
std::mutex mtx;//全局的互斥锁
//模拟卖票的线程
void sellTicket(int index)
{
	
	while (Ticketcount>0)
	{	
		{
			std::lock_guard<std::mutex>lock(mtx);
			
			//mtx.lock();
			if (Ticketcount > 0)
			{
				std::cout << "窗口" << index << "第" << Ticketcount << "张票" << std::endl;
				Ticketcount--;
			}
		}
		//mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}
int main()
{
	std::list<std::thread>tlist;
	for (int i = 1; i <= 3; ++i)
	{
		tlist.push_back(std::thread(sellTicket, i));
	}
	for (std::thread& t : tlist)
	{
		t.join();
	}
	std::cout << "所有窗口卖票结束！" << std::endl;
}
