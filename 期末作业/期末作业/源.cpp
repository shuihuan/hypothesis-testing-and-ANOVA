//����д������ͳ�Ƽ������ͷ�������ļ��㹤��
//�ȴ���дд��������ʱ��Ļ��ڲ��䡣  12.10
#include<iostream>
#include<cmath>

using namespace std;

void menu(char); //�˵�����
void single_population_av();//����̬�����ֵ
void single_population_va();//����̬���巽��
void double_population_av();//˫��̬�����ֵ���Ƿ�Ϊ�㣨����ֵ�Ƿ���ȣ�
void double_population_va();//˫��̬�����ֵ֮��


int main()
{
	char choice = '0';
	cout << "�ַ���Ӧ�����·�����" << endl;
	cout << "������̬�����ֵ��a" << endl;
	cout << "������̬���巽��(Ĭ�Ͼ�ֵδ֪)��b" << endl;
	cout << "�밴���Լ�������������Ӧ��ѡ���ַ���ѡ���ַ������ִ�Сд��";
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
	case '0':cout << "����������ѡ���ַ���";
		cin >> choice;
		menu(choice);
		return;
	case '1':cout << "��Ҫ�������밴�ַ���Ӧ�����룬�˳�������q��";
		cin >> choice;
		menu(choice);

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