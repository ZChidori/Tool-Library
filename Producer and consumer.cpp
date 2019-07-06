#include"stdafx.h"
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
using namespace std;
int main()
{
	srand((unsigned int)time(nullptr));
	bool f=false;
	vector<int> r,s,t;
	int i=0,y=0,z=0;
	thread a([&r,&z]()
	{
		for(;r.size()<4&&z<10;)
		{
			mutex m;
			m.lock();
			r.push_back(rand()%5);
			++z;
			printf("生产第%d个数据：%d\n",z,r[r.size()-1]);
			m.unlock();
		}
	}),b([&r,&s]()
	{
		for(;r.size()!=0;)
		{
			mutex m;
			m.lock();
			printf("消费者进程1获得了数据：%d\n",r[0]);
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
			printf("消费者进程2获得了数据：%d\n",r[0]);
			t.push_back(r[0]);
			r.erase(r.begin());
			m.unlock();
		}
	});
	a.join();
	b.join();
	c.join();
	for(;i<s.size();y+=s[i++]);
	for(cout<<"消费者进程1数据和："<<y<<endl,i=y=0;i<t.size();y+=t[i++]);
	cout<<"消费者进程2数据和："<<y<<endl;
	system("pause");
    return 0;
}
