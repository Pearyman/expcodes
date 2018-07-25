/*****************************************
  Description: OTP����ʵ�ְ�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#include "stdafx.h"
#include "num_utils.h"
#include "str_utils.h"
#include "time_utils.h"
#include "crypto_utils.h"
#include "otp_impl.h"

#define ERROR_TOKEN "INNER_ERROR\0"

/*
 * ��ȡָ��ʱ��ı�λƫ�Ƶ�
 * @param timeMillis ָ��ʱ��(ms)
 * @param timeOffset ʱ��ƫ����(ms)
 * @return ָ��ʱ��ı�λƫ�Ƶ�(ms)
 */
inline const long long getOffsetTime(const long long timeMillis, const long long timeOffset) {
	long long offset = (timeOffset <= 0LL ? 1LL : timeOffset);	//�����0
	long long remainder = timeMillis % timeOffset;
	return timeMillis - remainder;
}


namespace OTP_IMPL {

	/*
	 * ���ɶ�̬����
	 * @param privateKey ˽Կ����Ӣ���ַ���
	 * @param timeOffset ʱ��ƫ������ms��
	 * @return ��̬����
	 */
	const char* getOtpToket(const char* privateKey, const long long timeOffset) {

		// ��ȡ��ǰϵͳʱ���[��λƫ�Ƶ�]
		const long long curSysTime = TIME_UTILS::getCurrentTimeMillis();
		const long long curSysTimeOffset = getOffsetTime(curSysTime, timeOffset);

		// ���� ��λƫ�Ƶ� ��MD5��
		const char* sCurSysTimeOffset = NUM_UTILS::toStr(curSysTimeOffset);
		const char* md5 = CRYPTO_UTILS::toMD5(sCurSysTimeOffset, privateKey);

		// ��ʱ��ƫ������Ϊ����ˮӡǶ��MD5
		const char* dwMD5 = CRYPTO_UTILS::addWatermark(md5, timeOffset);

		// ��������
		const char* otpToken = STR_UTILS::reverse(dwMD5);

		// �����Ƴ��Ȳ�Ϊ64��˵�������ڲ��쳣
		if(STR_UTILS::sLen(otpToken) != 64) {
			STR_UTILS::sFree(otpToken);
			otpToken = ERROR_TOKEN;
		}

		// �ͷ���ʱ��Դ
		STR_UTILS::sFree(sCurSysTimeOffset);
		STR_UTILS::sFree(md5);
		STR_UTILS::sFree(dwMD5);
		return otpToken;
	}

	/*
	 * У�鶯̬����
	 * @param otpToken ��̬����
	 * @param privateKey ˽Կ����Ӣ���ַ���
	 * @return true:У��ɹ�; false:У��ʧ��
	 */
	const bool isValid(const char* otpToken, const char* privateKey) {
		bool isValid = false;

		// MD5������64��
		if(STR_UTILS::sLen(otpToken) == 64) {
			const char* otpTokenUpper = STR_UTILS::toUpperCase(otpToken);
			const char* dwMD5 = STR_UTILS::reverse(otpTokenUpper);		// ������ˮӡ��MD5
			long long digitalWater = CRYPTO_UTILS::getWatermark(dwMD5);	// ��ȡ����ˮӡ

			// ��ˮӡͨ����У��ʱ, ˵��ˮӡδ���޸�
			if(digitalWater > 0) {
				const long long timeOffset = digitalWater;				// ����ˮӡ���������������õ� ʱ��ƫ����
				const char* otpTokenMd5 = CRYPTO_UTILS::getMD5(dwMD5);	// ��ȡ����������MD5��

				// �����Ƴ��Ȳ�Ϊ32��˵�������ڲ��쳣
				if(STR_UTILS::sLen(otpTokenMd5) != 32) {
					// TODO: Print Error

				} else {

					// ���㱾��ʱ��ƫ�Ƶ�
					const long long curSysTime = TIME_UTILS::getCurrentTimeMillis();
					const long long ctOffset = getOffsetTime(curSysTime, timeOffset);	// ��λƫ�Ƶ�
					const long long ptOffset = ctOffset + timeOffset;	// ��ƫ�Ƶ�
					const long long ntOffset = ctOffset - timeOffset;	// ��ƫ�Ƶ�
					const char* sCtOffset = NUM_UTILS::toStr(ctOffset);
					const char* sPtOffset = NUM_UTILS::toStr(ptOffset);
					const char* sNtOffset = NUM_UTILS::toStr(ntOffset);

					// ���㱾�ظ���ʱ��ƫ�Ƶ�� MD5
					const char* ctMD5 = CRYPTO_UTILS::toMD5(sCtOffset, privateKey);	//��λƫ�Ƶ��MD5
					const char* ptMD5 = CRYPTO_UTILS::toMD5(sPtOffset, privateKey);	//��ƫ�Ƶ��MD5
					const char* ntMD5 = CRYPTO_UTILS::toMD5(sNtOffset, privateKey);	//��ƫ�Ƶ��MD5
			
					// ֻҪ���ص�ĳ��ʱ��ƫ�Ƶ�������MD5ƥ�䣬 ��OTP������Ч
					if (STR_UTILS::isEqual(otpTokenMd5, ctMD5) || 
							STR_UTILS::isEqual(otpTokenMd5, ptMD5) || 
							STR_UTILS::isEqual(otpTokenMd5, ntMD5)) {
						isValid = true;
					}

					// �ͷ���ʱ��Դ
					STR_UTILS::sFree(sCtOffset);
					STR_UTILS::sFree(sPtOffset);
					STR_UTILS::sFree(sNtOffset);
					STR_UTILS::sFree(ctMD5);
					STR_UTILS::sFree(ptMD5);
					STR_UTILS::sFree(ntMD5);
				}

				STR_UTILS::sFree(otpTokenMd5);
			}
			
			STR_UTILS::sFree(otpTokenUpper);
			STR_UTILS::sFree(dwMD5);
		}
		return isValid;
	}

}
