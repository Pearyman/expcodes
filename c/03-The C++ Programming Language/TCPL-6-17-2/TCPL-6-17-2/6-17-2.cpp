//����ת��!!
//�����������ݵ�char[]�ַ���

#include<iostream>
using namespace std;
char* ITOA(int i,char b[])
{
	char* pb=b;
	int count=0;
	while(i/10>0)          //���￪ʼת������
	{
		*pb++=i%10+'0';   //�������ּ���'0'�����ַ�
		i/=10;
		count++;
	}
	*pb=i+'0';
	count++;
	char* t=new char[count+1];          //��������ת��ʱ���µ����⣬���￪ʼ��β��������
	char* pt=t;         //����new�ռ��׵�ַ�����ڷ���ָ��ֵ
	while((pb+1)!=b)
		*t++=*pb--;
	*t='\0';
	return pt;
}

int main(void)
{
	int num;
	char a[10];
	cin>>num;
	cout<<ITOA(num,a)<<endl;

	system("pause");
	return 0;
}

