#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
//���򴴽� check
//����VLR������LVR������LRV����check
//��α���check
//�ڵ����check
//Ҷ�ڵ����check
//�������߶�check
//����������check
//����������������������check
//�ж��Ƿ�Ϊ��С�� check
	//�޸�Ϊ��С��  check
//�������������ַ�������������������������������� check
//���������룬����
	//�����������  check
	//������������� ������루�����ڱ��������������ͦ�õģ�  check
	//������� �����������  check


	//������
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
	//ѭ������
typedef struct queue
{
	int front;
	int rear;
	int maxSize;
	BTNode* element; //�������ڵ�Ϊ���ݳ�Ա
}Queue;
	//˳����ѣ�
typedef struct seqlist
{
	int n;
	int maxLength;
	int* element;
}SeqList;

	//������������
typedef struct hfmTNode
{

	char element;  //Ԫ����
	int w;   //Ȩֵ
	struct hfmTNode* lChild;
	struct hfmTNode* rChild;
}HFMTNode;
typedef struct
{
	HFMTNode* root;
}HFMTree;
	//����Ȩ���� ��������Ԫ��Ϊ�����������ĵ�ַ 
typedef struct priorityQueue
{
	HFMTNode** element;                                               //�޸ĺ��ָ�� �������ڵ��ַ������ �߼��ϱ�֤���������������
	int n;
	int maxSize;

}PriorityQueue;


//----------------------------------------------------------------------------------���в���
	//��������
void CreateQ(Queue* q, int msize)
{
	q->maxSize = msize;
	q->element = (BTNode*)malloc(sizeof(BTNode) * msize);
	q->front = q->rear = 0;
}
//��������
void DestoryQ(Queue* q)
{
	q->maxSize = 0;
	free(q->element);//�ͷſռ�
	q->front = q->rear = -1;
}
//��ȡ����ͷԪ�ظ�t,���ز����Ƿ�ɹ�
int FrontQueue(Queue* q, BTNode* t)
{
	if (q->front == q->rear)//�п�
		return 0;
	*t = q->element[(q->front + 1) % q->maxSize];
	return 1;

}
//�ڶ�β����Ԫ��t,���ز����Ƿ�ɹ�
int Enqueue(Queue* q, BTNode t)
{
	if ((q->rear + 1) % q->maxSize == q->front)//�ж��Ƿ�����
		return 0;
	q->rear = (q->rear + 1) % q->maxSize;
	q->element[q->rear] = t;
	return 1;
}
//ɾ������ͷԪ��,���ز����Ƿ�ɹ�
int Dnqueue(Queue* q)
{
	if (q->front == q->rear)
		return 0;
	q->front = (q->front + 1) % q->maxSize;
	return 1;

}


//----------------------------------------------------------------------------------�Ѳ���
	//��ʼ��
