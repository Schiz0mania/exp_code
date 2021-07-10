#pragma once
#include<stdio.h>
#include<stdlib.h>
# define INFINITE 9999
# define START -1
# define MAXSIZE 20
//循环队列
typedef struct queue
{
	int front;
	int rear;
	int maxSize;
	int *element; //顶点为数据成员
}Queue;
//邻接矩阵
typedef struct mGraph
{
	int** a;      //邻接矩阵
	int n;        //图当前顶点数
	int e;        //图当前边数
	int noEdge;   //两顶点间无边的值

}MGraph;
//邻接表
typedef struct eNode
{
	int  adjVex;  //与任意节点u相邻接的顶点(当前节点下标值)
	int w;  //权值
	struct eNode* nextArc; //指向下一边节点
}ENode;
typedef struct lGragh
{
	int n;  //顶点个数
	int e;  //边个数
	ENode** a;

}LGragh;
//----------------------------------------------------------------------------------队列操作
	//创建队列
void CreateQ(Queue* q, int msize)
{
	q->maxSize = msize;
	q->element = (int*)malloc(sizeof(int) * msize);
	q->front = q->rear = 0;
}
//撤销队列
void DestoryQ(Queue* q)
{
	q->maxSize = 0;
	free(q->element);//释放空间
	q->front = q->rear = -1;
}
//获取队列头元素给t,返回操作是否成功
int FrontQueue(Queue* q, int* t)
{
	if (q->front == q->rear)//判空
		return 0;
	*t = q->element[(q->front + 1) % q->maxSize];
	return 1;

}
//在队尾插入元素t,返回操作是否成功
int Enqueue(Queue* q, int t)
{
	if ((q->rear + 1) % q->maxSize == q->front)//判断是否已满
		return 0;
	q->rear = (q->rear + 1) % q->maxSize;
	q->element[q->rear] = t;
	return 1;
}
//删除队列头元素,返回操作是否成功
int Dnqueue(Queue* q)
{
	if (q->front == q->rear)
		return 0;
	q->front = (q->front + 1) % q->maxSize;
	return 1;

}
//-------------------------------------------------------------邻接矩阵
//初始化邻接矩阵 
int InitMg(MGraph* mg, int nSize, int noEdgeValue)
{
	int i, j;
	mg->n = nSize;       //参数初始化顶点数
	mg->e = 0;           //初始化时边数为0
	mg->noEdge = noEdgeValue;
	mg->a = (int**)malloc(nSize * sizeof(int*));//长度为nSize的一维指针数组
	if (!mg->a)
		return 0;
	for (i = 0; i < nSize; i++)
	{
		mg->a[i] = (int*)malloc(nSize * sizeof(int));
		//初始化工作
		for (j = 0; j < nSize; j++)
			mg->a[i][j] = noEdgeValue;		//都赋值为无边值
		mg->a[i][i] = 0;				    //对角线都为0

	}
	return 1;
}
//撤销邻接矩阵
void DestoryMg(MGraph* mg)
{
	int i;
	for (i = 0; i < mg->n; i++)
		free(mg->a[i]);
	free(mg->a);
}
//寻找下标值u,v之间是否存在边
int ExistMg(MGraph* mg, int u, int v)
{
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge)//uv越界、相等，或为无边
		return 0;
	return 1;
}
//下标值u，v间增加权值为w的边
int InsertMg(MGraph* mg, int u, int v, int w)
{
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] != mg->noEdge)//uv越界、相等或已有边
		return 0;
	mg->a[u][v] = w;
	mg->e++;
	return 1;
}
//删去下标u,v之间的边
int RemoveMg(MGraph* mg, int u, int v)
{
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge)//uv越界、相等，或为无边
		return 0;
	mg->a[u][v] = mg->noEdge;
	mg->e--;
	return 1;

}
//邻接矩阵的dfs 
void DFSmg(int v, int* visited, MGraph mg)//起始下标v，标记数组visited
{
	int i;
	printf("%d ", v+1);
	visited[v] = 1; //标记
	for (i = 0; i < mg.n; i++)
	{
		if (mg.a[v][i] != mg.noEdge && v != i && !visited[i])//寻找下一个未访问的邻接顶点
			DFSmg(i, visited, mg);
	}
}
void DFSMGraph(MGraph mg)
{
	int i;
	int* visited = (int*)malloc(sizeof(int) * mg.n);
	for (i = 0; i < mg.n; i++)
		visited[i] = 0;				//初始化标记数组
	for (i = 0; i < mg.n; i++)
		if (!visited[i])
			DFSmg(i, visited, mg);  //对每一个未访问节点执行DFS
	free(visited);                  //释放

}
//邻接矩阵的bfs
void BFSmg(int v, int* visited, MGraph mg)
{
	Queue q;
	int i;
	int tmp;
	CreateQ(&q, mg.n);//初始化队列
	printf("%d ", v+1);
	visited[v] = 1;
	Enqueue(&q, v);//当前已访问节点入队
	while (q.front != q.rear)//队列空退出
	{
		FrontQueue(&q, &tmp);
		Dnqueue(&q);
		//tmp获取队头元素
		for (i = 0; i < mg.n; i++)
		{
			if (mg.a[tmp][i] != mg.noEdge && tmp != i && !visited[i])//寻找未访问的邻接顶点并入队
			{
				printf("%d ", i+1);
				visited[i] = 1;
				Enqueue(&q, i);
			}
		}

	}
}
void BFSMGraph(MGraph mg)
{
	int i;
	int* visited = (int*)malloc(sizeof(int) * mg.n);
	for (i = 0; i < mg.n; i++)
		visited[i] = 0;
	for (i = 0; i < mg.n; i++)
		if (!visited[i])
			BFSmg(i, visited, mg);
	free(visited);
}
//-------------------------------------------------------------邻接表
//初始化邻接表
int Init(LGragh* lg, int nsize)
{
	int i;
	lg->n = nsize;
	lg->e = 0;
	lg->a = (ENode**)malloc(sizeof(ENode*) * nsize);
	if (!lg->a)
		exit(1);
	else
	{
		for (i = 0; i < nsize; i++)
			lg->a[i] = NULL;//置空
		return 1;
	}
}
//撤销邻接表
void DestoryLg(LGragh* lg)
{
	int i;
	ENode* p, * q;
	for (i = 0; i < lg->n; i++)
	{//先撤销每个顶点的单链表
		p = lg->a[i];
		q = p;
		while (p)
		{
			p = p->nextArc;
			free(q);
			q = p;
		}
	}
	//后撤销指针数组
	free(lg->a);


}
//搜索u，v边(单向)
int  ExistLg(LGragh* lg, int u, int v)
{
	ENode* p;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
		return 0;
	p = lg->a[u];//在u的单链表中寻找v
	while (p && p->adjVex != v)//退出条件：找到或到头
		p = p->nextArc;
	if (!p)
		return 0;
	else
		return 1;
}
//插入u，v边（单向）
int InsertLg(LGragh* lg, int u, int v, int w)
{
	ENode* p;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v || ExistLg(lg, u, v))
		return 0;
	p = (ENode*)malloc(sizeof(ENode));
	p->adjVex = v;
	p->w = w;
	p->nextArc = lg->a[u];
	lg->a[u] = p;
	//新节点插入在最前面
	lg->e++;
	return 1;

}
//删除u，v边
int RemoveLg(LGragh* lg, int u, int v)
{
	ENode* p, * q;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
		return 0;
	p = lg->a[u];
	q = NULL;
	while (p && p->adjVex != v)
	{
		q = p;
		p = p->nextArc;
	}
	if (!p)
		return 0;
	if (q)//删去节点非第一个节点
		q->nextArc = p->nextArc;
	else
		lg->a[u] = p->nextArc;
	free(p);
	lg->e--;
	return 1;
}
//邻接表dfs
void DFSlg(int v, int* visited, LGragh lg)
{
	ENode* w;
	printf("%d ", v+1);
	visited[v] = 1;
	for (w = lg.a[v]; w; w = w->nextArc)
		if (!visited[w->adjVex])
			DFSlg(w->adjVex, visited, lg);


}
void DFSLGraph(LGragh lg)
{
	int i;
	int* visited = (int*)malloc(sizeof(ENode) * lg.n);
	for (i = 0; i < lg.n; i++)
		visited[i] = 0;
	for (i = 0; i < lg.n; i++)
		if (!visited[i])
			DFSlg(i, visited, lg);
	free(visited);
}
//邻接表bfs
void BFSlg(int v, int* visited, LGragh lg)
{
	ENode* w;
	Queue q;
	CreateQ(&q, lg.n);
	printf("%d ", v+1);
	Enqueue(&q, v);
	while (q.front != q.rear)
	{
		FrontQueue(&q, &v);
		Dnqueue(&q);
		for (w = lg.a[v]; w; w = w->nextArc)
			if (!visited[w->adjVex])
			{
				printf("%d ", w->adjVex+1);
				visited[w->adjVex] = 1;
				Enqueue(&q, w->adjVex);
			}
	}
}
void BFSLGraph(LGragh lg)
{
	int i;
	int* visited = (int*)malloc(sizeof(ENode) * lg.n);
	for (i = 0; i < lg.n; i++)
		visited[i] = 0;
	for (i = 0; i < lg.n; i++)
		if (!visited[i])
			BFSlg(i, visited, lg);
	free(visited);

}
//----------------------综合题
//寻找数组中可以访问的下一个最小值，找到返回下标，否则返回n
int FindMin(int* a, int n, int* visited)
{
	int i;
	int index = 0;
	while (visited[index] && index < n)//寻找有效对比对象（即可访问的数据里抽选）
	{
		index++;
	}
	for (i = 1; i < n && !visited[i]; i++)
		if (a[i] < a[index])
			index = i;
	return index;
}
// 迪杰斯特拉
void dijkstra(LGragh* lg, int u, int* dis, int* pre, int* visited)
{
	ENode* p = lg->a[u];
	int len;
	if (dis[u] < 0)
		len = 0;
	else
		len = dis[u];
	for (; p; p = p->nextArc)
	{
		//先更新距离
		if (len + p->w < dis[p->adjVex])//当前访问节点到下一可访问节点的距离小于原本到达该可访问节点的距离值，则更新数据
			dis[p->adjVex] = p->w + len;
		//再更新前置
		if (!visited[p->adjVex])//由于双向，防止数据更新重复
			pre[p->adjVex] = u;

	}
	//最后标记访问
	visited[u] = 1;

}
//递归回溯输出最短路径
void PrintPath(int* pre, int u, int v, char* name)//前置顶点表，起点，终点

