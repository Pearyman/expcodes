//�����0��1Ϊ��������а�λ�߼�����ֵ.    6����λ�߼������ ~ & | ^ << >>

#include<iostream>
using namespace std;
int main(void)
{
	int a;
	a=0&0;
	cout<<"0&0="<<a<<endl;
	a=1&0;
	cout<<"1&0="<<a<<endl;
	a=0&1;
	cout<<"0&1="<<a<<endl;
	a=1&1;
	cout<<"1&1="<<a<<endl;

	a=0|0;
	cout<<"0|0="<<a<<endl;
	a=1|0;
	cout<<"1|0="<<a<<endl;
	a=0|1;
	cout<<"0|1="<<a<<endl;
	a=1|1;
	cout<<"1|1="<<a<<endl;

	a=0>>0;
	cout<<"0>>0="<<a<<endl;
	a=1>>0;
	cout<<"1>>0="<<a<<endl;
	a=0>>1;
	cout<<"0>>1="<<a<<endl;
	a=1>>1;
	cout<<"1>>1="<<a<<endl;

	a=0<<0;
	cout<<"0<<0="<<a<<endl;
	a=1<<0;
	cout<<"1<<0="<<a<<endl;
	a=0<<1;
	cout<<"0<<1="<<a<<endl;
	a=1<<1;
	cout<<"1<<1="<<a<<endl;

	a=0^0;
	cout<<"0^0="<<a<<endl;
	a=1^0;
	cout<<"1^0="<<a<<endl;
	a=0^1;
	cout<<"0^1="<<a<<endl;
	a=1^1;
	cout<<"1^1="<<a<<endl;

	a=~0;
	cout<<"~0="<<a<<endl;
	a=~1;
	cout<<"~1="<<a<<endl;

	system("pause");
	return 0;
}