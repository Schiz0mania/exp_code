/*
           //思路一：利用两行数组完成计算
              观察递归式，每次第一层数据都是初始化为0，第二层数据的第一个也初始化为0（递归式直接定义出，没问题）
              每次递归数据的计算都却决于他周围的三个元素（如图，[cur][j]取决于其他三个数据），利用递归规律计算改行数据之后，当前行作为新的基础数据，即替换到第一层去，为接下来的计算做基础

              ...   [pre][j-1] [pre][j]     完成该层计算之后       ...   [pre][j-1] [pre][j]  // data from last cur row
                                          ------------------->
              ...   [cur][j-1] [cur][j]                           [pre][0](0)   ......(根据递归式与上层迭代数据计算该层数据)

          //进一步优化(滑动窗口优化)
              ...   [pre][j-1] [pre][j]                   last(start with 0)          dp([j](->tmp)                             last(last dp[j])          dp[j](new dp[j])
                                          ----------->                                                 ---------->
              ...   [cur][j-1] [cur][j]                  dp[j-1](starts with 0)       ans_tmp                                ans_tmp(new dp[j-1])       ans_tmp(2)

              每一层开始时pre=dp[0]=0
              对于每一个字符的j遍历

                  last=dp[j]   记录数据，在该迭代点计算完后，dp[j]应当跟新到

                  if equal    dp[j]=last+1
                  else        dp[j]=max(dp[j-1],tmp)

                 last=tmp;

              难点理解
                  每一层递归结束后，dp[j]都存储这一层的结果数据，所以在下一层迭代时，dp[j]可以作为二维数组里的dp[i-1][j],而因为后面按照二维上的规律，应当保存到last位置，所以需要一个tmp来过渡
                  这么说吧，假设i层进行到j
                      所谓dp[j-1]保存数据对应二维理解里的dp[i][j-1],
                      dp[j]仍旧保留着上一层的数据，即dp[i-1][j]       ****
                      而last作为左对角的元素，每次都存储着上一次计算出现的dp[j]
                  当i层j次计算结束后,
                      dp[j]将被更新为结果dp[i][j],作为下一次运算的dp[i][j-1]出现

     */


#include <iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class LCS {
private:
    string a;
    string b;
    int m, n;
    vector<vector<int>> c1;//动态规划
    vector<vector<int>> c2;//备忘录
    vector<int> dp;//一维空间动态规划
public:
    LCS(string s1, string s2) {
        a = s1;
        b = s2;
        m = a.length();
        n = b.length();
        for (int i = 0; i <= m; i++) {
            c1.push_back(vector<int>(n + 1, 0));
            c2.push_back(vector<int>(n + 1, -1));

        }
        for (int i = 0; i <= m; i++) {
            dp.push_back(0);
        }
    }

    //7-11 build sequence using only the c table
    void LCSBulid_ver_two(vector<vector<int>>& c, int i, int j) {

        if (i == 0 || j == 0)
            return;
        if (a[i - 1] == b[j - 1]) {
            LCSBulid_ver_two(c, i - 1, j - 1);
            cout << a[i - 1];
        }
        else if (c[i - 1][j] >= c[i][j - 1]) {
            LCSBulid_ver_two(c, i - 1, j);

        }
        else LCSBulid_ver_two(c, i, j - 1);




    }
    //dp-from bottom to top
    int LCS_ver_one() {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i - 1] == b[j - 1]) {
                    c1[i][j] = c1[i - 1][j - 1] + 1;

                }
                else if (c1[i - 1][j] >= c1[i][j - 1]) {
                    c1[i][j] = c1[i - 1][j];

                }
                else {
                    c1[i][j] = c1[i][j - 1];

                }
            }
        }
        return c1[m][n];

    }
    //7-10 memoization-from top to bottom
    int LCS_ver_two(string& a, string& b, vector<vector<int>>& c2, int i, int j) {
        //备忘录方法
        if (c2[i][j] != -1)
            return c2[i][j];
        else if (a[i - 1] == b[j - 1]) {
            return LCS_ver_two(a, b, c2, i - 1, j - 1) + 1;
        }
        else {
            int tmp1 = LCS_ver_two(a, b, c2, i - 1, j);
            int tmp2 = LCS_ver_two(a, b, c2, i, j - 1);
            if (tmp1 >= tmp2)
                return tmp1;
            else return tmp2;


        }


    }
    int LCS_Memo(string& a, string& b) {
      
        
        for (int i = 0; i < m; i++) {
            c2[i][0] = 0;
        }
        for (int j = 0; j < n; j++) {
            c2[0][j] = 0;
        }
        return LCS_ver_two(a, b, c2, m, n);

    }
    //7-12 using only one row of dp to form ans
    int LCS_ver_three() {

     
       
        int last, tmp;
        
        for (int i = 1; i < m + 1; i++) {
            last = 0;
            for (int j = 1; j < n + 1; j++) {
                tmp = dp[j];//保留上一层dp[i-1][j],

                //完成该层滑动
                if (a[i - 1] == b[j - 1]) {
                    dp[j] = last + 1;
                }
                else dp[j] = max(dp[j - 1], dp[j]);

                //上一层实现滑动
                last = tmp;
            }
        }
        return dp[m-1];
    }
    void PrintAns() {
        cout << "自底向上动态规划求解(线性空间复杂程度)：" << endl;
        cout << "   LCS-长度" << LCS_ver_three() << endl;
        cout << "   LCS-序列";
        LCS_ver_one();
        LCSBulid_ver_two(c1, m, n);
        cout << endl;
        cout << "自顶向下动态规划备忘录求解：" << endl;
        cout << "   LCS-长度" << LCS_Memo(a, b) << endl;
        cout << "   LCS-序列";
        LCSBulid_ver_two(c1, m, n);
        cout << endl;







    }
};
class MatrixChain {
private:
    vector<int> p;
    vector<vector<int>> s1;
    vector<vector<int>> m1;
    vector<vector<int>> m2;
    vector<vector<int>> s2;

public:

