#include<iostream>
#include<stdlib.h>
#include<string>
#include<time.h>
#include<vector>
using namespace std;
void Warshell(vector<vector<int> > & kd,int n)//�������ʵ����Ϊ�ڽӾ��󣨿�ʼʱkd��lj��ȣ�
{
 for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
	  if(kd[j][i] )
	     for(int k=0;k<n;k++)
		    kd[j][k] = kd[j][k] | kd[i][k];
	  
}
bool Is_in(int x,vector<vector<int> > & kd,int n)//���ܣ��ж�x�Ƿ��ھ����
{
	vector<vector<int> >::iterator it1;//�е�����
 vector<int>::iterator it2;//�е�����
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
int Odd_node(vector<vector <int>> &lj,int n)//��ȡͼ�������ڵ�ĸ�����������������0�������������ڵ㣨���һ��Ԫ�أ���ţ�.�����������0��
{ int result=1;
  int sum=0;
  int countodd=0;
  for(int i=0;i<n;i++)
	  {for(int j=0;j<n;j++)
	      sum+=lj[i][j];
       if(sum%2)//����Ϊ����
         {countodd++;
	      result=i+1;
         }
	   sum=0;
      }

  if(countodd == 0 || countodd ==2)
	  return result;
  else return 0;

}
bool Judge_Bridge(vector<vector<int> >  lj,int i,int j,int n)//�ж�i->j������·�Ƿ�Ϊ�ţ�ע�����Ϊ��ֵ��
{  
	lj[i][j]=lj[j][i]=0;
   Warshell(lj,n);
   //warshell������lj��Ϊ��ȥi->j��ͼ�Ŀɴ��Ծ���
   if(Is_in(0,lj,n))//��ȥ��ͼ���ɴ��i->j��·Ϊ��
     return true;
   else return false;

}
void Fleury( vector<vector<int> >  &lj,vector <int> &path,int start,int n, int &count)//���ŷ��·�ĸ������㷨
{   
	int mark=start;
	
	if ( !Is_in(1,lj[start],n))//�ýڵ���·����--�ݹ����
		
	  {  path[count]=start+1;
	     count++;
		 return ;
	  }
    else
	{ for(int j=0;j<n;j++)
		{if(lj[start][j])//�߹���
			if(Judge_Bridge(lj,start,j,n))//����
		         {mark=j;//�����
	              continue;
	             }
			else//�����ţ�����
			   {path[count]=start+1;//��¼·�Ŀ�ʼ�ڵ�
				count++;//��Ƿ�����
			    lj[start][j]=lj[j][start]=0;//���start->j��·
				start=j;//jΪ��·�Ŀ�ʼ�ڵ�
				Fleury(lj,path,start,n,count);//�ݹ�
				return;
			   }
		}

	//ִ����for��û������һ���ݹ�Ļ���˵���������ߵ�·���������ţ�
			    path[count]=start+1;//��¼·�Ŀ�ʼ�ڵ�
				count++;//��Ƿ���1
			    lj[start][mark]=lj[mark][start]=0;//���start->mark����
				start=mark;//markΪ��·�Ŀ�ʼ�ڵ�
				Fleury(lj,path,start,n,count);//�ݹ�
				return;
    }



}
int main()
{
 //---------------------------create	
 int n;
 int start=0;//���ڵ��±�
 cout<<"����Ԫ�ؽڵ������"<<endl;
 cin>>n;
 vector<vector<int> > lj(n);//�ڽӾ���
 for(int i=0;i<n;i++)
	  lj[i].resize(n);
 vector<vector<int> > kd(n);//�ڽӾ���
 for(int i=0;i<n;i++)
	  kd[i].resize(n);
 vector<int > path(n*n,0);//��¼·��������
 int count=0;//��¼path���
//----------------------------construct
  srand(unsigned int (time(NULL)));//�����ڽӾ���(����ͼ)
  for(int i=0;i<n;i++)
	  for(int j=i;j<n;j++)
		{if(i==j) 
			kd[i][j]=lj[i][j]=0;
		else 
			kd[i][j]=kd[j][i]=lj[j][i]=lj[i][j]=rand()%2;
        }
//---------------------------output
    cout<<"�ڽӾ���"<<endl;
	  for(int i=0;i<n;i++)
	  {for(int j=0;j<n;j++)
		  cout<<lj[i][j]<<"  ";
	  cout<<endl;
	  }

	

 
//---------------------------------------cal and judge
  Warshell(kd,n);
  if(Is_in(0,kd,n))
    {cout<<"����ͼ����ͨ��"<<endl;
     system("pause");
     exit(0);
	
    }
  else
	  cout<<"����ͼ��ͨ��"<<endl;

  start=Odd_node(lj,n);//ȡŷ��·��㣨�����ڣ�(ע�⣬�����±�)���������򷵻�0��
  if(start)
    cout<<"��ͼ����ŷ�����أ�·��"<<endl;
  else
  {cout<<"��ͼ������ŷ�����أ�·��"<<endl;
     system("pause");
     exit(0);
  }
  
//------------------------------------draw
  Fleury( lj,path,start-1, n,count);
  cout<<"ŷ�����أ�·��"<<endl;
  for(int i=0; i<count;i++)
	  cout<<path[i]<<" ";
  cout<<endl;
  system("pause");
  return 0;
}