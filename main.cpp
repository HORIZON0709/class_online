//=================================================
//
//オンライン利用技術[main.cpp]
//Date:2022/04/15
//Author:KishimotoEiji
//
//=================================================

//********************************
//インクルード
//********************************
#include <stdio.h>

//=================================================
//メイン関数
//=================================================
void main(void)
{
	int nNum = 0;	//int型変数

	//入力
	printf("\n 値を入力 > ");
	scanf("%d", &nNum);

	unsigned char* pNum = (unsigned char*)&nNum;	//ポインタ

	//出力
	printf("\n 《 16進数表示 》\n");

	for (int i = 0; i < sizeof(int); i++)
	{//16進数で表示する
		printf("\n [ 0x%.2x ]", *(pNum + i));
	}

	//Enter入力待ち
	printf("\n\n Press Enter");
	rewind(stdin);
	getchar();
}