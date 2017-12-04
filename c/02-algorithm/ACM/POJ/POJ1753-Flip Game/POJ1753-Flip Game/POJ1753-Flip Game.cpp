/*
	Author:     Exp
	Date:       2017-12-01
	Code:       POJ 1753
	Problem:    Flip Game
	URL:		http://poj.org/problem?id=1753
*/

/*
	���������
	 ��ĳ��״̬��ʼ��ʹ����ȫ�ڻ�ȫ�ף�������Ҫ��ת���ٲ�

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

// �޷�������(32λ)
typedef unsigned int _UINT;

const static int MAX_STEP = 16;			// �ɷ���������
const static int MAX_STATUS = 65536;	// ��״̬�� = 2^16

class Chess {
	public:
		Chess();
		~Chess();
		int getStep(int chess);

	private:
		void initAllStatus(void);
		_UINT filp(_UINT chess, int bitPos);
		int getMaxBitPos(_UINT chess);

		bool isMonochrome(_UINT chess);
		int getFilpCount(_UINT chess);

	private:
		set<_UINT>* chessStatus;
		int* steps;
};


int main(void) {
	Chess* chess = new Chess();

	int status = 0;
	int byteCnt = 0;
	char byteBuff[5] = { '\0' };
	while(cin >> byteBuff && ++byteCnt) {
		int offset = 4 * (byteCnt - 1);
		for(int i = 0; i < 4; i++) {
			if(byteBuff[i] == 'w') {	// b���Ϊ0, w���Ϊ1
				status |= (0x00000001 << (i + offset));
			}
		}

		if(byteCnt >= 4) {
			int step = chess->getStep(status);
			if(step >= 0) {
				cout << step << endl;
			} else {
				cout << "Impossible" << endl;
			}

			byteCnt = 0;
			status = 0;
		}
	}
	delete chess;
	return 0;
}


Chess::Chess() {
	this->chessStatus = new set<_UINT>[MAX_STEP + 1];

	this->steps = new int[MAX_STATUS];
	memset(steps, -1, sizeof(int) * MAX_STATUS);

	initAllStatus();
}


Chess::~Chess() {
	for(int s = 0; s <= MAX_STEP; s++) {
		chessStatus->clear();
	}
	delete[] chessStatus; chessStatus = NULL;
	delete[] steps; steps = NULL;
}


void Chess::initAllStatus(void) {
	const int ALL_ZERO_CHESS = 0;
	steps[ALL_ZERO_CHESS] = 0;
	chessStatus[0].insert(ALL_ZERO_CHESS);	// ����0�ε�״̬��(��ʼ״̬������ȫ��)

	//int cnt = 1;

	// ��¼����1-16�ε�����״̬��
	for(int filpCnt = 1; filpCnt <= MAX_STEP; filpCnt++) {
		set<_UINT>* lastStatus = &chessStatus[filpCnt - 1];	// ��ǰһ�ε�״̬�������Ϸ�������
		set<_UINT>* curStatus = &chessStatus[filpCnt];	// ���·���filpCnt��״̬��

		for(set<_UINT>::iterator its = lastStatus->begin(); its != lastStatus->end(); its++) {
			_UINT chess = *its;
			for(int pos = getMaxBitPos(chess) + 1; pos < 16; pos++) {
				_UINT nextChess = filp(chess, pos);
				curStatus->insert(nextChess);

				// ȡ��һ�γ��ֵļ�����С����
				int status = (nextChess & 0x0000FFFF); // ���β���λ
				if(steps[status] < 0) {
					steps[status] = filpCnt;
				}
			}
		}
		//cout << "����" << filpCnt << "�ι�" << curStatus->size() << "��״̬" << endl;
		//cnt += curStatus->size();
	}
	//cout << "��״̬��" << cnt << endl;
}


/**
 * ��ת�����ϵ�һֻ����
 * @param chess ��תǰ�����̱���(��16λ��ʾ����״̬, ��16λ��ʾ��ȫ0״̬������ǰ״̬�Ĳ���λ)
 * @param bitPos Ҫ��ת������λ��, ȡֵ��ΧΪ[0, 15]
 * return ��ת������̱���
 */
_UINT Chess::filp(_UINT chess, int bitPos) {

	// ��16λ��¼��ǰ����λ
	_UINT op = 0x00010000 << bitPos;

	// ��16λ��¼״̬
	const _UINT BASE = 0x00000001;
	op |= BASE << bitPos;	// ��ת��������λ��
	if(bitPos > 3) { op |= BASE << (bitPos - 4);  }	// ��ת�����Ϸ�������
	if(bitPos < 12) { op |= BASE << (bitPos + 4);  }	// ��ת�����·�������

	int mod = bitPos % 4;
	if(mod != 0) { op |= BASE << (bitPos - 1);  }	// ��ת�����󷽵�����
	if(mod != 3) { op |= BASE << (bitPos + 1);  }	// ��ת�����ҷ�������
	return chess ^ op;
}


/**
 * ��ȡ���̱���ת�����б������һ��
 * return û�в������򷵻�-1�����򷵻�0-15
 */
int Chess::getMaxBitPos(_UINT chess) {
	_UINT MASK = 0x80000000;
	int bitPos = -1;
	for(int i = MAX_STEP - 1; i >= 0; i--) {
		if((chess & MASK) == MASK) {	// ע�������, ==���ȼ���&Ҫ��
			bitPos = i;
			break;
		}
		MASK >>= 1;
	}
	return bitPos;
}


int Chess::getStep(int chess) {
	int step = -1;
	if(chess >= 0 && chess < MAX_STATUS) {
		step = steps[chess];

		//if(step < 0) {
		//	chess = ((~chess) & 0x0000FFFF);	// ȡ��
		//	step = steps[chess];
		//}
	}
	return step;
}


/**
 * ��ȡ���̱���ת���ӵ���������
 * return 
 */
int Chess::getFilpCount(_UINT chess) {
	const _UINT MASK = 0xFFFF0000;
	chess &= MASK;	// ���ε�16λ��״̬λ

	// �жϸ�16λ����λ�ж��ٸ�1, ��Ϊ��ת����
	int cnt = 0;
	while(chess > 0) {
		chess = (chess & (chess - 1));
		cnt++;
	}
	return cnt;
}

/**
 * �ж������Ƿ�Ϊ��ɫ��ȫ�ڻ�ȫ�ף�
 * return true:��ɫ; false:�ǵ�ɫ
 */
bool Chess::isMonochrome(_UINT chess) {
	const _UINT MASK = 0x0000FFFF;
	chess &= MASK;	// ���θ�16λ�Ĳ���λ
	return (chess == 0 || chess == MASK);
}
