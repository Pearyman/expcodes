/*****************************************
  Description: �ַ��������߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#include "stdafx.h"
#include "str_utils.h"

namespace STR_UTILS {

	/*
	 * �����ַ�������
	 * @param str �ַ���
	 * @return �ַ�������
	 */
	const int sLen(const char* str) {
		int len = 0;
		while(*(str + len) != '\0') {
			len++;
		}
		return len;
	}

	/*
	 * ��ת�ַ���
	 * @param str �ַ���
	 * @return ��ת���ַ���
	 */
	const char* reverse(const char* str) {
		int len = sLen(str);
		char* rStr = new char[len + 1];

		len--;
		for(int i = 0; i <= len; i++) {
			*(rStr + i) = *(str + len - i);
		}
		*(rStr + len + 1) = '\0';
		return rStr;
	}

	/*
	 * ��ȡ�Ӵ�
	 * @param str �ַ���
	 * @param start ��ʼ�±꣨����������С0�Զ�����Ϊ0
	 * @param end ��ֹ�±꣨���������������ڴ����Զ�����Ϊ����
	 * @return �Ӵ�
	 */
	const char* substr(const char* str, const int start, const int end) {
		int len = sLen(str);
		int sIdx = start < 0 ? 0 : start;
		int eIdx = end > len ? len : end;
		
		char* s;
		int i = 0;
		if(sIdx < eIdx) {
			s = new char[eIdx - sIdx + 1];
			for(int idx = sIdx; idx < eIdx; idx++) {
				*(s + i++) = *(str + idx);
			}

		} else if (sIdx > eIdx) {
			s = new char[sIdx - eIdx + 1];
			for(int idx = sIdx; idx > eIdx; idx--) {
				*(s + i++) = *(str + idx);
			}

		} else {
			s = new char[2];
			*(s + i++) = *(str + sIdx);
		}
		*(s + i) = '\0';
		return s;
	}

	/*
	 * �ַ���ƴ��
	 * @param str1 �ַ���1
	 * @param str2 �ַ���2
	 * @return str1 + str2
	 */
	const char* concat(const char* str1, const char* str2) {
		int len1 = sLen(str1);
		int len2 = sLen(str2);
		char* str = new char[len1 + len2 + 1];
		int idx = 0;

		for(int i = 0; i < len1; i++) {
			*(str + idx) = *(str1 + i);
			idx++;
		}

		for(int i = 0; i < len2; i++) {
			*(str + idx) = *(str2 + i);
			idx++;
		}

		*(str + idx) = '\0';
		return str;
	}
	
	/*
	 * ���ַ���������Ӣ���ַ�ת��Ϊ��д
	 * @param str �ַ���
	 * @return ת���ɴ�д���ַ���
	 */
	const char* toUpperCase(const char* str) {
		int len = sLen(str);
		char* upper = new char[len + 1];
		for(int i = 0; i < len; i++) {
			char c = *(str + i);
			if(c >= 'a' && c <= 'z') {
				c -= 32;
			}
			*(upper + i) = c;
		}
		*(upper + len) = '\0';
		return upper;
	}

	/*
	 * ���ַ���������Ӣ���ַ�ת��ΪСд
	 * @param str �ַ���
	 * @return ת����Сд���ַ���
	 */
	const char* toLowCase(const char* str) {
		int len = sLen(str);
		char* low = new char[len + 1];
		for(int i = 0; i < len; i++) {
			char c = *(str + i);
			if(c >= 'A' && c <= 'Z') {
				c += 32;
			}
			*(low + i) = c;
		}
		*(low + len) = '\0';
		return low;
	}

	/*
	 * �Ƚ��ַ�����ֵ�Ƿ���ͬ
	 * @param str1 �ַ���1
	 * @param str2 �ַ���2
	 * @return true:��ͬ; false:��ͬ
	 */
	const bool isEqual(const char* str1, const char* str2) {
		bool isEqual = true;
		int len1 = sLen(str1);
		int len2 = sLen(str2);

		if(len1 != len2) {
			isEqual = false;

		} else {
			for(int i = 0; i < len1; i++) {
				if(*(str1 + i) != *(str2 + i) ) {
					isEqual = false;
					break;
				}
			}
		}
		return isEqual;
	}
		
	/*
	 * �ͷ��ַ���ָ��ָ����ڴ�
	 * @param str �ַ���ָ��
	 */
	void sFree(const char* str) {
		delete[] str;
		str = NULL;
	}

}
