//����д������ͳ�Ƽ������ͷ�������ļ��㹤��
//�ȴ���дд��������ʱ��Ļ��ڲ��䡣  12.10

//д�굥��̬���巢�ִ������ȹ��ƵĶ࣬��������������ʵ�ֵĻ�����Ϊһ��Ҫ��500�д������Ĵ���ҵ�����е�̫�����˷�ʱ��
//���Ծ������ǰ�ÿ��ģ�����Ϊ���ӵ����ʵ�֡�  12.11

//�����Ѿ�����ʵ�֣����ܽ���֮�������ע�;�����ˣ�������Ų����ٽ��в�����޸�  12.12

//���ǵ�����ս��˻ع������Ϊ��д��ҵ����һ�㣬������ʱ����һԪ�ع����
//����flag�ˡ���  12.13

#include<iostream>
#include<cmath>
#include<vector>//����vectorҲ��ʵ�֣�����ʹ��ֻ������չʾ����Ķ�����
#include<iomanip>

using namespace std;

void menu(char); //�˵�����
void menu(int);//������ޱ�Ҫ����Ϊ����������Ҫ��"�����������Ե�����"������д�˸����ء�
void single_population_av();//����̬�����ֵ
void single_population_va();//����̬���巽��
void double_population_av();//˫��̬�����ֵ���Ƿ�Ϊ�㣨����ֵ�Ƿ���ȣ�
void double_population_va();//˫��̬�����ֵ֮��(����δ֪����ȵ����)
void one_way_ANOVA();//�����ط������
void two_way_ANOVA_1();//�޽������õ�˫���ط������
void two_way_ANOVA_2();//�н������õ�˫���ط������
void linearity_regression_mode_1();//һԪ���Իع�ģ�͡�


class cmpt
{
public:
	void av_cmpt(int);
	double av = 0;
	double va = 0;
	double va_ori = 0;//��Ϊ˽�еĻ���������ʡ���Ȼ��������Ԫ���ߵ�ַ���ʣ������������û�б�Ҫ��
private:
	void va_cmpt(vector<double>, double);
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
	va_cmpt(a1, av);
}



void cmpt::va_cmpt(vector<double> a, double b)
{
	for (int i = 0; unsigned(i) < a.size(); i++)
		va_ori = pow((a[i] - av), 2) + va_ori;
	va = va_ori / (a.size() - 1);
}


//��������ʵ����Ϊ��չʾ����Ķ���,��ʡ��������


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

//��������õ������������࣬�㷨Ҳ��΢��Ĳ�ͬ���������˼̳С�
class cmpt_2 :public cmpt_1
{
public:
	double sum1 = 0;
	double av_x = 0;
	double SR = 0;
	double ST = 0;
	double Se = 0;
	double Se1 = 0;
	double lxx = 0;
	double lyy = 0;
	double lxy = 0;
	double ��1 = 0;
	double ��0 = 0;
	void cmpt(int);
};


void cmpt_2::cmpt(int a) 
{
	vector<double> x(a, 0);
	vector<double> y(a, 0);
	cout << "������x������,���ݼ��ÿո�ָ���" << endl;
	for (int i = 0; i < a; i++)
	{
		cin >> x[i];
		av_x = x[i] + av_x;
		sum1 = pow(x[i], 2) + sum1;
	}
	av_x = av_x / a;
	lxx = sum1 - a * pow(av_x, 2);
	cout << "������y�����ݣ����ݼ��ÿո�ָ���" << endl;
	for (int i = 0; i < a; i++)
	{
		cin >> y[i];
		av = y[i] + av;
		sum2 = pow(y[i], 2) + sum2;
	}
	av = av / a;
	lyy = sum2 - a * pow(av, 2);
	for (int i = 0; i < a; i++)
		lxy = lxy + x[i] * y[i];
	lxy = lxy - a * av_x * av;
	��1 = lxy / lxx;
	��0 = av - ��1 * av_x;
	ST = lyy;
	SR = lxx * pow(��1, 2);
	Se = ST - SR;
	Se1 = Se / (double(a) - double(2));
}



