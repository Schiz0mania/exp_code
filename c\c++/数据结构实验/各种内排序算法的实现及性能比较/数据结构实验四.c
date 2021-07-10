#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
# define MAXSIZE 500000 //两路合并临时存储数组大小 

typedef struct entry
{
    int key;
    int data;
}Entry;
typedef struct list
{
    int n;
    int maxLength;
    Entry* D;
}List;
Entry tmp[MAXSIZE];
//-------基本操作
//初始化
int InitList(List* L, int msize)
{
    L->maxLength = msize;
    L->n = 0;
    L->D = (Entry*)malloc(sizeof(Entry) * msize);
    if (!L->D)
        return 0;
    return 1;
}
//插入（x成为下标为i+1的元素）---O(n)
int InsertList(List* L, int i, Entry x)
{
    int j;
    if (i<-1 || i>L->n - 1)//下标越界
        return 0;
    if (L->n == L->maxLength)//插入空间是否充足
        return 0;
    for (j = L->n - 1; j > i; j--)//后移
        L->D[j + 1] = L->D[j];
    L->D[i + 1] = x;
    L->n++;//增加
    return 1;

}
//输出
int OutputList(List* L)
{
    int i;
    if (!L->n)
        return 0;
    for (i = 0; i < L->n; i++)
        printf("%d  ", L->D[i].data);
    printf("\n");
    return 1;
}
//撤销
int DestList(List* L)
{
    if (! L->D)
        return 0;
    L->maxLength = 0;
    L->n = 0;
    free(L->D);
}
//----------------排序函数
//交换函数（下标i j互换）
void Swap(Entry* D, int i, int j)//交换下标 i j
{
    Entry tmp;
    if (i == j)
        return;
    tmp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = tmp;
}
//简单排序(找最小)
void SelectSort(List* list)
{
    int i, j, mindex;
    //i j控制循环，mindex指向最小关键词下标 tmp用于交换数据
    for (i = 0; i < list->n; i++)
    {
        mindex = i;
        for (j = i + 1; j < list->n; j++)
        {
            if (list->D[j].key < list->D[mindex].key)
                mindex = j;
        }
        if (mindex != i)//当前非待排序数列最小值 交换数据
        {
            Swap(list->D, i, mindex);
        }
    }

}
//直接插入排序
void InsertSort(List* list)
{
    int i, j;
    Entry item;
    for (i = 1; i < list->n; i++)
    {
        item = list->D[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (item.key < list->D[j].key)
                list->D[j + 1] = list->D[j];
            else break;
        }
        list->D[j + 1] = item;
    }
}
//冒泡排序
void BubbleSort(List* list)
{
    int i, j;//i,j控制循环 tmp用于交换
    for (i = list->n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (list->D[j].key > list->D[j + 1].key)//下沉
            {
                Swap(list->D, j, j + 1);
            }
        }
    }
}
//快速排序
    //分割序列
int Partition(List* list, int low, int high)
{
    int i = low, j = high + 1;
    Entry pivot = list->D[low];//分割元素
    do {
        do i++;
        while (i <= high && (list->D[i].key < pivot.key));//i 前进找大
        do j--;
        while (list->D[j].key > pivot.key);//j 前进找小
    } while (i < j);
    Swap(list->D, low, j);
    return j;//当前分割元素下标
}
    //递归主体
void QSort(List* list, int low, int high)
{
    int k;
    if (low < high)
    {
        k = Partition(list, low, high);
        QSort(list, low, k - 1);
        QSort(list, k + 1, high);
    }
}
    //封装函数
void QuickSort(List* list)
{
    QSort(list, 0, list->n - 1);
}

