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
const int MAX_DATA = 4;		//データの最大数
}// namespaceはここまで

//*******************************
//プロトタイプ宣言
//*******************************
namespace
{
void ZeroClear(unsigned char* aData);
void CopyNumber(int nNum, unsigned char* aData);
void Output(unsigned char* aData);
void WaitPressEnter(void);
}// namespaceはここまで

//=================================================
//メイン関数
//=================================================
void main(void)
{
	int nNum = 0x01020304;			//int型変数
	unsigned char aData[MAX_DATA];	//配列

	//ゼロクリア
	ZeroClear(&aData[0]);

	//nNumの値をaDataにコピーする
	CopyNumber(nNum, &aData[0]);

	//出力
	Output(&aData[0]);

	//Enter入力待ち
	WaitPressEnter();
}

namespace
{
//=================================================
//ゼロクリア
//=================================================
void ZeroClear(unsigned char* aData)
{
	//メモリのセット(セット先のアドレス,セットする値,セットするサイズ)
	memset(&aData[0], 0, sizeof(aData));
}

//=================================================
//値をコピーする
//=================================================
void CopyNumber(int nNum, unsigned char* aData)
{
	//メモリのコピー(コピー先のアドレス,コピー元アドレス,コピーするサイズ)
	memcpy(&aData[0], &nNum, sizeof(aData));
}

//=================================================
//出力
//=================================================
void Output(unsigned char* aData)
{
	//aDataのポインタ
	unsigned char* pData = (unsigned char*)&aData[0];

	//メッセージ
	printf("\n 《 16進数表示 》\n");

	for (int i = 0; i < sizeof(int); i++)
	{//16進数で表示する
		printf("\n [ 0x%.2x ]", *(pData + i));
	}
}

//=================================================
//Enter入力待ち
//=================================================
void WaitPressEnter(void)
{
	printf("\n\n Press Enter");		//メッセージ
	rewind(stdin);
	getchar();
}
}// namespaceはここまで