int main()
{
	char choice = '0';
	cout << "�ַ���Ӧ�����·�����" << endl;
	cout << "������̬�����ֵ��A" << endl;
	cout << "������̬���巽��(Ĭ�Ͼ�ֵδ֪)��B" << endl;
	cout << "������̬��������֮��(Ĭ�ϲ�Ϊ0,������ȵ�δ֪)��C" << endl;
	cout << "������̬���巽��֮��(Ĭ��˫����ֵδ֪����ֵΪ1)��D" << endl;
	cout << "�����ط��������E" << endl;
	cout << "�޽������õ�˫���ط��������F" << endl;
	cout << "�н������õ�˫���ط��������G" << endl;
	cout << "һԪ���Է���ģ�ͣ�H" << endl;
	cout << "�˳���Q" << endl;
	cout << "�밴���Լ�������������Ӧ��ѡ���ַ��������Ե�һ���ַ�Ϊ׼��ѡ���ַ������ִ�Сд��";//�ṩѡ��
	cin >> choice;
	cin.ignore(200, '\n');
	while (cin.eof() == true)
	{
		cout << endl << "������󣬳����˳���";
		return 0;
	}
	menu(choice);
	return 0;
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
	case 'f':
	case 'F':two_way_ANOVA_1();
		break;
	case 'g':
	case 'G':two_way_ANOVA_2();
		break;
	case 'h':
	case 'H':linearity_regression_mode_1();
		break;
	case 'q':
	case 'Q':return;
	default:cout << "��ƥ��ѡ����������롣";
		cin >> choice;
		cin.ignore(200, '\n');
		while (cin.eof() == true)
		{
			cout << endl << "������󣬳����˳���";
			return;
		}
		menu(choice);
		return;

	}
}



void menu(int a)
{
	char choice = 'q';
	switch(a)
	{
	case 0:cout << "����������ѡ���ַ���";
		cin >> choice;
		cin.ignore(200, '\n'); //ʵ��ֻ��һ���ַ��������ʣ��������������cin.get()��������ʵ�֡�
		while (cin.eof() == true)
		{
			cout << endl << "������󣬳����˳���";
			return;
		}
		menu(choice);   //����֮ǰ�����ԣ��������ctrl+z�����ַ����ᵼ�³����޷��������У��������ӿ��ַ���⡣
		return;
	case 1:cout << "��Ҫ�������밴�ַ���Ӧ�����룬�˳�������Q��";
		cin >> choice;
		cin.ignore(200, '\n');
		while (cin.eof() == true)
		{
			cout << endl << "������󣬳����˳���";
			return;
		}
		menu(choice);
		return;
	}
}



void single_population_av()
{
	cout << "���������ݸ�������Ҫ����������0��";
	int n = 0;
	while (!(cin >> n))
	{
		cin.clear();
		cin.ignore(200, '\n');//�������ͻ���������������׸����
		cout << "����������������룺";
	}
	if (n == 0)
	{
		menu(0);
		return;
	}
	double* p = new double[n];
	cout << "���������ݣ��ÿո����ݷָ���" << endl;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
		sum = p[i] + sum;
	}
	double av_1 = sum / n; //���ֵ
	cout << "��������������µľ�ֵ��";
	double av = 0;
	while (!(cin >> av))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "����������������룺";
	}
	cout << "�����뷽��������δ֪������0��";
	double variance = 0;
	while (!(cin >> variance))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "����������������룺";
	}
	while (variance < 0)
	{
		cout << "������Ǹ���ţ��Ҿ��÷���С��0�������Ӧ�ô��ڡ�" << endl << "��������ȷ�ķ������ݣ�";
		cin >> variance;
	}
	//�ų������쳣��
	if (variance == 0)
	{
		for (int i = 0; i < n; i++)
			variance = variance + pow((p[i] - av_1), 2);

		variance = variance / (double(n) - double(1));
		double t = (av_1 - av) / sqrt(variance) * sqrt(n);
		cout << "���ݾ�ֵΪ��" << av_1 << endl;
		cout << "���ݷ���Ϊ��" << variance << endl;
		cout << "T = " << t << " ~ t(" << n - 1 << ')' << endl;
	}
	else
	{
		double u = (av_1 - av) / sqrt(variance) * sqrt(n);
		cout << "���ݾ�ֵΪ��" << av_1 << endl;
		cout << "���ݷ���Ϊ��" << variance << endl;
		cout << "U = " << u << " ~ N(0,1)" << endl;
	}
	delete[] p;
	menu(1);
	return;
}