int InitSeqList(SeqList* L, int msize)
{
	L->maxLength = msize;
	L->n = 0;
	L->element = (int*)malloc(sizeof(int) * msize);
	if (!L->element)
		return 0;
	return 1;
}
//���루x��Ϊ�±�Ϊi+1��Ԫ�أ�
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
//���
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
//����
int DestSeqList(SeqList* L)
{
	if (!L->element)
		return 0;
	L->maxLength = 0;
	L->n = 0;
	free(L->element);
	return 1;
}
//�ж���С��
int JudgeMinHeap(SeqList* heap)
{
	int flag = 1;
	int i;
	int min;
	if (heap->n == 0)
		return 0;
	for (i = (heap->n - 2) % 2; i > -1 && flag; i--)//�����һ���Ƿ�Ҷ�ڵ㿪ʼִ���ж�
	{
		if ((2 * i + 2 <= heap->n - 1) && (heap->element[2 * i + 2] < heap->element[2 * i + 1]))//�Һ��Ӵ���(���������Ӷ���)���Һ��ӽ�С----�����н�С��Ϊ�Һ���
			min = 2 * i + 2;
		else //�Һ��Ӳ�����(ֻ������) �� �Һ��ӽϴ�---�����н�С��Ϊ����
			min = 2 * i + 1;
		//minָ���ӽڵ��н�С���Ǹ�
		if (heap->element[i] > heap->element[min])//���������ڵ����Сֵ����Ƿ���Ϊ0
			flag = 0;
	}
	return flag;
}
//���µ�������
void AdjustDown(SeqList* heap, int current)
{
	int p = current;
	int min;//ָ���С���ӵ��±�
	int tmp;
	while (2 * p + 1 <= heap->n - 1)//pΪ��Ҷ�ӽ��
	{
		if ((2 * p + 2 <= heap->n - 1) && (heap->element[2 * p + 2] < heap->element[2 * p + 1])) //���Ӷ������ҽ�С
			min = 2 * p + 2;
		else//���С
			min = 2 * p + 1;
		if (heap->element[p] <= heap->element[min]) //��������
			break;
		else//����
		{
			//����
			tmp = heap->element[p];
			heap->element[p] = heap->element[min];
			heap->element[min] = tmp;
			//���µ����������
			p = min;
		}
	}
}
//�޸�Ϊ��С�ѵ�����
void FixMinHeap(SeqList* heap)
{
	int i;
	for (i = (heap->n - 2) / 2; i >= 0; i--)
		AdjustDown(heap, i);

}


//----------------------------------------------------------------------------------����������
	//�������
