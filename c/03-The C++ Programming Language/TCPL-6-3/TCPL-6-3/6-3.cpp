//����һϵ���ɿո�ָ��� �����֣�ֵ����  ���ַ�����Ȼ��ֱ��ÿһ�Զ�Ӧ��������������ֵ֮�ͼ�ƽ��ֵ

#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int main()
{
	//	string input="li 78 king 67 dyu 78.9";
	string input;
	cout<<"Please input a series of 'name value'"<<endl;
	getline(cin,input);
	double num,ave,sum=0;
	int i=0;
	string str;
	istringstream iss(input);
	while(iss>>str>>num)
	{
		cout<<str<<':'<<num<<endl;
		sum+=num;
		i++;
	}
	ave=sum/i;
	cout<<"Value Sum="<<sum<<"\nValue average="<<ave<<endl;

	system("pause");
	return 0;
}
