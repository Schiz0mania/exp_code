
#include"headfile.h"

	//先序创建+先序、中序、后序、层次遍历+结点个数+叶结点个数+高度+交换左右子树 测试
void Test1()
{
	BinaryTree bt;
	printf("先序创建： \n");
	PreMakeTree(&bt);
	printf("先序遍历： \n");
	VLR(&bt);
	printf("\n");
	printf("中序遍历： \n");
	LVR(&bt);
	printf("\n");
	printf("后序遍历： \n");
	LRV(&bt);
	printf("\n");
	printf("层次遍历：\n");
	LevelOrder(&bt);
	printf("\n");
	printf("节点个数： %d \n", TreeSize(&bt));
	printf("叶子节点个数: %d \n", LeaveCount(&bt));
	printf("二叉树高度：%d \n", TreeHeight(&bt));
	printf("------交换所有左右子树-----\n");
	SwapTree(&bt);//--------------------交换二叉树左右子树
	printf("层次遍历：\n");
	LevelOrder(&bt);
	printf("\n");
	Clear(bt.root);
	system("pause");


}
	//判断最小堆与修改成最小堆
void Test2()
{
	
	SeqList L;
	int msize;
	int num;
	int i = -1;
	printf("输入目标完全二叉树节点个数：\n");
	scanf_s("%d", &msize);
	InitSeqList(&L, msize);
	printf("输入目标完全二叉树序列(以 -1 结束)：\n");
	scanf_s("%d", &num);
	while (num != -1)
	{
		InsertSeqList(&L, i, num);
		i++;
		scanf_s("%d", &num);
	}
	printf("目标堆输出如下：\n");
	OutputSeqList(&L);
	if (JudgeMinHeap(&L))
		printf("该二叉树为最小堆。\n");
	else
	{
		FixMinHeap(&L);
		printf("该二叉树不是最小堆，但已经被调整成最小堆啦\n");
		OutputSeqList(&L);
	}
	DestSeqList(&L);
	system("pause");
}
	//先序 中序字符序列建立二叉树并输出层次与后序遍历
void Test3()
{
	
	BinaryTree bt;
	char pre[50], in[50];
	char ch1, ch2;
	int len1, len2, len;
	len1 = len2 = len = 0;
	printf("输入先序字符序列（以#结尾）:\n");
	scanf_s("%c",&ch1,sizeof(ch1));
	while (ch1 != 35)
	{
		pre[len1] = ch1;
		len1++;
		scanf_s("%c", &ch1,sizeof(ch1));
	}
	getchar();  //处理多余的回车符号
	printf("输入中序字符序列（以#结尾）: \n");
	scanf_s("%c", &ch2,sizeof(ch2));
	while (ch2 != 35)
	{
		in[len2] = ch2;
		len2++;
		scanf_s("%c", &ch2,sizeof(ch2));
	}
	len = len2;
	PreInMakeTree(pre, in, len, &bt);
	printf("目标二叉树层次遍历：\n");
	LevelOrder(&bt);
	printf("\n");
	printf("目标二叉树后序遍历：\n");
	LRV(&bt);
	Clear(bt.root);
	system("pause");
}
	//哈夫曼测试
void HFMTTest()//用户输入数据，生成 编码字符集与权值集合
{
	char s[MAXSIZE];//字符集
	int w[MAXSIZE];//权值集
	int len1 = 0;   //以上两个的长的
	int code[100];//密码集
	int len2 = 0;//密码长度
	char ch;
	int i = 0;
	int num;
	HFMTree hfmt;
	hfmt.root = NULL;
	printf("输入连续且以#结尾的字符集：\n");
	scanf_s("%c", &ch,sizeof(ch));
	while (ch != 35)
	{
		s[len1] = ch;
		len1++;
		scanf_s("%c", &ch, sizeof(ch));
	}
	printf("输入以上字符集中各字符的对应权值(以负数结尾)：\n");
	scanf_s("%d", &num);
	while (num > 0)
	{
		w[i] = num;
		i++;
		scanf_s("%d", &num);
	}

	MakeHFMTree(s, w, len1, &hfmt);
	printf("哈夫曼树已创建！\n");
flag1:
	printf("输正确的入操作值\n");
	printf("1、编码\n");
	printf("2、解码\n");
	printf("3、退出\n");
	scanf_s("%d", &num);
	switch (num)
	{
	case 1://编码
	{
		HFMTCoding(&hfmt);
		printf("编码成功，是否继续操作（1/0）：");
		scanf_s("%d", &num);
		if (num)
			goto flag1;
		else {
			printf("操作结束！\n");
			ClearHFMTree(hfmt.root);  //撤销
			return;
		}
		break;
	}
	case 2://解码
	{
		printf("输入码文（以-1结尾）：\n");
		scanf_s("%d", &num);
		while (num >= 0)
		{
			code[len2] = num;
			len2++;
			scanf_s("%d", &num);
		}
		HFMTDecoding(&hfmt, code, len2);
		printf("解码成功，是否继续操作（1/0）：");
		scanf_s("%d", &num);
		if (num)
			goto flag1;
		else {
			printf("操作结束！\n");
			ClearHFMTree(hfmt.root);  //撤销
			return;
		}
		break;

	}
	case 3:
	{
		printf("操作结束！\n");
		ClearHFMTree(hfmt.root);   //撤销
		return;
	}
	default: {
		printf("请重新输入操作数。");
		goto flag1;

	}

	}




}

int main()
{
	int choice;
	int num;
	MAINFLAG:
	printf("----------实验二测试----------\n");
	printf("1、二叉树操作测试（先序创建+先序、中序、后序、层次遍历+结点个数+叶结点个数+高度+交换左右子树 ）\n");
	printf("2、最小堆测试（判断最小堆与修改成最小堆）\n");
	printf("3、二叉树创建测试（先序 中序字符序列建立二叉树并输出层次与后序遍历）\n");
	printf("4、哈夫曼测试\n");
	printf("5、退出\n");
	printf("输入操作数：\n");
	SUBFLAG:
	scanf_s("%d",&choice);
	getchar();//必要操作--连续输入时排除上次输入结尾的回车符
	switch (choice)
	{
		case 1: {
			Test1();
			printf("测试成功，是否继续操作（1/0）：");
			scanf_s("%d", &num);
			if (num)
				goto MAINFLAG;
			else {
				printf("测试结束！\n");
				system("pause");
				return 1;
			}	
		}
		case 2: {
			Test2();
			printf("测试成功，是否继续操作（1/0）：");
			scanf_s("%d", &num);
			if (num) {
				system("CLS");
				goto MAINFLAG;
			}
			
			else {
				printf("测试结束！\n");
				system("pause");
				return 1;
			}
	
	
		}
		case 3:{
			Test3();
			printf("测试成功，是否继续操作（1/0）：");
			scanf_s("%d", &num);
			if (num) {
				system("CLS");
				goto MAINFLAG;
			}
			else {
				printf("测试结束！\n");
				system("pause");
				return 1;
			}
	
		}
		case 4:{
			HFMTTest();
			printf("测试成功，是否继续操作（1/0）：");
			scanf_s("%d", &num);
			if (num) {
				system("CLS");
				goto MAINFLAG;
			}
			else {
				printf("测试结束！\n");
				system("pause");
				return 1;
			}
	
		}
		case 5: {
			system("pause");
			return 1;
		}
			
		default: {
			printf("请输入正确的操作数！\n");
			goto SUBFLAG;
		}
	}
	system("pause");




	return 0;
}