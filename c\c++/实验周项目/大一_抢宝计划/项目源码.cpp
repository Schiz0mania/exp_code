#include<iostream>
#include<stdio.h>
#include<string>
#include<ctime>
#include<time.h>
#include<fstream>
#include<iomanip>
#include<map>
#include<thread>
#include<mutex>
#include<Windows.h>
using namespace std;//------------------------------------------------------------输入不得有空格
map <string, int >link;//解决  读入内存时购物车类的库存信息为0  
int num;//----------------促销、商品信息个数
string USERNAME_PATH = "0";//根据用户名生成的路径
string id;//用户名
int c;//各种选择
int countnum;//------------------------------文件读入购物车物品数量
int endsign = 0;//结束标志 共享资源--由thread1结束时赋值为1，thread2进行只读操作，为thread2 的结束标志
int searchflag = 1;//查找是否成功
typedef struct
{
	string Type;//商品类型
	string name;//商品名
	string G_desc;//商品描述
	double price;//价格
	int store;//库存
	string name2;//店名
}Goods;
typedef struct
{
	Goods good;
	int num;//数量
	double cutprice;//促销后的价格（默认值为商品原价*数量  这是使用促销后的总价）
}UserGoods;
class Sales
{
public:
	string code;//促销编码
	double k1;//促销关键数据一号   促销阈值  /  打折力度
	double k2;//促销关键数据二号   促销减额  /   0不储存数据
	Goods obj;//促销对象
	string desc;//促销描述（自然语言）
	tm starttime;//促销开始时间  仅考虑 时分秒！
	string ShopName;//促销商家名
	void Search(int);//查询函数  关键词 商品名    择 1    选择码为第一参
						 // 关键词 商家名（不需要传参）选择2
	bool Judge(UserGoods& us, int i);//判断商品是否符合促销条件  i为促销信息的序号  i-1才是数组下标
	void Cut(UserGoods& us, int i);//计算商品使用促销后的价格	
	friend ostream& operator <<(ostream& out, const Sales& s);
	friend istream& operator >>(istream& in, const Sales& s);
};

class user
{
private:
	string ID;
	string Name;
	string Email;
	string Password;
public:
	user() {};
	void Register();
	void Enter();
};

class Admin :public user
{
public:
	void Enter()
	{
		ifstream fin("C:\\抢宝计划\\AdminInfo.txt", ios::in);
		if (!fin)
		{
			cout << "无法连接服务器";
			return;
		}

		string textline[200];//欲读200行，自己定义 
		int j = 0;
		for (; !fin.eof();)
		{
			getline(fin, textline[j], '\n');
			j++;
		}
		cout << "\t\t*****************************" << endl;
		cout << "\t\t\t请输入您的ID：";
	flag1:
		string id;
		string pwd;
		cin >> id;
		int tk = 1;
		for (int i = 0; i < 200; i++)
		{
			//验证ID是否存在
			tk++;
			if ((i % 2) != 0) continue;//排除掉密码行
			if (textline[i] == id)
			{
				tk = 2;
				cout << "\t\t\t请输入您的密码：";
			flag2:
				cin >> pwd;
				if (textline[i + 1] != pwd)
				{
					cout << "\t密码错误，请重新输入:";
					goto flag2;
				}
				cout << "\t登录成功！" << endl;
				break;
			}
		}
		if (tk > 200)
		{
			cout << "\t该ID不存在，请重新输入:";
			goto flag1;
		}
	}
};

Sales s[100];//促销信息
Goods g[100];//商品信息
UserGoods us[100];//购物车

bool Judge_time(tm& t1, tm& t2)//第一为比较标准，即促销开始时间，第二个为当前时间
{
	if (t2.tm_hour > t1.tm_hour)
		return true;
	if (t2.tm_hour == t1.tm_hour)
		if (t2.tm_min > t1.tm_min)
			return true;
	if (t2.tm_min == t1.tm_min)
		if (t2.tm_sec >= t1.tm_sec)
			return true;
	return false;


}

