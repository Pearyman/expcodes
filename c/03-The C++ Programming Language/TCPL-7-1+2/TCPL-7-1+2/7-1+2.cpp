//һЩ����ĺ�������

#include<iostream>
using namespace std;

int main(void)
{
	void f1(char*,int&);   //��ָ���ַ���ָ��Ͷ�����������Ϊ������������ֵ
	void (*pf1)(char*,int&)=f1;  //һ��ָ�����������ָ��  or    void (*pf1)(char* pc,int& i)=&f1

	typedef void (*pf2)(char*,int&);  
	void f3(pf2);         //һ��������ָ��Ϊ�����ĺ���
	pf2 f4(char*,int&);   //��������ָ��ĺ���
	pf2 f5(pf2);         //��������ָ����Ϊ�������������������Ϊ����ֵ

	//	int rif(int,int);
	typedef int (&rifii)(int,int);
	rifii rif(int,int);               //˭��˭�����ã�

	return 0;
}
// pf2 f5(pf2)   ���壿����������
// {
//...
// }