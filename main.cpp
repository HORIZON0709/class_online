//=================================================
//
//オンライン利用技術[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//インクルード
//*******************************
#include "main.h"

#include <stdio.h>
#include <string.h>

//*******************************
//定数の定義
//*******************************
namespace
{
const int MAX_DATA = 4;		//データの最大数
}//namespaceはここまで

//=================================================
//メイン関数
//=================================================
void main(void)
{
	/* 2.Winsockの初期化関数を実行する */

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//WSAStartup関数：winsockの初期化処理

	if (nErr != 0)
	{//初期化に失敗した場合(※エラーメッセージを表示して終了)

	}

	/* 3.ソケット作成 */

	SOCKET sockServer;
	sockServer = socket(AF_INET, SOCK_STREAM, 0);	//socket関数：ソケットを作成する。接続受付用のソケット作成

	if (sockServer == INVALID_SOCKET)
	{//エラーメッセージを表示して終了

	}

	/* 4.接続を受け付けるための準備 */

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22333);	/* ポート番号 */
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(sockServer, (struct sockaddr*)&addr, sizeof(addr));	//bind関数：ソケットにポートを割り当て
	listen(sockServer, 10);		/* 保留中の接続最大数 */		//listen関数：接続受付の準備

	/* 5.接続を待つ */

	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);
	SOCKET sock = accept(sockServer, (struct sockaddr*)&clientAddr, &nLength);	//accept関数：接続を受け付ける

	/* 6.データの送信 */

	int nData = 12345;
	char aData[MAX_DATA];
	memcpy(&aData[0], &nData, sizeof(int));
	send(sock, &aData[0], sizeof(int), 0);	//send関数：データを送信する

	/* 7.接続を切断する */

	//クライアントとの接続を閉じる
	closesocket(sock);

	//接続受付用ソケットを閉じる
	closesocket(sockServer);		//closesocket関数：ソケットを閉じる

	/* 8.Winsock終了処理 */

	WSACleanup();	//WSACleanup関数：winsockの終了処理
}