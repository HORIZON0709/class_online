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
		printf("\n 初期化失敗");
	}

	/* 3.ソケット作成 */

	SOCKET sockServer;
	sockServer = socket(AF_INET, SOCK_STREAM, 0);	//socket関数：ソケットを作成する。接続受付用のソケット作成

	if (sockServer == INVALID_SOCKET)
	{//エラーメッセージを表示して終了
		printf("\n error");
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

	/* データを受け取って計算 */

	//データを受け取る
	char aRecvData[MAX_DATA] = {};
	int nRecvByte = recv(sock, &aRecvData[0], sizeof(aRecvData), 0);	//recv関数：データを受信する
	int nRecvData = 0;
	memcpy(&nRecvData, &aRecvData[0], sizeof(int));

	nRecvData *= 2;	//受け取った値を2倍にする

	/* 6.データの送信 */

	//変数
	//int nData = 44444444;
	char aData[MAX_DATA];

	//データを送る
	memcpy(&aData[0], &nRecvData, sizeof(int));
	send(sock, &aData[0], sizeof(int), 0);	//send関数：データを送信する

	/* 7.接続を切断する */

	//クライアントとの接続を閉じる
	closesocket(sock);

	//接続受付用ソケットを閉じる
	closesocket(sockServer);		//closesocket関数：ソケットを閉じる

	/* 8.Winsock終了処理 */

	WSACleanup();	//WSACleanup関数：winsockの終了処理
}