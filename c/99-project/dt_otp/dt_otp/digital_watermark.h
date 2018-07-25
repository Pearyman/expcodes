/*****************************************
  Description: ����32λMD5�ģ�����ˮӡ�㷨.
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#ifndef __DIGITAL_WATERMARK_H_
#define __DIGITAL_WATERMARK_H_

	class DigitalWatermark {
		public:
			DigitalWatermark();
			~DigitalWatermark();

			const char* generate(const char* md5_32, const long long digital);	// ��32λMD5����Ƕ������ˮӡ
			const char* extractMD5(const char* md5_64);							// ����Ƕ������ˮӡ��MD5������ȡMD5��
			const long long extractDigital(const char* md5_64);					// ����Ƕ������ˮӡ��MD5������ȡ����ˮӡ

		private:
			const char* toDwStr(const long long digital);	// ת������ˮӡΪ�ַ��������س��ȱض�Ϊ8�������λ��0��Խ����λ�ضϣ�
			const char add(char xA, char xB);				// 16�����ַ���� xA + xB
			const char minus(char xA, char xB);				// 16�����ַ���� xA - xB
			int hex2Int(char x);							// 16�����ַ�ת��Ϊ10��������
			char int2Hex(int n);							// 10��������ת��Ϊ16�����ַ�

		private:
			const static char HEX_TABLE[16];			// 16���Ʊ����
			const static char CHECKCODE_TABLE[10][3];	// ����0-9��У���루���У���룩

            const static int MD5_LEN = 32;      // MD5����
            const static int DW_MD5_LEN = 64;   // Ƕ������ˮӡ��MD5����
            const static int DW_LEN = 8;        // ����ˮӡ����
	};


#endif