void single_population_va()
{
	cout << "���������ݸ�������Ҫ����������0��";
	int n = 0;
	while (!(cin >> n))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "����������������룺";
	}
	if (n == 0)
	{
		menu(n);
		return;
	}
	double* p = new double[n];
	cout << "���������ݣ��ÿո����ݷָ���" << endl;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
		sum = p[i] + sum;
	}
	double av_1 = sum / n;
	cout << "�����뷽�";
	double variance = 0;
	double variance_1 = 0;//�����������ݵķ��
	while (!(cin >> variance))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "����������������룺";
	}
	while (variance < 0)
	{
		cout << "������Ǹ���ţ��Ҿ��÷���С��0�������Ӧ�ô��ڡ�" << endl << "��������ȷ�ķ������ݣ�";
		cin >> variance;
	}
	//�����������������ݼ�⡣
	for (int i = 0; i < n; i++)
	{
		variance_1 = variance_1 + pow((p[i] - av_1), 2);
	}
	variance_1 = variance_1 / (double(n) - double(1));
	double x2 = (double(n) - double(1)) * variance_1 / variance;
	cout << "���ݾ�ֵΪ��" << av_1 << endl;
	cout << "���ݷ���Ϊ��" << variance_1 << endl;
	cout << "X^2 = " << x2 << " ~ X^2(" << n - 1 << ')' << endl;
	delete[] p;
	menu(1);
	return;
}
void double_population_av()
{
	cout << "�������������ݸ��Ը������м��Կո����ӣ���Ҫ����������0��" << endl;
	int a = 0;
	int b = 0;
	cin >> a >> b;    //���Ŵ���ҵ���ٴ����ظ���������д�㶫�����뷨�����ﲻ���������ʽ��⡣��ط�ʽ�Ѿ��ڵ���̬����ĺ�����ʵ�ֹ�������ͬ������׸����
	if (a == 0 or b == 0)
	{
		menu(0);
		return;
	}
	cmpt n1, n2;
	cout << "�������һ�����ݣ��м��ÿո����ӣ�" << endl;
	n1.av_cmpt(a);
	cout << "������ڶ������ݣ��м��ÿո����ӣ�" << endl;
	n2.av_cmpt(b);
	double Sw = (n1.va_ori + n2.va_ori) / (double(a) + double(b) - double(2));
	double T = (n1.av - n2.av) * sqrt(a * b) / sqrt(Sw) / sqrt(a + b);
	cout << "��һ�����ݾ�ֵΪ��" << n1.av << endl;
	cout << "�ڶ������ݾ�ֵΪ��" << n2.av << endl;
	cout << "��һ�����ݷ���Ϊ��" << n1.va << endl;
	cout << "�ڶ������ݷ���Ϊ��" << n2.va << endl;
	cout << "Sw = " << Sw << endl;
	cout << "T = " << T << " ~ t(" << a + b - 1 << ')' << endl;
	menu(1);
	return;

}



void double_population_va()
{
	cout << "�������������ݸ��Ը������м��Կո����ӣ���Ҫ����������0��" << endl;
	int a = 0;
	int b = 0;
	cin >> a >> b;
	if (a == 0 or b == 0)
	{
		menu(0);
		return;
	}
	cmpt n1, n2;
	cout << "�������һ�����ݣ��м��ÿո����ӣ�" << endl;
	n1.av_cmpt(a);
	cout << "������ڶ������ݣ��м��ÿո����ӣ�" << endl;
	n2.av_cmpt(b);
	double F = n1.va / n2.va;
	cout << "��һ�����ݾ�ֵΪ��" << n1.av << endl;
	cout << "�ڶ������ݾ�ֵΪ��" << n2.av << endl;
	cout << "��һ�����ݷ���Ϊ��" << n1.va << endl;
	cout << "�ڶ������ݷ���Ϊ��" << n2.va << endl;
	cout << "F = " << F << " ~ F(" << a - 1 << ',' << b - 1 << ')' << endl;
	menu(1);
	return;

}



