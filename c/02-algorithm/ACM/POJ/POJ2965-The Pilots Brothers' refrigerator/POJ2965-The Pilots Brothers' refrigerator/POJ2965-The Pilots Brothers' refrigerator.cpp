/*
	Author:     Exp
	Date:       2017-12-04
	Code:       POJ 2965
	Problem:    The Pilots Brothers' refrigerator
	URL:        http://poj.org/problem?id=2965
*/

/*
	���������
	  ��һ���䣬����4x4��16�����أ�"-"״̬��ʾ�򿪣�"+"״̬��رգ��� 
	  ���ı�һ������״̬ʱ���ÿ��������С��е�ȫ������״̬Ҳ��ͬʱ�ı䡣 
	  ����һ������״̬���ʴӸ�״̬��ʼ��ʹ�����п��ش򿪣�ȫ"-"����
	  ������Ҫ�������ٲ������Ѳ������̴�ӡ����


	����˼·��
	  ����� POJ 1753 �Ľ���˼·��һģһ���ģ�ֻ�Ǵ��ڼ�������㣬ʹ�ý��⼼����΢�����һ��.
	  û�� POJ 1753 ��ͬѧ��ȥ�������⣬������ٻ�ͷ������.


	  ������͵����ֱ���������Լ� POJ 1753 �Ĵ��룬�ѿ���ģ�ͳ��������ģ�ͣ�
	  �����ϸ�Ľ���˼·�Ͳ��ٸ����ˣ�����ֻ�г�����Ĳ��죬�Լ���Բ���Ĵ����ַ���
		�� ����״ֻ̬��ȫ0һ�֣� POJ-1753��ȫ0��ȫ1����
		�� ��ת��Ӱ�����ȫ��+ȫ�й�7������
		�� ����65536�ֲ��ظ�״̬����ȫ0��ȫ1����16��
		�� ȫ״̬�Ե�8��Ϊ���ġ�һ��ȡ����ʶԳƷֲ�������λ �� ״̬λ ����ȫ�Գƣ��� ������ָ����֦
		�� Ҫ������������̣�ʹ�ò����뼴�ɣ�
		�� ������Ŀ��עΪSpecial Judge���༴һ���⣬ԭ���ǲ����ǹ̶��ģ����ǲ������ص�˳��Ҫ��,
		   ������Ϊ����ͬ�������ɸ����أ�����˳�򲻻�Ӱ�����յ����״̬
*/

#include <iostream>
using namespace std;


// �޷�������(32λ)�����ڼ�¼���̱��룬��ҪΪ�˱���int32�ĸ���Ӱ��  
// ��ʼ����״̬Ϊȫ0��ȫ"-"��  
// ��16λΪ���̲���λ��������������λ�ñ��Ϊ1  
// ��16λΪ����״̬λ, ��¼��ǰ����״̬��"+"����Ϊ1��"-"����Ϊ0��  
typedef unsigned int _UINT;


const static int MAX_STEP = 16;			// �ɷ���������
const static int MAX_STATUS = 65536;	// ��״̬�� = 2^16�����ظ�����


// ����״̬���룺����תλ��i������ʱ,STATUS_MASKS[i]Ϊ������Ӱ�������λ�� 
// λ��i����4x4�����ڣ������ҡ����ϵ��°�0-15���α���  
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
		void print(int status);
		
	private:
		void bfsAllStatus(void);			// ��¼���ظ��ط���1-16���ɵõ�����������״̬
		_UINT filp(_UINT chess, int bitPos);// ����������ĳ��ָ��λλ�õ�����
		
		int toStatus(_UINT chess);		// �����̱�����ȡ����״̬��Ϣ
		int getMaxBitPos(_UINT chess);	// �����̱�����ȡ���̲�����Ϣ������������ת��ŵ�λ��
		int getFilpCount(_UINT chess);	// �����̱�����ȡ���̲�����Ϣ����ȡ���̴�ȫ0״̬��ʼ�����������ӵĴ���

	private:
		_UINT* chesses;		// ��¼��ȫ0��ʼ����ÿ������״̬�����̱���
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
			if(byteBuff[i] == '+') {	// -���Ϊ0, +���Ϊ1
				chessStatus |= (0x00000001 << (i + offset));
			}
		}

		// ÿ����4���ֽ����һ��
		if(byteCnt >= 4) {
			chess->print(chessStatus);
			
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
	this->chesses = new _UINT[MAX_STATUS];
	memset(chesses, -1, sizeof(_UINT) * MAX_STATUS);

	bfsAllStatus();
}


/**
 * ��������
 */
Chess::~Chess() {
	delete[] chesses;
	chesses = NULL;
}


/**
 * ��ʼ�����ظ��ط���1-16���ɵõ�����������״̬
 *
 *   ��������״̬����POJ1753Ҫ�࣬��˲���ʹ��STL��set����ά��BFS���У������TLE
 */
void Chess::bfsAllStatus(void) {
	const int ALL_ZERO_CHESS = 0;
	_UINT bfsQueue[MAX_STATUS];
	int head = 0, tail = 0;
	bfsQueue[tail++] = ALL_ZERO_CHESS;

	while(head < tail) {
		_UINT lastChess = bfsQueue[head++];
		int status = toStatus(lastChess);		// ���θ�16λ����λ���õ���16λ����������״̬
		chesses[status] = lastChess;			// ��������״̬��Ӧ�����̱���

		// ��֦1��.....
		for(int pos = getMaxBitPos(lastChess) + 1; pos < MAX_STEP; pos++) {
			_UINT nextChess = filp(lastChess, pos);	// �������ӵõ���һ������״̬����
			bfsQueue[tail++] = nextChess;
		}
	}
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
void Chess::print(int status) {
	if(status >= 0 && status < MAX_STATUS) {
		_UINT chess = chesses[status];

		// ��ӡ����
		int step = getFilpCount(chess);
		cout << step << endl;

		// ��ӡ��ת����
		for(int mask = 0x00010000, bit = 0; bit < MAX_STEP; bit++, mask <<= 1) {
			if((chess & mask) > 0) {
				cout << (bit / 4) + 1 << " " << (bit % 4) + 1 << endl;
			}
		}
	}
}
