//��д����cat()����ƴ�������ַ�����ƴ�ӵ��ַ�������new���ٵĿռ�

#include<iostream>
using namespace std;

char* CAT(char* s,char* t)
{
	char* p=new char[strlen(s)+strlen(t)];   //��ʹ��new char[strlen(s)+strlen(t)+1]����Ϊ�������ʹ��ƴ�Ӻ���ַ������ȱ�ԭ��
	//�����ַ����ܳ�֮����1  (����һ��'\0')

	char* ca=p;//�ⲽ�ǽ���ģ�ʹcaָ��new���ٵĴ洢�ռ俪ͷ����������������󷵻ص���һ��ָ��new����ָ��p����Ϊ����ĳ����������鷳
	while(*s)         //���ﲻ��ʹ��while(*p++=*s++); ����s�е�'\0'Ҳ�ᱻ���Ƶ�p��ʹ�����ַ������Ӻ��м仹��һ��'\0'
		*p++=*s++;    //Ŀ����ʹ��s���ֻ�ƶ�ָ�룬������'\0'
	//����ʹ��*(p++)=*(s++)Ҳ�Ǵ��������������ʹ�ַ�ֵ��1��������ָ���ƶ�����ַ��1��
	while(*p++=*t++); //����ͬ�ϣ�������Ŀ����ʹ��t�����ƶ�ָ�룬�ָ���'\0'
	return ca;        //ע�ⲻ�ܷ���*ca��*ca��char�ַ�������char*ָ��
}

int main(void)
{
	char a[]="zxcvb 098jfh\n";
	char b[]="%!@#$^&*()oim \tYYk";
	char* q=CAT(a,b);
	cout<<q<<endl;         //cout<<*q<<endl;  �����Ĵ���ֻ�����һ���ַ�

	system("pause");
	return 0;
}