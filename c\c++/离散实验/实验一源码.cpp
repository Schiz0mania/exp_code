#include<iostream>
#include<map>
#include<stack>    
using namespace std;     //                      优先级：  非        5    ！       
char bds[50]={"0"}; //原表达式                             析取      4    &
stack <char> hz;//后缀表达式栈 (逆序）                      合取      3    |
int flag=1;              //                               条件      2    >   
stack <char> oper;//操作符  栈                             双条件    1    ~ 
char var[10];//不超过10个变元储存在这
int num=0;   //变元个数
stack <char> pf;//后缀表达式（正序）以便于计算
stack <char> ans;//结果在这里
int table[1025][1025];//变元赋值情况表（不多于10个变元）
stack <int> Tstc;//存放表达式为真时的row情况，推到table中row行各变元的赋值情况 
stack <int> Fstc;//同上
int row = 0;// 行标记值
map<char,int> link;
void Input()
{cout<<"欢迎使用本计算系统！（支持10个以内变元的计算）\n";
 cout<<"输入变元个数(不大于10)"<<endl;
 cin>>num;
 while(num<1 || num>10)
 {cout<<"请重新输入变元个数：\n";
  cin>>num;
 }  
cout<<"输入单个变元(大写,不加空格)"<<endl;
for(int n=0;n<=num-1;n++)
	cin>>var[n];
 cout<<"本系统操作符规定如下："<<endl;
 cout<<"非     ！ "<<endl;
 cout<<"合取     &"<<endl;
 cout<<"析取       |"<<endl;
 cout<<"条件         >   "<<endl;
 cout<<"双条件        ~ "<<endl;
cout<<"输入需要计算的表达式（以“#”结尾）:\n";
}
void assign(int num)//变元赋值
{
	
    for(int i = 0; i < (1<<num); i++) //从0～2^n-1个状态
    {
        for(int j = 0; j < num; j++) //遍历二进制的每一位
        {
            if(i & (1 << j))//判断二进制第j位是否为1
            {
                table[i][j]=1;//如果为1，赋值table相应赋为1
            }
        }
        
    }

}  
int rate(char c)//运算优先级
{switch(c)
{case 33:     //  !
     return 5;
case 38:      // &   
	return 4;
case 124:     // |
	return 3;
case 62:      //  >
	return 2;
case 126:     //  ~
	return 1;
default :return 0;//  两个括号
}	
}
void trans(char c)//转化表达式
{if(c>=65 && c<=90)//为大写字母,直接入栈
   {hz.push(c);
   return ;}
 if(c == 35) //  #
   {while(!oper.empty())
        {hz.push(oper.top());
         oper.pop();
         }
    flag=0;//式子结束,flag赋值为0，hz完备
	return;
   }
//运算符的话
switch (c)
{  case 40:// 左括号直接入栈
      oper.push(c);
      return ;
  case  33:// ! 优先级最高 
	  oper.push(c);
	  return ;
  default: 
	  if(oper.empty() )//栈空 只要输入正确，肯定不会出现右括号入空栈
		  {oper.push(c);       
	         return;}
     if(rate(oper.top()) <= rate(c) ) oper.push(c);//优先级大的直接入栈
		  else//需要复杂操作的
		    {
				
				while( (!oper.empty()) && (oper.top() != 40)   )//栈顶不是左括号 或者 栈没空
		         {hz.push(oper.top());
	              oper.pop();
		          }
	           if(oper.top() ==40)//弹到左括号处停
				   {oper.pop();
			        return ;}
			   if(oper.empty())
				   {oper.push(c);
			         return ;}
		    }
		  }

}
void cal(int count,char *pfarr)//传了个后缀表达式数组过来计算------------------------这个函数一次只计算一种赋值下的表达式值
{    char a=char("T");
     char b=char("F");
	 char temp;
	for(int i=count-1;i>=0;i--)//建立计算栈pf
       pf.push(pfarr[i]);   
	for(int i=0;i<=num-1;i++)
       link[var[i]]=table[row][i];//建立映射关系，在row行（row+1为第row+1个变元赋值情况）下，第i个变元对应table里i列的赋值情况
	
	while(!pf.empty())
	{      if((pf.top()>=65)&&(pf.top()<=90))//字母直接入ans栈
	            ans.push(pf.top());                          
	       else//运算符的情况分类
		   {     switch(pf.top())
                   {case 33://  !  一元
	                     if(link[ans.top()])//变元对应赋值为真,压栈值则为"F"
						   {ans.pop();
					        ans.push(b);
					        }
					     else 
						  {ans.pop();
						   ans.push(a);
						  }
	                   break;
				   //二元，两个操作数，每次pop两次
				   case 38://&  逻辑和
					   temp=ans.top();
					   ans.pop();//pop 1
					      if(!link[temp] || !link[ans.top()])//有一个为假
					         {ans.pop();//pop2
					          ans.push(b);
					          }
					      else
					         {ans.pop();//pop2
					         ans.push(a);
					         }
	                    break;
				   case 124:// |  逻辑或
					   temp=ans.top();
					   ans.pop();
					     if(link[temp] || link[ans.top()])//一个为真
					        {ans.pop();
					         ans.push(a);
					        }
					      else
					        {ans.pop();
					        ans.push(b);
					        }
						 break;
				   case 62://  >  条件
					   temp=ans.top();//这个时后操作数
					   ans.pop();
					     if(link[ans.top()])//这里注意逻辑短路 后假前真
					         {if(! link[temp])//唯假情况
						       {ans.pop();
					            ans.push(b);
						       }
							  else 
							   {ans.pop();
					            ans.push(a);
					            }
						      }
					     else {ans.pop();
					          ans.push(a);
						      }
							 break;
				   case 126:// ~ 双条件
					   temp=ans.top();
					   ans.pop();
					     if (link[temp] == link[ans.top()])//赋值情况相同为真
					        {ans.pop();
					         ans.push(a);
					         }
					     else
					       {ans.pop();
					        ans.push(b);
					       }
	                    break;
	             }
	       }
	pf.pop();//统一在这里弹pf的栈顶

	}
  //最后ans栈里只有一个字符，对应这表达式的真假值
	if(link[ans.top()])//表达式为真
		Tstc.push(row);//建立表达式为真  变元赋值情况 的隐形对应
	else 
		Fstc.push(row);
	ans.pop();//清空
	row++;//下一次运算取下一种变元赋值情况
}
void Output(int num)//实参：变元个数
{ // ∧   ¬ ∨	
	cout<<endl;
	int count=1;//小项个数
	cout<<"主析取范式：\n";
		if( Tstc.empty()) cout<<"\t无主析取和式！\n";
		while(! Tstc.empty())
		{  if(count!=1) 
		      cout<<"∨";
		   cout<<"(";
		   for(int i=0;i<=num-1;i++)
		      { if(table[Tstc.top()][i])
				  cout<<var[i];
			    else 
				  cout<<"!"<<var[i];

			    if(i+1 != num)
			 	 cout<<"∧";
		      }
		  cout<<")";
		  Tstc.pop();
		  count++;
		 }
		cout<<endl;
		count=1;
	cout<<"主合取范式：\n";
		if( Fstc.empty()) cout<<"\t无主合取范式！\n";
		while( ! Fstc.empty() )
		 {   if(count!=1) 
		        cout<<"∧";
		     cout<<"(";
		     for(int i=0;i<=num-1;i++)
		         { if(!table[Fstc.top()][i])
		               cout<<var[i];
		           else 
					   cout<<"!"<<var[i];

		           if(i+1 != num)
			          cout<<"∨";
		         }
		   cout<<")";
		   Fstc.pop();
		   count++;
         }
	cout<<endl;	 
	cout<<"运算结束，谢谢使用！\n";
}
void main()
{//------------------------------------------------Input------------------------------------------------
 Input();
//------------------------------------------------assign（变元赋值）------------------------------------------------
 assign(num);
//------------------------------------------------trans（中缀转后缀）------------------------------------------------
 int i;
 for(i=0;(i<=49)&&flag;i++)//该循环结束后hz中为目标表达式的逆序（按出栈顺序）
     {   cin>>bds[i];
         trans(bds[i]);      
     }
 //后缀表达式转入pfarr数组里
 int count=int(hz.size());//也就是pfarr 元素个数
 char *pfarr= new char[hz.size()];//
 if(pfarr==NULL)
 {cout<<"Allocation failed!"<<endl;
  exit(1);}
 for(int i=hz.size()-1;i>=0;i--) //令pfarr里有正序的后缀表达式
	   {pfarr[i]=hz.top();
        hz.pop();
       }
//------------------------------------------------cal（计算表达式的真值情况）------------------------------------------------
link[char("T")]=1;
link[char("F")]=0;
for(int time=1;time<=(1<<num);time++)
  cal( count ,pfarr);
//------------------------------------------------Output------------------------------------------------
Output(num);
delete []pfarr;
}





 


