// 请求式分页存储管理.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>

/*
*定义页面结构
*/
typedef struct page
{
	int head , tail ; //页头与页尾地址
	int x_size ; //页面大小
	struct page *next ; // 指向下一页的指针
} Page ;

/*
*定义页面管理控制块
*/
typedef struct mcb
{
	Page *head , *tail ; //指向页表的头指针与尾指针
	Page *change ; //替换指针
	int mem_size ; //总内存空间
	int mem_left ; //剩余内存
} MCB ;

/*
*发起页面大小为x的页面内存空间请求
*返回false则申请成功
*/
bool resquestPage(MCB *m , int x) ;

/*
*进行页面淘汰
*/
void eliminatePage(MCB *m) ;

/*
*进行当前内存空间的显示
*/
void displayPage(MCB *m) ;

/*
*测试主函数
*/
int main()
{
	int k , x ;
	//定义页面控制块
	MCB *m ;
	m = (MCB*)malloc(sizeof(MCB)) ;

	if(m == NULL)
	{
		return 0;
	}

	//进行初始化
	m->head = m->tail = m->change = NULL ;
	m->mem_size = 128 ;
	m->mem_left = 128 ;

	while(true)
	{
		printf("Wheather go on to deliever memory  (1/0) : ") ;
		scanf_s("%d" , &k) ;
		if(k)
		{
			printf("Please input the size of page : ") ;
			scanf_s("%d" , &x) ;
			if(resquestPage(m , x))
			{
				printf("Deliever success ! \n") ;
			}
			else
			{
				return 0;
			}
			displayPage(m) ;
		}
		else
		{
			break ;
		}
	}
	return 0 ;
}

bool resquestPage(MCB *m , int x)
{
	Page *p ;
	p = (Page*)malloc(sizeof(Page)) ;
	if(p == NULL)
	{
		return false ;
	}
	else{
		p->x_size = x ;
		p->next = NULL ;
		while(m->mem_left <= p->x_size)
		{
			eliminatePage(m) ;
		}
		m->mem_left -= p->x_size ;
		if(m->head == NULL)
		{
			m->head = m->tail = p ;
			p->head = 0 ;
			p->tail = p->head + p->x_size - 1 ;
			m->change = m->head ;
		}
		else
		{
			//进行该页的内存分配
			p->head = (m->tail->tail + 1) % m->mem_size ;
			p->tail = (p->head + p->x_size - 1) % m->mem_size ;
			m->tail->next = p ;
			m->tail = p ;
		}
		return true ;
	}
}

void eliminatePage(MCB *m)
{
	if(m->head)
	{
		Page *p ;
		p = m->head ;
		m->head = m->head->next ;
		m->change = m->head ;
		m->mem_left += p->x_size ;
		delete p ;
	}
}

void displayPage(MCB *m)
{
	Page *p ;
	p = m->head ;
	while(p)
	{
		printf("%4d     %4d     %4d \n" , p->head , p->tail , p->x_size) ;
		p = p->next ;
	}
}
