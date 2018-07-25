/*****************************************
  Description: java-to-c����ת�����߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/


#include "stdafx.h"	
#include "str_utils.h"
#include "jni_utils.h"

namespace JNI_UTILS {

	/*
	 * [jlong] -> [long long]
	 * @param _long [jlong]����ֵ��java��
	 * @return [long long]����ֵ��c++��
	 */
	const long long jlong2LL(const jlong _long) {
		return (long long) _long;
	}

	/*
	 * [long long] -> [jlong]
	 * @param _long [long long]����ֵ��c++��
	 * @return [jlong]����ֵ��java��
	 */
	const jlong ll2Jlong(const long long _long) {
		return (jlong) _long;
	}

	/*
	 * [jstring] -> [char*]
	 * @param env JNI��������ָ��
	 * @param str [jstring]����ֵ��java��
	 * @return [char*]����ֵ��c++��
	 */
	const char* jstring2Char(JNIEnv* env, const jstring str) {
		return env->GetStringUTFChars(str, NULL);
	}

	/*
	 * [char*] -> [jstring]
	 * @param env JNI��������ָ��
	 * @param str [char*]����ֵ��c++��
	 * @return [jstring]����ֵ��java��
	 */
	const jstring char2Jstring(JNIEnv* env, const char* str) {
		jclass stringClass = env->FindClass("java/lang/String");
		jmethodID mId = env->GetMethodID(stringClass, "<init>", "([BLjava/lang/String;)V");
		jstring encode = env->NewStringUTF("utf-8");

		jsize len = STR_UTILS::sLen(str);
		jbyteArray byteAry = env->NewByteArray(len);
		env->SetByteArrayRegion(byteAry, 0, len, (jbyte*) str);

		return (jstring) env->NewObject(stringClass, mId, byteAry, encode);
	}

	/*
	 * �ͷ�[��ʹ�����][��Ե�] jstring �� char* ָ����ڴ�
	 * @param env JNI��������ָ��
	 * @param jStr [jstring]����ֵ��java��
	 * @param cStr [char*]����ֵ��c++��
	 */
	void releaseJstring(JNIEnv* env, const jstring jStr, const char* cStr) {
		env->ReleaseStringUTFChars(jStr, cStr);
	}

}
