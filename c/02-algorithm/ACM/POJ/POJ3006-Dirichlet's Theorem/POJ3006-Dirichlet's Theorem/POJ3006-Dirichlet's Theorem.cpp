/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 3006
	Problem:    Dirichlet's Theorem on Arithmetic Progressions
	URL:		http://poj.org/problem?id=3006
*/

/*
	���������
	 ���������˵����������У�����ʵû�õ��������׶�������⡣
	 �����������м����� a+nd �ĵȲ����У�����a��d���ʣ���Լ��ֻ��1��������Ȼ������n=1,2,3,......
	 ��֪�ڵ������������У��������������������Щ����ģdͬ��a��������û�õ�������ԣ�

	 �ָ���a��d��ͨ������������������У��������еĵ�n��������
	 ���� a��[1,9307], b��[1,346], n��[1,210]


	����˼·��
	 ����Ĺؼ����ǵ����������У�������������
	 �����ķ�Χ����ͨ�� a��b��n �����ֵȦ����ԼΪ100W���ڣ���
	 ����������֮����Ǳ�����ѧ�Ĺ�����

	 �� ��ɸ����ȡ��Ŀ�������Χ�ڵ���������
	 �� ����a��b��������������У�ͨ���������ҵ����е�n������

*/

#include <memory.h>
#include <math.h>
#include <iostream>
using namespace std;


const static int LEN = 1000000;							// ��Ȼ�����鳤��(���������Χ)
const static int SQRT_NUM = ceil(sqrt((double) LEN));	// ���ݺ�������õ�����������Χ

/* 
 * ʹ��ɸ���ҳ���Ȼ����Χ�ڵ���������
 * @param primes ������
 */
void findPrimes(bool* primes);

/* 
 * ��ȡ�������������е�n������
 * @param primes ������
 * @param a �����������в��� a��[1,9307]
 * @param d �����������в��� b��[1,346]
 * @param n �����õ�������� n��[1,210]
 * return �����õ��ĵ�n������
 */
int getDirichletPrime(bool* primes, int a, int d, int n);

int main(void) {
	bool primes[LEN];		// ������, ���ÿ����Ȼ���Ƿ�Ϊ����
	findPrimes(primes);		// �ҳ���Χ����������

	int a, d, n;
	while(cin >> a >> d >> n && (a + d + n != 0)) {
		int prime = getDirichletPrime(primes, a, d, n);
		cout << prime << endl;
	}
	return 0;
}


void findPrimes(bool* primes) {
	memset(primes, true, sizeof(bool) * LEN);	// ע��memset�ǰ��ֽڸ�д�ڴ��
	primes[0] = primes[1] = false;

	for(int i = 2; i <= SQRT_NUM; i++) {
		if(primes[i] == false) {
			continue;
		}

		// ɸ����С���������б���
		int multiple = 2;	// i�ı��ʣ��򲻰�������, ��2����ʼ��	
		while(true) {
			int mNum = i * multiple;	// i�ı���
			if(mNum >= LEN) {
				break;
			}
			primes[mNum] = false;
			multiple++;
		}
	}
}

int getDirichletPrime(bool* primes, int a, int d, int n) {
	int dirichlet = 0;	// ��n������
	int cnt = 0;		// �������ּ�����
	int i = 1;
	while(true) {
		int num = a + i * d;
		if(primes[num] == true) {
			cnt++;
			if(cnt >= n) {
				dirichlet = num;
				break;
			}
		}
	}
	return dirichlet;
}