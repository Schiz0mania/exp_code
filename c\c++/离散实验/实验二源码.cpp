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
void cal_jiao(bool **p,bool **tmp, bool **use ,int n)//���󽻼��㣨��Ҫ�Ǿ����Գ�),ע�⴫��˳��----tmp�л�������
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
void cal_bing(bool **tmp,bool **pt2,int n)//��������
{
	for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)                                            
	   {pt2[i][j]=pt2[i][j] || tmp[i][j];
	   }
}
void cal_bing(bool **ps,int n)//���� ���ڶԳƱհ�����
{for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)                                            
	   {ps[i][j]=ps[i][j] || ps[j][i];
	   }


}
bool JudgeReflexivity( bool **p, int n)//�Է��뷴�Է�,�����Է��жϵĽ�������ڱհ����㣩
{int flag1=1;
 int flag2=1;
 for(int i=0;i<n;i++)
	 {  if(p[i][i] == 0)//�Է��ԣ����Խ�Ԫ��ȫΪ1
		   flag1=0;
	    if(p[i][i] == !0)//���Է��ԣ����Խ�Ԫ��ȫΪ0
		   flag2=0;
       }
 if(flag1)
	 cout<<"��ϵ��������Է���!\n";
 else
	 cout<<"��ϵ���󲻾����Է��ԣ�\n";
 if(flag2)
	 cout<<"��ϵ������з��Է���!\n";
 else
	 cout<<"��ϵ���󲻾��з��Է��ԣ�\n";
 if(flag1)
	 return true;
 else
	 return false;
}
bool JudgeSymmetry( bool **p, int n)//�Գ��뷴�Գƣ����ضԳ��жϵĽ�������ڱհ����㣩
{int flag1=1;
 int flag2 = 1;
 for(int i =0;i<n;i++)
	 for(int j=i+1;j<n;j++)
	 {if(p[i][j] != p[j][i])//�Գ��ԣ�����������Խ��߶Գ�
	   flag1=0;
	  if(p[i][j]&&p[j][i] == !0)//���Գ��ԣ��Գ�Ԫ�ز���ͬʱΪ1
		flag2=0;
	 }
if(flag1)
	 cout<<"��ϵ������жԳ���!\n";
 else
	 cout<<"��ϵ���󲻾��жԳ��ԣ�\n";
 if(flag2)
	 cout<<"��ϵ������з��Գ���!\n";
 else
	 cout<<"��ϵ���󲻾��з��Գ��ԣ�\n";
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
void Traditional(bool **pt2,bool **p,bool **tmp,bool **use,int n,int countnum)//���ݱհ����㴫ͳ�㷨
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
{ for(int i=0;i<n;i++)//ʹ��use�����ɵ�λ����
    for(int j=0;j<n;j++)
	  {if(i==j)
	     use[i][j]=1;
	  else use[i][j]=0;
	  }
 cal_bing(use,pr,n);
}
int main()
{ clock_t s1,s2,s3,e1,e2,e3;
  s1 = clock();//�ܼ�ʱ��ʼ
	
	
	//-----------------------creat
	int n;
	int countnum=0;
	cout<<"������������\n";
	cin>>n;
	bool **p=new bool *[n];  //ԭ����
	for(int i=0;i<n;i++)
		p[i]=new bool [n];

		bool **pr=new bool *[n];  //�Է��հ�����
	for(int i=0;i<n;i++)
		pr[i]=new bool [n];

		bool **ps=new bool *[n];  //�ԳƱհ�����
	for(int i=0;i<n;i++)
		ps[i]=new bool [n];

		bool **pt1=new bool *[n];  //���ݱհ����飨warshell��
	for(int i=0;i<n;i++)
		pt1[i]=new bool [n];

	
		bool **pt2=new bool *[n];  //���ݱհ����飨��ͳ��
	for(int i=0;i<n;i++)
		pt2[i]=new bool [n];


	    bool **tmp=new bool *[n];  //���ݱհ������м�����
	for(int i=0;i<n;i++)
		tmp[i]=new bool [n];    

	
	    bool **use=new bool *[n];  //��������
	for(int i=0;i<n;i++)
		use[i]=new bool [n];  


	//-----------------------input
	bool temp;
	cout<<"���������Ϣ��\n";
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
s2 = clock();//waeshell�㷨��ʱ��ʼ
Warshell(pt1,n);
e2= clock();//warshell �㷨��ʱ����


s3=clock();//��ͳ�հ��㷨��ʱ��ʼ
Traditional(pt2,p,tmp,use,n,countnum);	
e3=clock(); //��ͳ�հ��㷨��ʱ����


cal_reflex(pr,use, n);//�Է��հ�����

cal_bing(ps,n);//�ԳƱհ�����

//-----------------------judge
JudgeReflexivity(p,n);
JudgeSymmetry(p,n);

if(Is_equal(p,pt1,n))
	cout<<"��ϵ������д����ԣ�\n";
else cout<<"��ϵ���󲻾��д����ԣ�\n";

cout<<endl;


//-----------------------output
cout<<"���ִ��ݱհ��������Ƿ���ȣ�\n";
if(Is_equal(pt1,pt2,n)) cout<<"yes!"<<endl;
else cout<<"no!"<<endl;

cout<<"ԭ����\n"	;
Print(p,n);
cout<<"���ݱհ���\n";
Print(pt1,n);
cout<<"�Է��հ���\n";
Print(pr,n);
cout<<"�ԳƱհ���\n";
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
e1 = clock();//��ʱ����
cout << "Warshell algorithm run time is: " <<(double)(e2- s2)/ CLOCKS_PER_SEC << "s" << endl;
cout << "Traditional transitive closure operation run time is: " <<(double)(e3- s3)/ CLOCKS_PER_SEC << "s" << endl;
cout << "Tatol run time is: " <<(double)(e1 - s1)/ CLOCKS_PER_SEC << "s" << endl;
//---------------------------
system("pause");
return 0;}