/*****************************************
  Description: ����/���ܹ��߰�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#ifndef __CRYPTO_UTILS_H_
#define __CRYPTO_UTILS_H_

	namespace CRYPTO_UTILS {

		/*
		 * ����MD5�루32λ��
		 * @param text ����
		 * @param key ��Կ
		 * @return MD5�루32λ��
		 */
		const char* toMD5(const char* text, const char* key);

		/*
		 * ��MD5��32λ��Ƕ������ˮӡ
		 * @param md5 MD5�루32λ��
		 * @param digitalWatermark ����ˮӡ������1~8��
		 * @return Ƕ������ˮӡ��MD5��64��λ
		 */
		const char* addWatermark(const char* md5, const long long digitalWatermark);

		/*
		 * ��Ƕ������ˮӡ��MD5��64λ������ȡMD5�루32λ��
		 * @param dwMD5 Ƕ������ˮӡ��MD5��64λ��
		 * @return MD5�루32λ��
		 */
		const char* getMD5(const char* dwMD5);

		/*
		 * ��Ƕ������ˮӡ��MD5��64λ������ȡ����ˮӡ
		 * @param dwMD5 Ƕ������ˮӡ��MD5��64λ��
		 * @return ����ˮӡ
		 */
		const long long getWatermark(const char* dwMD5);

	}

#endif