void PreOrder(BTNode* t)
{ //�ع�
	if (!t)
		return;
	//�ݼ�
	printf("%c ", t->element);  //V
	PreOrder(t->lChild);       //L
	PreOrder(t->rChild);       //R
	return;
}
void VLR(BinaryTree* bt)
{
	PreOrder(bt->root);
}
//�������
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
//�������
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
//���򴴽�-------------�����������Ķ�����
BTNode* PreCreateBT(BTNode* t)
{
	char ch;
	scanf_s("%c",&ch,sizeof(ch));
	if (ch == 35) // "#" ִ�пն�����
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
//������������
void Clear(BTNode* t)
{
	if (!t)
		return;
	Clear(t->lChild);
	Clear(t->rChild);
	free(t);
}
//��α�����ѭ�����У�
void LevelOrder(BinaryTree* bt)
{
	Queue q;
	BTNode p = *(bt->root);
	if (!bt->root)		//�ն�����
		return;

	CreateQ(&q, 100);		//��ʼ������

	Enqueue(&q, p);		//���ڵ����
	while (q.front != q.rear)		//��������������Ϊ��
	{
		FrontQueue(&q, &p);		//��ȡ��ͷԪ��
		Dnqueue(&q);		//ɾȥ��ͷԪ��
		printf("%c ", p.element);		//���ʽڵ�����
		if (p.lChild)
			Enqueue(&q, *(p.lChild));		//�ǿ��������
		if (p.rChild)
			Enqueue(&q, *(p.rChild));		//�ǿ��Һ������

	}
	Dnqueue(&q);
}
//������
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
//Ҷ�ӽڵ����
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
//��������߶�
int Height(BTNode* t)
{
	if (!t)
		return 0;
	else
		return (Height(t->lChild) >= Height(t->rChild)) ? Height(t->lChild) + 1 : Height(t->rChild) + 1;  //ȡ��
}
int TreeHeight(BinaryTree* bt)
{
	return Height(bt->root);
}
//����������������������
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
//�������������ַ��������������������������������
BTNode* MakeTree(char* pre, char* in, int len, BTNode* t)//pre-ǰ���ַ� in-�����ַ� len-���鳤�ȣ�ǰ�����ַ����鳤����ȣ�  �ݹ�
{
	int rootidx; //��Ǹ��ڵ�����������±�
	int flag = 1;
	if (len == 0)  //����Ϊ0 �˳�
		return t = NULL;
	t = (BTNode*)malloc(sizeof(BTNode));
	t->element = pre[0];  //ǰ�����еĵ�һ��Ϊ��ǰ���ڵ�
	t->lChild = t->rChild = NULL;  //�ÿ� ����Ҫ  
	for (rootidx = 0; rootidx < len && flag; rootidx++)
		if (in[rootidx] == pre[0])//�Ҹ��ڵ���������±�
			flag = 0;
	rootidx--;
	if (rootidx != 0) //��ǰ�ڵ����������
		t->lChild = MakeTree(pre + 1, in, rootidx, t->lChild);
	// ǰ�� �ӵ�ǰǰ���1��ʼ
	// ���� �ӵ�ǰ����ʼ
	//����Ϊ �������ڵ������������и��ڵ��±꣡��
	if (rootidx != len - 1) //��ǰ�ڵ����������
		//ǰ�� ��ǰ��������+1+�������ڵ�������������¸��ڵ��±꣩
		//���� ��ǰ����+1+�������ڵ���
		//����Ϊ�ܳ���-1-�������ڵ���
		t->rChild = MakeTree(pre + 1 + rootidx, in + 1 + rootidx, len - 1 - rootidx, t->rChild);

	return t;

}
void PreInMakeTree(char* pre, char* in, int len, BinaryTree* t)
{
	t->root = MakeTree(pre, in, len, t->root);

}


//----------------------------------------------------------------------------------����Ȩ���в���
//����������Ȩ����
void CreatePQ(PriorityQueue* pq, int msize)
{
	pq->maxSize = msize;
	pq->n = 0;
	pq->element = (HFMTNode*)malloc(msize * sizeof(HFMTNode*));
}
//��������Ȩ����
void DestoryPQ(PriorityQueue* pq)
{
	free(pq->element);
	pq->n = 0;
	pq->maxSize = 0;
}
//�������ѵ����ϵ���
void AdjustUpHfm(HFMTNode** heap, int current)
{
	int p = current;
	HFMTNode* tmp;
	while (p > 0)
	{
		if ((heap[p]->w < heap[(p - 1) / 2]->w))//��ǰλ��ȨֵС��˫��Ȩֵ
		{   //����
			tmp = heap[p];
			heap[p] = heap[(p - 1) / 2];
			heap[(p - 1) / 2] = tmp;
			p = (p - 1) / 2;   //����
		}
		else
			break;  //Ȩֵ���� ����
	}
}
//��β+1������Ϊ��С��
void Append(PriorityQueue* pq, HFMTNode* x)
{
	if (pq->n == pq->maxSize)
		return;
	pq->element[pq->n] = x;
	pq->n++;
	AdjustUpHfm(pq->element, pq->n - 1);//���²���Ķ�βԪ�ؽ���Ȩֵ����

}
//�������ѵ����µ���
void AdjustDownHfm(HFMTNode** heap, int current, int border)
{
	int p = current;
	int min;//ָ���С���ӵ��±�
	HFMTNode* tmp;
	while (2 * p + 1 <= border)//pΪ��Ҷ�ӽ��
	{
		if ((2 * p + 2 <= border) && (heap[2 * p + 2]->w < heap[2 * p + 1]->w)) //���Ӷ������ҽ�С 
			min = 2 * p + 2;
		else//���С
			min = 2 * p + 1;
		if (heap[p]->w <= heap[min]->w) //�������� 
			break;
		else//����
		{
			//����
			tmp = heap[p];
			heap[p] = heap[min];
			heap[min] = tmp;
			//���µ����������
			p = min;
		}
	}
}
//���ض�ͷԪ�ز�����Ϊ��С��
HFMTNode* ServePQ(PriorityQueue* pq, HFMTNode* x)
{
	if (pq->n == 0)
		return NULL;
	x = pq->element[0];
	pq->n--;
	pq->element[0] = pq->element[pq->n]; //�������ݣ���ʱ�����ң�
	AdjustDownHfm(pq->element, 0, pq->n - 1);
	return x;
}


//----------------------------------------------------------------------------------������������
// ���������й�����������Χ������ ����ʱ���붯̬�ռ�ĵ�ַ  չ��
//�ϲ����������Ĳ���---���ϲ����ĸ���Ԫ������Ϊ#��Ȩֵ��Ϊ��������Ȩֵ֮��,���Ҹ���Ӧ������
HFMTNode* MakePair(HFMTNode* p, int w, char ch, HFMTNode* left, HFMTNode* right)
{
	HFMTNode* hfmt;
	hfmt = (HFMTNode*)malloc(sizeof(HFMTNode));
	if (!hfmt)
	{
		printf("�ڴ�����ʧ�ܣ�\n");
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
//���������Ĵ���
HFMTNode* CreateHFMTree(char* s, int* w, int len, HFMTNode* hfmt)// sΪ�ַ����飬wΪȨֵ���飨���ַ����ж�Ӧ�±�Ĺ�ϵ��lenΪ����   
{
	PriorityQueue pq;   //����������Ȩ����
	HFMTNode* x, * y, * z;
	int i;
	x = y = z = NULL;
	CreatePQ(&pq, len);
	for (i = 0; i < len; i++)//���и��ڵ㽨�����
	{
		x = MakePair(x, w[i], s[i], NULL, NULL);
		Append(&pq, x);
	}
	while (pq.n > 1) //�ϲ�Ϊһ�Ź�������
	{
		x = ServePQ(&pq, x);
		//ȡ���ڵ�Ȩֵ��С�ĸ�x
		y = ServePQ(&pq, y);
		//ȡ���ڵ�Ȩֵ��С�ĸ�y
		//�ϲ�x��y�����¶�������ӣ��ϲ�����Ȩֵ��С��Ϊ��������----�ϲ���������ڵ�Ԫ�ؽ�Ϊ��#��
		if (x->w < y->w) //xС Ϊ������
			z = MakePair(z, x->w + y->w, '#', x, y);
		else
			z = MakePair(z, x->w + y->w, '#', y, x);
		Append(&pq, z);
	}
	x = ServePQ(&pq, x);
	//ȡ���ϲ��Ĺ�������������x                                         
	hfmt = x;
	DestoryPQ(&pq);//��������Ȩ����
	return hfmt;
}
void  MakeHFMTree(char* s, int* w, int len, HFMTree* hfmt)
{
	hfmt->root = CreateHFMTree(s, w, len, hfmt->root);
}
//���������� -�߱����߱��� 
void Coding(HFMTNode* t, int* code, int len)
{
	int i;
	if (!t)//��
		return;
	if (!t->lChild && !t->rChild)//Ҷ�ӽڵ� �������
	{
		printf("%c �Ĺ���������Ϊ�� ", t->element);
		for (i = 0; i < len; i++)
			printf("%d", code[i]);
		putchar('\n');
	}
	else
	{
		code[len] = 0;
		Coding(t->lChild, code, len + 1);//����������
		code[len] = 1;
		Coding(t->rChild, code, len + 1);//����������

	}



}
void HFMTCoding(HFMTree* hfmt)
{
	int code[20];//�������ĸ�ı��������
	Coding(hfmt->root, code, 0);

}
//����������
void HFMTDecoding(HFMTree* hfmt, int* code, int len)//lenӦ�����û������ʱ��õ���ΪԪ�ظ��������
{
	int i;
	HFMTNode* t = hfmt->root;
	if (!t)
		return;
	printf("��������Ϊ��\n");
	for (i = 0; i < len; i++)
	{
		(code[i] && 1) ? (t = t->rChild) : (t = t->lChild);//���ʽΪ�棬����Ϊ1�����ң���֮��Ȼ
		if ((!t->lChild) && (!t->rChild))//Ҷ�� ---(����ȡ����nullָ������ô������ѣ������붯̬�ڴ�ʱ�����ж��Ƿ�����ɹ�����)--(�����˻��ǻ����ѡ������ⲻ��)
		{
			printf("%c ", t->element);
			t = hfmt->root;  //����
		}

	}
	putchar('\n');
}
//������������
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



