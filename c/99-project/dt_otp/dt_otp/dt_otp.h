/*****************************************
  Description: ���� DLL Ӧ�ó���ĵ�������
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DT_OTP_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DT_OTP_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DT_OTP_EXPORTS
#define DT_OTP_API __declspec(dllexport)
#else
#define DT_OTP_API __declspec(dllimport)
#endif

// ����java�ӿڶ�����ļ�
#include "exp_token_otp__OTP_CAPI.h"
