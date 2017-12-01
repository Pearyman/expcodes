/*****************************************
  Description: �㷨���߰�-��ѧ
  Authod     : EXP
  Modify By  : None
  Date       : 2017-12-01
******************************************/

#define DLL_IMPLEMENT

#include "stdafx.h"
#include <math.h>
#include <memory.h>
#include "algorithm_math.h"


/**
 * ���캯�������� [2, range] ��Χ�ڵ���������
 *  ע�⣺��range>100Wʱ��ĳЩ������������ʱ���ܻ��������ʱ�쳣��
 *			ԭ���Ǳ�����Ĭ�Ϸ���Ķ�ջ��С������Ĭ��1M������ʱ���˹��޸Ŀɷ���Ķ�ջ��С
 * @param range ��Ȼ����Χ
 */
DLL_API Prime::Prime(int range) {
	this->range = (range < 2 ? 2 : range + 1);
	this->isPrimes = new bool[this->range];

	this->count = screen();
	this->primes = new int[this->count];
	toPrimes();
}


/**
 * ��������
 */
DLL_API Prime::~Prime() {
	delete[] isPrimes; isPrimes = NULL;
	delete[] primes; primes = NULL;
}


/**
 * ʹ�ð�����˹����ɸ�����������
 * return ��������С
 */
int Prime::screen(void) {
	memset(isPrimes, true, sizeof(bool) * range);	// ע��memset�ǰ��ֽڸ�д�ڴ��
	isPrimes[0] = isPrimes[1] = false;
	int cnt = 2;	// ����������

	const int SQRT_NUM = ceil(sqrt((double) range));
	for(int i = 2; i <= SQRT_NUM; i++) {
		if(isPrimes[i] == false) {
			continue;
		}

		// ɸ����С���������б���
		int multiple = 2;	// i�ı��ʣ��򲻰�������, ��2����ʼ��	
		while(true) {
			int mNum = i * multiple;	// i�ı���
			if(mNum >= range) {
				break;
			}

			if(isPrimes[mNum] == true) {	// �����ظ�����
				isPrimes[mNum] = false;
				cnt++;
			}
			multiple++;
		}
	}
	return range - cnt;
}


/**
 * ��������Ǽ�ת����������
 */
void Prime::toPrimes(void) {
	for(int i = 0, j = 0; i < range; i++) {
		if(isPrimes[i] == true) {
			primes[j++] = i;
		}
	}
}

/**
 * ��ȡ��Χ�ڵ���������
 * @return ��������
 */
DLL_API int Prime::getCount(void) {
	return count;
}


/**
 * ���ָ�������Ƿ�Ϊ����
 * @param num ���������
 * @return true:������; false:�������� �� ������������ڷ�Χ��
 */
DLL_API bool Prime::isPrime(int num) {
	bool isPrime = false;
	if(num > 1 && num <= range) {
		isPrime = isPrimes[num];
	}
	return isPrime;
}


/**
 * ��ȡ��Χ�ڵ�������
 * @return ������
 */
DLL_API int* Prime::getPrimes(void) {
	return primes;
}