

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class NQUEENS {
private:
	int n;
	vector<int> x;//解向量
	vector<vector<int>> ans;
public:
	NQUEENS(int m) {
		n = m;
		for (int i = 0; i < n; i++) {
			x.push_back(-1);
		}
	}
	bool isValid(int k, int c) {
	//判断是否可以放置，k为queen下标同样也代表row，c为放置的列数
		for (int i = 0; i < k; i++) {
			if (x[i] == c || abs(k - i) == abs(c - x[i])) {
				return false;
			}
		}
		return true;
	}
	void NQ_tracing(int k) {
		if (k == n ) {
			ans.push_back(x);
		}

		for (int i = 0; i < n; i++) {
			if (isValid(k, i)) {
				x[k] = i;//修改当前
				
				NQ_tracing(k+1);//子状态搜索

				x[k] = -1;//回改
			}
		}
	}
	void NQueens() {
	
		NQ_tracing(0);
	}
	void Print(vector<int>& x) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (x[i] == j)
					cout << " Q ";
				else cout << " * ";
			}
			cout << endl;
		}
		cout << endl;
	
	
	}
	void PrintAns(){
		NQueens();
		int r = ans.size();
		if (r == 0) {
			cout << "no result" << endl;
			return;
		}
		for (int i = 0; i < r; i++) {
			cout << "第"<<i+1<<"个解如下:"<< endl;
			Print(ans[i]);
		}
	}
};
void Test_NQueens() {
	cout << "N-Queens 测试" << endl;
	int n;
	cout << "输入N的数据(0<N)：" << endl;
	cin >> n;
	NQUEENS m(n);
	m.PrintAns();
	system("pause");

}


/*

问题描述：将n个集装箱装上两艘轮船的最佳装载问题
形式化描述：c0，c1为轮船载重，n为集装箱数量，w[]为集装箱重量
			解向量形式xi=0/1,表示该集装箱装载轮船编号
			要求 Σwi <= c0+c1 
*/

class Ferrys {
private:
	int n;
	int c0, c1;//将在求解过程中变化
	vector<int > w;
	vector<vector<int>> ans;//最终解
	vector<int > tmp;//当前解

public:
	Ferrys(int N,int C0,int C1,vector<int> & W) {
		n = N;
		c0 = C0;
		c1 = C1;
		for (int i = 0; i < W.size(); i++) {
			w.push_back(W[i]);
			tmp.push_back(-1);
		}
	}
	bool isValid(int k,int i) {
		//k表示当前分配物品下标，i表示轮船编号
		if (i == 0) {
			if (w[k] <= c0) 
				return true;
			else return false;
		}
		else {
			if (w[k] <= c1)
				return true;
			else return false;
		}
	}
	void Backtracing(int k) {
		if (k == n ) {
			ans.push_back(tmp);
			return;
		}
		for (int i = 0; i <= 1; i++) {//每个节点下最多就两个状态
			if (isValid(k, i)) {
				
				//修改当前节点状态
				i == 0 ? c0 = c0 - w[k] : c1 = c1 - w[k];  
				tmp[k] = i;
				
				//回溯子节点
				Backtracing(k + 1);
				
				// 回改当前节点
				i == 0 ? c0 = c0 + w[k] : c1 = c1 + w[k];
				tmp[k] = -1;
			
			
			}
		
		}
	}
	void Solution() {
		Backtracing(0);
	}
	void PrintAns() {
		Solution();
		int m = ans.size();
		if (m == 0) {
			cout << "无分配方案。" << endl;
		}
		cout<<"分配方案如下（分别对应物品放置轮船的编号）"<<endl;
		for (int i = 0; i < m; i++) {
			cout << "      ";
			for (int j = 0; j < ans[0].size(); j++) {
				cout <<ans[i][j]+1 << " ";
			}
			cout << endl;
		}
	
	
	}



};
void Test_Ferry() {
	cout << "输入集装箱数目:" << endl;
	int n;
	cin >> n;
	
	cout << "逐个输入集装箱重量：" << endl;
	vector<int> w;
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >>  tmp;
		w.push_back(tmp);
	}
	cout << "输入两个轮船的载重上限:" << endl;
	int c0 ;
	int c1 ;
	cin >> c0 >> c1;
	Ferrys ferry(n, c0, c1, w);
	ferry.PrintAns();
	system("pause");
}



int main() {

	Test_NQueens();
	
	//Test_Ferry();
	
	return 0;
}
