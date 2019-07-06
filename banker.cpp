#include"stdafx.h"
#include<string>
#include<iostream>
#include<ctime>
#include<vector>
using namespace std;
const int J=4,P=3;
int available[J],pid=0,turn=0;
struct pcb
{
	int id,counter;
	bool finish;
	int allocation[J],need[J],currentrequest[J],distribution[J];
	vector<int> restoretime,currentresource;
	vector<vector<int>> historyresource;
	pcb()
	{
		counter=0;
		id=pid++%J;
		finish=false;
		for(int i=0;i<J;need[i]=rand()%11+1,allocation[i]=0,++i);
	}
	void restore()
	{
		int i=0;
		if(finish)
		{
			for(;i<J;available[i]+=allocation[i],allocation[i]=0,++i);
			return;
		}
		for(int s=0;s<restoretime.size();)
		{
			if(restoretime[s]>0)
			{
				--restoretime[s++];
				continue;
			}
			if(restoretime[s]==0)
			{
				for(i=0;i<J;available[i]+=historyresource[s][i],allocation[i]-=historyresource[s][i],++i);
				restoretime.erase(restoretime.begin()+s);
				historyresource.erase(historyresource.begin()+s);
			}
		}
	}
	string request(int j)
	{
		if(finish)
			return "已完成";
		int i=0;
		char a='a';
		for(cout<<endl<<"\t进程"<<++j<<"："<<endl,i=0;i<J;++i)
		{
			bool f=false;
			int count=0;
			do
			{
				/*for(i=0;i<J;++i)
					if(need[i]!=0&&available[i]==0)
						return "系统资源不足";*/
				int t[J];
				for(i=0;i<J;t[i]=need[i]>available[i]?available[i]:need[i],++i);
				for(i=0;i<J;currentrequest[i]=rand()%((need[i]>available[i]?available[i]:need[i])+1),++i);
				for(i=0;i<J;++i)
					if(t[i]!=0)
						break;
				if(i==J)
					return "系统资源不足";
				for(i=0;i<J;++i)
					if(currentrequest[i]!=0)
					{
						f=true;
						break;
					}
				count++;
			}while(!f);
			for(cout<<"\t\t\t共需\t本次需\t持有",i=0;i<J;cout<<'\t'<<allocation[i],++i)
			{
				cout<<endl<<"\t\t资源"<<a++<<'\t'<<need[i]<<"\t0";
				if(currentrequest[i]!=0)
					cout<<'-'<<currentrequest[i];
			}
			for(currentresource.clear(),cout<<'\n'<<endl,a='a',i=0;i<J;++a,++i)
			{
				if(currentrequest[i]==0)
				{
					distribution[i]=0;
					continue;
				}
				cout<<"\t\t分配资源"<<a<<"数：";
				cin>>distribution[i];
				if(distribution[i]>available[i]||distribution[i]>currentrequest[i])
					return "输入资源过多";
			}
			for(i=0;i<J;++i)
				if(distribution[i]!=0)
					break;
			if(i==J)
				return "未分配资源";
			for(i=0;i<J;currentresource.push_back(distribution[i]),available[i]-=distribution[i],need[i]-=distribution[i],allocation[i]+=distribution[i],++i);
			historyresource.push_back(currentresource);
		}
		for(i=0;i<J;++counter,++i)
			if(need[i]!=0)
			{
				counter=0;
				goto r;
			}
		finish=true;
		return "本次完成";
	r:
		int c=rand()%4;
		restoretime.push_back(c);
		return "成功";
	}
};
void printavailable()
{
	int i=0;
	char a='a';
	for(cout<<"\n系统资源数："<<endl<<'\t';i<J-1;cout<<a++<<'\t',++i);
	for(cout<<a<<endl<<'\t',i=0;i<J-1;cout<<available[i]<<'\t',++i);
	cout<<available[i]<<endl;
}
int main()
{
	srand((unsigned int)time(nullptr));
	int i=0;
	for(;i<J;available[i]=(rand()%6)+10,++i);
	for(pcb b[P];1;cout<<endl)
	{
		for(cout<<"第"<<++turn<<"次调度："<<endl,printavailable(),i=0;i<P;++i)
		{
			string t=b[i].request(i);
			if(t=="输入资源过多"||t=="系统资源不足"||t=="未分配资源")
				cout<<"\n\t"<<t<<endl;
			if(t=="已完成")
				cout<<"\n\t进程"<<i+1<<"：完成"<<endl;
			if(t=="成功")
			{
				cout<<"\n\t分配成功，将于"<<b[i].restoretime[b[i].restoretime.size()-1]<<"次调度后归还"<<endl;
				printavailable();
			}
		}
		char a;
		for(i=0;i<P;b[i].restore(),cout<<endl,++i)
		{
			a='a';
			cout<<endl<<"进程"<<i+1<<"：";
			cout<<endl<<"\t\t持有\t还需";
			for(int j=0;j<J;cout<<endl<<"\t资源"<<a++<<'\t'<<b[i].allocation[j]<<'\t'<<b[i].need[j],++j);
		}
		for(i=0;i<P;++i)
			if(!b[i].finish)
				break;
		if(i==P)
		{
			for(cout<<"\n调度完成"<<endl,printavailable(),i=0;i<P;cout<<endl,++i)
			{
				a='a';
				cout<<endl<<"进程"<<i+1<<"：";
				cout<<endl<<"\t\t持有\t还需";
				for(int j=0;j<J;cout<<endl<<"\t资源"<<a++<<'\t'<<b[i].allocation[j]<<'\t'<<b[i].need[j],++j);
			}
			break;
		}
	}
	cout<<'\n';
	system("pause");
	return 0;
}
