//���ֵȼ�ѭ��

#include<iostream>
#include<string>
using namespace std;
int main(void)
{
	char str[]="?hgju? du??76?=098dd?jnmcn??";
	char* input_line=str;
	int max_length=strlen(str);
	int i,quest_count=0;
	//ԭ�����
	for(i=0;i<max_length;i++)
		if(input_line[i]=='?')
			quest_count++;
	cout<<"ԭ�����quest_count="<<quest_count<<endl;
	quest_count=0;
	//��д����
	i=0;
	while(i<max_length)
	{
		if(input_line[i]=='?')
			quest_count++;
		i++;
	}
	cout<<"��д����quest_count="<<quest_count<<endl;

	system("pause");
	return 0;
}
