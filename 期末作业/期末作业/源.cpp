//打算写个数理统计假设检验和方差分析的计算工具
//先大体写写，后面有时间的话在补充。  12.10

//写完单正态总体发现代码数比估计的多，如果把所有情况都实现的话，作为一个要求500行代码量的大作业来讲有点太过于浪费时间
//所以决定仅是把每种模型里较为复杂的情况实现。  12.11
#include<iostream>
#include<cmath>
#include<vector>//不用vector也能实现，这里使用只不过是展示更多的东西。
#include<iomanip>

using namespace std;

void menu(char); //菜单功能
void single_population_av();//单正态总体均值
void single_population_va();//单正态总体方差
void double_population_av();//双正态总体均值差是否为零（两均值是否相等）
void double_population_va();//双正态总体均值之比(方差未知的情况)
void one_way_ANOVA();//单因素方差分析
void two_way_ANOVA_1();//无交互作用的双因素方差分析
void two_way_ANOVA_2();//有交互作用的双因素方差分析


class cmpt
{
	public:
		void av_cmpt(int);
		double av = 0;
		double va = 0;
		double va_ori = 0;//设为私有的话不方便访问。虽然可以用友元或者地址访问，但在这里好像没有必要。
    private:
		void va_cmpt(vector<double>,double);
};



void cmpt::av_cmpt(int a)
{
	vector<double> a1(a, 0);
	for (int i = 0; i < a; i++)
	{
		cin >> a1[i];
		av = a1[i] + av;
	}
	av = av / a;
	va_cmpt(a1,av);
}



void cmpt::va_cmpt(vector<double> a,double b)
{
	for (int i = 0; unsigned(i) < a.size(); i++)
		va_ori = pow((a[i] - av), 2) + va_ori;
	va = va_ori / (a.size() - 1);
}


//这里用类实现是为了展示更多的东西,节省代码量。


class cmpt_1 :public cmpt
{
public:
	int n = 0;
	double sum = 0;
	double sum2 = 0;
	void av_cmpt(int);
};


void cmpt_1::av_cmpt(int a)
{
	n = a;
	vector<double> a1(a, 0);
	for (int i = 0; i < a; i++)
	{
		cin >> a1[i];
		av = a1[i] + av;
		sum2 = pow(a1[i], 2) + sum2;
	}
	sum = av;
	av = av / a;
}

//方差分析用到的数据量更多，算法也有微妙的不同，所以用了继承。


int main()
{
	char choice = '0';
	cout << "字符对应表在下方给出" << endl;
	cout << "单个正态总体均值：a" << endl;
	cout << "单个正态总体方差(默认均值未知)：b" << endl;
	cout << "两个正态总体期望之差(默认差为0,方差相等但未知)：c" << endl;
	cout << "两个正态总体方差之比(默认双方均值未知，比值为1)：d" << endl;
	cout << "单因素方差分析：e" << endl;
	cout << "退出：q" << endl;
	cout << "请按照自己的需求输入相应的选项字符，输入以第一个字符为准。选项字符不区分大小写：";
	cin >> choice;
	menu(choice);
	
}




void menu(char choice)
{
	switch (choice)
	{
	case 'a':
	case 'A':single_population_av();
		break;
	case 'b':
	case 'B':single_population_va();
		break;
	case 'c':
	case 'C':double_population_av();
		break;
	case 'd':
	case 'D':double_population_va();
		break;
	case 'e':
	case 'E':one_way_ANOVA();
		break;
	case 'q':
	case 'Q':return;
	case '0':cout << "请重新输入选项字符：";
		cin >> choice;
		cin.ignore(200, '\n'); //实现只读一个字符，并清空剩余的输出。这里用cin.get()反而难以实现。
		while (cin.eof() == true)
		{
			cout << endl << "输入错误，程序退出。";
			return;
		}
		menu(choice);   //这里之前做测试，如果输入ctrl+z（空字符）会报错，所以增加空字符检测。
		return;
	case '1':cout << "如要继续，请按字符对应表输入，退出请输入q：";
		cin >> choice; 
		cin.ignore(200, '\n');
		while (cin.eof() == true)
		{
			cout << endl << "输入错误，程序退出。";
			return;
		}
		menu(choice);
		return;
	default:cout << "无匹配选项，程序退出。";
		return;

	}
}





void single_population_av()
{
	cout << "请输入数据个数，如要返回请输入0：";
	int n = 0;
	while(!(cin >> n))
	{
		cin.clear();
		cin.ignore(200, '\n');//清空输入和缓存区。后续不再赘述。
		cout << "输入错误，请重新输入：";
	}
	if (n == 0)
	{
		menu('0');
		return;
	}
	double* p = new double[n];
	cout << "请输入数据，用空格将数据分隔：" << endl;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
		sum = p[i] + sum;
	}
	double av_1 = sum / n; //求均值
	cout << "请输入正常情况下的均值：";
	double av = 0;
	while (!(cin >> av))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "输入错误，请重新输入：";
	}
	cout << "请输入方差，如果方差未知请输入0：";
	double variance = 0;
	while (!(cin >> variance))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "输入错误，请重新输入：";
	}
	while (variance < 0)
	{
		cout << "请输入正确的方差格式：";
		cin >> variance;
	}
	//排除输入异常。
	if (variance == 0)
	{
		for (int i = 0; i < n; i++)
		{
			variance = variance + pow((p[i] - av_1), 2);
		}
		variance = variance / (double(n) - double(1));
		double t = (av_1 - av) / sqrt(variance) * sqrt(n);
		cout << "数据均值为：" << av_1 << endl;
		cout << "数据方差为：" << variance << endl;
		cout << "T = " << t << " ~ t(" << n - 1 << ')' << endl;
	}
	else
	{
		double u = (av_1 - av) / sqrt(variance) * sqrt(n);
		cout << "数据均值为：" << av_1 << endl;
		cout << "数据方差为：" << variance << endl;
		cout << "U = " << u << " ~ N(0,1)" << endl;
	}
	delete[] p;
	menu('1');
	return;
}





