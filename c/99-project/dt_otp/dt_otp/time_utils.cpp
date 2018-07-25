/*****************************************
  Description: ����ʱ�乤�߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#include "stdafx.h"
#include "time_utils.h"

namespace TIME_UTILS {
	
	#ifdef _WIN32
		#include <windows.h>

		/*
		 * ��ȡ1970������UTC��΢��ʱ��ֵ(win�汾, ��ȷ��ms)
		 * ����java�ĵ�ǰϵͳʱ�亯��System.currentTimeMillis()�ȼ۵�ʱ��ֵ��
		 * @return ��ǰϵͳʱ��
		 */
		const long long getCurrentTimeMillis() {
			union {
				long long ns100;	//����ʱ��
				FILETIME filetime;	//ϵͳ�ļ�ʱ��
			} now;
			GetSystemTimeAsFileTime(&now.filetime);

			long long second = (now.ns100 - 116444736000000000LL) / 10000000LL;	// �벿��(��λns)
			long long millis = (now.ns100 / 10LL) % 1000000LL;	// ΢�벿��(��λns)
			long long ms = second * 1000 + millis / 1000;	// ΢����(��λms)
			return ms;
		}

	#else
		#include <time.h>

		/*
		 * ��ȡ1970������UTC��΢��ʱ��ֵ��linux�汾, ��ȷ��s��
		 * @return ��ǰϵͳʱ��
		 */
		const long long getCurrentTimeMillis() {
			long long second = (long long) time((time_t*) NULL);    // time_t ��32λ���뻷�������, ������long longǿת�洢
			long long millis = second * 1000;
			return millis;
		}

	#endif
	
}
