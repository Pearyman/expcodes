/*****************************************
  Description: ����ʱ�乤�߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#ifndef __TIME_UTILS_H_
#define __TIME_UTILS_H_

	namespace TIME_UTILS {
		
		/*
		 * ��ȡ1970������UTC��΢��ʱ��ֵ
		 * ����java�ĵ�ǰϵͳʱ�亯��System.currentTimeMillis()�ȼ۵�ʱ��ֵ��
		 * @return ��ǰϵͳʱ��
		 */
		const long long getCurrentTimeMillis();

	}

#endif