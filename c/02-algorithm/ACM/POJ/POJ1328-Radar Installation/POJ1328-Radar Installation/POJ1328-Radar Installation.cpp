/*
	Author:     Exp
	Date:       2017-11-30
	Code:       POJ 1328
	Problem:    Radar Installation
	URL:		http://poj.org/problem?id=1328
*/

/*
	���������
	  ����һ��ֱ������ϵ������x��Ϊ�����ߣ��������Ϸ��Ǻ����·���½��.
	  �ں������Ƿֲ�һЩ����, ��ҪҪ�ں������ϰ�װ���ɸ��״︲����Щ����,
	  ÿ���״�ĸ��ǰ뾶������ͬ�ҹ̶���.

	  ���ڸ������к���������(x,y), �Լ��״�ĸ��ǰ뾶d��
	  �ʿ��Ը������к�������С�״���.


	����˼·��
	  ���ȿ�����ȷ���ǣ�ֻҪ��������һ������λ�ó����״���󸲸ǰ뾶����y>d�������޽�.

	  �����к����� y<=d ��ǰ����ȥ˼�������⣬
	  ��ô����������������Ҫ֪����һ���״�Ҫ����һ������������԰�װ��Χ�Ƕ��١�

	  �Ժ�������(x,y)ΪԲ�ģ����״︲�ǰ뾶d��Բ������ǰ��������֪��
	  ���Բ��x��ض���������1��(y=d)�����2������(y<d).

	  ������Ϊ1��������2�������غϵ������������ô��2��������x���Ϲ��ɵ��������䣬
	  ���Կ��������ı����Ƿ�Χ��x���ϵ�ͶӰ (�ɴ˾Ϳ��԰Ѷ�ά�ļ�������ת����һά��������)

	  �������к�����x�����꣬��С�������μ���ÿ��������x���ϵ�ͶӰ���䣨ͶӰ���ܴ����ص�����
	  ͬʱ��ÿ���״�����1���㣬��ô�������ת���ɣ�

	  ����֪x�������ɸ����䣨���ܴ��ڽ�����������Ҫ����Щ�����ڷ����ɸ��㣬
	  ������������Щ�㣬ʹ��ÿ�����������ٴ���һ���㣬�������õĵ���������������١�
	
	  
	  ��ʹ��̰���㷨��⣺
	    ������n��������x����˳���С���������Ӧ������:
		�� �ڵ�i��������Ҷ˵� R(i) ����һ���㣬�ܷ��õ��� P+1 , ����i��[1, n]
		�� ��j=i
		�� ��j++
		�� ����j���������˵� L(j)<=R(i)����ת�ۣ�����ת��
		�� ��i=j��ת��
*/


#include <iostream>
using namespace std;



int main(void) {

	return 0;
}






//Memory Time 
//288K   110MS 


#include<iostream>
#include<math.h>
using namespace std;

const int island_max=1000;

int main(void)
{
	int i,j;
	double x[island_max],y[island_max];
	double num,rad;
	for(;;)
	{
		/*Input end*/
		cin>>num>>rad;
		if(!(num&&rad))break;

		static int count=1;  //��¼case��Ŀ

		/*read in coordinate*/
		bool flag=false;
		for(i=0;i<num;i++)
		{
			cin>>x[i]>>y[i];
			if(y[i]>rad)
				flag=true;
		}

		/*case fail*/
		if(flag)
		{
			cout<<"Case "<<count++<<": -1"<<endl;
			continue;
		}

		/*bubble sort*/
		//��������yҪ��x�������򣬲��ܼ򵥵�ʹ�� ����qsort
		double temp;
		for(i=0;i<num-1;i++)
			for(j=0;j<num-i-1;j++)
				if(x[j]>x[j+1])
				{
					temp=x[j];
					x[j]=x[j+1];
					x[j+1]=temp;
					temp=y[j];
					y[j]=y[j+1];
					y[j+1]=temp;
				}

				double left[island_max],righ[island_max];  //����Բ�ں������ϵ����ҽ���
				for(i=0;i<num;i++)
				{
					left[i]=x[i]-sqrt(rad*rad-y[i]*y[i]);
					righ[i]=x[i]+sqrt(rad*rad-y[i]*y[i]);
				}

				int radar=1;
				for(i=0,temp=righ[0];i<num-1;i++)
					if(left[i+1]>temp)
					{
						temp=righ[i+1];
						radar++;
					}
					else if(righ[i+1]<temp)
						temp=righ[i+1];

				cout<<"Case "<<count++<<": "<<radar<<endl;
	}
	return 0;
}