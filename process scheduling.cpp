#include<iostream>
#include<string>
#include<ctime>
#include<vector>
class pcb
{
public:
	string pid,state;
	int priority,arrivetime,alltime,cputime,startblock,blocktime,starttime;
	pcb(int at)
	{
		priority=(rand()%1000)+1;//[1,1000]
		arrivetime=at;
		alltime=(rand()%40)+11;//[11,50]
		startblock=(rand()%10)+1;//[1,10]
		cputime=blocktime=0;
		starttime=(rand()%10)+1;//[1,10]
		state="就绪";
	}
};
int main()
{
	srand((unsigned int)time(nullptr));
	std::vector<pcb> ready,block,finish,remain;
	int arrivetime=0,k,p=0;
	double t=0;
	for(pcb *a=new pcb(arrivetime);true;remain.push_back(*a),a=new pcb(++arrivetime))
	{
		std::cout<<"请输入一个pid（输入0结束）：";
		for(std::cin.getline(std::cin,(*a).pid);strchr((*a).pid.data(),(int)' ')!=NULL||strchr((*a).pid.data(),(int)'\t')!=NULL||(*a).pid.compare("")==0;std::cout<<"pid不能包含空格、制表符或回车，请重新输入：",std::cin.getline(std::cin,(*a).pid));
		if((*a).pid=="0")
		{
			delete a;
			break;
		}
		for(int q=0;q<remain.size();q++)
			if((*a).pid==remain[q].pid)
			{
				std::cout<<"该pid已存在，请重新输入：";
				std::cin>>(*a).pid;
				continue;
			}
	}
	arrivetime=(int)remain.size()-1;
	if(arrivetime+1!=0)
	{
		std::cout<"\n初始状态：\n\t\tpid|优先数|到达时间|剩余时间|已用时间|阻塞时间|已阻塞时间|冷却时间|状态";
		for(int i=0;i<arrivetime+1;++i)
			std::cout<<"\n\t进程"<<i+1<<"：\t"<<remain[i].pid<<'|'<<remain[i].priority<<'|'<<remain[i].arrivetime<<'|'<<remain[i].alltime<<'|'<<remain[i].cputime<<'|'<<remain[i].startblock<<'|'<<remain[i].blocktime<<'|'<<remain[i].starttime<<'|'<<remain[i].state;
		std::cout<<std::endl;
		std::cin.get();
		for(int i=0;1;++i,++t)
		{
			int j=0,maxpriority,at;
			string pid;
			for(std::cout<<std::endl<<"第"<<i+1<<"次调度：";p<remain.size();++p)
				if(remain[p].arrivetime==i)
				{
					ready.push_back(remain[p]);
					break;
				}
			for(;j<block.size();++j)
				if(block[j].blocktime==block[j].starttime)
				{
					for(p=0;ready[p].pid!=block[j].pid;++p);
					ready[p].state="就绪";
					block.erase(block.begin()+j);
				}
				else
					++block[j].blocktime;
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
			std::cout<<"\n\t\tpid|优先数|到达时间|剩余时间|已用时间|阻塞时间|已阻塞时间|冷却时间|状态\n\t运行进程：";
			if(j!=ready.size())
				std::cout<<"\n\t\t"<<ready[j].pid<<'|'<<ready[j].priority<<'|'<<ready[j].arrivetime<<'|'<<ready[j].alltime<<'|'<<ready[j].cputime<<'|'<<ready[j].startblock<<'|'<<ready[j].blocktime<<'|'<<ready[j].starttime<<'|'<<ready[j].state;
			k=j;
			std::cout<<"\n\t就绪进程：";
			for(j=0;j<ready.size();++j)
				if(ready[j].state=="就绪")
					cout<<"\n\t\t"<<ready[j].pid<<'|'<<ready[j].priority<<'|'<<ready[j].arrivetime<<'|'<<ready[j].alltime<<'|'<<ready[j].cputime<<'|'<<ready[j].startblock<<'|'<<ready[j].blocktime<<'|'<<ready[j].starttime<<'|'<<ready[j].state;
			std::cout<<"\n\t阻塞进程：";
			for(j=0;j<block.size();++j)
				if(block[j].state=="阻塞")
					cout<<"\n\t\t"<<block[j].pid<<'|'<<block[j].priority<<'|'<<block[j].arrivetime<<'|'<<block[j].alltime<<'|'<<block[j].cputime<<'|'<<block[j].startblock<<'|'<<block[j].blocktime<<'|'<<block[j].starttime<<'|'<<block[j].state;
			std::cout<<"\n\t完成进程：";
			for(j=0;j<ready.size();++j)
				if(ready[j].state=="完成")
					cout<<"\n\t\t"<<ready[j].pid<<'|'<<ready[j].priority<<'|'<<ready[j].arrivetime<<'|'<<ready[j].alltime<<'|'<<ready[j].cputime<<'|'<<ready[j].startblock<<'|'<<ready[j].blocktime<<'|'<<ready[j].starttime<<'|'<<ready[j].state;
			std::cout<<std::endl;
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
		}
	}
	std::cout<<"\n调度完成：\n\t\tpid|优先数|到达时间|周转时间|带权周转时间|阻塞时间|已阻塞时间|冷却时间|状态";
	for(int i=0;i<arrivetime+1;++i)
		std::std::cout<<"\n\t进程"<<i+1<<"：\t"<<ready[i].pid<<'|'<<ready[i].priority<<'|'<<ready[i].arrivetime<<'|'<<ready[i].cputime<<'|'<<(t+1-ready[i].arrivetime)/ready[i].cputime<<'|'<<ready[i].startblock<<'|'<<ready[i].blocktime<<'|'<<ready[i].starttime<<'|'<<ready[i].state;
	std::cout<<std::endl;
	std::cin.get();
	return 0;
}