void one_way_ANOVA()
{
	cout << "�������������,��Ҫ����������0��";
	int a = 0;
	cin >> a;
	if (a == 0)
	{
		menu(a);
		return;
	}
	cmpt_1* p = new cmpt_1[a];
	int n = 0;
	for (int i = 0; i < a; i++)
	{
		cout << "������� " << i + 1 << " ���������ݸ���" << endl;
		int j = 0;
		cin >> j;
		n = n + j;
		cout << "������� " << i + 1 << " ���������ݣ����ݼ��ÿո����ӣ�" << endl;
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
		SA = pow(p[i].av, 2) * p[i].n + SA;
	}
	av = av / n;
	ST = sum2 - n * pow(av, 2);
	SA = SA - n * pow(av, 2);
	Se = ST - SA;
	double SA1 = SA / (double(a) - double(1));
	double Se1 = Se / (double(n) - double(a));
	cout << setw(6) << "��Դ" << setw(12) << "ƽ����" << setw(12) << "���ɶ�" << setw(12) << "������" << setw(12) << "F��   " << endl;
	cout << setw(6) << "SA" << setw(12) << SA << setw(12) << a - 1 << setw(12) << SA1 << setw(12) << "F =   " << endl;
	cout << setw(6) << "Se" << setw(12) << Se << setw(12) << n - a << setw(12) << Se1 << setw(12) << SA1 / Se1 << endl;
	cout << setw(6) << "ST" << setw(12) << ST << setw(12) << n - 1 << endl;//ʵ�ֱ��ʽ�����
	delete[]p;
	menu(1);
	return;

}


void two_way_ANOVA_1()
{
	int a, b;
	cout << "������������A��������B�ĸ������м��ÿո����ӣ�������һ��������0��" << endl;
	cin >> a >> b;
	if (a == 0 or b == 0)
	{
		menu(0);
		return;
	}
	int i, j;
	double** p = new double* [a];//��̬�����ά����
	for (i = 0; i < a; i++)
		p[i] = new double[b];

	printf("�밴��˳������%d��Ԫ�أ���������Ԫ�أ���������Ԫ�أ�Ԫ�ؼ��Կո�ָ�:\n", a * b);//C��������ʽ��
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			cin >> p[i][j];

	int n = a * b;
	double ST = 0;
	double Se = 0;
	double SA = 0;
	double SB = 0;
	double av_n = 0;
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			av_n = av_n + p[i][j];

	av_n = av_n / n;
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			ST = pow(p[i][j] - av_n, 2) + ST;

	for (i = 0; i < a; i++)
	{
		double av_i = 0;
		for (j = 0; j < b; j++)
			av_i = p[i][j] + av_i;

		av_i = av_i / b;
		SA = pow(av_i - av_n, 2) + SA;
	}
	SA = SA * b;
	for (i = 0; i < b; i++)
	{
		double av_j = 0;
		for (j = 0; j < a; j++)
			av_j = p[j][i] + av_j;

		av_j = av_j / a;
		SB = pow(av_j - av_n, 2) + SB;
	}
	SB = SB * a;
	Se = ST - SA - SB;
	double SA1 = SA / (double(a) - double(1));
	double SB1 = SB / (double(b) - double(1));
	double ne = (double(a) - double(1)) * (double(b) - double(1));
	double Se1 = Se / ne;
	cout << setw(6) << "��Դ" << setw(12) << "ƽ����" << setw(12) << "���ɶ�" << setw(12) << "������" << setw(12) << "F��" << endl;
	cout << setw(6) << "SA" << setw(12) << SA << setw(12) << a - 1 << setw(12) << SA1 << setw(12) << SA1 / Se1 << endl;
	cout << setw(6) << "SB" << setw(12) << SB << setw(12) << b - 1 << setw(12) << SB1 << setw(12) << SB1 / Se1 << endl;
	cout << setw(6) << "Se" << setw(12) << Se << setw(12) << ne << setw(12) << Se1 << endl;
	cout << setw(6) << "ST" << setw(12) << ST << setw(12) << n - 1 << endl;
	delete[]p;
	menu(1);
	return;
}



