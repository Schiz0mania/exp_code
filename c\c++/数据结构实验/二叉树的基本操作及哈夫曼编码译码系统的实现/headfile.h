#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
//先序创建 check
//先序VLR，中序LVR，后序LRV遍历check
//层次遍历check
//节点个数check
//叶节点个数check
//二叉树高度check
//撤销二叉树check
//交换二叉树所有左右子树check
//判断是否为最小堆 check
	//修改为最小堆  check
//输入中序，先序字符串，构造二叉树并输出其其他遍历结果 check
//哈夫曼编码，解码
	//构造哈夫曼树  check
	//输入待编译序列 输出编码（编码在遍历过程中输出，挺好的）  check
	//输入编码 输出解码序列  check


	//二叉树
typedef struct btnode
{
	char element;
	struct btnode* lChild;
	struct btnode* rChild;
} BTNode;
typedef struct binarytree
{
	BTNode* root;
}BinaryTree;
	//循环队列
typedef struct queue
{
	int front;
	int rear;
	int maxSize;
	BTNode* element; //二叉树节点为数据成员
}Queue;
	//顺序表（堆）
typedef struct seqlist
{
	int n;
	int maxLength;
	int* element;
}SeqList;

	//哈夫曼二叉树
typedef struct hfmTNode
{

	char element;  //元素域
	int w;   //权值
	struct hfmTNode* lChild;
	struct hfmTNode* rChild;
}HFMTNode;
typedef struct
{
	HFMTNode* root;
}HFMTree;
	//优先权队列 队列数组元素为哈夫曼树结点的地址 
typedef struct priorityQueue
{
	HFMTNode** element;                                               //修改后的指向 哈夫曼节点地址的数组 逻辑上保证后续操作不会出错
	int n;
	int maxSize;

}PriorityQueue;


//----------------------------------------------------------------------------------队列操作
	//创建队列
