/*****************************************
  Description: ���ִ����߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#include "stdafx.h"
#include "str_utils.h"
#include "num_utils.h"

/*
 * �Ѷ��������ַ���ת����long long��ֵ
 * �����ַ��������������ַ����������ַ���
 * @param str �����ַ���
 * @param len �ַ�������
 * @return long long ��ֵ
 */
inline long long toLL(const char* str, const int len) {
	long long n = 0LL;
	for(int i = 0; i < len; i++) {
		char c = *(str + i);
		if(c < '0' || c > '9') {
			continue;
		}
		n *= 10;
		n += (c - '0');
	}
	return n;
}

namespace NUM_UTILS {

	/*
	 * �������ַ���ת����long long��ֵ
	 * @param str �����ַ���
	 * @return long long ��ֵ
	 */
	const long long toLongLong(const char* str) {
		long long n = 0LL;
		int len = STR_UTILS::sLen(str);

		// λ�����(long long �͵����ֵ9223372036854775807�� ���Ϸ���λ���20λ)
		if(len > 20) {
			// Undo

		// ����1λ���Ƿ���λ��λ�����
		} else if (len > 19) {
			if(*(str) == '-' || *(str) == '+') {
				n = toLL(str + 1, 19);
			}

		// λ�������������ֵ��������� �˴�������ֵ�������)
		} else {	
			if(*(str) == '-' || *(str) == '+') {
				n = toLL(str + 1, len - 1);
			} else {
				n = toLL(str, len);
			}
		}

		n = (*(str) == '-' ? -n : n);
		return n;
	}

	/*
	 * ��long long��ֵת���������ַ���
	 * @param _long long long ��ֵ
	 * @return �����ַ���
	 */
	const char* toStr(const long long _long) {
		char* s = new char[21];	//long long �����ֵ 9223372036854775807 ��19λ�����Ϸ���λ�ͽ�β��������19+2λ�ռ�
		int idx = 0;
		long long n = _long;

		do {
			int r = (n % 10);
			r = (r < 0 ? -r : r);
			*(s + idx++) = r + '0';
			n /= 10;
		} while(n != 0LL);

		if(_long < 0) {
			*(s + idx++) = '-';
		}
		*(s + idx) = '\0';

		const char* sLong = STR_UTILS::reverse(s);
		STR_UTILS::sFree(s);
		return sLong;
	}

}

