//����ת��!!
//���ڶ���ʮ���ơ��˽��ơ�ʮ��������ʽ���ַ���������������ַ��������ֽ�����ʽ�������ת��Ϊʮ����ֵ

#include<iostream>
#include<sstream>   //istringstream
#include<cctype>     //isdigit,isalpha
#include<iomanip>    //hex,oct,dec
using namespace std;
int ATOI(const char* pc)
{
	int num;
	istringstream iss(pc);
	if(*pc=='0'&&isdigit(*(pc+1)))        //����ʮ���ơ��˽��ơ�ʮ�����ƣ�0ֵ����һ���ģ���������Ϊ�˷����������0����˽���
		iss>>oct>>num;                        //isdigit(ch)�ж�ch�Ƿ�Ϊ���֣��Ƿ��ط��㣬�񷵻���
	else if(*pc=='0'&&isalpha(*(pc+1)))	    //isalpha(ch)�ж�ch�Ƿ�Ϊ��ĸ���Ƿ��ط��㣬�񷵻���
		iss>>hex>>num;
	else
		iss>>dec>>num;
	iss.str("");                      //���iss�洢����
	return num;
}
int main(void)
{
	char str[10];
	cin>>str;
	cout<<ATOI(str)<<endl;

	system("pause");
	return 0;
}