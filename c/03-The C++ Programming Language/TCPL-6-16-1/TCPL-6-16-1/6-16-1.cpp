//����ת��!!
//���ڶ���ʮ���ơ��˽��ơ�ʮ��������ʽ���ַ�����������ַ��������ֽ�����ʽ�����Ҳ�����ֽ�����ʽ

#include<iostream>
#include<sstream>   //istringstream
#include<cctype>     //isdigit,isalpha
#include<iomanip>    //hex,oct,dec,showbase,uppercase
using namespace std;
void ATOI(const char* pc)
{
	int num;
	istringstream iss(pc);
	if(*pc=='0'&&isdigit(*(pc+1)))        //����ʮ���ơ��˽��ơ�ʮ�����ƣ�0ֵ����һ���ģ���������Ϊ�˷����������0����˽���
	{                                         ///isdigit(ch)�ж�ch�Ƿ�Ϊ���֣��Ƿ��ط��㣬�񷵻���
		iss>>oct>>num;
		cout<<showbase<<oct<<num<<endl;
	}
	else if(*pc=='0'&&isalpha(*(pc+1)))        //isalpha(ch)�ж�ch�Ƿ�Ϊ��ĸ���Ƿ��ط��㣬�񷵻���
	{	
		iss>>hex>>num;
		cout<<uppercase<<showbase<<hex<<num<<endl;
	}
	else
	{
		iss>>dec>>num;
		cout<<num<<endl;
	}
	iss.str("");                      //���iss�洢����
	return;
}
int main(void)
{
	char str[10];
	cin>>str;
	ATOI(str);
	
	system("pause");
	return 0;
}