void CreateQ(Queue* q, int msize)
{
	q->maxSize = msize;
	q->element = (BTNode*)malloc(sizeof(BTNode) * msize);
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
int FrontQueue(Queue* q, BTNode* t)
{
	if (q->front == q->rear)//判空
		return 0;
	*t = q->element[(q->front + 1) % q->maxSize];
	return 1;

}
//在队尾插入元素t,返回操作是否成功
int Enqueue(Queue* q, BTNode t)
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


//----------------------------------------------------------------------------------堆操作
	//初始化
int InitSeqList(SeqList* L, int msize)
{
	L->maxLength = msize;
	L->n = 0;
	L->element = (int*)malloc(sizeof(int) * msize);
	if (!L->element)
		return 0;
	return 1;
}
//插入（x成为下标为i+1的元素）
int InsertSeqList(SeqList* L, int i, int x)
{
	int j;
	if (i<-1 || i>L->n - 1)
		return 0;
	if (L->n == L->maxLength)
		return 0;
	for (j = L->n - 1; j > i; j--)
		L->element[j + 1] = L->element[j];
	L->element[i + 1] = x;
	L->n++;
	return 1;

}
//输出
int OutputSeqList(SeqList* L)
{
	int i;
	if (!L->n)
		return 0;
	for (i = 0; i < L->n; i++)
		printf("%d  ", L->element[i]);
	printf("\n");
	return 1;
}
//撤销
int DestSeqList(SeqList* L)
{
	if (!L->element)
		return 0;
	L->maxLength = 0;
	L->n = 0;
	free(L->element);
	return 1;
}
//判断最小堆
int JudgeMinHeap(SeqList* heap)
{
	int flag = 1;
	int i;
	int min;
	if (heap->n == 0)
		return 0;
	for (i = (heap->n - 2) % 2; i > -1 && flag; i--)//从最后一个非非叶节点开始执行判断
	{
		if ((2 * i + 2 <= heap->n - 1) && (heap->element[2 * i + 2] < heap->element[2 * i + 1]))//右孩子存在(即两个孩子都有)且右孩子较小----孩子中较小的为右孩子
			min = 2 * i + 2;
		else //右孩子不存在(只有左孩子) 或 右孩子较大---孩子中较小的为左孩子
			min = 2 * i + 1;
		//min指向孩子节点中较小的那个
		if (heap->element[i] > heap->element[min])//该子树根节点非最小值，标记符赋为0
			flag = 0;
	}
	return flag;
}
//向下调整运算
void AdjustDown(SeqList* heap, int current)
{
	int p = current;
	int min;//指向较小孩子的下标
	int tmp;
	while (2 * p + 1 <= heap->n - 1)//p为非叶子结点
	{
		if ((2 * p + 2 <= heap->n - 1) && (heap->element[2 * p + 2] < heap->element[2 * p + 1])) //孩子都有且右较小
			min = 2 * p + 2;
		else//左较小
			min = 2 * p + 1;
		if (heap->element[p] <= heap->element[min]) //满足条件
			break;
		else//调整
		{
			//交换
			tmp = heap->element[p];
			heap->element[p] = heap->element[min];
			heap->element[min] = tmp;
			//向下调整考察对象
			p = min;
		}
	}
}
//修改为最小堆的运算
void FixMinHeap(SeqList* heap)
{
	int i;
	for (i = (heap->n - 2) / 2; i >= 0; i--)
		AdjustDown(heap, i);

}


//----------------------------------------------------------------------------------二叉树操作
	//先序遍历
void PreOrder(BTNode* t)
{ //回归
	if (!t)
		return;
	//递减
	printf("%c ", t->element);  //V
	PreOrder(t->lChild);       //L
	PreOrder(t->rChild);       //R
	return;
}
void VLR(BinaryTree* bt)
{
	PreOrder(bt->root);
}
//中序遍历
void InOrder(BTNode* t)
{
	if (!t)
		return;
	InOrder(t->lChild);		//L
	printf("%c ", t->element);  //V
	InOrder(t->rChild);        //R
	return;

}
void LVR(BinaryTree* bt)
{

	InOrder(bt->root);

}
//后序遍历
void PostOrder(BTNode* t)
{
	if (!t)
		return;
	PostOrder(t->lChild);      //L
	PostOrder(t->rChild);	    //R
	printf("%c ", t->element);  //V
	return;
}
void LRV(BinaryTree* bt)
{
	PostOrder(bt->root);
}
//先序创建-------------输入先序规则的二叉树
BTNode* PreCreateBT(BTNode* t)
{
	char ch;
	scanf_s("%c",&ch,sizeof(ch));
	if (ch == 35) // "#" 执行空二叉树
		t = NULL;
	else
	{
		t = (BTNode*)malloc(sizeof(BTNode));
		t->element = ch;
		t->lChild = PreCreateBT(t->lChild);
		t->rChild = PreCreateBT(t->rChild);

	}
	return t;
}
void PreMakeTree(BinaryTree* bt)
{
	bt->root = PreCreateBT(bt->root);
}
//后序撤销二叉树
void Clear(BTNode* t)
{
	if (!t)
		return;
	Clear(t->lChild);
	Clear(t->rChild);
	free(t);
}
//层次遍历（循环队列）
void LevelOrder(BinaryTree* bt)
{
	Queue q;
	BTNode p = *(bt->root);
	if (!bt->root)		//空二叉树
		return;

	CreateQ(&q, 100);		//初始化队列

	Enqueue(&q, p);		//根节点入队
	while (q.front != q.rear)		//结束条件：队列为空
	{
		FrontQueue(&q, &p);		//获取队头元素
		Dnqueue(&q);		//删去队头元素
		printf("%c ", p.element);		//访问节点数据
		if (p.lChild)
			Enqueue(&q, *(p.lChild));		//非空左孩子入队
		if (p.rChild)
			Enqueue(&q, *(p.rChild));		//非空右孩子入队

	}
	Dnqueue(&q);
}
//结点个数
int Size(BTNode* t)
{
	if (!t)
		return 0;
	else
		return Size(t->lChild) + Size(t->rChild) + 1;

}
int TreeSize(BinaryTree* bt)
{
	return Size(bt->root);

}
//叶子节点个数
void Leave(BTNode* t, int* count)
{
	if (t)
	{
		if (!t->lChild && !t->rChild)
			*count += 1;
		else
		{
			Leave(t->lChild, count);
			Leave(t->rChild, count);
		}

	}

}
int LeaveCount(BinaryTree* bt)
{
	int count = 0;
	Leave(bt->root, &count);
	return count;

}
//求二叉树高度
int Height(BTNode* t)
{
	if (!t)
		return 0;
	else
		return (Height(t->lChild) >= Height(t->rChild)) ? Height(t->lChild) + 1 : Height(t->rChild) + 1;  //取大
}
int TreeHeight(BinaryTree* bt)
{
	return Height(bt->root);
}
//交换二叉树所有左右子树
void Swap(BTNode* t)
{
	BTNode* tmp;
	if (!t)
		return;
	else
	{

		tmp = t->lChild;
		t->lChild = t->rChild;
		t->rChild = tmp;
		Swap(t->lChild);
		Swap(t->rChild);
	}
}
void SwapTree(BinaryTree* bt)
{
	Swap(bt->root);
}
//输入中序，先序字符串，构造二叉树并输出其其他遍历结果
BTNode* MakeTree(char* pre, char* in, int len, BTNode* t)//pre-前序字符 in-中序字符 len-数组长度（前两个字符数组长度相等）  递归
{
	int rootidx; //标记根节点在中序里的下标
	int flag = 1;
	if (len == 0)  //长度为0 退出
		return t = NULL;
	t = (BTNode*)malloc(sizeof(BTNode));
	t->element = pre[0];  //前序序列的第一个为当前根节点
	t->lChild = t->rChild = NULL;  //置空 很重要  
	for (rootidx = 0; rootidx < len && flag; rootidx++)
		if (in[rootidx] == pre[0])//找根节点在中序的下标
			flag = 0;
	rootidx--;
	if (rootidx != 0) //当前节点存在左子树
		t->lChild = MakeTree(pre + 1, in, rootidx, t->lChild);
	// 前序 从当前前序加1开始
	// 中序 从当前中序开始
	//长度为 左子树节点数量即中序中根节点下标！！
	if (rootidx != len - 1) //当前节点存在右子树
		//前序 当前先序数组+1+左子树节点个数（即中序下根节点下标）
		//中序 当前中序+1+左子树节点数
		//长度为总长度-1-左子树节点数
		t->rChild = MakeTree(pre + 1 + rootidx, in + 1 + rootidx, len - 1 - rootidx, t->rChild);

	return t;

}
void PreInMakeTree(char* pre, char* in, int len, BinaryTree* t)
{
	t->root = MakeTree(pre, in, len, t->root);

}


//----------------------------------------------------------------------------------优先权队列操作
//创建空优先权队列
void CreatePQ(PriorityQueue* pq, int msize)
{
	pq->maxSize = msize;
	pq->n = 0;
	pq->element = (HFMTNode*)malloc(msize * sizeof(HFMTNode*));
}
//撤销优先权队列
void DestoryPQ(PriorityQueue* pq)
{
	free(pq->element);
	pq->n = 0;
	pq->maxSize = 0;
}
//哈夫曼堆的向上调整
void AdjustUpHfm(HFMTNode** heap, int current)
{
	int p = current;
	HFMTNode* tmp;
	while (p > 0)
	{
		if ((heap[p]->w < heap[(p - 1) / 2]->w))//当前位置权值小于双亲权值
		{   //交换
			tmp = heap[p];
			heap[p] = heap[(p - 1) / 2];
			heap[(p - 1) / 2] = tmp;
			p = (p - 1) / 2;   //上移
		}
		else
			break;  //权值正常 结束
	}
}
//队尾+1并调整为最小堆
void Append(PriorityQueue* pq, HFMTNode* x)
{
	if (pq->n == pq->maxSize)
		return;
	pq->element[pq->n] = x;
	pq->n++;
	AdjustUpHfm(pq->element, pq->n - 1);//对新插入的队尾元素进行权值调整

}
//哈夫曼堆的向下调整
void AdjustDownHfm(HFMTNode** heap, int current, int border)
{
	int p = current;
	int min;//指向较小孩子的下标
	HFMTNode* tmp;
	while (2 * p + 1 <= border)//p为非叶子结点
	{
		if ((2 * p + 2 <= border) && (heap[2 * p + 2]->w < heap[2 * p + 1]->w)) //孩子都有且右较小 
			min = 2 * p + 2;
		else//左较小
			min = 2 * p + 1;
		if (heap[p]->w <= heap[min]->w) //满足条件 
			break;
		else//调整
		{
			//交换
			tmp = heap[p];
			heap[p] = heap[min];
			heap[min] = tmp;
			//向下调整考察对象
			p = min;
		}
	}
}
//返回队头元素并调整为最小堆
HFMTNode* ServePQ(PriorityQueue* pq, HFMTNode* x)
{
	if (pq->n == 0)
		return NULL;
	x = pq->element[0];
	pq->n--;
	pq->element[0] = pq->element[pq->n]; //保存数据（此时堆已乱）
	AdjustDownHfm(pq->element, 0, pq->n - 1);
	return x;
}


//----------------------------------------------------------------------------------哈夫曼树操作
// ！！！所有哈夫曼操作都围绕下面 构造时申请动态空间的地址  展开
//合并哈夫曼树的操作---（合并树的根部元素域置为#，权值域为左右子树权值之和,左右各对应参数）
HFMTNode* MakePair(HFMTNode* p, int w, char ch, HFMTNode* left, HFMTNode* right)
{
	HFMTNode* hfmt;
	hfmt = (HFMTNode*)malloc(sizeof(HFMTNode));
	if (!hfmt)
	{
		printf("内存申请失败！\n");
		exit(1);
	}
	hfmt->element = ch;
	hfmt->w = w;
	if (left)
	{
		hfmt->lChild = (HFMTNode*)malloc(sizeof(HFMTNode));
		hfmt->lChild = left;
	}
	else
		hfmt->lChild = NULL;
	if (right)
	{
		hfmt->rChild = (HFMTNode*)malloc(sizeof(HFMTNode));
		hfmt->rChild = right;
	}
	else
		hfmt->rChild = NULL;
	left = right = NULL;
	p = hfmt;

	return p;
}
//哈夫曼树的创建
HFMTNode* CreateHFMTree(char* s, int* w, int len, HFMTNode* hfmt)// s为字符数组，w为权值数组（与字符集有对应下标的关系）len为长度   
{
	PriorityQueue pq;   //哈夫曼优先权队列
	HFMTNode* x, * y, * z;
	int i;
	x = y = z = NULL;
	CreatePQ(&pq, len);
	for (i = 0; i < len; i++)//所有根节点建树入队
	{
		x = MakePair(x, w[i], s[i], NULL, NULL);
		Append(&pq, x);
	}
	while (pq.n > 1) //合并为一颗哈夫曼树
	{
		x = ServePQ(&pq, x);
		//取根节点权值最小的给x
		y = ServePQ(&pq, y);
		//取根节点权值最小的给y
		//合并x，y并将新二叉树入队（合并规则：权值较小的为左子树）----合并后的树根节点元素皆为“#”
		if (x->w < y->w) //x小 为左子树
			z = MakePair(z, x->w + y->w, '#', x, y);
		else
			z = MakePair(z, x->w + y->w, '#', y, x);
		Append(&pq, z);
	}
	x = ServePQ(&pq, x);
	//取出合并的哈夫曼树，存入x                                         
	hfmt = x;
	DestoryPQ(&pq);//撤销优先权队列
	return hfmt;
}
void  MakeHFMTree(char* s, int* w, int len, HFMTree* hfmt)
{
	hfmt->root = CreateHFMTree(s, w, len, hfmt->root);
}
//哈夫曼遍码 -边遍历边编码 
void Coding(HFMTNode* t, int* code, int len)
{
	int i;
	if (!t)//空
		return;
	if (!t->lChild && !t->rChild)//叶子节点 输出编码
	{
		printf("%c 的哈夫曼编码为： ", t->element);
		for (i = 0; i < len; i++)
			printf("%d", code[i]);
		putchar('\n');
	}
	else
	{
		code[len] = 0;
		Coding(t->lChild, code, len + 1);//深入左子树
		code[len] = 1;
		Coding(t->rChild, code, len + 1);//深入右子树

	}



}
void HFMTCoding(HFMTree* hfmt)
{
	int code[20];//保存各字母的编码的数组
	Coding(hfmt->root, code, 0);

}
//哈夫曼解码
void HFMTDecoding(HFMTree* hfmt, int* code, int len)//len应该在用户输入的时候得到，为元素个数最合适
{
	int i;
	HFMTNode* t = hfmt->root;
	if (!t)
		return;
	printf("解码序列为：\n");
	for (i = 0; i < len; i++)
	{
		(code[i] && 1) ? (t = t->rChild) : (t = t->lChild);//表达式为真，编码为1，走右，反之亦然
		if ((!t->lChild) && (!t->rChild))//叶子 ---(出现取消对null指针的引用错误提醒，在申请动态内存时加入判断是否申请成功即可)--(加入了还是会提醒。。问题不大)
		{
			printf("%c ", t->element);
			t = hfmt->root;  //置零
		}

	}
	putchar('\n');
}
//撤销哈夫曼树
void ClearHFMTree(HFMTNode* t)
{
	if (!t)
		return;
	if (t->rChild)
		ClearHFMTree(t->rChild);
	if (t->lChild)
		ClearHFMTree(t->lChild);

	free(t);
}



