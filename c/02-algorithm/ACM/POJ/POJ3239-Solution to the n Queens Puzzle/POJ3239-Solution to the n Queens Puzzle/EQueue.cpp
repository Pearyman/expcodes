#include<iostream>
using namespace std;
#include<stdlib.h>
#include<ctime>
#define N 8
#define MAX 65536
int Queen[N];
int Evaluation[N];	
int __main()
{
    int sum=1;
    bool flag=true;
    int min=N+1;
    int CurrentPosition=0;
    srand((unsigned int)time(0));
    int count=0;
    while(sum!=0 && count < 20)
    {
        cout<<"number "<<count++<<endl;
        flag=true;
        for(int i=0;i<N;i++)
        {
            Queen[i]=rand()%N;	// Ԥѡn���ʺ��λ��
        }

        while(flag)
        {
            sum=0;
            flag=false;	// lqb: ��Ǳ����Ƿ���λ������


            for(int i=0;i<N;i++)//����ÿ��
            {
                min=MAX;
                for(int ii=0;ii<N;ii++)//���г�ͻ������
                {
                    Evaluation[ii]=0;
                }

				// lqb: �������лʺ󣬼��㵱ǰ�����и��ӵĳ�ͻ��, ȡ��ͻ����С��һ��
                for(int l=0;l<N;l++)//���ڵ�i�еĵ�l������
                {
                    for(int j=0;j<N;j++)//���ڵ�j���ʺ�
                    {
                        if(j==i)//��i���еĵ�i���ʺ���ڵ�ǰ�еĳ�ͻ���ü��� ????
                            continue;


						// lqb:  ͬ�и���б�ʸ� ��ͻ��+1
                        if(Queen[j] == l)
                            Evaluation[l]++;

                        else if((Queen[j]-l) / (j-i) == 1 || (Queen[j]  -l) / (j-i) == -1)
                            Evaluation[l]++;
                    }

                    //cout<<Evaluation[l];
                    if(Evaluation[l]<min)
                    {
                        min=Evaluation[l];
                        CurrentPosition=l;
                    }

					// ������������ͬ����Сֵʱ��ͨ��������ж�ȡ��ʷ����ȡ��ǰ
                    if(Evaluation[l]==min && rand()%2)//�����е������
                    {
                        min=Evaluation[l];
                        CurrentPosition=l;
                    }
                }


				// lqb: ������i���ʺ��λ��
                //cout<<endl;
                if(Queen[i]!=CurrentPosition)
                {
                    Queen[i]=CurrentPosition;
                    sum+=Evaluation[CurrentPosition];
                    flag=true;
                }
                else
                {
                    sum+=Evaluation[Queen[i]];
                }
            }
            //cout<<endl;
        }
        for(int i=0;i<N;i++)
        {
            cout<<Queen[i]<<" ";
        }
        cout<<endl;
		cout<<sum << endl;
    }
    //cout<<sum;
    cout<<endl;
	system("pause");
	return 0;
}