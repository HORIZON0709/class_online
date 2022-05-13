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
void ZeroClear(unsigned char* pMemory);
int CopyToBuffer(unsigned char* pMemory, void* pSource, int nIdx, int nSize, int nMaxSize);
void Output(unsigned char* pMemory);
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
	unsigned char pMemory[MAX_DATA];	//配列
	int nIdx = 0;						//インデックス数

	//ゼロクリア
	ZeroClear(pMemory);

	//値をコピーする
	nIdx += CopyToBuffer(pMemory, &nNum, nIdx, sizeof(nNum), MAX_DATA);
	nIdx += CopyToBuffer(pMemory, &cNum, nIdx, sizeof(cNum), MAX_DATA);
	nIdx += CopyToBuffer(pMemory, aNum, nIdx, sizeof(aNum), MAX_DATA);

	//出力
	Output(pMemory);

	//Enter入力待ち
	WaitPressEnter();
}

namespace
{
//-------------------------------------------------
//ゼロクリア
//-------------------------------------------------
void ZeroClear(unsigned char* pMemory)
{
	//メモリのセット
	memset(&pMemory[0], 0, sizeof(pMemory));
}

//-------------------------------------------------
//値をコピーする
//-------------------------------------------------
int CopyToBuffer(unsigned char* pMemory, void* pSource, int nIdx, int nSize, int nMaxSize)
{
	if ((nIdx + nSize) <= nMaxSize)
	{//バッファオーバーランのチェックして問題無し
		memcpy(&pMemory[nIdx], pSource, nSize);
	}
	else
	{//オーバーランしている
		printf("\n ※ バッファオーバーラン ※");	//メッセージ
	}

	return nSize;
}

//-------------------------------------------------
//出力
//-------------------------------------------------
void Output(unsigned char* pMemory)
{
	//pMemoryのポインタ
	unsigned char* pSource = pMemory;

	//メッセージ
	printf("\n 《 16進数表示 》\n");

	//インデックス数
	int nIdx = sizeof(int) + sizeof(char) + sizeof(int[MAX_NUMBER]);

	for (int i = 0; i < nIdx; i++)
	{//16進数で表示する
		printf("\n [ 0x%.2x ]", *(pSource + i));
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