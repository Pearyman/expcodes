/*****************************************
  Description: ����32λMD5�ģ�����ˮӡ�㷨.
  Authod     : EXP
  Modify By  : None
  Date       : 2017-11-14
******************************************/

#define DLL_IMPLEMENT

#include "stdafx.h"
#include "utils_str.h"
#include "_digital_watermark.h"

/* 10���� - 16���� ת������� */
const char DigitalWatermark::HEX_TABLE[16] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'A', 'B',
	'C', 'D', 'E', 'F'
};

/* 
 * ����ˮӡУ�����.
 * �˱��У����Ϊ������ɣ�ֻ�豣֤����ˮӡ����ȡˮӡ��У�������ͬ���ɡ�
 */
const char DigitalWatermark::CHECKCODE_TABLE[10][3] = {
	{'8', 'D', 'C'},	// ���� 0 У����
	{'A', 'A', '9'},	// ���� 1 У����
	{'6', '7', 'D'},	// ���� 2 У����
	{'4', '3', '3'},	// ���� 3 У����
	{'5', '4', 'B'},	// ���� 4 У����
	{'7', '5', 'E'},	// ���� 5 У����
	{'F', '2', '3'},	// ���� 6 У����
	{'E', '3', '6'},	// ���� 7 У����
	{'C', '0', '1'},	// ���� 8 У����
	{'8', 'E', '2'},	// ���� 9 У����
};

/* ���캯�� */
DigitalWatermark::DigitalWatermark() {
	// None
}

/* �������� */
DigitalWatermark::~DigitalWatermark() {
	// None
}

/*
 * ��MD5��32λ��Ƕ������ˮӡ
 * @param md5_32 MD5�루32λ��
 * @param digital ����ˮӡ������1~8��
 * @return Ƕ������ˮӡ��MD5��64��λ
 */
const char* DigitalWatermark::generate(const char* md5_32, const long long digital) {
	char* dwMD5 = new char[1];	// ������ˮӡ��MD5��
	*dwMD5 = '\0';

	if(STR_UTILS::sLen(md5_32) == MD5_LEN) {
		const char* sDigital = toDwStr(digital);	// ����ˮӡ���ַ��������ȱض�Ϊ8
        STR_UTILS::sFree(dwMD5);
		dwMD5 = new char[DW_MD5_LEN + 1];
		int idx = 0;

		for(int i = 0; i < DW_LEN; i++) {
			const char* pMD5 = md5_32 + (i * 4);	// ÿ4λΪһ��
			const char n = *(sDigital + i);			// ȡ��Ӧ��ˮӡλ
			const char* cCode = *(CHECKCODE_TABLE + (n - '0'));	// ȡˮӡλ���ֶ�Ӧ��У����

			// Ƕ��ԭ��λ
			*(dwMD5 + idx++) = *(pMD5 + 0);
			*(dwMD5 + idx++) = *(pMD5 + 1);
			*(dwMD5 + idx++) = *(pMD5 + 2);
			*(dwMD5 + idx++) = *(pMD5 + 3);

			// Ƕ��ˮӡλ
			*(dwMD5 + idx++) = add(*(pMD5 + 0), n);

			// Ƕ��У��λ
			*(dwMD5 + idx++) = add(*(pMD5 + 1), *(cCode + 0));
			*(dwMD5 + idx++) = add(*(pMD5 + 2), *(cCode + 1));
			*(dwMD5 + idx++) = add(*(pMD5 + 3), *(cCode + 2));
		}

		*(dwMD5 + idx++) = '\0';
        STR_UTILS::sFree(sDigital);
	}
	return dwMD5;
}

/*
 * ��Ƕ������ˮӡ��MD5��64λ������ȡMD5�루32λ��
 * @param md5_64 Ƕ������ˮӡ��MD5��64λ��
 * @return MD5�루32λ��
 */
const char* DigitalWatermark::extractMD5(const char* md5_64) {
	char* md5 = new char[1];	// ������MD5��
	*md5 = '\0';

	if(STR_UTILS::sLen(md5_64) == DW_MD5_LEN) {
        STR_UTILS::sFree(md5);
		md5 = new char[MD5_LEN + 1];
		int idx = 0;
		for(int i = 0; i < DW_LEN; i++) {
			const char* pMD5 = md5_64 + (i * 8);	// ÿ8λΪһ��

			// ֻȡ��4λ
			*(md5 + idx++) = *(pMD5 + 0);
			*(md5 + idx++) = *(pMD5 + 1);
			*(md5 + idx++) = *(pMD5 + 2);
			*(md5 + idx++) = *(pMD5 + 3);
		}
		*(md5 + idx) = '\0';
	}
	return md5;
}

