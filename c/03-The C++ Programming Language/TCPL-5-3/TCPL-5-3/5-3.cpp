//�ض���������

#include<iostream>
#include<string>
using namespace std;
int main(void)
{
	typedef unsigned char uchar;//�ض�������unsigned char
	typedef const unsigned char cuchar;//�ض�������const unsigned char
	typedef int* pint;//��������ָ��
	typedef char* pchar;//���ַ���ָ��
	typedef char** ppchar;//���ַ��� ָ���ָ��
	typedef char (*Pchar)[10];//���ַ��������ָ�� (ָ����10��Ԫ�ص��ַ������ָ��)
	typedef int NUM[3];//����3��Ԫ�ص���������
	NUM n;
	int i;
	int a[3][3]={6,7,8,4,5,6,8,9,0};
	int b[]={1,2,3,4,5,6,7};
	for(i=0;i<3;i++)
		{n[i]=i;cout<<n[i]<<','<<endl;}
	typedef int (*BER)[3];//�����͵������ָ�� (ָ����3��Ԫ�ص��ַ������ָ��)
	BER k;
	int (*j)[3]=a;
	for(k=a;k<a+3;k++,j++)
		cout<<**k<<**j<<endl;
	typedef int* pintt[7];//7����������ָ������� (һ������7������ָ��Ԫ�ص�����)
	pintt f;
	for(i=0;i<7;i++)
		{f[i]=&b[i];cout<<*f[i]<<endl;}

	system("pause");
	return 0;
}