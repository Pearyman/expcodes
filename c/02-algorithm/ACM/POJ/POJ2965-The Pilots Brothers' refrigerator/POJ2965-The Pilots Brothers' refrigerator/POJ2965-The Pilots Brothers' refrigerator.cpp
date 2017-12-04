/*
	Author:     Exp
	Date:       2017-12-04
	Code:       POJ 2965
	Problem:    The Pilots Brothers' refrigerator
	URL:        http://poj.org/problem?id=2965
*/

/*
	���������
*/

#include <set>
#include <iostream>
using namespace std;


// �޷�������(32λ)�����ڼ�¼��������룬��ҪΪ�˱���int32�ĸ���Ӱ��
// ��ʼ������״̬Ϊȫ0��ȫ- �򿪣�
// ��16λΪ���������λ���������Ŀ���λ�ñ��Ϊ1
// ��16λΪ������״̬λ, ��¼��ǰ������״̬��+��Ϊ1��-�ر�Ϊ0��
typedef unsigned int _UINT;


const static int MAX_STEP = 16;			// �ɷ���������
const static int MAX_STATUS = 65536;	// ��״̬�� = 2^16�����ظ�����


const static int MASKS[16] = {
	0x0000111F, 0x0000222F, 0x0000444F, 0x0000888F,
	0x000011F1, 0x000022F2, 0x000044F4, 0x000088F8,
	0x00001F11, 0x00002F22, 0x00004F44, 0x00008F88,
	0x0000F111, 0x0000F222, 0x0000F444, 0x0000F888
};


/**
 * ���̶���
 */
class Chess {
	public:
		Chess();
		~Chess();
		int getStep(int status);	// �����ȫ0��ȫ1״̬����ָ������״̬����С����
		int getOp(int status);
		int min(int a, int b);		// ������Сֵ

	private:
		void bfsAllStatus(void);			// ��¼���ظ��ط���1-16���ɵõ�����������״̬
		_UINT filp(_UINT chess, int bitPos);// ����������ĳ��ָ��λλ�õ�����
		
		int toStatus(_UINT chess);		// �����̱�����ȡ����״̬��Ϣ
		int getMaxBitPos(_UINT chess);	// �����̱�����ȡ���̲�����Ϣ������������ת��ŵ�λ��
		int getFilpCount(_UINT chess);	// �����̱�����ȡ���̲�����Ϣ����ȡ���̴�ȫ0״̬��ʼ�����������ӵĴ���

	private:
		set<_UINT>* chessStatus;	// ������ȫ0��ʼ���ֱ��¼���ظ��ط���1-16���ɵõ�����������״̬
		int* steps;					// ������ȫ0��ʼ������ָ������״̬��Ҫ�������ӵ���С����
		int* ops;
};


int main(void) {
	// һ�μ������������״̬���
	Chess* chess = new Chess();

	// ������������״̬ ���
	int chessStatus = 0;
	int byteCnt = 0;
	char byteBuff[5] = { '\0' };
	while(cin >> byteBuff && ++byteCnt) {
		int offset = 4 * (byteCnt - 1);
		for(int i = 0; i < 4; i++) {
			if(byteBuff[i] == '-') {	// -���Ϊ0, +���Ϊ1
				chessStatus |= (0x00000001 << (i + offset));
			}
		}

		// ÿ����4���ֽ����һ��
		if(byteCnt >= 4) {
			chessStatus = (~chessStatus) & 0x0000FFFF;
			int step = chess->getStep(chessStatus);
			cout << step << endl;

			int op = chess->getOp(chessStatus);
			for(int base = 0x0001, bit = 0; bit < MAX_STEP; bit++, base <<= 1) {
				if((op & base) > 0) {
					cout << (bit / 4) + 1 << " " << (bit % 4) + 1 << endl;
				}
			}

			byteCnt = 0;
			chessStatus = 0;
		}
	}
	delete chess;
	return 0;
}


/**
 * ���캯��
 */
Chess::Chess() {
	this->chessStatus = new set<_UINT>[MAX_STEP + 1];

	this->steps = new int[MAX_STATUS];
	memset(steps, -1, sizeof(int) * MAX_STATUS);

	this->ops = new int[MAX_STATUS];
	memset(ops, -1, sizeof(int) * MAX_STATUS);

	bfsAllStatus();
}


/**
 * ��������
 */
Chess::~Chess() {
	for(int s = 0; s <= MAX_STEP; s++) {
		chessStatus->clear();
	}
	delete[] chessStatus; chessStatus = NULL;
	delete[] steps; steps = NULL;
	delete[] ops; ops = NULL;
}


/**
 * ��ʼ�����ظ��ط���1-16���ɵõ�����������״̬
 */
