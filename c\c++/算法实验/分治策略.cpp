#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
 #define MAXSIZE 20
using namespace std;

//两路合并排序-- O(nlog2n)
void Merge(vector<int> & list, int * tmp, int low, int n1, int n2)
{
    int i = low, j = low + n1;
    while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1)
    {
        if (list[i] <= list[j])
            *tmp++ = list[i++];
        else *tmp++ = list[j++];
    }
    while (i <= low + n1 - 1) 
        *tmp++= list[i++];
    while (j <= low + n1 + n2 - 1)
        *tmp++ = list[j++];
}
void MergeSort(vector<int>& list)
{
    int tmp[MAXSIZE];
    int low, n1, n2, i, size = 1;
    int n = list.size();
    while (size < n)
    {
        low = 0;
        while (low + size <n)
        {
            n1 = size;
            if (low + size * 2 < n)
                n2 = size;
            else
                n2 = n - low - size;
            Merge(list, tmp + low, low, n1, n2);
            low += n1 + n2;
        }
        for (i = 0; i < low; i++)
            list[i] = tmp[i];
        size *= 2;
    }
}
void test_mergesort() {
    vector<int > a = { 9,1,8,2,7,3,6,4,5,0 };
    cout<<"原数组："<<endl;
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
    MergeSort(a);
    cout << "排序后数组：" << endl;
    for (int i = 0; i < a.size();i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
}

//快速排序 ---最好O(nlog2n),最坏与平均O(n^2)
//分割序列
int Partition(vector<int> & list, int low, int high)
{
    int i = low, j = high + 1;
    int pivot = list[low];//采用最基础的中枢元素选择，以便于更好的与后面的代码交互
    do {
        do i++;
        while (i <= high && (list[i] < pivot));//i 前进找大
        do j--;
        while (list[j] > pivot);//j 前进找小
        if (i < j)
            swap(list[i],list[j]);
    } while (i < j);
    swap(list[low],list[j]);
    return j;//当前分割元素下标
}
//递归主体
void QSort(vector<int>& list, int low, int high)
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
void QuickSort(vector<int> & list)
{
    QSort(list, 0, list.size()-1);
}
void test_qsort() {
    vector<int> a = {7,4,8,5,9,2,0,13,56,34,27,44};
    cout << "原数组：" << endl;
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
    QuickSort(a);
    cout << "排序后数组：" << endl;
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << ' ';
    }
    cout << endl;


}

//插入排序-用于对分组后的子序列进行有选择的排序，以便于输出子序列中位数
void InsertSort(vector<int>& list,int start,int length)
{
    int i, j;
    int item;
    for (i = start+1; i < start+length; i++)
    {
        item = list[i];
        for (j = i - 1; j >= start; j--)
        {
            if (item < list[j])
                list[j + 1] = list[j];
            else break;
        }
        list[j + 1] = item;
    }
}
//寻找算法
int find(vector<int>& mid_sub, int low, int high) {
    if (low == high)//递归结束
        return mid_sub[low];
    //5个一组元素处理
    int index = low;
    int count = 0;//记录本次递归处理的中值数
    //5个一组处理，不足则转入下面小于5元数据组处理
    int m = (high-low + 1) / 5 * 5 - 1;
    for (; index < (high - low + 1) / 5 * 5 - 1; index += 5) {//中间判断条件确保
        InsertSort(mid_sub,index,5);
        mid_sub[count] = mid_sub[index + 2];//处理好的5元组中第三个数据存入中值数组
        count++;
    }
    //c处理小于5元组数据
    int remain = high - index + 1;
    if (remain > 0) {
        InsertSort(mid_sub, index, remain);
         mid_sub[count] = mid_sub[index + (remain % 2 == 0 ? remain/2-1:remain/2) ];
        count++;
    }
    if (count == 1)
        return mid_sub[0];
    else
        return find(mid_sub, 0, count - 1);
}
//寻找中枢元素，完成交换操作，使最后序列的第一个元素为五元组中值分割法查找得到的pivot —O(n)
void set_pivot(vector<int>& list) {
    vector<int> mid_sub(list);//存放中间中位数的数组
    int pivot=find(mid_sub, 0, mid_sub.size() - 1);
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == pivot) {
            swap(list[0], list[i]);
            return;
        }
    }
           
}
//寻找第k个小元素—O(n)
int find_kth_min(vector<int>& list,int k) {
    //第k个小的元素，即寻找下表为k-1
    int left = 0, right = list.size() - 1;
    int mid;
    int target = k-1;
    set_pivot(list);//处理序列
    while (left < right) {
        mid = Partition(list, left, right);
        if (mid == target) return list[mid];
        else if (mid < target) left = mid + 1;
        else right = mid - 1;
    }
    return list[left];
}
void test_kth() {
    vector<int> a = { 8,2,6,3,11,9,12,15,1,0 ,7};
    cout << "原数组：" << endl;
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << ' ';
    }
    cout << endl;

    int k;
    cout << "寻找第k个小的元素" << endl;
    cin >> k;
    while (k -1<0 || k >=a.size()) {
        cout << "k值无效，请重新输入！" << endl;
        cin >> k;
   
    }
    cout << "第" << k << "个小的元素为" << find_kth_min(a, k) << endl;
    
    
    QuickSort(a);
    cout << "排序后数组：" << endl;
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << ' ';
    }
    cout << endl;

}
int main() {
    cout << "两路合并测试" << endl;
    test_mergesort();
    cout << endl;
    cout << "快排测试" << endl;
    test_qsort();
    cout << endl;
    cout<<"第k小元素搜索测试"<<endl;
    test_kth();
    system("pause");
    return 0;
}
