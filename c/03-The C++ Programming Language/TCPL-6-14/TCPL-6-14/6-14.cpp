//��д����rev()ʹ�ַ�����β����

#include<iostream>
using namespace std;

char* REV(char* p)
{
	char* s=p+strlen(p)-1;           //ʹsָ��p�ַ���'\0'��ǰһ���ַ�
	char* t=new char[strlen(p)+1];   //ע��洢�ռ��С������Ϊʲô��һ����-1��������+1
	char* ca=t;                      //Ŀ����ʹ��󷵻�һ��ָ��������ַ�����ͷ��ָ��
	while((s+1)!=p)                  //��ѭ����֪�ڸ�����p��һ���ַ���sָ����p�ַ�����ͷ�����棬�����s+1��p�ȽϽ���ѭ��
		//pָ����ʼ����û���ƶ�
		*t++=*s--;
	*t='\0';                         //�������t�����û��'\0'�ģ�����������
	return ca;
}

int main(void)
{
	char a[]="hjhg46 87!@##$%^*()\t\n+_-==";
	char* q=REV(a);
	cout<<q<<endl;

	system("pause");
	return 0;
}