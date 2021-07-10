#include<iostream>
using namespace std;
int countnum;
//构造邻接矩阵
void Divisibility(int *p1,int total,bool **p2,bool **p3)//判断整除关系，搭建邻接矩阵(这里就已经去掉了自反关系了)
{for(int i=0;i<total;i++)
	for(int j=i+1;j<total;j++)
	{  if(p1[j]%p1[i]==0)
	      {p2[i][j]=p3[i][j]=true;
            countnum++;//记录邻接矩阵元素个数
		}
	}

	
}
void cal_jiao(bool **p,bool **tmp, bool **cal ,int n)//矩阵交计算（p-原邻接矩阵，tmp-依次存放p的k次方，use-中间过渡
{  bool mid=0;
	for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
		   {for(int k=0;k<n;k++)
	            {mid=mid || (tmp[i][k] && p[k][j]);}
	        cal[i][j]=mid;
	        mid=0;
	        }

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		tmp[i][j]=cal[i][j];
}
void Print(bool **p,int total)
{for(int i=0;i<total;i++)
		{for(int j=0;j<total;j++)
			cout<<p[i][j]<<" ";
	  cout<<endl;    
	  }
cout<<endl;
}
int GLB(int a,int b)//下确界函数---------两者最大公约数(a>b)
{if(b)
  return GLB(b,a%b);
else
	return a;
}
int LUB(int a,int b)//上确界函数-------两者最小公倍数
{
	return (a*b)/GLB(a,b);
}
bool Is_in(int x,int *p,int total )//寻找x是否在p数组里
{for(int i=0;i<total;i++)
   if(p[i]==x) return true;
 return false;

}
bool Judge_lattice(int *p ,int total)
{int  flag1=1;
 int  tflag1=0;
 int  flag2=1;
 int tflag2=0;
  for(int i=0;i<total-1;i++)
	for(int j=i+1;j<total;j++)
	{  for(int k=j;(k<total) && (!tflag1);k++)//是否存在上确界
	       if( p[k]>=LUB(p[j],p[i]) && p[k]%LUB(p[j],p[i])==0  )
		   tflag1=1;
	  for(int k=i;(k>=0) && (!tflag2);k--)//是否存在下确界
	     if( (p[k]<=GLB(p[j],p[i]))&&(GLB(p[j],p[i])%p[k]==0) )
			 tflag2=1;
	flag1= flag1 && tflag1;
	flag2 = flag2 && tflag2;
	tflag1=tflag2=0;
	
	}
 if(flag1 && flag2)
	 return true;
 else return false;
	 


}
bool Judge_bounded(int *p,int total)
{int flag1=1;
 int flag2=1;
	for(int i=0;i<total;i++)
	{if(p[total-1]%p[i] !=0)//最大元
	      flag1=0;
	 if(p[i]%p[0] !=0)
		flag2=0;
	}
if(flag1 && flag2)
	return true;
else return false;

}
bool Judge_complemented(int *p,int total)
{ int *mark =new int [total];//标记是否有补元(针对最大下界)

 for(int i=0;i<total;i++)
	 mark[i]=0;
 
  for(int i=0;i<total-1 ;i++)
	  for(int k=i+1;k<total ;k++)
	  {   if(Is_in(GLB(p[k],p[i]),p,total) && GLB(p[k],p[i])==p[0])//两元素下确界满足关系，进入判断上确界是否也满足 若满足 mark赋值为1（表示两元素互为补元）
	         {  if(Is_in(LUB(p[k],p[i]),p,total) && LUB(p[k],p[i])==p[total-1])
				        mark[i]=mark[k]=1;
			    if(!Is_in(LUB(p[k],p[i]),p,total))
				    if(LUB(p[k],p[i])<=p[total-1] && p[total-1]%LUB(p[k],p[i])==0)
					     mark[i]=mark[k]=1;
	           }
	  
	          
       if(!Is_in(GLB(p[k],p[i]),p,total))
	       if(GLB(p[k],p[i])>=p[0] && GLB(p[k],p[i])%p[0]==0)    
		   {    if(Is_in(LUB(p[k],p[i]),p,total) && LUB(p[k],p[i])==p[total-1])
		                mark[i]=mark[k]=1;
				if(!Is_in(LUB(p[k],p[i]),p,total))
		              if(LUB(p[k],p[i])<=p[total-1] && p[total-1]%LUB(p[k],p[i])==0)
			             mark[i]=mark[k]=1;
		   
		   
		   }
	  }
 
 bool tmp= Is_in(0,mark,total);
 delete [] mark;
 return !tmp;
}
int main()
{ //----------------------------------------------------input
  int total=0;
  cout<<"输入论域元素个数：\n";
  cin>>total;
  int  *p =new int [total];
  cout<<"升序输入论域元素：\n";
  for(int i=0;i<total;i++)
	  cin>>p[i];
  //----------------------------------------------------create
	bool **lj=new bool *[total];  //邻接矩阵
	for(int i=0;i<total;i++)
		lj[i]=new bool [total];  
	
	
	bool **tmp=new bool *[total];  //用于缓存数据
	for(int i=0;i<total;i++)
		tmp[i]=new bool [total];  


	for(int i=0;i<total;i++)//初始化
		for(int j=0;j<total;j++)
			{if(i == j)
	           lj[i][j]=tmp[i][j]=1;
			 lj[i][j]=tmp[i][j]=0;
	       }

	bool **cal=new bool *[total];  //用于计算
	for(int i=0;i<total;i++)
		cal[i]=new bool [total];  

	bool **cov=new bool *[total];  //盖住关系矩阵
	for(int i=0;i<total;i++)
		cov[i]=new bool [total]; 
	

 //----------------------------------------------------construct cov
	Divisibility(p,total,lj,tmp);
	for(int i=0;i<total;i++)//对cov简单初始化
		for(int j=0;j<total;j++)
		{if(lj[i][j]==0)
		  cov[i][j]=0;
		else 
			if(i==j) cov[i][j]=0;
			else cov[i][j]=1;
		}
	for(int i=2;i<=countnum;i++)//计算cov关系矩阵
		{cal_jiao(lj,tmp,cal ,total);
		  for(int j=0;j<total;j++)
			  for(int k=0; k<total;k++)
			  {    if((tmp[j][k])&&(cov[j][k]))
					  cov[j][k]=false;         
			    }
	     }
//----------------------------------------------------output cov

	cout<<"cov<>={ ";
	for(int i=0;i<total;i++)
		for(int j=0;j<total;j++)
		{if(cov[i][j])
		cout<<" <"<<p[i]<<","<<p[j]<<"> ";
		}
		cout<<"}"<<endl;
//----------------------------------------------------judge

if(Judge_lattice(p,total))
	cout<<"该偏序关系是格！"<<endl;
else
	{cout<<"该偏序关系不是格！"<<endl;
    system("pause");
    exit(1);
    }

//
	if(Judge_bounded(p,total))
	cout<<"该偏序关系是有界格！"<<endl;
else
	{cout<<"该偏序关系不是有界格！"<<endl;
    system("pause");
    exit(1);
    }

//
if(Judge_complemented(p,total))
	cout<<"该偏序关系是有补格！"<<endl;
else
	{cout<<"该偏序关系不是有补格！"<<endl;
    system("pause");
    exit(1);
    }





//----------------------------------------------------delete
	for(int i=0;i<total;i++)
		delete [] cov[i];
	delete [] cov;

	for(int i=0;i<total;i++)
		delete [] cal[i];
	delete [] cal;

	
	for(int i=0;i<total;i++)
		delete [] tmp[i];
	delete [] tmp;

	for(int i=0;i<total;i++)
		delete [] lj[i];
	delete [] lj;
	
	delete [] p;

	system("pause");
	return 0;
}