{
	if (u != v && v != INFINITE)
		PrintPath(pre, u, pre[v], name);
	printf("%c ", name[v]);



}
//最短路径 传入参数，构建好的邻接表lg ，起点下标u，终点下标v
void ShortCut(LGragh* lg, int u, int v, char* name)//u,v皆为下标
{
	ENode* p;
	int* dis = (int*)malloc(sizeof(int) * lg->n);//动态距离表
	int* visited = (int*)malloc(lg->n * sizeof(int));//动态标记数组，标记距离表访问
	int* pre = (int*)malloc(lg->n * sizeof(int));//动态前置顶点表数组
	int i;
	int count = 0; //标记访问个数------------------------预设，输入模型无孤立节点（那么结束条件就是count=n）

	for (i = 0; i < lg->n; i++)//初始化
	{
		visited[i] = 0;
		dis[i] = pre[i] = INFINITE;
	}
	dis[u] = START;
	dijkstra(lg, u, dis, pre, visited);//先从起点开始
	count++;
	while (count != lg->n)
	{
		//找dis中最小且未访问，作为下一个访问节点----------------------------------------------------------------------------------
		if (FindMin(dis, lg->n, visited) < lg->n)
		{
			dijkstra(lg, FindMin(dis, lg->n, visited), dis, pre, visited);
			count++;
		}
		else
			break;

	}
	printf("最短路径：\n");
	PrintPath(pre, u, v, name);
	putchar('\n');
	free(dis);
	free(visited);
	free(pre);
}
