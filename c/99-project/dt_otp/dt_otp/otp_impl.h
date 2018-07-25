/*****************************************
  Description: OTP����ʵ�ְ�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#ifndef __OTP_IMPL_H_
#define __OTP_IMPL_H_

	namespace OTP_IMPL {

		/*
		 * ���ɶ�̬����
		 * @param privateKey ˽Կ����Ӣ���ַ���
		 * @param timeOffset ʱ��ƫ������ms��
		 * @return ��̬����
		 */
		const char* getOtpToket(const char* privateKey, const long long timeOffset);

		/*
		 * У�鶯̬����
		 * @param otpToken ��̬����
		 * @param privateKey ˽Կ����Ӣ���ַ���
		 * @return true:У��ɹ�; false:У��ʧ��
		 */
		const bool isValid(const char* otpToken, const char* privateKey);

	}

#endif