void Chess::bfsAllStatus(void) {
	const int ALL_ZERO_CHESS = 0;
	steps[ALL_ZERO_CHESS] = 0;	// ��ʼ״̬������ȫ��
	chessStatus[0].insert(ALL_ZERO_CHESS);	// ������0�ε�״̬��

	int cnt =0;
	// ��¼�Բ��ظ�����Ϸ�ʽ����1-16�εĿ��Ե��������״̬��
	for(int filpStep = 1; filpStep <= MAX_STEP; filpStep++) {
		set<_UINT>* lastStatus = &chessStatus[filpStep - 1];	// ��һ����״̬��
		set<_UINT>* nextStatus = &chessStatus[filpStep];		// ��һ����״̬��

		// ������һ��ÿ������״̬����������Ͼ��෭һ�����ӣ���Ϊ��һ����״̬��
		for(set<_UINT>::iterator its = lastStatus->begin(); its != lastStatus->end(); its++) {
			_UINT lastChess = *its;	// ��һ������״̬����

			// ��֦1�������Ǵӵ�λ��ſ�ʼ�����ģ�Ϊ�˲��ظ��������ӣ�����һ����״̬�����λ��ſ�ʼ����
			for(int pos = getMaxBitPos(lastChess) + 1; pos < MAX_STEP; pos++) {
				_UINT nextChess = filp(lastChess, pos);	// �������ӵõ���һ������״̬����
				int status = toStatus(nextChess);		// ���θ�16λ����λ���õ���16λ����������״̬

				// ��֦2�������ظ���״̬����Ҫ�Ǽǵ���һ����״̬��
				// ע������ʹ��steps�������ȫ��״̬���أ������ܽ���ʹ��nextStatus�Ա��η�������
				if(steps[status] < 0) {	
					steps[status] = filpStep;		// ״̬�״γ��ֵĲ����ض�����С����
					ops[status] = nextChess >> 16;	// FIXME
					nextStatus->insert(nextChess);

				} else {
					// Undo: �ظ�״̬���ټ�¼��״̬��
					//  ͨ����ͬ������������Ͽɴﵽ���ظ�״̬��61440�֣�
					//  �ܷ��������65536������֮��Ч״ֻ̬��4096�֣�
					//  �ⲽ��֦�Ǻ���Ҫ�ģ�����ض���ʱ
					cnt++;
				}
			}
		}
		cout << filpStep << ":" << nextStatus->size() << endl;
		// ��֦3����ǰ״̬�������֦���£�ȫ�գ����������״̬�������ټ���
		if(nextStatus->empty()) {
			break;
		}
	}
	cout << cnt << endl;
}


/**
 * ����������ĳ��ָ��λλ�õ�����,
 *  �˲�����ͬʱ�ı����̱���Ĳ���λ����16λ����״̬λ����16λ��
 * @param chess ��תǰ�����̱���
 * @param bitPos Ҫ��ת������λ��, ȡֵ��ΧΪ[0, 15]��
 *				���ζ�Ӧ4x4�����ϴ����ҡ����϶��µı�ţ�Ҳ��Ӧ���������ӵ͵��ߵĽ���λ
 * return ��ת������̱���
 */
_UINT Chess::filp(_UINT chess, int bitPos) {
	_UINT OP_MASK = 0x00010000 << bitPos;	// ��16λ:��ǰ����λ
	_UINT STATUS_MASK = MASKS[bitPos];	// ��16λ:���״̬λ
	return (chess ^ (OP_MASK | STATUS_MASK));	// �������̱���
}


/**
 * �����̱�����ȡ����״̬��Ϣ
 * return ����״̬��Ϣ����16λ��
 */
int Chess::toStatus(_UINT chess) {
	const _UINT MASK = 0x0000FFFF;
	return (int) (chess & MASK);
}


/**
 * �����̱�����ȡ���̲�����Ϣ����16λ��������������ת��ŵ�λ��
 * @param chess ���̱���
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


/**
 * �����̱�����ȡ���̲�����Ϣ����16λ������ȡ���̴�ȫ0״̬��ʼ�����������ӵĴ���
 * @param chess ���̱���
 * return ����ת����
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
 * �����ȫ0��ȫ1״̬����ָ������״̬����С����
 * @param status ����״̬
 * return ��С�����������ɴ��򷵻�-1��
 */
int Chess::getStep(int status) {
	int step = -1;
	if(status >= 0 && status < MAX_STATUS) {
		step = steps[status];	// ��ȫ0��ʼ����ָ��״̬�Ĳ���
		// ���迼��ȫ1�������������Ҫ������ȫ�򿪿��أ�
		
	}
	return step;
}


int Chess::getOp(int status) {
	int op = -1;
	if(status >= 0 && status < MAX_STATUS) {
		op = ops[status];
	}
	return op;
}

/**
 * ������Сֵ
 * @param a ����a
 * @param b ����b
 * return ��Сֵ
 */
int Chess::min(int a, int b) {
	return (a <= b ? a : b);
}