bool Sales::Judge(UserGoods& us, int i)//M-93  D-84---促销问题  先提供可用促销（调用促销搜索函数） 再由用户选择
{
	int flag1 = 1;
	int flag2 = 1;
	int flag3 = 1;
	time_t tmptime;
	struct tm p;
	time(&tmptime); //获取从1970至今过了多少秒，存入time_t类型的timep
	localtime_s(&p, &tmptime);//用localtime将秒数转化为struct tm结构体
	if (Judge_time(s[i - 1].starttime, p))
		flag1 = 1;
	else flag1 = 0;


	if (!s[i - 1].code.compare(string("D")))//促销为打折类-
	{
		if (!s[i - 1].obj.name.compare(us.good.name))
		{
			flag2 = 1;
			return flag1 && flag2;
		}
		else
		{
			flag2 = 0;
			return flag1 && flag2;
		}
	}
	if (!s[i - 1].code.compare(string("M")))//促销为满减类
	{
		if (!s[i - 1].obj.name.compare(us.good.name))  //需要商品名一致
		{
			if ((us.num * us.good.price) < s[i - 1].k1)  //未达到促销阈值
			{
				flag3 = 0;
				return flag1 && flag3;
			}
			else
			{
				flag3 = 1;
				return flag1 && flag3;
			}
		}
		else
		{
			flag3 = 0;
			return flag1 && flag3;
		}
	}
}

void Sales::Cut(UserGoods& us, int i)
{
	if (Judge(us, i))
	{
		if (!s[i - 1].code.compare(string("D")))
			us.cutprice = us.num * us.good.price * s[i - 1].k1 * 0.1;
		if ((!s[i - 1].code.compare(string("M"))))
			us.cutprice = us.num * us.good.price - s[i - 1].k2;

		cout << "\t促销使用完成！\n";

	}
	else
		cout << "\t促销条件不满足！\n";
}

void Sales::Search(int c)//大循环遍历在主函数中进行
{
	cout << "*****************************************" << endl;
	switch (c)
	{
	case 1:
	{
		//商品名查找----------------------------
		int flag = 0;
		string tmp;
		cout << "\t输入商品名：\t";
		cin >> tmp;
		for (int i = 0; i <= num - 1; i++)
			if (!(tmp.compare(s[i].obj.name)))
			{
				cout << "\t匹配促销信息如下：" << endl;
				cout << "\t第" << i + 1 << "条、" << s[i].ShopName << " " << s[i].obj.name << " " << s[i].desc << endl;
				flag = 1;
			}
		if (!flag)
		{
			cout << "\t无匹配信息！\n";
			searchflag = 0;//标记未找到

		}
		break;
	}

	case 2:
	{
		//商家查找------------------
		int flag = 0;
		string tmp;
		cout << "\t输入商家名：\t";
		cin >> tmp;
		for (int i = 0; i <= num - 1; i++)
			if (!(tmp.compare(s[i].ShopName)))
			{
				cout << "\t匹配促销信息如下：" << endl;
				cout << "\t第" << i + 1 << "条、" << s[i].ShopName << " " << s[i].obj.name << " " << s[i].desc << endl;
				flag = 1;
			}
		if (!flag)
		{
			cout << "\t无匹配信息！\n";
			searchflag = 0;//标记未找到
		}
		break;
	}
	}

}

bool Is_cut(UserGoods& us)//是否已使用促销
{
	if (us.good.price * us.num == us.cutprice)return false;
	else return true;
}

istream& operator >>(istream& in, Sales& s)//重载>>运算符 对象为促销类
{
	in >> s.code
		>> s.k1
		>> s.k2
		>> s.obj.Type
		>> s.obj.name
		>> s.obj.G_desc
		>> s.obj.price
		>> s.obj.store
		>> s.desc
		>> s.starttime.tm_hour
		>> s.starttime.tm_min
		>> s.starttime.tm_sec
		>> s.ShopName;
	return in;
}

