//Server process.
//Creat a socket.
//Bind socket to ip and port.
//Wait for connect request.
//Return.
#include"stdafx.h"
#include<conio.h>
#include<windows.h>
#include<winsock2.h>//socket头文件
#pragma comment(lib,"ws2_32.lib")//socket库的lib
void TCPServer()
{
	SOCKET socksvr=socket(AF_INET,SOCK_STREAM,0);//IPv4，TCP
	if(INVALID_SOCKET==socksvr)
		return;
	struct sockaddr_in svraddr;
	memset(&svraddr,0,sizeof(svraddr));
	svraddr.sin_family=AF_INET;//internet协议族
	svraddr.sin_port=htons(5678);//htons()是将u_short型变量从主机字节顺序变换为TCP/IP网络字节顺序，此处涉及CPU问题。intel处理器是低位字节在较低地址存放，而高位字节在较高地址存放，与网络字节顺序相反,故需要调换过来。htonl()函数是改变u_long型变量。
	//svraddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//此宏为0，当前机器上任意IP地址，也可以指定当前机的ip和端口。
	svraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(socksvr,(struct sockaddr *)&svraddr,sizeof(svraddr));//将服务器端套接字与服务器端套接字地址绑定，指定名字，类型，长度。
	listen(socksvr,SOMAXCONN);//侦听，第一个参数是套接字，第二个参数是等待连接队列的最大长度。
	//等候客户端建立连接
	printf("等候客户端.......\n");
	//建立客户端套接字地址，主要是为了接收客户端返回参数之用
	struct sockaddr_in clientaddr={0};
	int nLen=sizeof(clientaddr);
	//以下是建立客户端套接字并建立连接函数。有一个确认的过程。
	//注：后面填的是客户端地址长度的地址。
	SOCKET sockclient=accept(socksvr,(struct sockaddr*)&clientaddr,&nLen);//建立连接函数
	printf("客户端已连接\n");
	/********以下是数据收发部分*********/
	//先接收后发送，由上面知，数据已在sockclient中，我们只需读此结构便可知晓数据
	CHAR szText[100]={0};
	//接收缓冲区数据
	recv(sockclient,szText,100,0); //接收函数，一直处于侦听模式，等待服务器端发送数据的到来。
	printf("%s\n",szText);
	CHAR szSend[100]="Hello Client";
	send(sockclient,szSend,sizeof(szSend),0);//发送函数。
  /****accept/recv/send 都是堵塞函数，需要把所以的数据都接收完或发送完才可以工作。*****/
	// getch();//暂停一下
	//关闭socket
	closesocket(sockclient);
	closesocket(socksvr);

}

void UDPServer()
{
	//创建socket
	SOCKET socksvr=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(INVALID_SOCKET==socksvr)
		return;
	//服务器套接字地址
	//绑定ip与端口，先定义端口等一些信息。
	struct sockaddr_in svraddr={0};
	svraddr.sin_family=AF_INET;
	svraddr.sin_port=htons(5780);
	svraddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	bind(socksvr,(struct sockaddr*)&svraddr,sizeof(svraddr));
	/********以下是数据收发部分*********/
	//客户端套接字地址，接收客户端数据时需要用，数据都在套接字里面。
	CHAR szRecv[100]={0};
	struct sockaddr_in clientaddr={0};
	int nLen=sizeof(clientaddr);
	/*下面函数前四个参数同TCP接收数据函数recv()一样，后两个中，一个是返回发送*******/
	/*数据地址的主机的地址，包括IP地址以及端口号，最后一个为地址长度的地址。*******/
	/*此函数中，先是服务器端的套接字，后是客户端的地址*/
	//从后往前读此函数
	recvfrom(socksvr,szRecv,100,0,(struct sockaddr*)&clientaddr,&nLen);//构造ip地址
	printf("%s\n",szRecv);

	//注1：该程序也可以向客户端发送数据。
	//注2：服务器端中，必须也是先接收后发送，不然，我们无法知道客户端的地址。下面函数中clientaddr已知晓
	CHAR szSend[100]="hello udp client";
	//从前往后读此函数
	 sendto(socksvr,szSend,100,0,(struct sockaddr*)&clientaddr,nLen);//发送时构造ip地址和端口。

//	getch();//可以暂停显示，这个很重要。

	//关闭socket
	closesocket(socksvr);


}
int main()
{
	//初始化socket库
	WSADATA wsa={0}; //WinSockApi 取WSA+DATA组成套接字结构体
	WSAStartup(MAKEWORD(2,2),&wsa);
	//服务器
	TCPServer();
	//UDPServer();
	//清理套接字资源
	WSACleanup();
	getch();//暂停一下
	return 0;
}
