/*****************************************
  Description: ����/���ܹ��߰�
  Authod     : EXP
  Modify By  : None
  Date       : 2017-11-14
******************************************/

#define DLL_IMPLEMENT

#include "stdafx.h"
#include "utils_str.h"
#include "_md5.h"
#include "_digital_watermark.h"
#include "utils_crypto.h"

namespace CRYPTO_UTILS {

	/*
	 * ����MD5�루32λ��
	 * @param text ����
	 * @param key ��Կ
	 * @return MD5�루32λ��
	 */
	DLL_API const char* toMD5(const char* text, const char* key) {
		const char* eText = STR_UTILS::concat(text, key);
		const int eLen = STR_UTILS::sLen(eText);
		const char* md5 = MD5(eText, eLen).toCharArray();
		const char* md5Upper = STR_UTILS::toUpperCase(md5);

		STR_UTILS::sFree(eText);
		STR_UTILS::sFree(md5);
		return md5Upper;
	}

	/*
	 * ��MD5��32λ��Ƕ������ˮӡ
	 * @param md5 MD5�루32λ��
	 * @param digitalWatermark ����ˮӡ������1~8��
	 * @return Ƕ������ˮӡ��MD5��64��λ
	 */
	DLL_API const char* addWatermark(const char* md5, const long long digitalWatermark) {
		const char* dwMD5 = DigitalWatermark().generate(md5, digitalWatermark);
		const char* dwMD5Upper = STR_UTILS::toUpperCase(dwMD5);

        STR_UTILS::sFree(dwMD5);
		return dwMD5Upper;
	}

	/*
	 * ��Ƕ������ˮӡ��MD5��64λ������ȡMD5�루32λ��
	 * @param dwMD5 Ƕ������ˮӡ��MD5��64λ��
	 * @return MD5�루32λ��
	 */
	DLL_API const char* getMD5(const char* dwMD5) {
		return DigitalWatermark().extractMD5(dwMD5);
	}

	/*
	 * ��Ƕ������ˮӡ��MD5��64λ������ȡ����ˮӡ
	 * @param dwMD5 Ƕ������ˮӡ��MD5��64λ��
	 * @return ����ˮӡ
	 */
	DLL_API const long long getWatermark(const char* dwMD5) {
		return DigitalWatermark().extractDigital(dwMD5);
	}

}