ostream& operator <<(ostream& out, const Sales& s)// << 对 促销类的重载
{
	out << s.code << endl
		<< s.k1 << endl
		<< s.k2 << endl
		<< s.obj.Type << endl
		<< s.obj.name << endl
		<< s.obj.G_desc << endl
		<< s.obj.price << endl
		<< s.obj.store << endl
		<< s.desc << endl
		<< s.starttime.tm_hour << endl
		<< s.starttime.tm_min << endl
		<< s.starttime.tm_sec << endl
		<< s.ShopName << endl;
	return out;
}

istream& operator >>(istream& in, Goods& g)
{
	in >> g.Type >> g.name >> g.G_desc >> g.price >> g.store;
	return in;
}

ostream& operator <<(ostream& out, const Goods& g)// << 对 商品信息（商品结构数组）的重载
{
	out << g.Type << endl
		<< g.name << endl
		<< g.G_desc << endl
		<< g.price << endl
		<< g.store << endl;
	return out;
}

istream& operator >>(istream& in, UserGoods& us)
{
	in >> us.good.Type >> us.good.name >> us.good.G_desc >> us.good.price >> us.num;
	return in;
}

ostream& operator <<(ostream& out, const UserGoods& us)//对购物车信息录入的重载
{
	out << us.good.Type << endl
		<< us.good.name << endl
		<< us.good.G_desc << endl
		<< us.good.price << endl
		<< us.num << endl;
	return out;
}

void ReadInfo()
{

	ifstream ifile1("C:\\抢宝计划\\sales.txt", ios::in);//促销信息写入内存
	if (!ifile1)
	{
		cout << "文件打开失败！\n";
		exit(1);
	}
	ifile1 >> num;
	for (int i = 0; i <= num - 1; i++)
		ifile1 >> s[i];
	ifile1.close();

	ifstream ifile2("C:\\抢宝计划\\goods.txt", ios::in);//商品信息写入内存
	if (!ifile2)
	{
		cout << "文件打开失败！\n";
		exit(1);
	}
	ifile2 >> num;
	for (int i = 0; i <= num - 1; i++)
		ifile2 >> g[i];
	ifile2.close();

	for (int i = 0; i <= num - 1; i++)
	{
		g[i].store = s[i].obj.store;
		g[i].name2 = s[i].ShopName;
		link[g[i].name] = g[i].store;//建立map容器
	}
}

void ReadCharts()
{
	ifstream ifile3(USERNAME_PATH, ios::in);//购物车信息写入内存
	if (USERNAME_PATH == "0") {}
	else
	{
		if (!ifile3)
		{
			cout << "购物车文件打开失败！\n";
			exit(1);
		}
	}

	ifile3 >> countnum;
	for (int i = 0; i <= countnum - 1; i++)
		ifile3 >> us[i];
	ifile3.close();
	for (int i = 0; i <= countnum - 1; i++)
	{
		us[i].good.store = link[us[i].good.name];
		us[i].cutprice = us[i].good.price * us[i].num;

	}

}

