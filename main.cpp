//=================================================
//
//オンライン利用技術[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//インクルード
//*******************************
#include <stdio.h>
#include <string.h>

//*******************************
//定数の定義
//*******************************
namespace
{
const int MAX_NUMBER = 4;		//個数の最大数
const int MAX_DATA = 128;		//データの最大数
}// namespaceはここまで

//*******************************
//プロトタイプ宣言
//*******************************
namespace
{
void ZeroClear(unsigned char* aData);
void CopyNumber(unsigned char* aData, int nNum, char cNum, int aNum[]);
void Output(unsigned char* aData);
void WaitPressEnter(void);
}// namespaceはここまで

//=================================================
//メイン関数
//=================================================
void main(void)
{
	int nNum = 1;						//int型変数
	char cNum = 2;						//char型変数
	int aNum[MAX_NUMBER] = { 3,4,5,6 };	//int型配列

	unsigned char aData[MAX_DATA];	//配列

	//ゼロクリア
	ZeroClear(&aData[0]);

	//値をコピーする
	CopyNumber(aData, nNum, cNum, &aNum[0]);

	//出力
	Output(aData);

	//Enter入力待ち
	WaitPressEnter();
}

namespace
{
//-------------------------------------------------
//ゼロクリア
//-------------------------------------------------
void ZeroClear(unsigned char* aData)
{
	//メモリのセット
	memset(&aData[0], 0, sizeof(aData));
}

//-------------------------------------------------
//値をコピーする
//-------------------------------------------------
void CopyNumber(unsigned char* aData, int nNum, char cNum, int aNum[])
{
	//nNum
	memcpy(&aData[0], &nNum, sizeof(nNum));

	//cNum
	memcpy(&aData[sizeof(nNum)], &cNum, sizeof(cNum));

	for (int i = 0; i < MAX_NUMBER; i++)
	{
		//アドレスのインデックス数
		int nIndex = sizeof(nNum) + sizeof(char) + (sizeof(int) * i);

		//aNum[0] ～ aNum[3]
		memcpy(&aData[nIndex], &aNum[i], sizeof(aNum));
	}
}

//-------------------------------------------------
//出力
//-------------------------------------------------
void Output(unsigned char* aData)
{
	//aDataのポインタ
	unsigned char* pData = (unsigned char*)&aData[0];

	//メッセージ
	printf("\n 《 16進数表示 》\n");

	//表示に必要なサイズ
	int nSize = sizeof(int) + sizeof(char) + sizeof(int[4]);

	for (int i = 0; i < nSize; i++)
	{//16進数で表示する
		printf("\n [ 0x%.2x ]", *(pData + i));
	}
}

//-------------------------------------------------
//Enter入力待ち
//-------------------------------------------------
void WaitPressEnter(void)
{
	printf("\n\n Press Enter");		//メッセージ
	rewind(stdin);
	getchar();
}
}// namespaceはここまで