void single_population_va()
{
	cout << "请输入数据个数，如要返回请输入0：";
	int n = 0;
	while (!(cin >> n))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "输入错误，请重新输入：";
	}
	if (n == 0)
	{
		menu('0');
		return;
	}
	double* p = new double[n];
	cout << "请输入数据，用空格将数据分隔：" << endl;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
		sum = p[i] + sum;
	}
	double av_1 = sum / n;
	cout << "请输入方差：";
	double variance = 0;
	double variance_1 = 0;
	while (!(cin >> variance))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "输入错误，请重新输入：";
	}
	while (variance < 0)
	{
		cout << "请输入正确的方差格式：";
		cin >> variance;
	}
	//对上述输入做出数据检测。
	for (int i = 0; i < n; i++)
	{
		variance_1 = variance_1 + pow((p[i] - av_1), 2);
	}
	variance_1 = variance_1 / (double(n) - double(1));
	double x2 = (double(n) - double(1)) * variance_1 / variance;
	cout << "数据均值为：" << av_1 << endl;
	cout << "数据方差为：" << variance_1 << endl;
	cout << "X^2 = " << x2 << " ~ X^2(" << n - 1 << ')' << endl;
	delete[] p;
	menu('1');
	return;
}
void double_population_av()
{
	cout << "请输入两组数据各自个数，中间以空格链接，如要返回请输入0：" << endl;
	int a = 0;
	int b = 0;
	cin >> a >> b;    //本着大作业减少代码重复，尽量多写点东西的想法，这里不再做输入格式检测。相关方式已经在单正态总体的函数里实现过。后续同理，不再赘述。
	if (a == 0 or b == 0)
	{
		menu('0');
		return;
	}
	cmpt n1, n2;
	cout << "请输入第一组数据，中间用空格链接：" << endl;
	n1.av_cmpt(a);
	cout << "请输入第二组数据，中间用空格链接：" << endl;
	n2.av_cmpt(b);
	double Sw = (n1.va_ori + n2.va_ori) / (double(a) + double(b) - double(2));
	double T = (n1.av - n2.av) * sqrt(a * b) / Sw / sqrt(a + b);
	cout << "第一组数据均值为：" << n1.av << endl;
	cout << "第二组数据均值为：" << n2.av << endl;
	cout << "第一组数据方差为：" << n1.va << endl;
	cout << "第二组数据方差为：" << n2.va << endl;
	cout << "Sw = " << Sw << endl;
	cout << "T = " << T << " ~ t(" << a + b - 1 << ')' << endl;
	menu('1');
	return;

}



void double_population_va()
{
	cout << "请输入两组数据各自个数，中间以空格链接，如要返回请输入0：" << endl;
	int a = 0;
	int b = 0;
	cin >> a >> b;
	if (a == 0 or b == 0)
	{
		menu('0');
		return;
	}
	cmpt n1, n2;
	cout << "请输入第一组数据，中间用空格链接：" << endl;
	n1.av_cmpt(a);
	cout << "请输入第二组数据，中间用空格链接：" << endl;
	n2.av_cmpt(b);
	double F = n1.va / n2.va;
	cout << "第一组数据均值为：" << n1.av << endl;
	cout << "第二组数据均值为：" << n2.av << endl;
	cout << "第一组数据方差为：" << n1.va << endl;
	cout << "第二组数据方差为：" << n2.va << endl;
	cout << "F = " << F << " ~ F(" << a - 1 << ',' << b - 1 << ')' << endl;
	menu('1');
	return;

}



void one_way_ANOVA()
{
	cout << "请输入测试组数,如要返回请输入0：";
	int a = 0;
	cin >> a;
	if (a == 0)
	{
		menu('0');
		return;
	}
	cmpt_1* p = new cmpt_1[a];
	int n = 0;
	for (int i = 0; i < a; i++)
	{
		cout << "请输入第 " << i + 1 << " 组数据数据个数" << endl;
		int j = 0;
		cin >> j;
		n = n + j;
		cout << "请输入第 " << i + 1 << " 组数据数据，数据间用空格链接：" << endl;
		p[i].av_cmpt(j);
	}
	double av = 0;
	double sum2 = 0;
    double ST = 0;
	double SA = 0;
	double Se = 0;
	for (int i = 0; i < a; i++)
	{
		av = av + p[i].sum;
		sum2 = sum2 + p[i].sum2;
		SA = pow(p[i].av, 2) * p[i].n + SA ;
	}
	av = av / n;
    ST = sum2 - n * pow(av, 2);
	SA = SA - n * pow(av, 2);
	Se = ST - SA;
	double SA1 = SA / (double(a) - double(1));
	double Se1 = Se / (double(n) - double(a));
	cout << setw(6) << "来源" << setw(12) << "平方和" << setw(12) << "自由度" << setw(12) << "均方和" << setw(12) << "F比   " << endl;
	cout << setw(6) << "SA" << setw(12) << SA << setw(12) << a - 1 << setw(12) << SA1 << setw(12) << "F =   " << endl;
	cout << setw(6) << "Se" << setw(12) << Se << setw(12) << n - a << setw(12) << Se1 << setw(12) << SA1 / Se1 << endl;
	cout << setw(6) << "ST" << setw(12) << ST << setw(12) << n - 1 << endl;//实现表格式输出。
	delete[]p;
	menu('0');
	return;

}