void InputInfo()
{
	//录入
	//-------------------先输入在内存里，调用结束前写入文件
	int numtep;//新增的信息条数
	int temp = num;//原有信息条数
	cout << "\t\t输入促销信息条数:\n";
	cout << "\t\t";

	cin >> numtep;
	cout << "*****************************************" << endl;
	num += numtep;//------------------------------------num表示总促销数（文件读入内存后）
	if (numtep)
		for (int i = temp; i <= num - 1; i++)//写入内存(app法加进数组)
		{
			int a;//促销code选择
			cout << "\n\t\t选择促销类型：\n";
			cout << "\t\t1、满xx减xx\n";
			cout << "\t\t2、一律打xx折\n";
			cout << "\t\t";
			cin >> a;
			cout << "*****************************************" << endl;
			if (!(a - 1))//选1
			{
				s[i].code = "M";
				int t1, t2;
				cout << "\t\t输入价格阈值：\t";
				cin >> t1;
				s[i].k1 = t1;
				cout << "\n\t\t输入满减额度：\t";
				cin >> t2;
				s[i].k2 = t2;
				cout << "\n";
				cout << "*****************************************" << endl;
			}
			else//选2
			{
				s[i].code = "D";
				int t1;
				cout << "\t\t输入打折力度（x折）：\t";
				cin >> t1;
				s[i].k1 = t1;
				cout << "\n";
				cout << "*****************************************" << endl;
			}
			string t1;
			double t2;
			int t3;
			cout << "\t\t输入商品类型(A B C)：" << "\t";
			cin >> t1;
			s[i].obj.Type = t1;
			g[i].Type = t1;
			cout << "\n\t\t输入商品名称：" << "\t";
			cin >> t1;
			s[i].obj.name = t1;
			g[i].name = t1;
			cout << "\n\t\t输入商品细节描述：" << "\t";
			cin >> t1;
			s[i].obj.G_desc = t1;
			g[i].G_desc = t1;
			cout << "\n\t\t输入商品价格：" << "\t";
			cin >> t2;
			s[i].obj.price = t2;
			g[i].price = t2;
			cout << "\n\t\t输入对象商品限额（库存）：" << "\t";
			cin >> t3;
			s[i].obj.store = t3;
			g[i].store = t3;
			cout << "\n\t\t输入促销信息：" << "\t";
			cin >> t1;
			s[i].desc = t1;
			cout << "\n\t\t输入促销时间（时 分 秒）：" << "\t";//------有时间加一个输入控制
			int time1, time2, time3;
			cin >> time1 >> time2 >> time3;
			s[i].starttime.tm_hour = time1;
			s[i].starttime.tm_min = time2;
			s[i].starttime.tm_sec = time3;



			cout << "\n\t\t输入促销商家：" << "\t";
			cin >> t1;
			s[i].ShopName = t1;
			system("CLS");//-------------------------------------------------------------------------------------------------------------------
		}

}

void WriteInfo()
{
	ofstream ofile1("C:\\抢宝计划\\sales.txt", ios::out);//----------------------------------------应该用覆盖写入
	if (!ofile1)
	{
		cout << "目标文件打开失败！\n";
		exit(0);
	}
	ofile1 << num << endl;
	for (int i = 0; i <= num - 1; i++)//促销信息写入文件
	{
		ofile1 << s[i];
	}
	ofile1.close();
	//--------
	ofstream ofile2("C:\\抢宝计划\\goods.txt", ios::out);
	if (!ofile2)
	{
		cout << "目标文件打开失败！\n";
		exit(0);
	}
	ofile2 << num << endl;
	for (int i = 0; i <= num - 1; i++)//商品信息写入文件
	{
		ofile2 << g[i];
	}
	ofile2.close();
	//---------
	ofstream ofile3(USERNAME_PATH.c_str(), ios::out);//购物车信息写入文件
	if (!ofile3)
	{
		cout << "\t购物车文件打开失败！" << endl;
		exit(0);
	}
	ofile3 << countnum << endl;
	for (int i = 0; i <= countnum - 1; i++)
		ofile3 << us[i];
	ofile3.close();
}

