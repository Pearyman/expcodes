//����һϵ�е��ʣ��ÿո��س��ָ�����������Quitʱ������������ĸ��˳���ظ��ش�ӡ��Щ����

#include<iostream>
#include<string>
using namespace std;
int main()
{
	string temp;
	string word[20];               //�����ַ�������
	int i,j,count=0;
	cout<<"Please input some words.\nIf you finish ,input 'Quit'."<<endl;
	cout<<"======================================================"<<endl;
	cout<<"--> ";
	for(i=0;word[i++]!="Quit";)           //����һϵ�е��ʣ�������ַ��������У����ж�����ĵ���ΪQuitʱ��������
	{
		cin>>word[i];
		count++;
	}
	for(i=0;i<count-1;i++)             //����ASCII�������ĵ��ʽ���ð������
		for(j=0;j<count-1-i;j++)
			if(word[j]>word[j+1])
			{
				temp=word[j];
				word[j]=word[j+1];
				word[j+1]=temp;
			}
			for(i=0;i<count;i++)                   //������ͬ�ĵ��ʣ��Ѻ�һ���������¸�ֵΪ"**"
				for(j=i+1;j<count;j++)
					if(word[i]==word[j])
						word[j]="**";                  //ע����Ȼ�ַ����������뵥���ַ������������õ����ַ�ȥ��ֵ����˲�����'*'���¸�ֵ
			cout<<endl;
			cout<<endl;
			cout<<"======================================================"<<endl;
			cout<<"Now print your words:"<<endl;              //��ӡ�������һϵ�е��ʣ���������Ϊ"**"��"Quit"���������൱�ڲ���ӡ�ظ�����
			cout<<"--> ";
			for(i=1;i<count;i++)                              //��i=1��ʼʱ��Ϊ�������ж�ʱword[1]�������ˣ��������
				if(word[i]=="**"||word[i]=="Quit")
					continue;
				else
					cout<<word[i]<<' ';
			cout<<endl;
			cout<<"======================================================"<<endl;

	system("pause");
	return 0;
}
