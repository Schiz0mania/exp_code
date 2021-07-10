#include"headfile.h"
//邻接矩阵操作测试
void TESTMG()
{
	//不带权的有向图
	int size,u,v;
	MGraph mg;
	printf("输入图节点个数： \n");
	scanf_s("%d",&size);
	InitMg(&mg, size, 0);
	printf("输入路径,以任意负数结束输出：\n");
	scanf_s("%d %d", &u, &v);
	InsertMg(&mg, u - 1, v - 1, 1);
	while (u >= 1 && v >= 1 )
	{
		scanf_s("%d %d", &u, &v);
		InsertMg(&mg, u - 1, v - 1,1);
	}
	printf("构造完毕！\n");
	printf("DFS输出: \n");
	DFSMGraph(mg);
	putchar('\n');
	printf("BFS输出：\n");
	BFSMGraph(mg);
	putchar('\n');
	DestoryMg(&mg);
	
}
//邻接表操作测试
void TESTLG()
{
	//不带权有向图
	int size, u, v;
	LGragh lg;
	printf("输入图节点个数： \n");
	scanf_s("%d", &size);
	Init(&lg, size);
	printf("输入路径,以任意负数结束输出：\n");
	scanf_s("%d %d", &u, &v);
	InsertLg(&lg, u - 1, v - 1, 1);
	while (u >= 1 && v >= 1)
	{
		scanf_s("%d %d", &u, &v);
		InsertLg(&lg, u - 1, v - 1, 1);
	}
	printf("构造完毕！\n");
	printf("DFS输出: \n");
	DFSLGraph(lg);
	putchar('\n');
	printf("BFS输出：\n");
	BFSLGraph(lg);
	putchar('\n');
	DestoryLg(&lg);
	
}
//综合题测试
void TEST2()
{
	//带权无向图
	LGragh lg;
	int i, num, choice;
	int u, v, len;
	char name[MAXSIZE];
	printf("输入目标城市目的地个数：\n");
	scanf_s("%d", &num);
	Init(&lg, num);
	getchar();
	printf("输入各目的地名称：\n");
	for (i = 0; i < num; i++)
	{
		printf("%d、 ", i + 1);
		scanf_s("%c", name + i);
		getchar();
	}
	printf("城市模型如下:\n");
	for (i = 0; i < num; i++)
	{
		printf("%d、%c\n", i + 1, name[i]);
	}
	printf("输入各道路与其长度（例： 2 3 15）,以任意负数结束输出：\n");
	scanf_s("%d %d %d", &u, &v, &len);
	InsertLg(&lg, u - 1, v - 1, len);
	InsertLg(&lg, v - 1, u - 1, len);
	while (u >= 1 && v >= 1 && len > 0)
	{
		scanf_s("%d %d %d", &u, &v, &len);
		InsertLg(&lg, u - 1, v - 1, len);
		InsertLg(&lg, v - 1, u - 1, len);
	}
	printf("城市构造完毕！\n");
MAINFLAG:
	printf("请输入起点和终点：\n");
	scanf_s("%d %d", &u, &v);
	ShortCut(&lg, u - 1, v - 1, name);
	printf("是否继续搜索路径：(1/0) \n");
	scanf_s("%d", &choice);
	if (choice)
		goto MAINFLAG;
	system("pause");


}
int main()
{
	int choice,n;
	MAIN:
	printf("1、邻接矩阵操作测试  \n");
	printf("2、邻接表操作测试  \n");
	printf("3、综合题测试  \n");
	printf("4、退出\n");
	printf("输入你的选择\n");
	scanf_s("%d",&choice);
	switch(choice)
	{
		case 1: {
		TESTMG();
		printf("1、返回主界面 \n2、退出\n");
		scanf_s("%d", &n);
		if (n - 1)
			goto END;
		else
		{
			system("cls");
			goto MAIN;
		}
	}
		case 2: {
			TESTLG();
			printf("1、返回主界面 \n2、退出\n");
			scanf_s("%d", &n);
			if (n - 1)
				goto END;
			else
			{
				system("cls");
				goto MAIN;
			}

	}
		case 3: {
			TEST2();
			printf("1、返回主界面 \n2、退出\n");
			scanf_s("%d", &n);
			if (n - 1)
				goto END;
			else
			{
				system("cls");
				goto MAIN;
			}
			
		}
 }	
END:
	system("pause");
	return 0;
}
