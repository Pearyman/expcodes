//�������������͵�����

#include<iostream>
#include<string>
using namespace std;

int main()
{
	char c='h';
	int x=9,y=0;
	int f(int m);//����һ������
	int (&ff)(int n)=f;//�Ժ���������
	char* pc=&c;//һ�����ַ���ָ��
	char** pcc=&pc;//һ�����ַ���ָ���ָ��
	int num[10]={1,9,8,7,6,0,5,4,3,2};//һ������10������������
	int (&NUM)[10]=num;//һ������10�����������������
	char* ps="wanglin";//һ�����ַ����������ָ��
	string str="liangting";//һ�����ַ����������ָ��
	const int a=8;//һ����������
	const int* pa=&a;//һ��������������ָ��
	int *const px=&x;//һ���������ĳ���ָ��
	y=ff(y);
	y=f(y);
	cout<<"y="<<y<<endl;
	cout<<"*pc="<<*pc<<endl;
	cout<<"**pcc="<<**pcc<<endl;
	cout<<"ps="<<ps<<endl;
	cout<<"str="<<str<<endl;
	cout<<"const int* pa="<<*pa<<endl;
	cout<<"int *const px="<<*px<<endl;
	for(x=0;x<10;x++)
		cout<<"NUM["<<x<<"]="<<NUM[x]<<endl;

	system("pause");
	return 0;
}

int f(int m)
{
	m++;
	return m;
}