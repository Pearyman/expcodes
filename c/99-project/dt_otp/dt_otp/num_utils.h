/*****************************************
  Description: ���ִ����߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#ifndef __NUM_UTILS_H_
#define __NUM_UTILS_H_

	namespace NUM_UTILS {

		/*
		 * �������ַ���ת����long long��ֵ
		 * @param str �����ַ���
		 * @return long long ��ֵ
		 */
		const long long toLongLong(const char* str);

		/*
		 * ��long long��ֵת���������ַ���
		 * @param _long long long ��ֵ
		 * @return �����ַ���
		 */
		const char* toStr(const long long _long);

	}

#endif