    MatrixChain(vector<int> p0) {
        p = p0;
        int n = p0.size() - 1;
        for (int i = 0; i < n; i++) {

            m1.push_back(vector<int >(n, -1));
            s1.push_back(vector<int >(n, 0));

            m2.push_back(vector<int >(n, -1));
            s2.push_back(vector<int >(n, 0));

        }
    }

    int MChina_bottom_to_top() {
        int n = p.size() - 1;
        for (int i = 0; i < n; i++) m1[i][i] = 0;
        for (int r = 2; r <= n; r++) {
            for (int i = 0; i <= n - r; i++) {
                int j = i + r - 1;
                m1[i][j] = m1[i + 1][j] + p[i] * p[i + 1] * p[j + 1];//初值
                s1[i][j] = i;
                for (int k = i + 1; k < j; k++) {
                    int tmp = m1[i][k] + m1[k+1][j] + p[i] * p[k + 1] * p[j + 1];
                    if (tmp < m1[i][j]) {
                        m1[i][j] = tmp;
                        s1[i][j] = k;
                    }
                }
            }
        }
        return m1[0][n - 1];
    }

    int MChina_lookup(int i, int j) {

        if (m2[i][j] >= 0) return m2[i][j];
        if (i == j) return 0;

        int u = MChina_lookup(i + 1, j) + p[i] * p[i + 1] * p[j + 1];
        s2[i][j] = i;
        for (int k = i + 1; k < j; k++) {
            int tmp = MChina_lookup(i, k) + MChina_lookup(k + 1, j) + p[i] * p[k + 1] * p[j + 1];
            if (tmp < u) {
                u = tmp;
                s2[i][j] = k;
            }
        }
        m2[i][j] = u;
        return u;
    }

    void LookUpChain() {
        MChina_lookup(0, p.size() - 2);
    }

    void TraceBack(int i, int j) {
        if (i == j) {
            cout << "A" << i;
            return;
        }
        if (i < s1[i][j])
            cout << "("; TraceBack(i, s1[i][j]);
        if (i < s1[i][j])
            cout << ")";
        if (s1[i][j] + 1 < j)
            cout << "("; TraceBack(s1[i][j] + 1, j);
        if (s1[i][j] + 1 < j)
            cout << ")";

    }

    void PrintAns() {

        MChina_bottom_to_top();
        cout << "最佳连乘次序(由底到顶)：" << endl;
        TraceBack(0, p.size() - 2);
        cout << endl << endl;

        LookUpChain();
        cout << "最佳连乘次序(备忘录)：" << endl;
        TraceBack(0, p.size() - 2);
        cout << endl;

    }

};
void Test_LCS() {
    string a = "xzyzzyx";
    string b = "zxyyzxz";
    cout << "序列a:" << a << endl;
    cout << "序列b:" << b << endl;
    LCS seq(a, b);
    seq.PrintAns();

}
void Test_MC() {
    vector<int > p = { 30,35,15,5,10,20,25 };
    cout << "连乘矩阵数据：" << endl;
    for (int i = 0; i < p.size();i++) {
        cout << p[i] << " ";
    }
    cout << endl;
    MatrixChain m(p);
    m.PrintAns();

}
int main() {
    cout << "LCS测试" << endl;
    Test_LCS();
    cout << endl << endl;
    cout << "矩阵连乘测试" << endl << endl;;
    Test_MC();
    cout << endl << endl;
    system("pause");
    return 0;
}
