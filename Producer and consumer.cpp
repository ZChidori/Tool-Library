#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
int main()
{
	srand((unsigned int)time(nullptr));
	bool f=false;
	std::vector<int> r,s,t;
	int i=0,y=0,z=0;
	thread a([&r,&z]()
	{
		for(;r.size()<4&&z<10;)
		{
			mutex m;
			m.lock();
			r.push_back(rand()%5);
			std::cout<<"生产第"<<++z<<"个数据："<<r[r.size()-1])<<std::endl;
			m.unlock();
		}
	}),b([&r,&s]()
	{
		for(;r.size()!=0;)
		{
			mutex m;
			m.lock();
			std::cout<<"消费者进程1获得了数据："<<r[0]<<std::endl;
			s.push_back(r[0]);
			r.erase(r.begin());
			m.unlock();
		}
	}),c([&r,&t]()
	{
		for(;r.size()!=0;)
		{
			mutex m;
			m.lock();
			std::cout<<"消费者进程2获得了数据："<<r[0]<<std::endl;
			t.push_back(r[0]);
			r.erase(r.begin());
			m.unlock();
		}
	});
	a.join();
	b.join();
	c.join();
	for(;i<s.size();y+=s[i++]);
	for(std::cout<<"消费者进程1数据和："<<y<<std::endl,i=y=0;i<t.size();y+=t[i++]);
	std::cout<<"消费者进程2数据和："<<y<<std::endl;
	std::cin.get();
	return 0;
}
