//�ֱ�ͳ��string�ַ�����char�ַ�������ĳ�� �ַ��� ���ֵ�Ƶ��,���������ַ���

#include<iostream>
#include<string>
using namespace std;

void style_Cpp(void)
{
	int i,count=0;
	string str;       //������Ϊstring�������ʵ����һ��ָ���ַ�����ַ�ġ�ָ�롱
	string let;       //�������ָ��ֵ�Ȳ��ܸ�ֵ��ͬ���͵�string��ָ�롱�������ܸ�ֵ��char*ָ��
	cout<<"Please input a string:"<<endl;
	cin>>str;
	cout<<"please input a pair of letters:"<<endl;
	cin>>let;
	cout<<endl;
	for(i=0;i<sizeof(str);i++)
		if(let[0]==str[i])     //����ͨ���±��ҵ�string��ָ�롱��ָ���ַ����еľ���ĳ���ַ�
			if(let[1]==str[i+1])
			{
				count++;
				if(let[0]==let[1])  //�����ַ���Ϊ����ʱ���ַ����պ��ִ���3�����ϵ��ֵ��ظ����������
					i++;            //���û������жϣ���ô�ж�����"abcccd"��"cc"�ĸ���ʱ�����ж�Ϊ2��
			}
			cout<<"There are(is) "<<count<<" '"<<let<<"' int the string '"<<str<<"'."<<endl;
			//	cout<<sizeof(str)<<endl;  //�������string�ַ�����Ĭ�ϴ������Ϊ16���ַ�
			return;
}

void style_C(void)
{
	int i,count=0;
	char stri[30],lett[2];
	cout<<"Please input a string:"<<endl;
	gets(stri);
	cout<<"please input a pair of letters:"<<endl;
	gets(lett);
	cout<<endl;
	for(i=0;stri[i]!='\0';i++)
		if(lett[0]==stri[i])
			if(lett[1]==stri[i+1])
			{
				count++;
				if(lett[0]==lett[1])
					i++;
			}
			cout<<"There are(is) "<<count<<" '"<<lett<<"' int the string '"<<stri<<"'."<<endl;
			return;
}

int main()
{
	cout<<"=====================style_Cpp====================="<<endl;
	style_Cpp();

	getchar();
	//���ַ�����������ж���û������
	//�����ŵ�һ���ļ�ʱ����C++��ִ�У�Ҫע��C����ַ�����ĸ�ֵ�ص�
	//��������������C++���һ������let�Ļس������Ե�������ȻC�е�����S�ʹ���˻س����������ٶ��������ַ�����
	cout<<endl;

	cout<<"======================style_C======================"<<endl;
	style_C();
	cout<<endl;

	//��C�����ִ��ʱ����������ʹ��getchar()���Ե����س������ɼ�C++��string�Ǿ����Ż���
	cout<<"=====================style_Cpp====================="<<endl;
	style_Cpp();
	cout<<endl;

	system("pause");
	return 0;
}


