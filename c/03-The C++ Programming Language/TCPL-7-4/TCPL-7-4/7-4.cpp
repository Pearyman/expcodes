//����ַ���ƴ��

#include<iostream>
#include<sstream>
#include<string>
using namespace std;

void CAT(string ss[])
{
	int i;
	ostringstream oss;
	for(i=0;ss[i++]!="Exit";)
	{
		cin>>ss[i];
		if(ss[i]!="Exit")
			oss<<ss[i];
	}
	cout<<oss.str()<<endl;
	oss.str("");
	return;
}
int main(void)
{
	const int num=20;
	string str[num];
	cout<<"������Ҫƴ���ַ������ÿո��س��ָ����ɣ�����Exit��������:"<<endl;
	CAT(str);

	system("pause");
	return 0;
}

