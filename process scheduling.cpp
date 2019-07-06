#include"stdafx.h"
#include<iostream>
#include<string>
#include<ctime>
#include<vector>
using namespace std;
class pcb
{
public:
	string pid;
	int priority;
	int arrivetime;
	int alltime;
	int cputime;
	int startblock;
	int blocktime;
	int starttime;
	string state;
	pcb(int at)
	{
		priority=(rand()%1000)+1;//[1,1000]
		arrivetime=at;
		alltime=(rand()%40)+11;//[11,50]
		cputime=0;
		startblock=(rand()%10)+1;//[1,10]
		blocktime=0;
		starttime=(rand()%10)+1;//[1,10]
		state="就绪";
	}
};
int main()
{
	srand((unsigned int)time(nullptr));
	vector<pcb> ready,block,finish,remain;
	int arrivetime=0,k,p=0;
	double t=0;
	for(pcb *a=new pcb(arrivetime);1;remain.push_back(*a),a=new pcb(++arrivetime))
	{
		cout<<"请输入一个pid（输入0结束）：";
		for(getline(cin,(*a).pid);strchr((*a).pid.data(),(int)' ')!=NULL||strchr((*a).pid.data(),(int)'\t')!=NULL||(*a).pid.compare("")==0;cout<<"pid不能包含空格、制表符或回车，请重新输入：",getline(cin,(*a).pid));
		if((*a).pid=="0")
		{
			delete a;
			break;
		}
		for(int q=0;q<remain.size();)
		{
			if((*a).pid==remain[q].pid)
			{
				cout<<"该pid已存在，请重新输入：";
				cin>>(*a).pid;
				continue;
			}
			++q;
		}
	}
	arrivetime=(int)remain.size()-1;
	if(arrivetime+1==0)
		goto end;
	cout<<endl<<"初始状态："<<endl<<"\t\tpid|优先数|到达时间|剩余时间|已用时间|阻塞时间|已阻塞时间|冷却时间|状态";
	for(int i=0;i<arrivetime+1;++i)
		cout<<endl<<"\t进程"<<i+1<<"：\t"<<remain[i].pid<<'|'<<remain[i].priority<<'|'<<remain[i].arrivetime<<'|'<<remain[i].alltime<<'|'<<remain[i].cputime<<'|'<<remain[i].startblock<<'|'<<remain[i].blocktime<<'|'<<remain[i].starttime<<'|'<<remain[i].state;
	cout<<'\n';
	system("pause");
	for(int i=0;1;++i,++t)
	{
		int j=0,maxpriority,at;
		string pid;
		cout<<endl<<"第"<<i+1<<"次调度：";
		for(;p<remain.size();++p)
			if(remain[p].arrivetime==i)
			{
				ready.push_back(remain[p]);
				break;
			}
		for(;j<block.size();++j)
		{
			if(block[j].blocktime==block[j].starttime)
			{
				for(p=0;ready[p].pid!=block[j].pid;++p);
				ready[p].state="就绪";
				block.erase(block.begin()+j);
			}
			else
				++block[j].blocktime;
		}
		for(j=0;j<ready.size();++j)
			if(ready[j].state=="就绪")
			{
				maxpriority=ready[j].priority;
				pid=ready[j].pid;
				at=ready[j].arrivetime;
				break;
			}
		for(;j<ready.size();++j)
			if((ready[j].priority>maxpriority||ready[j].priority==maxpriority&&ready[j].arrivetime<at)&&ready[j].state=="就绪")
			{
				maxpriority=ready[j].priority;
				pid=ready[j].pid;
				at=ready[j].arrivetime;
			}
		for(j=0;j<ready.size();++j)
			if(pid==ready[j].pid&&ready[j].state=="就绪")
				break;
		if(j<ready.size())
		{
			ready[j].state="运行";
			ready[j].priority-=3;
			--ready[j].alltime;
			++ready[j].cputime;
		}
		cout<<endl<<"\t\tpid|优先数|到达时间|剩余时间|已用时间|阻塞时间|已阻塞时间|冷却时间|状态"<<endl<<"\t运行进程：";
		if(j!=ready.size())
			cout<<endl<<"\t\t"<<ready[j].pid<<'|'<<ready[j].priority<<'|'<<ready[j].arrivetime<<'|'<<ready[j].alltime<<'|'<<ready[j].cputime<<'|'<<ready[j].startblock<<'|'<<ready[j].blocktime<<'|'<<ready[j].starttime<<'|'<<ready[j].state;
		k=j;
		cout<<endl<<"\t就绪进程：";
		for(j=0;j<ready.size();++j)
			if(ready[j].state=="就绪")
				cout<<endl<<"\t\t"<<ready[j].pid<<'|'<<ready[j].priority<<'|'<<ready[j].arrivetime<<'|'<<ready[j].alltime<<'|'<<ready[j].cputime<<'|'<<ready[j].startblock<<'|'<<ready[j].blocktime<<'|'<<ready[j].starttime<<'|'<<ready[j].state;
		cout<<endl<<"\t阻塞进程：";
		for(j=0;j<block.size();++j)
			if(block[j].state=="阻塞")
				cout<<endl<<"\t\t"<<block[j].pid<<'|'<<block[j].priority<<'|'<<block[j].arrivetime<<'|'<<block[j].alltime<<'|'<<block[j].cputime<<'|'<<block[j].startblock<<'|'<<block[j].blocktime<<'|'<<block[j].starttime<<'|'<<block[j].state;
		cout<<endl<<"\t完成进程：";
		for(j=0;j<ready.size();++j)
			if(ready[j].state=="完成")
				cout<<endl<<"\t\t"<<ready[j].pid<<'|'<<ready[j].priority<<'|'<<ready[j].arrivetime<<'|'<<ready[j].alltime<<'|'<<ready[j].cputime<<'|'<<ready[j].startblock<<'|'<<ready[j].blocktime<<'|'<<ready[j].starttime<<'|'<<ready[j].state;
		cout<<endl;
		if(k<ready.size())
		{
			if(ready[k].state=="运行")
				ready[k].state="就绪";
			if(ready[k].alltime==0)
				ready[k].state="完成";
			else
				if(ready[k].cputime%ready[k].startblock==0)
				{
					ready[k].state="阻塞";
					block.push_back(ready[k]);
				}
			for(j=0;j<ready.size()&&ready[j].state=="完成";++j);
			if(j==ready.size())
				break;
		}
		//system("pause");
	}
end:
	cout<<endl<<"调度完成："<<endl<<"\t\tpid|优先数|到达时间|周转时间|带权周转时间|阻塞时间|已阻塞时间|冷却时间|状态";
	for(int i=0;i<arrivetime+1;++i)
		cout<<endl<<"\t进程"<<i+1<<"：\t"<<ready[i].pid<<'|'<<ready[i].priority<<'|'<<ready[i].arrivetime<<'|'<<ready[i].cputime<<'|'<<(t+1-ready[i].arrivetime)/ready[i].cputime<<'|'<<ready[i].startblock<<'|'<<ready[i].blocktime<<'|'<<ready[i].starttime<<'|'<<ready[i].state;
	cout<<endl;
	system("pause");
	return 0;
}
