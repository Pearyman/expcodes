#include<iostream>
using namespace std;

//����������from���Ƶ���������to,����count������to�ĳ���
//������to�ĳ��ȱ�����from�ĳ��� С����ֻ��������from��ǰcount��Ԫ��
//������to�ĳ��ȱ�����from�ĳ��� ����ѭ����������from
void send(int* to,int* from,int count)
{
	int n=(count+7)/8;
	switch(count%8){
	case 0: do{*to++=*from++;
	case 7:    *to++=*from++;
	case 6:    *to++=*from++;
	case 5:    *to++=*from++;
	case 4:    *to++=*from++;
	case 3:    *to++=*from++;
	case 2:    *to++=*from++;
	case 1:    *to++=*from++;
			}while(--n>0);
	}
}

int main(void)
{
	const int NUM=5;
	int a[NUM];
	int b[11]={19,18,17,16,15,14,13,12,11,10,9};
	int i;
	send(a,b,NUM);
	for(i=0;i<NUM;i++)
		cout<<a[i]<<' ';
	cout<<endl;

	system("pause");
	return 0;
}
