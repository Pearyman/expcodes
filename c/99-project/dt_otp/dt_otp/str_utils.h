/*****************************************
  Description: �ַ��������߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#ifndef __STR_UTILS_H_
#define __STR_UTILS_H_

	namespace STR_UTILS {

		/*
		 * �����ַ�������
		 * @param str �ַ���
		 * @return �ַ�������
		 */
		const int sLen(const char* str);

		/*
		 * ��ת�ַ���
		 * @param str �ַ���
		 * @return ��ת���ַ���
		 */
		const char* reverse(const char* str);

		/*
		 * ��ȡ�Ӵ�
		 * @param str �ַ���
		 * @param start ��ʼ�±꣨����������С0�Զ�����Ϊ0
		 * @param end ��ֹ�±꣨���������������ڴ����Զ�����Ϊ����
		 * @return �Ӵ�
		 */
		const char* substr(const char* str, const int start, const int end);

		/*
		 * �ַ���ƴ��
		 * @param str1 �ַ���1
		 * @param str2 �ַ���2
		 * @return str1 + str2
		 */
		const char* concat(const char* str1, const char* str2);

		/*
		 * ���ַ���������Ӣ���ַ�ת��Ϊ��д
		 * @param str �ַ���
		 * @return ת���ɴ�д���ַ���
		 */
		const char* toUpperCase(const char* str);

		/*
		 * ���ַ���������Ӣ���ַ�ת��ΪСд
		 * @param str �ַ���
		 * @return ת����Сд���ַ���
		 */
		const char* toLowCase(const char* str);

		/*
		 * �Ƚ��ַ�����ֵ�Ƿ���ͬ
		 * @param str1 �ַ���1
		 * @param str2 �ַ���2
		 * @return true:��ͬ; false:��ͬ
		 */
		const bool isEqual(const char* str1, const char* str2);

		/*
		 * �ͷ��ַ���ָ��ָ����ڴ�
		 * @param str �ַ���ָ��
		 */
		void sFree(const char* str);

	}

#endif