void Carts(int m)
{//购物车管理

	switch (m)
	{
	case 1://添加物品
	{cout << "\t\t可选商品如下：" << endl;
	cout << "*****************************************" << endl;
	if (!num)
		cout << "\t\t\t无可选商品！\n";
	else
	{
		for (int i = 0; i <= num - 1; i++)
			cout << "\t" << i + 1 << "、  " << g[i].Type << "类  " << g[i].name << endl << "\t" << g[i].G_desc << endl << "\t价格：\t" << g[i].price << endl << "\t库存：\t" << g[i].store << "\n" << endl;

		int n;
		cout << "*****************************************" << endl;
		cout << "\t输入你的选择(结束请输-1)：\t";
		cin >> n;
		while (n != -1)
		{
			while (!((n >= 0) && (n <= num)))//num 是促销(商品)数量上限
			{
				cout << "\t请输入有效数字！\n";
				cin >> n;
				cout << "*****************************************" << endl;
			}
			//-确保countnum<=10  !!!!         -----------------------test
			us[countnum].good.Type = g[n - 1].Type;
			us[countnum].good.name = g[n - 1].name;
			us[countnum].good.price = g[n - 1].price;
			us[countnum].good.store = g[n - 1].store;
			us[countnum].good.G_desc = g[n - 1].G_desc;
			//录入UserGoods的Goods部分的信息录入

			cout << "\t输入数量：\t";//----------------------------个数要小于库存        补充！！！！
			int num;//局部重名
			cin >> num;
			while (!(num >= 0 && num <= g[n - 1].store))
			{
				if (num < 0) cout << "\t请输入有效数字！\n";
				cout << "*****************************************" << endl;
				if (num > g[n - 1].store) cout << "\t库存不足！\n";
				cin >> num;
			}
			us[countnum].num = num;
			us[countnum].cutprice = us[countnum].num * us[countnum].good.price;//初始化促销价格
			cout << "\t继续添加购物车（结束输-1）：\t" << endl;
			cin >> n;
			countnum++;

		}
	}
	break;
	}
	case 3://购物车打印
	{

		if (!countnum)
			cout << "\t\t您的购物车为空！\n";
		else
		{
			cout << "\t购物车商品如下：\n";
			cout << "*****************************************" << endl;
			for (int i = 0; i <= countnum - 1; i++)
				cout << "\t" << i + 1 << "、  " << us[i].good.name << endl << "\t价格：  " << us[i].good.price << endl << "\t个数：  " << us[i].num << endl << "\t库存：" << us[i].good.store << "\n" << endl;
			cout << "*****************************************" << endl;
		}
		break;
	}
	case 2://修改 删除
	{if (!countnum)
		cout << "\t\t购物车为空！" << endl;
	else
	{
		cout << "\t\t购物车商品如下：\n";
		cout << "*****************************************" << endl;
		for (int i = 0; i <= countnum - 1; i++)
			cout << "\t" << i + 1 << "、  " << us[i].good.name << endl << "\t价格：  " << us[i].good.price << endl << "\t个数：  " << us[i].num << "\n" << endl;
		cout << "*****************************************" << endl;
		int n;
		cout << "\t\t输入修改目标序号(退出按-1)：\n";
		cin >> n;//n-1 为购物车数组下标
		while (n != -1)
		{
			while (!((n > 0) && (n <= countnum)))
			{
				cout << "\t请输入有效数字！\n";
				cin >> n;
			}
			int delt;
			cout << "\t输入改变值：";
			cin >> delt;
			while ((delt + us[n - 1].num) < 0 || ((delt + us[n - 1].num) > us[n - 1].good.store))
			{
				if ((delt + us[n - 1].num) < 0)cout << "\t\t出现负操作！请重新输入\n";
				if ((delt + us[n - 1].num) > us[n - 1].good.store)cout << "\t\t库存不足！请重新输入\n";
				cin >> delt;
			}
			us[n - 1].num += delt;
			if (us[n - 1].num == 0)
			{
				cout << "\t\t目标商品已删除！\n";
				//---------------------------------------------------------------------数组进位操作，countnum--
				for (int i = n - 1; i <= countnum - 1 - 1; i++)
					us[i] = us[i + 1];
				//us[countnum-1]={0};------------------------------------清空操作 可有可无
				countnum--;
			}
			if (!countnum)
			{
				cout << "\t\t购物车已空！" << endl;
				n = -1;
			}
			else
			{
				system("CLS");
				cout << "\t\t修改后购物车商品如下：\n";
				cout << "*****************************************" << endl;
				for (int i = 0; i <= countnum - 1; i++)
					cout << "\t" << i + 1 << "、  " << us[i].good.name << endl << "\t价格：  " << us[i].good.price << endl << "\t个数：  " << us[i].num << "\n" << endl;
				cout << "*****************************************" << endl;
				cout << "\t\t输入修改目标序号(退出按-1)：\n";
				cin >> n;
				cout << "*****************************************" << endl;
			}
		}
	}
	break;
	}
	case 4://预算管理
	{if (!countnum)
		cout << "\t\t购物车为空！" << endl;
	else
	{
		cout << "\t购物车商品如下：\n";
		cout << "*****************************************" << endl;
		for (int i = 0; i <= countnum - 1; i++)
			cout << "\t" << i + 1 << "、  " << us[i].good.name << endl << "\t价格：  " << us[i].good.price << endl << "\t个数：  " << us[i].num << "\n" << endl;
		cout << "*****************************************" << endl;
		int tmp;
		double sum = 0;
		cout << "\t输入你需要结算的购物车物品序号(若选择完毕输-1以结算)：\n";
		cin >> tmp;
		cout << "*****************************************" << endl;
		while (tmp != -1)
		{
			if (Is_cut(us[tmp - 1])) cout << "\t\t本物品已使用促销！\n";
			else cout << "\t\t本物品未使用促销！\n";
			sum += us[tmp - 1].cutprice;
			cin >> tmp;
		}
		cout << "\t您的预算为：" << sum << "元" << endl;
	}
	break;
	}
	case 6://个人账户信息查询
		ifstream fin("C:\\抢宝计划\\UsrInfo.txt", ios::in);
		if (!fin)
		{
			cout << "无法连接服务器";

		}
		string textline[200];//欲读200行，自己定义 
		int j = 0;
		for (; !fin.eof();)
		{
			getline(fin, textline[j], '\n');
			j++;
		}

		for (int i = 0; i < 200; i++)
		{//验证ID是否存在
			int tk = 1; tk++;
			if ((i % 4) != 0) continue;
			if (textline[i] == id)
			{
				cout << "\t您的ID为：" << textline[i] << endl;
				cout << "\t您的用户名为：" << textline[i + 1] << endl;
				cout << "\t您的密码为：" << textline[i + 3] << endl;
			}

		}
		break;
	}


}