void two_way_ANOVA_2()
{
	int a, b, c;
	cout << "����������A,����B��ͬ������ĸ������м��Կո����ӣ�������һ��������0��" << endl;
	cin >> a >> b >> c;
	if (a == 0 or b == 0 or c == 0 )
	{
		menu(0);
		return;
	}
	int i, j, k;
	double*** p;//��̬������ά����
	p = new double** [a];
	for (i = 0; i < a; i++)
		p[i] = new double* [b];

	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			p[i][j] = new double[c];

	cout << "�밴����˳����ͬ��ʵ��Ϊ��λ��ÿ��Ԫ�ؼ��ÿո����ӣ�����" << a * b * c << "��Ԫ��:\n";
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			for (k = 0; k < c; k++)
				cin >> p[i][j][k];

	int n = a * b * c;
	double ST = 0;
	double Se = 0;
	double SA = 0;
	double SB = 0;
	double SAB = 0;
	double av_n = 0;
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
		    for (k = 0; k < c; k++)
				av_n = av_n + p[i][j][k];

	av_n = av_n / n;
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			for (k = 0; k < c; k++)
				ST = pow(p[i][j][k] - av_n, 2) + ST;

	for (i = 0; i < a; i++)
	{
		for (j = 0; j < b; j++)
		{
			double av_ij = 0;
			for (k = 0; k < c; k++)
				av_ij = p[i][j][k] + av_ij;

			av_ij = av_ij / k;
			for (k = 0; k < c; k++)
				Se = pow(p[i][j][k] - av_ij, 2) + Se;
		}
	}
	for (i = 0; i < a; i++)
	{
		double av_i = 0;
		for (j = 0; j < b; j++)
			for (k = 0; k < c; k++)
				av_i = p[i][j][k] + av_i;

		av_i = av_i / (double(b) * double(c));
		SA = pow(av_i - av_n, 2) + SA;
	}
	SA = SA * b * c;
	for (i = 0; i < b; i++)
	{
		double av_j = 0;
		for (j = 0; j < a; j++)
			for (k = 0; k < c; k++)
				av_j = p[j][i][k] + av_j;

		av_j = av_j / (double(a) * double(c));
		SB = pow(av_j - av_n, 2) + SB;
	}
	SB = SB * a * c;
	SAB = ST - SA - SB - Se;
	double SA1 = SA / (double(a) - double(1));
	double SB1 = SB / (double(b) - double(1));
	double nAB = (double(a) - double(1)) * (double(b) - double(1));
	double SAB1 = SAB / nAB;
	double ne = double(a) * double(b) * (double(c) - double(1));
	double Se1 = Se / ne;
	cout << setw(6) << "��Դ" << setw(12) << "ƽ����" << setw(12) << "���ɶ�" << setw(12) << "������" << setw(12) << "F��" << endl;
	cout << setw(6) << "SA" << setw(12) << SA << setw(12) << a - 1 << setw(12) << SA1 << setw(12) << SA1 / Se1 << endl;
	cout << setw(6) << "SB" << setw(12) << SB << setw(12) << b - 1 << setw(12) << SB1 << setw(12) << SB1 / Se1 << endl;
	cout << setw(6) << "SAxB" << setw(12) << SAB << setw(12) << nAB << setw(12) << SAB1 << setw(12) << SAB1 / Se1 << endl;
	cout << setw(6) << "Se" << setw(12) << Se << setw(12) << ne << setw(12) << Se1 << endl;
	cout << setw(6) << "ST" << setw(12) << ST << setw(12) << n - 1 << endl;
	delete[]p;
	menu(1);
	return;

}


void linearity_regression_mode_1()
{
	cout << "������x�����ݸ���,��Ҫ����������0��";
	int a = 0;
	cin >> a;
	if (a == 0)
	{
		menu(a);
		return;
	};
	cmpt_2 model;
	model.cmpt(a);
	cout << setw(6) << "��Դ" << setw(12) << "ƽ����" << setw(12) << "���ɶ�" << setw(12) << "������" << setw(12) << "F��   " << endl;
	cout << setw(6) << "SR" << setw(12) << model.SR << setw(12) << '1' << setw(12) << model.SR << setw(12) << "F =  " << endl;
	cout << setw(6) << "Se" << setw(12) << model.Se << setw(12) << a - 2 << setw(12) << model.Se1 << setw(12) << model.SR / model.Se1 << endl;
	cout << setw(6) << "ST" << setw(12) << model.ST << setw(12) << a - 1 << endl;
	cout << setw(6) << "��1" << setw(12) << model.��1 << setw(12) << "��0" << setw(12) << model.��0 << endl;
	menu(1);
	return;
}