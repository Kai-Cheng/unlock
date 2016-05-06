// FWUNLOCK.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"

#include <stdlib.h>
#include <memory.h>
#include <windows.h>

char toFwDeCode(int val)
{
	char ch = ' ';
	switch (val)
	{
		case 0:ch = ' '; break;
		case 1:ch = 'a'; break;
		case 2:ch = 'b'; break;
		case 3:ch = 'c'; break;
		case 4:ch = 'd'; break;
		case 5:ch = 'e'; break;
		case 6:ch = 'f'; break;
		case 7:ch = 'g'; break;
		case 8:ch = 'h'; break;
		case 9:ch = 'i'; break;
		case 10:ch = 'j'; break;
		case 11:ch = 'k'; break;
		case 12:ch = '1'; break;
		case 13:ch = '3'; break;
		case 14:ch = 'l'; break;
		case 15:ch = 'm'; break;
		case 16:ch = 'n'; break;
		case 17:ch = 'o'; break;
		case 18:ch = 'p'; break;
		case 19:ch = 'q'; break;
		case 20:ch = 'r'; break;
		case 21:ch = 's'; break;
		case 22:ch = '6'; break;
		case 23:ch = '7'; break;
		case 24:ch = 't'; break;
		case 25:ch = 'u'; break;
		case 26:ch = 'v'; break;
		case 27:ch = 'w'; break;
		case 28:ch = 'x'; break;
		case 29:ch = 'y'; break;
		case 30:ch = '8'; break;
		case 31:ch = '9'; break;
		case 32:ch = 'z'; break;
		case 33:ch = '.'; break;
		case 34:ch = '*'; break;
		case 35:ch = ','; break;
		case 36:ch = '\\'; break;
		case 37:ch = '2'; break;
		case 38:ch = 'A'; break;
		case 39:ch = 'B'; break;
		case 40:ch = 'C'; break;
		case 41:ch = 'D'; break;
		case 42:ch = 'E'; break;
		case 43:ch = 'F'; break;
		case 44:ch = 'G'; break;
		case 45:ch = 'H'; break;
		case 46:ch = 'I'; break;
		case 47:ch = 'J'; break;
		case 48:ch = 'K'; break;
		case 49:ch = 'L'; break;
		case 50:ch = '\r'; break;
		case 51:ch = '\n'; break;
		case 52:ch = 'M'; break;
		case 53:ch = 'N'; break;
		case 54:ch = 'O'; break;
		case 55:ch = 'P'; break;
		case 56:ch = 'Q'; break;
		case 57:ch = 'R'; break;
		case 58:ch = 'S'; break;
		case 59:ch = 'T'; break;
		case 60:ch = 'U'; break;
		case 61:ch = 'V'; break;
		case 62:ch = 'W'; break;
		case 63:ch = '0'; break;
		case 64:ch = '4'; break;
		case 65:ch = '5'; break;
		case 66:ch = ':'; break;
		default:ch = ' ';
	}
	return ch;
}

char toFwEnCode(char val)
{
	char code = 0;

	if (val >= '0' && val <= '9')
	{
		switch (val)
		{
		case '0': code = 63; break;
		case '1': code = 12; break;
		case '2': code = 37; break;
		case '3': code = 13; break;
		case '4': code = 64; break;
		case '5': code = 65; break;
		case '6': code = 22; break;
		case '7': code = 23; break;
		case '8': code = 30; break;
		case '9': code = 31; break;
		default: code = 0; break;
		}
	}
	else if (val >='a' && val <= 'z')
	{
		if (val >= 'a' && val <= 'k')
			code = (val - 'a') + 1;
		else if (val >= 'l' && val <= 's')
			code = (val - 'l') + 14;
		else if (val >= 't' && val <= 'y')
			code = (val - 't') + 24;
		else if (val == 'z')
			code = 32;
	}
	else if (val >= 'A' && val <= 'W')
	{
		if (val >= 'A' && val <= 'L')
			code = (val - 'A') + 38;
		else if (val >= 'M' && val <= 'W')
			code = (val - 'M') + 52;
	}
	else
	{
		switch (val)
		{
		case ' ': code = 0; break;
		case '.': code = 33; break;
		case '*': code = 34; break;
		case ',': code = 35; break;
		case '\\': code = 36; break;
		case '\r': code = 50; break;
		case '\n': code = 51; break;
		case ':': code = 66; break;
		default: code = 0; break;
		}
	}

	return code;
}

int reverseInt(int i)
{
	int iii = 1;
	unsigned char c1, c2, c3, c4;

	//#define is_bigendian() ( (*(char*)&iii) == 0 )
	if (((*(char*)&iii) == 0))
	{
		return i;
	}
	else
	{
		c1 = i & 255;
		c2 = (i >> 8) & 255;
		c3 = (i >> 16) & 255;
		c4 = (i >> 24) & 255;

		return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
	}
}

short int reverseShortInt(short int i)
{
	short int iii = 1;
	unsigned char c1, c2;

	//#define is_bigendian() ( (*(char*)&iii) == 0 )
	if (((*(char*)&iii) == 0))
	{
		return i;
	}
	else
	{
		c1 = i & 255;
		c2 = (i >> 8) & 255;

		return ((short int)c1 << 8) + ((short int)c2);
	}
}