void Serc()//查找促销函数 先
{
	int c;
	cout << "选择查找关键词：\n1、商品名\n2、商家名\n";
	cin >> c;
	s[0].Search(c);

}

void Cal()//选择促销 计算促销价格
{
	if (countnum)
	{
		Serc();
		if (searchflag)
		{
			cout << "\t\t购物车信息如下：" << endl;
			for (int i = 0; i <= countnum - 1; i++)
				cout << "\t" << i + 1 << "、  " << us[i].good.name << endl << "价格：  " << us[i].good.price << endl << "个数：  " << us[i].num << endl;
			int c1, c2;
			cout << "\t输入你的促销选择：\n";
			cin >> c1;
			cout << "\t输入购物车促销物品的序号\n";
			cin >> c2;
			s[c1 - 1].Cut(us[c2 - 1], c1);
		}
	}
	else
	{
		cout << "当前购物车为空！" << endl;
	}
}

void Sales_manage(int n)
{
	switch (n)
	{
	case 1://录入促销信息
	{	system("CLS");
	InputInfo();
	break;
	}

	case 2://打印促销信息
	{
		system("CLS");
		if (!num)
			cout << "\t\t\t当前无促销信息！" << endl;
		else
		{
			for (int i = 0; i < num; i++)
			{
				cout << "\t" << i + 1 << "号促销：" << s[i].obj.name << endl;
				cout << "\t商家名：\t" << s[i].ShopName << endl;
				cout << "\t促销信息：\t" << s[i].desc << endl;
				cout << "\t促销开始时间：  " << s[i].starttime.tm_hour << "时-" << s[i].starttime.tm_min << "分-" << s[i].starttime.tm_sec << "秒" << endl;
				cout << endl;
			}
		}

		break;
	}

	case 3:
	{  system("CLS");
	Serc();
	break;
	}

	}


}

string createtxt(string a)//注册完后根据用户名创建相印的购物车数据文档
{
	string FPATH = "C:\\抢宝计划\\用户信息\\";

	FPATH = FPATH + a + ".txt";
	ofstream lout(FPATH.c_str());
	lout << 0 << endl;
	lout.close();
	return FPATH;
}

