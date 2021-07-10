#include<iostream>
#include<string>
#include<time.h>
using namespace std;
void Print(bool **p,int n)
{for(int i=0;i<n;i++)
		{ for(int j=0;j<n;j++)
		  {cout<<p[i][j]<<" ";
		  }
	    cout<<endl;
	    }
cout<<endl;
}
void cal_jiao(bool **p,bool **tmp, bool **use ,int n)//矩阵交计算（主要是矩阵自乘),注意传参顺序----tmp中缓存数据
{  bool mid=0;
	for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
		   {for(int k=0;k<n;k++)
	            {mid=mid || (tmp[i][k] && p[k][j]);}
	        use[i][j]=mid;
	        mid=0;
	        }

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		tmp[i][j]=use[i][j];
}
void cal_bing(bool **tmp,bool **pt2,int n)//矩阵并运算
{
	for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)                                            
	   {pt2[i][j]=pt2[i][j] || tmp[i][j];
	   }
}
void cal_bing(bool **ps,int n)//重载 用于对称闭包运算
{for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)                                            
	   {ps[i][j]=ps[i][j] || ps[j][i];
	   }


}
bool JudgeReflexivity( bool **p, int n)//自反与反自反,返回自反判断的结果（便于闭包运算）
{int flag1=1;
 int flag2=1;
 for(int i=0;i<n;i++)
	 {  if(p[i][i] == 0)//自反性：主对角元素全为1
		   flag1=0;
	    if(p[i][i] == !0)//反自反性：主对角元素全为0
		   flag2=0;
       }
 if(flag1)
	 cout<<"关系矩阵具有自反性!\n";
 else
	 cout<<"关系矩阵不具有自反性！\n";
 if(flag2)
	 cout<<"关系矩阵具有反自反性!\n";
 else
	 cout<<"关系矩阵不具有反自反性！\n";
 if(flag1)
	 return true;
 else
	 return false;
}
bool JudgeSymmetry( bool **p, int n)//对称与反对称，返回对称判断的结果（便于闭包运算）
{int flag1=1;
 int flag2 = 1;
 for(int i =0;i<n;i++)
	 for(int j=i+1;j<n;j++)
	 {if(p[i][j] != p[j][i])//对称性：矩阵关于主对角线对称
	   flag1=0;
	  if(p[i][j]&&p[j][i] == !0)//反对称性：对称元素不可同时为1
		flag2=0;
	 }
if(flag1)
	 cout<<"关系矩阵具有对称性!\n";
 else
	 cout<<"关系矩阵不具有对称性！\n";
 if(flag2)
	 cout<<"关系矩阵具有反对称性!\n";
 else
	 cout<<"关系矩阵不具有反对称性！\n";
  if(flag1)
	 return true;
 else
	 return false;
}
void Warshell(bool **pt1,int n)
{ 
	

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
	  if(pt1[j][i] == !0)
	     for(int k=0;k<n;k++)
		   pt1[j][k] = pt1[j][k] | pt1[i][k];
	

}
void Traditional(bool **pt2,bool **p,bool **tmp,bool **use,int n,int countnum)//传递闭包运算传统算法
{
	
	
	for(int i=2;i<=countnum;i++)
   {cal_jiao(p,tmp,use,n);
    cal_bing(tmp,pt2,n);
	
   }



}
bool Is_equal(bool **p1,bool **p2,int n)
{bool flag=1;
 for(int i=0;i<n && flag;i++)
	 for(int j=0;j<n && flag;j++)
		 if(p1[i][j] != p2[i][j])
			 flag=0;
 return flag;
}
void cal_reflex(bool **pr,bool **use,int n)
{ for(int i=0;i<n;i++)//使得use矩阵变成单位矩阵
    for(int j=0;j<n;j++)
	  {if(i==j)
	     use[i][j]=1;
	  else use[i][j]=0;
	  }
 cal_bing(use,pr,n);
}
int main()
{ clock_t s1,s2,s3,e1,e2,e3;
  s1 = clock();//总计时开始
	
	
	//-----------------------creat
	int n;
	int countnum=0;
	cout<<"输入矩阵阶数：\n";
	cin>>n;
	bool **p=new bool *[n];  //原数组
	for(int i=0;i<n;i++)
		p[i]=new bool [n];

		bool **pr=new bool *[n];  //自反闭包数组
	for(int i=0;i<n;i++)
		pr[i]=new bool [n];

		bool **ps=new bool *[n];  //对称闭包数组
	for(int i=0;i<n;i++)
		ps[i]=new bool [n];

		bool **pt1=new bool *[n];  //传递闭包数组（warshell）
	for(int i=0;i<n;i++)
		pt1[i]=new bool [n];

	
		bool **pt2=new bool *[n];  //传递闭包数组（传统）
	for(int i=0;i<n;i++)
		pt2[i]=new bool [n];


	    bool **tmp=new bool *[n];  //传递闭包数组中间数组
	for(int i=0;i<n;i++)
		tmp[i]=new bool [n];    

	
	    bool **use=new bool *[n];  //用来计算
	for(int i=0;i<n;i++)
		use[i]=new bool [n];  


	//-----------------------input
	bool temp;
	cout<<"输入矩阵信息：\n";
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
	         {  
				cin>>temp;
				if(temp) 
					countnum++;
				p[i][j]=temp;
				pr[i][j]=temp;
				ps[i][j]=temp;
				pt1[i][j]=temp;
				pt2[i][j]=temp;
				tmp[i][j]=temp;
	         }

//-----------------------cal
s2 = clock();//waeshell算法计时开始
Warshell(pt1,n);
e2= clock();//warshell 算法计时结束


s3=clock();//传统闭包算法计时开始
Traditional(pt2,p,tmp,use,n,countnum);	
e3=clock(); //传统闭包算法计时结束


cal_reflex(pr,use, n);//自反闭包计算

cal_bing(ps,n);//对称闭包计算

//-----------------------judge
JudgeReflexivity(p,n);
JudgeSymmetry(p,n);

if(Is_equal(p,pt1,n))
	cout<<"关系矩阵具有传递性！\n";
else cout<<"关系矩阵不具有传递性！\n";

cout<<endl;


//-----------------------output
cout<<"两种传递闭包运算结果是否相等：\n";
if(Is_equal(pt1,pt2,n)) cout<<"yes!"<<endl;
else cout<<"no!"<<endl;

cout<<"原矩阵：\n"	;
Print(p,n);
cout<<"传递闭包：\n";
Print(pt1,n);
cout<<"自反闭包：\n";
Print(pr,n);
cout<<"对称闭包：\n";
Print(ps,n);

//-----------------------delete
	for(int i=0;i<n;i++)
		delete [] use[i];
	delete [] use;

    for(int i=0;i<n;i++)
		delete [] tmp[i];
	delete [] tmp;
	
	for(int i=0;i<n;i++)
		delete [] pt2[i];
	delete [] pt2;

	for(int i=0;i<n;i++)
		delete [] pt1[i];
	delete [] pt1;

	for(int i=0;i<n;i++)
		delete [] ps[i];
	delete [] ps;

	for(int i=0;i<n;i++)
		delete [] pr[i];
	delete [] pr;

	for(int i=0;i<n;i++)
		delete [] p[i];
	delete [] p;




//---------------------------runtime output
e1 = clock();//计时结束
cout << "Warshell algorithm run time is: " <<(double)(e2- s2)/ CLOCKS_PER_SEC << "s" << endl;
cout << "Traditional transitive closure operation run time is: " <<(double)(e3- s3)/ CLOCKS_PER_SEC << "s" << endl;
cout << "Tatol run time is: " <<(double)(e1 - s1)/ CLOCKS_PER_SEC << "s" << endl;
//---------------------------
system("pause");
return 0;}