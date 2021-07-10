#include<iostream>
#include<stdlib.h>
#include<string>
#include<time.h>
#include<vector>
using namespace std;
void Warshell(vector<vector<int> > & kd,int n)//传入参数实际上为邻接矩阵（开始时kd与lj相等）
{
 for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
	  if(kd[j][i] )
	     for(int k=0;k<n;k++)
		    kd[j][k] = kd[j][k] | kd[i][k];
	  
}
bool Is_in(int x,vector<vector<int> > & kd,int n)//功能：判断x是否在矩阵里，
{
	vector<vector<int> >::iterator it1;//行迭代器
 vector<int>::iterator it2;//列迭代器
 bool flag=false;
 for(it1=kd.begin();it1 != kd.end();it1++)
	 for(it2=(*it1).begin();it2 != (*it1).end();it2++)
		 if((*it2)== x)
			  flag=true;
 
 return flag;
}
bool Is_in(int x,vector<int> & start,int n)
{
 for(int i=0;i<n;i++)
   if(start[i] == x)
	   return true;
 return false;
}
int Odd_node(vector<vector <int>> &lj,int n)//获取图中奇数节点的个数。若有两个，或0个，返回奇数节点（或第一个元素）序号！.其他情况返回0；
{ int result=1;
  int sum=0;
  int countodd=0;
  for(int i=0;i<n;i++)
	  {for(int j=0;j<n;j++)
	      sum+=lj[i][j];
       if(sum%2)//度数为奇数
         {countodd++;
	      result=i+1;
         }
	   sum=0;
      }

  if(countodd == 0 || countodd ==2)
	  return result;
  else return 0;

}
bool Judge_Bridge(vector<vector<int> >  lj,int i,int j,int n)//判断i->j的这条路是否为桥，注意参数为传值！
{  
	lj[i][j]=lj[j][i]=0;
   Warshell(lj,n);
   //warshell结束，lj中为割去i->j后图的可达性矩阵
   if(Is_in(0,lj,n))//割去后图不可达，则i->j的路为桥
     return true;
   else return false;

}
void Fleury( vector<vector<int> >  &lj,vector <int> &path,int start,int n, int &count)//输出欧拉路的弗罗莱算法
{   
	int mark=start;
	
	if ( !Is_in(1,lj[start],n))//该节点无路可走--递归结束
		
	  {  path[count]=start+1;
	     count++;
		 return ;
	  }
    else
	{ for(int j=0;j<n;j++)
		{if(lj[start][j])//边关联
			if(Judge_Bridge(lj,start,j,n))//是桥
		         {mark=j;//标记桥
	              continue;
	             }
			else//不是桥，就走
			   {path[count]=start+1;//记录路的开始节点
				count++;//标记符加以
			    lj[start][j]=lj[j][start]=0;//标记start->j的路
				start=j;//j为新路的开始节点
				Fleury(lj,path,start,n,count);//递归
				return;
			   }
		}

	//执行完for还没进行下一步递归的话（说明存在能走的路，但都是桥）
			    path[count]=start+1;//记录路的开始节点
				count++;//标记符加1
			    lj[start][mark]=lj[mark][start]=0;//标记start->mark的桥
				start=mark;//mark为新路的开始节点
				Fleury(lj,path,start,n,count);//递归
				return;
    }



}
int main()
{
 //---------------------------create	
 int n;
 int start=0;//起点节点下标
 cout<<"输入元素节点个数："<<endl;
 cin>>n;
 vector<vector<int> > lj(n);//邻接矩阵
 for(int i=0;i<n;i++)
	  lj[i].resize(n);
 vector<vector<int> > kd(n);//邻接矩阵
 for(int i=0;i<n;i++)
	  kd[i].resize(n);
 vector<int > path(n*n,0);//记录路径的数组
 int count=0;//记录path标记
//----------------------------construct
  srand(unsigned int (time(NULL)));//生成邻接矩阵(无向图)
  for(int i=0;i<n;i++)
	  for(int j=i;j<n;j++)
		{if(i==j) 
			kd[i][j]=lj[i][j]=0;
		else 
			kd[i][j]=kd[j][i]=lj[j][i]=lj[i][j]=rand()%2;
        }
//---------------------------output
    cout<<"邻接矩阵："<<endl;
	  for(int i=0;i<n;i++)
	  {for(int j=0;j<n;j++)
		  cout<<lj[i][j]<<"  ";
	  cout<<endl;
	  }

	

 
//---------------------------------------cal and judge
  Warshell(kd,n);
  if(Is_in(0,kd,n))
    {cout<<"生成图不连通！"<<endl;
     system("pause");
     exit(0);
	
    }
  else
	  cout<<"生成图连通！"<<endl;

  start=Odd_node(lj,n);//取欧拉路起点（若存在）(注意，不是下标)，不存在则返回0；
  if(start)
    cout<<"该图存在欧拉（回）路！"<<endl;
  else
  {cout<<"该图不存在欧拉（回）路！"<<endl;
     system("pause");
     exit(0);
  }
  
//------------------------------------draw
  Fleury( lj,path,start-1, n,count);
  cout<<"欧拉（回）路："<<endl;
  for(int i=0; i<count;i++)
	  cout<<path[i]<<" ";
  cout<<endl;
  system("pause");
  return 0;
}