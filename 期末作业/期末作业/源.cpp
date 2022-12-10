//打算写个数理统计假设检验和方差分析的计算工具
//先大体写写，后面有时间的话在补充。  12.10
#include<iostream>
#include<cmath>

using namespace std;

void menu(char); //菜单功能
void single_population_av();//单正态总体均值
void single_population_va();//单正态总体方差
void double_population_av();//双正态总体均值差是否为零（两均值是否相等）
void double_population_va();//双正态总体均值之比


int main()
{
	char choice = '0';
	cout << "字符对应表在下方给出" << endl;
	cout << "单个正态总体均值：a" << endl;
	cout << "单个正态总体方差(默认均值未知)：b" << endl;
	cout << "请按照自己的需求输入相应的选项字符，选项字符不区分大小写：";
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
	case 'q':
	case 'Q':return;
	case '0':cout << "请重新输入选项字符：";
		cin >> choice;
		menu(choice);
		return;
	case '1':cout << "如要继续，请按字符对应表输入，退出请输入q：";
		cin >> choice;
		menu(choice);

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