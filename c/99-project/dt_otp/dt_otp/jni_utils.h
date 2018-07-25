/*****************************************
  Description: java-to-c����ת�����߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#ifndef __JNI_UTILS_H_
#define __JNI_UTILS_H_

	#include "jni.h"	

	namespace JNI_UTILS {

		/*
		 * [jlong] -> [long long]
		 * @param _long [jlong]����ֵ��java��
		 * @return [long long]����ֵ��c++��
		 */
		const long long jlong2LL(const jlong _long);

		/*
		 * [long long] -> [jlong]
		 * @param _long [long long]����ֵ��c++��
		 * @return [jlong]����ֵ��java��
		 */
		const jlong ll2Jlong(const long long _long);

		/*
		 * [jstring] -> [char*]
		 * @param env JNI��������ָ��
		 * @param str [jstring]����ֵ��java��
		 * @return [char*]����ֵ��c++��
		 */
		const char* jstring2Char(JNIEnv* env, const jstring str);

		/*
		 * [char*] -> [jstring]
		 * @param env JNI��������ָ��
		 * @param str [char*]����ֵ��c++��
		 * @return [jstring]����ֵ��java��
		 */
		const jstring char2Jstring(JNIEnv* env, const char* str);

		/*
		 * �ͷ��� jstring ���ɵ� char* ��ָ����ڴ�
		 * @param env JNI��������ָ��
		 * @param jStr [jstring]����ֵ��java��
		 * @param cStr [char*]����ֵ��c++��
		 */
		void releaseJstring(JNIEnv* env, const jstring jStr, const char* cStr);

	}
	

#endif