/*
 * ��Ƕ������ˮӡ��MD5��64λ������ȡ����ˮӡ
 * @param md5_64 Ƕ������ˮӡ��MD5��64λ��
 * @return ����ˮӡ
 */
const long long DigitalWatermark::extractDigital(const char* md5_64) {
	long long digital = 0LL;	// ����ˮӡ
	
	if(STR_UTILS::sLen(md5_64) == DW_MD5_LEN) {
		for(int i = 0; i < DW_LEN; i++) {
			const char* pMD5 = md5_64 + (i * 8);	// ÿ8λΪһ��
			
			// ����ˮӡλ
			int n = hex2Int(minus(*(pMD5 + 4), *(pMD5 + 0)));

			// У��ˮӡλ
			bool isOk = false;
			if(n >=0 && n <= 9) {
                
				const char* cCode = *(CHECKCODE_TABLE + n);	// ȡˮӡλ���ֶ�Ӧ��У����
                isOk = true;
                isOk &= (*(cCode + 0) == minus(*(pMD5 + 5), *(pMD5 + 1)));
                isOk &= (*(cCode + 1) == minus(*(pMD5 + 6), *(pMD5 + 2)));
                isOk &= (*(cCode + 2) == minus(*(pMD5 + 7), *(pMD5 + 3)));
			}

            // ��ԭ����ˮӡ
			if(isOk == true) {
				digital = digital * 10 + n;	

            // ��ԭ����ˮӡ����
			} else {
				digital = 0LL;
				break;
			}
		}
	}
	return digital;
}

/*
 * ת������ˮӡΪ 8λ�ַ����������λ��0��Խ����λ�ضϣ�
 * @param digital ����ˮӡ
 * @return 8λ����ˮӡ�ַ���
 */
const char* DigitalWatermark::toDwStr(const long long digital) {
	char* s = new char[DW_LEN + 1];
	int idx = 0;
	long long n = digital;

	do {
		int r = (n % 10);
		r = (r < 0 ? -r : r);
		*(s + idx++) = r + '0';
		n /= 10;
	} while(n != 0LL && idx < DW_LEN);	// ����Խ�޽ض�

	while(idx < DW_LEN) {
		*(s + idx++) = '0';	// ���Ȳ����λ��0
	}
	*(s + idx) = '\0';

	const char* dwStr = STR_UTILS::reverse(s);
	STR_UTILS::sFree(s);
	return dwStr;
}

/*
 * 16�����ַ����
 * @param xA ��������0-F��
 * @param xB ������0-F��
 * @return 16�����ַ���Խ��ȡģ��
 */
const char DigitalWatermark::add(char xA, char xB) {
	int nA = hex2Int(xA);
	int nB = hex2Int(xB);
	return int2Hex(nA + nB);
}

/*
 * 16�����ַ����
 * @param xA ��������0-F��
 * @param xB ������0-F��
 * @return 16�����ַ���Խ��ȡģ��
 */
const char DigitalWatermark::minus(char xA, char xB) {
	int nA = hex2Int(xA);
	int nB = hex2Int(xB);
	return int2Hex(nA - nB);
}

/*
 * 16�����ַ�ת��Ϊ10��������
 * @param x 16��������0-F��
 * @return 10��������
 */
int DigitalWatermark::hex2Int(char x) { 
	int n = 0;

	if(x >= '0' && x <= '9') {
		n = x - '0';

	} else if(x >= 'a' && x <= 'f') {
		n = x - 'a' + 10;

	} else if(x >= 'A' && x <= 'F') {
		n = x - 'A' + 10;
	}
	return n;
}

/*
 * 10��������ת��Ϊ16�����ַ�
 * @param n 10��������
 * @return 16��������Խ��ȡģ��
 */
char DigitalWatermark::int2Hex(int n) {
	int idx = n;

	if(n < 0) {
		idx = n % 16 + 16;

	} else if(n >= 16) {
		 idx = n % 16;
	}
	return HEX_TABLE[idx];
}