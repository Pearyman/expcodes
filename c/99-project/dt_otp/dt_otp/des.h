/*****************************************
  Description: DES�㷨.
               ���㷨�Ľ��뷽�������ڴ����ȱ�ݣ����ṩ������Ϊ����ַ���ʱ99%����֣�,
			   ����ʹ��, ��������������д.

  Authod     : Internet: [http://blog.csdn.net/stilling2006/article/details/4036136]
  Modify By  : EXP | http://exp-blog.com
  Date       : 2015-07-20
******************************************/

#ifndef __DES_H_
#define __DES_H_

	#ifdef _LP64
		typedef unsigned long UINT;
	#else
		typedef unsigned long long UINT;
	#endif

	typedef unsigned char BYTE;
	typedef BYTE* LPBYTE;
	typedef BYTE* PBYTE;
	typedef bool BOOL;
	#define TRUE true;
	#define FALSE false;

	class DES {
		private:
			BYTE bOriMsg[8] ;				// ��ʼ��Ϣ ( 64 bit )
			BYTE LMsg[17][4], RMsg[17][4] ;	// �м����L0-->L16,R0-->R16 ( 32 bit )
			BYTE bKey[8] ;					// ������Կ ( 64 bit )
			BYTE bSubKey[17][6] ;			// ��������ԿK1-->K16 ( 48 bit )
			BYTE bCryptedMsg[8] ;			// ����

			const static BYTE bInitSwapTable[64];	// ��ʼ�û��� (IP)
			const static BYTE bInitReSwapTable[64];	// ��ʼ���û��� (IP-1)
			const static BYTE bBitExternTable[48];	// λ��չ��32-->48 (E)
			const static BYTE bTailSwapTable[32];	// 32λ�û���--����F��β�û� (P)
			const static BYTE SB[8][4][16];			// 8��S�� (S)
			const static BYTE bSelSwapTable_1[56];	// �û�ѡ���һ (PC-1)
			const static BYTE bSelSwapTable_2[48];	// �û�ѡ���� (PC-2)
			const static BYTE bBitMask[8];			// λ�����
			const static char HEX[16];				// 16���Ʊ�

		public:
			const static char* encrypt(const char* eText, const int eLen, const char* key);	// DES���ܣ�ԭ���������ã����ٷ�װһ�㣩
			const static char* decrypt(const char* cHexText, const int cHexLen, const char* key);	// DES���ܣ�ԭ���������ã����ٷ�װһ�㣩

		private:
			const char* char2Hex(const unsigned char* s, int slen);	// ��ASCII�ַ���ת����16���Ʊ�ʾ��ʽ
			unsigned char* hex2char(const char* hex, int xlen);		// ��16������ʽ���ַ���ת��ΪASCII�ַ���
			unsigned int hex2Uint(char hex);	// ����16�����ַ���Ӧ��10������ֵ

			unsigned char* cConst2Uvar(const char* s);	// �� [����]�ַ��� ת��Ϊ [�ǳ���][�޷���]�ַ���

		private:
			void *(memset) (void *s, int c, size_t n);	// �ڴ�����ã�ʵ�ֲ��õ���c���Դ�룬Ŀ����Ϊ��ƽ̨�޹أ�
			void *memcpy(void *dst, const void *src, size_t len);// �ڴ�鸴�ƣ�ʵ�ֲ��õ���c���Դ�룬Ŀ����Ϊ��ƽ̨�޹أ�

		private:
			void DES_Encrypt () ;	// DES����
			void DES_Decrypt () ;	// DES����
			BOOL DES_Encrypt ( LPBYTE lpSour, LPBYTE lpDest, UINT uLen, LPBYTE lpKey ) ;	// DES����
			BOOL DES_Decrypt ( LPBYTE lpSour, LPBYTE lpDest, UINT uLen, LPBYTE lpKey ) ;	// DES����

			void DESInitSwap () ;	// ��ʼ�û�
			void DESInitReSwap () ;	// ��ʼ���û�
			void DESGenSubKey () ;	// ��������Կ
			void DESSingleTurn ( BYTE nTurnIndex, BOOL bMode ) ;// DES�ĵ��ּ��ܹ���
			void DES_f ( BYTE bTurnIndex, BOOL bMode ) ;		// DES��F����

			void DES_SysInit () ;	// ��ʼ��
			void DES_SetOriMsg ( PBYTE pMsg, UINT uLen ) ;	// ��������
			void DES_SetKey ( PBYTE pKey, UINT uLen ) ;		// ������Կ
	} ;

#endif