/*
	Author:     Exp
	Date:       2017-12-01
	Code:       POJ 1753
	Problem:    Flip Game
	URL:		http://poj.org/problem?id=1753
*/

/*
	���������
	 ʹ����ȫ�ڣ���Ҫ��ת���ٲ�

	����˼·��

	  �����̾�����б��룺
	    * * * *      ���ҵ���ֱ�Ϊ�� 0, 1, 2, 3λ
	    % % % %      ���ҵ���ֱ�Ϊ�� 4, 5, 6, 7λ
	    # # # #      ���ҵ���ֱ�Ϊ�� 8, 9,10,11λ
        @ @ @ @      ���ҵ���ֱ�Ϊ��12,13,14,15λ

	  ��������ÿһ��ֻ�кڰ�����״̬������0��1���б�ʾ���ɴ˿�ת���ɶ���������
	    @@@@ #### %%%% ****
	   15      ��         0

	  ���տ�����һ��int���洢��������״̬��
	    �� ����תĳһλ�ϵ�����ʱ���൱��ʹ��λ�� 1 ���������.
		�� ���̴���ȫ��״̬ʱ��intֵΪ 0x0000
		�� ���̴���ȫ��״̬ʱ��intֵΪ 0xFFFF


	  ��¼��ȫ��=0��ʼ��������ת0~16�κ���Ե��������״̬.
	  ���������ֻ�ܷ�16�Σ���2^16 = 65536 ��״̬

*/


#include <set>
#include <iostream>
using namespace std;


/**
 * ��ת�����ϵ�һֻ����
 * @param chess ��תǰ�����̱���
 * @param pos Ҫ��ת������λ��, ȡֵ��ΧΪ[0, 15]
 * return ��ת������̱���
 */
int filp(int chess, int pos);


/**
 * �ж������Ƿ�Ϊ��ɫ��ȫ�ڻ�ȫ�ף�
 * return true:��ɫ; false:�ǵ�ɫ
 */
bool isMonochrome(int chess);


int main(void) {
	set<int>* statusTable = new set<int>[17];	// ��¼����0~16�ε�����״̬
	int chess = 0;	// ��ʼ״̬��ȫ�ڣ�

	
	//for(int s = 1; s <= 16; s++) {
	//	set<int> lastStatus = status[s - 1];
	//	set<int> curStatus = status[s];

	//}

	//for(int pos = 0; pos < 16; pos++) {
	//	//int chess = status[0].iterator(); ��һ�ε�״̬

	//	statusTable[1].insert(filp(chess, pos));
	//}

	statusTable[0].insert(chess);	// ����0��
	for(int a = 0; a < 16; a++) {

		for(int b = 0; b < 16; b++) {

			for(int c = 0; c < 16; c++) {

				for(int d = 0; d < 16; d++) {

				}
			}
		}
	}
	
	int input = 0;	// FIXME
	int step = -1;
	for(int s = 0; s <= 16; s++) {
		set<int> status = statusTable[step];
		if(status.count(input) > 0) {
			step = s;
			break;
		}
	}
	if(step >= 0) {
		cout << step << endl;
	} else {
		cout << "Impossible" << endl;
	}
	return 0;
}


int filp(int chess, int pos) {
	int op = 0x01 << pos;	// ��ת��������λ��
	if(pos > 3) { op |= (pos - 4);  }	// ��ת�����Ϸ�������
	if(pos < 12) { op |= (pos + 4);  }	// ��ת�����·�������

	int mod = pos % 4;
	if(mod != 0) { op |= (pos - 1);  }	// ��ת�����󷽵�����
	if(mod != 3) { op |= (pos + 1);  }	// ��ת�����ҷ�������

	return chess ^ op;
}


bool isMonochrome(int chess) {
	return (chess == 0 || chess == 0xFFFF);
}