char* FileStr_Decode(char *lpSrc, int nSize, short int* pumChecksum)
{
	char abWeighted[13] = { 9,2,5,8,1,7,3,4,13,18,11,5,17 };
	int i, j;
	short int uwChecksum;
	uwChecksum = 0;

	char *pcTemp = new char[nSize];

	nSize -= 2;
	pcTemp[nSize] = NULL;
	for (i = 0, j = 0; i < nSize; i++)
	{
		char bTemp = toFwDeCode(lpSrc[i] - abWeighted[j++]);
		pcTemp[i] = bTemp;
		uwChecksum += (unsigned char)lpSrc[i];
		if (j > 12) j = 0;
	}

	*pumChecksum = reverseShortInt(uwChecksum);
	return pcTemp;
}

int FileStr_Encode(char *lpSrc, char*lpDst, int nSize, short int* pumChecksum)
{
	char abWeighted[13] = { 9,2,5,8,1,7,3,4,13,18,11,5,17 };
	int i, j;
	short int uwChecksum;

	uwChecksum = 0;

	char *pcTemp = lpDst;

	nSize -= 2;
	lpDst[nSize] = NULL;
	for (i = 0, j = 0; i < nSize; i++)
	{
		char bTemp = toFwEnCode(lpSrc[i]);
		lpDst[i] = bTemp + abWeighted[j++];
		uwChecksum += (unsigned char)lpDst[i];
		if (j > 12) j = 0;
	}
	
	pcTemp += nSize;

	*pumChecksum = reverseShortInt(uwChecksum);
	pcTemp[0] = uwChecksum & 255;
	pcTemp[1] = (uwChecksum >> 8) & 255;
	return i+2;
}
int main(int argc, char* argv[])
{
	FILE *pfile;
	errno_t err;
	size_t size;
	unsigned char *pbuf = NULL, *pcomp = NULL;
	unsigned long  datasize;
	char type_flag = 0;

#if 0//[.4test.
	argc = 4;
	argv[0] = "FWUNLOCK.exe";
	argv[1] = "1";
	argv[2] = "FwCheck_20160506.txt";
	argv[3] = "FwCheck_20160506.dat";
#endif//].

	if (argc == 2 && (!strcmp(argv[1], "-?") || !strcmp(argv[1], "-h") || !strcmp(argv[1], "-help")))
	{
		printf("Version 1.01\r\n");
		printf("Usage: FwUnLockTool.exe \r\n\
			[Encode:1; Decode:2] \r\n\
			[before bin file name] \r\n\
			[after bin file name] \r\n");
		printf("This program built for Win8.1x64-Win32\r\n");
		printf("Report bugs to kai.cheng.wang@gmail.com\r\n");
	}
	else if (4 != argc)
	{
		printf("Command error!\r\n");
		printf("Usage: FwUnLockTool.exe \r\n\
			[Encode:1; Decode:2] \r\n\
			[before bin file name] \r\n\
			[after bin file name] \r\n");
	}
	else
	{

		// [type]
		type_flag = atoi(argv[1]);
		if (type_flag > 2 || type_flag <= 0)
		{
			printf("Command error: Type!\r\n");
			printf("Usage: FwUnLockTool.exe \r\n\
			[Encode:1; Decode:2] \r\n\
			[before bin file name] \r\n\
			[after bin file name] \r\n");
			return 0;
		}
		// open bin file
		err = fopen_s(&pfile, argv[2], "rb");

		if (pfile == NULL)
		{
			printf("File open error[%s]", argv[2]);
			return 0;
		}
		
		fseek(pfile, 0, SEEK_END);
		//binhead.uncompresssize = binhead.size = ftell(pfile);
		datasize = ftell(pfile);

		// read file
		char *pBufRd = new char[datasize];
		if (pBufRd)
		{
			fseek(pfile, 0, SEEK_SET);
			//size = fread(pbuf, sizeof(unsigned char), binhead.data_size, pfile);
			size = fread(pBufRd, sizeof(unsigned char), datasize, pfile);
			//if (size != binhead.data_size) {
			if (size != datasize)
			{
				delete[] pBufRd;
				pBufRd = NULL;
				printf("Read file fail.");
			}
		}
		else
		{
			printf("Malloc memory fail.");
		}
		fclose(pfile);

		char *pBufWt = new char[datasize + 2];
		if (pBufWt == NULL)
		{
			printf("Malloc memory fail!");
			delete[] pBufRd;
			pBufRd = NULL;
			return 0;
		}

		if (pBufRd)
		{
			short int checksum = 0;
			// start encode or decode
			if (type_flag == 1)
			{
				// Encode
				FileStr_Encode(pBufRd, pBufWt, datasize + 2, &checksum);
			}
			else if (type_flag == 2)
			{
				// Decode
				//FileStr_Decode()
				printf("Not support[Decode:2]\r\n");
				if (pBufRd) delete[] pBufRd;
				if (pBufWt) delete[] pBufWt;
				return 0;
			}
			else
			{
				printf("ErrorType[Encode:1; Decode:2]\r\n");
				if (pBufRd) delete[] pBufRd;
				if (pBufWt) delete[] pBufWt;
				return 0;
			}

			// save date to file
			err = fopen_s(&pfile, argv[3], "w+b");
			if (pfile)
			{
				size = fwrite(pBufWt, sizeof(unsigned char), datasize+2, pfile);

				if (size != datasize+2) {
					printf("Write file fail.");
				}
				fclose(pfile);

				printf("OK:%s[%x]", argv[3], checksum);
			}
			else
			{
				printf("The %s file open fail.", argv[3]);
			}
		}

		if (pBufRd)
		{
			delete[] pBufRd;
		}

		if (pBufWt)
		{
			delete[] pBufWt;
		}
		
	}
    return 0;
}