//两路合并排序
void Merge(List* list, Entry* tmp, int low, int n1, int n2)
{
    int i = low, j = low + n1;
    while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1)
    {
        if (list->D[i].key <= list->D[j].key)
            *tmp++ = list->D[i++];//---------
        else *tmp++ = list->D[j++];
    }
    while (i <= low + n1 - 1)
        *tmp++ = list->D[i++];
    while (j <= low + n1 + n2 - 1)
        *tmp++ = list->D[j++];
}
void MergeSort(List* list)
{
    //-----tmp为全局变量
    int low, n1, n2, i, size = 1;
    while (size < list->n)
    {
        low = 0;
        while (low + size < list->n)
        {
            n1 = size;
            if (low + size * 2 < list->n)
                n2 = size;
            else
                n2 = list->n - low - size;
            Merge(list, tmp + low, low, n1, n2);
            low += n1 + n2;
        }
        for (i = 0; i < low; i++)
            list->D[i] = tmp[i];
        size *= 2;
    }
}
//堆排序（使用最小堆）
//最小堆向下调整
void AdjustDown(List* heap, int current,int border)
{
    int p = current;
    int min;
    Entry tmp;
    while (2 * p + 1 <= border)
    {
        if ((2 * p + 2 <= border) && (heap->D[2 * p + 2].key < heap->D[2 * p + 1].key))
            min = 2 * p + 2;
        else
            min = 2 * p + 1;
        if (heap->D[p].key <= heap->D[min].key)
            break;
        else
        {
            tmp = heap->D[p];
            heap->D[p] = heap->D[min];
            heap->D[min] = tmp;
            p = min;
        }
    }
}
//堆排序
void HeapSort(List* hp)
{
    int i;
    int j = hp->n -1;
    for (i = (hp->n - 2) / 2; i >= 0; i--)
        AdjustDown(hp, i,hp->n-1);
    for (i = 0; i < hp->n - 1 && j>=0; i++)
    {
        Swap(hp->D, 0, j);
        j--;
        AdjustDown(hp, 0,j);
    }
} //生成n个关键词并写入文件
void  Prep(int n)
{
    int i;
    srand(time(NULL));
    errno_t err;
    FILE* p;
    err = fopen_s(&p, "F:\\DS4.txt", "w");
    if ( p== NULL)
    {
        printf("打开失败！\n");
        exit(1);
    }
    else
    {
        for (i = 1; i <= n; i++)
        {
            fprintf(p,"%d\n",rand() % 1000000 + 1);//使数据分散-----------------
        }
        fprintf(p, "%d\n", -1);
        fclose(p);
    }
    printf("写入了%d个数据",i-1);
}
//读取数据+排序测试
void TestFunc(int choice)
{
    List L;
    int size[4] = {500,10000,50000,100000};//关键字个数
    int i, j, k,m;//i控制循环 j读取 k初始化顺序表
    Entry tmp;
    SYSTEMTIME t1, t2;
    errno_t err;
    FILE* p;

    for (i = 0; i < 4 ; i++)//
    {
        InitList(&L,size[i]);
        Prep(size[i]);
        //读取
        j = 1;
        k = -1;
        err= fopen_s(&p,"F:\\DS4.txt", "r");
        if (p == NULL)
        {
            printf("打开失败！\n");
            exit(1);
        }
        else
        {
            fscanf_s(p,"%d",&j);//-------------------------
            while (j != EOF)
            {
                tmp.data = tmp.key = j;
                InsertList(&L, k, tmp);
                k++;
                fscanf_s(p, "%d", &j);//-------------------------
            }
            printf("读取了%d个数据\n",k+1);
            fclose(p);
        }
        //排序+时间测算
        GetSystemTime(&t1);
        switch (choice)
        {
        case 1:
        {   
            SelectSort(&L);//选择排序1
            printf("选择排序\n");
            //OutputList(&L);
            break;
        }
        case 2:
        {
            InsertSort(&L);//直接插入排序2
            printf("直接插入排序\n");
            break;
        }
        case 3:
        {
            BubbleSort(&L);//冒泡排序3
            printf("冒泡排序\n");
            break;
        }
        case 4:
        {
            QuickSort(&L);//快速排序4
            printf("快速排序\n");
            break;
        }
        case 5:
        {
            MergeSort(&L);//合并排序5
            printf("合并排序\n");
            break;
        }
        case 6:
        {
            HeapSort(&L);//堆排序6
            printf("堆排序\n");
            break;
        }
        }
        GetSystemTime(&t2);
        printf("关键词个数为%d，排序时间为 %u 毫秒\n", size[i],((t2.wMinute - t1.wMinute) * 60 +
            t2.wSecond - t1.wSecond) * 1000 + t2.wMilliseconds - t1.wMilliseconds);
        err = fopen_s(&p, "F:\\ds4_output.txt", "w");
        if (p == NULL)
        {
          printf("打开失败！\n");
          exit(1);
          }
         else
         {
          for (m = 0; m <= size[i]-1; m++)
          {
            fprintf(p, "%d\n", L.D[m]);
           }
        fclose(p);
    }



        DestList(&L);
        putchar('\n');
    }
    //
    
    system("pause");

}

int main()
{
    int choice;
FLAG:
    printf("1、选择排序\n");
    printf("2、直接插入排序\n");
    printf("3、冒泡排序\n");
    printf("4、快速排序\n");
    printf("5、合并排序\n");
    printf("6、堆排序\n");
    printf("输入你的选择\n");
    scanf_s("%d",&choice);
    TestFunc(choice);
    printf("继续？（1/0）\n");
    scanf_s("%d",&choice);
    if (choice)
    {
        system("cls");
        goto FLAG;
    }       
    system("pause"); 
    return 0;
}