void user::Register()//注册
{
	ifstream fin("C:\\抢宝计划\\UsrInfo.txt", ios::in);
	if (!fin)
	{
		cout << "无法连接服务器";

	}
	string textline[200];//欲读200行，自己定义 
	int j = 0;
	for (; !fin.eof();)
	{
		getline(fin, textline[j], '\n');
		j++;
	}
	ofstream fout("C:\\抢宝计划\\UsrInfo.txt", ios::app);
	if (!fout)
	{
		cout << "无法链接服务器!\n";

	}
	string pw1;
	string pw2;
	user person;
	cout << "\t请设置您的ID：";
flag:
	cin >> person.ID;
	for (int i = 0; i < 200; i++)
	{
		if ((i % 4) != 0) continue;
		if (textline[i] == person.ID) {
			cout << "\a\t\t该ID已存在，请重新设置:";
			goto flag;
		}
	}
	cout << "\t请设置您的用户名：";
	cin >> person.Name;
	cout << "\t请绑定您的邮箱：";
	cin >> person.Email;
	cout << "\t请设置您的密码：";
flag0:
	cin >> pw1;
	cout << "\t请再次确认您的密码：";
	cin >> pw2;
	if (pw1 != pw2)
	{
		cout << "\a\t前后两次输入密码不一致，请重新设置密码:";
		goto flag0;
	}
	cout << "\t注册成功！" << endl;
	person.Password = pw1;
	fout << person.ID << endl;
	fout << person.Name << endl;
	fout << person.Email << endl;
	fout << person.Password << endl;
	createtxt(person.ID);//创建该账号的用户文件
	system("pause");

}

void user::Enter()//登录
{
	ifstream fin("C:\\抢宝计划\\UsrInfo.txt", ios::in);
	if (!fin)
	{
		cout << "无法连接服务器";
		return;
	}
	string textline[200];//欲读200行，自己定义 
	int j = 0;
	for (; !fin.eof();)
	{
		getline(fin, textline[j], '\n');
		j++;
	}
	cout << "*****************************************" << endl;
	cout << "\t请输入您的ID：";
flag1:
	int tk = 1;
	string pwd;
	cin >> id;
	for (int i = 0; i < 200; i++)
	{//验证ID是否存在

		if ((i % 4) != 0) continue;
		if (textline[i] == id)
		{
			tk = 2;
			cout << "\t请输入您的密码：";
		flag2:
			cin >> pwd;
			if (textline[i + 3] != pwd)
			{
				cout << "\a\t密码错误，请重新输入:";
				goto flag2;
			}
			cout << "\t登录成功！" << endl;
			USERNAME_PATH = "C:\\抢宝计划\\用户信息\\" + id + ".txt";//---------------------------------------------------------------------------------------------------------------------------------
			ReadCharts();//登录成功后根据用户名路径打开相应的购物车数据文件
		}

	}if (tk == 1)
	{
		cout << "\a\t该ID不存在，请重新输入:";
		goto flag1;
	}


}

