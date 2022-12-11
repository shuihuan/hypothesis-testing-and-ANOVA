//����д������ͳ�Ƽ������ͷ�������ļ��㹤��
//�ȴ���дд��������ʱ��Ļ��ڲ��䡣  12.10

//д�굥��̬���巢�ִ������ȹ��ƵĶ࣬��������������ʵ�ֵĻ�����Ϊһ��Ҫ��500�д������Ĵ���ҵ�����е�̫�����˷�ʱ��
//���Ծ������ǰ�ÿ��ģ�����Ϊ���ӵ����ʵ�֡�  12.11
#include<iostream>
#include<cmath>
#include<vector>//����vectorҲ��ʵ�֣�����ʹ��ֻ������չʾ����Ķ�����

using namespace std;

void menu(char); //�˵�����
void single_population_av();//����̬�����ֵ
void single_population_va();//����̬���巽��
void double_population_av();//˫��̬�����ֵ���Ƿ�Ϊ�㣨����ֵ�Ƿ���ȣ�
void double_population_va();//˫��̬�����ֵ֮��(����δ֪�����)
void one_way_ANOVA();//�����ط������



class cmpt
{
	public:
		void av_cmpt(int);
		void va_cmpt(vector<double>,double);
		double av = 0;
		double va = 0;
		double va_ori = 0;//��Ϊ˽�еĻ���������ʡ���Ȼ��������Ԫ���ߵ�ַ���ʣ������������û�б�Ҫ��
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
	for (int i = 0; i < a.size(); i++)
		va_ori = pow((a[i] - av), 2) + va_ori;
	va = va_ori / (a.size() - 1);
}


//��������ʵ����ȫ��Ϊ��չʾ����Ķ�����vectorҲ��.



int main()
{
	char choice = '0';
	cout << "�ַ���Ӧ�����·�����" << endl;
	cout << "������̬�����ֵ��a" << endl;
	cout << "������̬���巽��(Ĭ�Ͼ�ֵδ֪)��b" << endl;
	cout << "������̬��������֮��(Ĭ�ϲ�Ϊ0,������ȵ�δ֪)��c" << endl;
	cout << "������̬���巽��֮��(Ĭ��˫����ֵδ֪����ֵΪ1)��d" << endl;
	cout << "�˳���q" << endl;
	cout << "�밴���Լ�������������Ӧ��ѡ���ַ��������Ե�һ���ַ�Ϊ׼��ѡ���ַ������ִ�Сд��";
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
	case 'q':
	case 'Q':return;
	case '0':cout << "����������ѡ���ַ���";
		cin >> choice;
		cin.ignore(200, '\n'); //ʵ��ֻ��һ���ַ��������ʣ��������������cin.get()��������ʵ�֡�
		while (cin.eof() == true)
		{
			cout << endl << "������󣬳����˳���";
			return;
		}
		menu(choice);   //����֮ǰ�����ԣ��������ctrl+z�����ַ����ᱨ���������ӿ��ַ���⡣
		return;
	case '1':cout << "��Ҫ�������밴�ַ���Ӧ�����룬�˳�������q��";
		cin >> choice; 
		cin.ignore(200, '\n');
		while (cin.eof() == true)
		{
			cout << endl << "������󣬳����˳���";
			return;
		}
		menu(choice);
		return;
	default:cout << "��ƥ��ѡ������˳���";
		return;

	}
}





void single_population_av()
{
	cout << "���������ݸ�������Ҫ����������0��";
	int n = 0;
	while(!(cin >> n))
	{
		cin.clear();
		cin.ignore(200, '\n');//�������ͻ���������������׸����
		cout << "����������������룺";
	}
	if (n == 0)
	{
		menu('0');
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
		cout << "��������ȷ�ķ����ʽ��";
		cin >> variance;
	}
	//�ų������쳣��
	if (variance == 0)
	{
		for (int i = 0; i < n; i++)
		{
			variance = variance + pow((p[i] - av_1), 2);
		}
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
	menu('1');
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
		menu('0');
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
	double variance_1 = 0;
	while (!(cin >> variance))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "����������������룺";
	}
	while (variance < 0)
	{
		cout << "��������ȷ�ķ����ʽ��";
		cin >> variance;
	}
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
	menu('1');
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
		menu('0');
		return;
	}
	cmpt n1, n2;
	cout << "�������һ�����ݣ��м��ÿո����ӣ�" << endl;
	n1.av_cmpt(a);
	cout << "������ڶ������ݣ��м��ÿո����ӣ�" << endl;
	n2.av_cmpt(b);
	double Sw = (n1.va_ori + n2.va_ori) / (double(a) + double(b) - double(2));
	double T = (n1.av - n2.av) * sqrt(a * b) / Sw / sqrt(a + b);
	cout << "��һ�����ݾ�ֵΪ��" << n1.av << endl;
	cout << "�ڶ������ݾ�ֵΪ��" << n2.av << endl;
	cout << "��һ�����ݷ���Ϊ��" << n1.va << endl;
	cout << "�ڶ������ݷ���Ϊ��" << n2.va << endl;
	cout << "Sw = " << Sw << endl;
	cout << "T = " << T << " ~ t(" << a + b - 1 << ')' << endl;
	menu('1');
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
		menu('0');
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
	menu('1');
	return;

}