void thread1()//主程序线程
{ //----------------写入内存
	ReadInfo();
	goto MAIN;
MAIN:
	cout << "                    ┌─────────────────────────────┐  " << endl;
	cout << "                    │欢迎来到商品促销管理系统     │" << endl;
	cout << "                    └─────────────────────────────┘  " << endl;
	cout << "                     亲(*^__^*) ！欢迎使用本系统！" << endl;;

	system("color e9");
	cout << "                    ┎────────┒" << endl;
	cout << "                    │【登录】│ " << endl;
	cout << "                    ┖────────┚  " << endl;
	cout << "\t\t\t1、管理员" << endl;
	cout << "\t\t\t2、普通用户" << endl;
	cout << "\t\t\t3、退出" << endl;
	cout << "\t\t*****************************" << endl;
	cout << "\t\t\t";



	int choice1;

flag2:
	cin >> choice1;
	switch (choice1)
	{
	case 1:
	{
		Admin A;
		A.Enter();

		break; }
	case 2:
	{
	flag3:
		system("CLS");
		cout << "\t用户登录：" << endl;
		cout << "\t1、注册\n\t2、登录\n\t3、返回上级菜单\n";
	flag1:
		int choice2;//选择界面
		user u;
		cout << "Choice:" << endl;
		cin >> choice2;
		switch (choice2)
		{
		case 1://注册

			u.Register();//调用函数,注册后返回登录界面
			goto flag3;
			break;
		case 2://登录
			u.Enter();//调用函数
			break;
		case 3://退出
			system("CLS");
			goto MAIN;
		default:
			cout << "请输入正确的选择！" << endl;
			goto flag1;
		}
		break; }
	case 3:system("CLS");
		goto END;
	default:
		cout << "\a\t请输入正确的选择！" << endl;
		goto flag2;
	}



	{
		int p = choice1;

		if (p == 1) { system("CLS"); goto SALES; }
		if (p == 2) { system("CLS"); goto CHARTS; }
		if (p == 3) { system("CLS"); goto END; }
	}

	//--------------------------录入各种信息
SALES:

	cout << "*****************************************" << endl;
	cout << "\t1、录入促销信息" << endl;
	cout << "\t2、打印促销信息" << endl;
	cout << "\t3、查询促销信息" << endl;
	cout << "\t4、退回主界面\n";
	cout << "\t5、退出本系统\n";
	cout << "*****************************************" << endl;
	int q;
	cin >> q;
	if (q == 4) {
		system("CLS");
		goto MAIN;
	}
	else if (q == 5) {
		system("CLS");
		goto END;
	}
	else
	{
		Sales_manage(q);
		system("pause");
		system("CLS");
		goto SALES;
	}
	//----------------------------购物车管理
CHARTS:
	int m;
	cout << "*****************************************" << endl;
	cout << "\t购物车管理：\n";
	cout << "\t1、添加物品\n";
	cout << "\t2、修改（删除）物品\n";
	cout << "\t3、打印购物单\n";
	cout << "\t4、购物车预算管理\n";
	cout << "\t5、查询并使用促销\n";
	cout << "\t6、回到主界面\n";
	cout << "\t7、退出本系统\n";
	cout << "*****************************************" << endl;
	cin >> m;
	if (m == 5) {

		Cal();
		WriteInfo();
		system("pause");
		system("CLS");//--------------------------------------------------------------------------------------------------------------------------------
		goto CHARTS;
	}
	else if (m == 6) {
		WriteInfo();
		system("CLS");
		goto MAIN;
	}
	else if (m == 7) {
		WriteInfo();
		system("CLS");
		goto END;
	}
	else {
		Carts(m);
		WriteInfo();
		system("pause");
		system("CLS");//---------------------------------------------------------------------------------------------------------------------------
		goto CHARTS;
	}
END:
	WriteInfo();
	endsign = 1;//   thread2 结束！
	return;
}

void thread2()//闹钟线程（提前x分钟播报）,退出标志为endsign
{
	time_t tmptime;
	struct tm p;
	time(&tmptime); //获取从1970至今过了多少秒，存入time_t类型的timep
	localtime_s(&p, &tmptime);//用localtime将秒数转化为struct tm结构体
	int* flag = new int[num];//记录促销信息是否已被播报  
	for (int i = 0; i < num; i++)
		flag[i] = 0;
	for (int i = 0; (i < num) && (!endsign); i++)//一直循环 直到thread1退出（endsign=1）
	{
		if ((!flag[i]) && (s[i].starttime.tm_hour >= p.tm_hour))
			if ((!flag[i]) && ((s[i].starttime.tm_min - p.tm_min <= 10) && (s[i].starttime.tm_min - p.tm_min >= 0)))//修改提前时间x  （这里x=10）
			{
				printf("\a\a\a\a\a");
				cout <<endl<< s[i].ShopName << " 家的" << s[i].obj.name << " 即将进入促销，快来康康吧！\n";
				flag[i] = 1;

			}

		if (i == num - 1)
			i = 0;
	}



	delete[] flag;

}

int main()
{
	std::thread t2(thread2);
	std::thread t1(thread1);
	t2.join();
	t1.join();


	system("pause");
	return 0;
}









