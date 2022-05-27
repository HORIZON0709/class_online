//=================================================
//
//オンライン利用技術～サーバー側～[main.cpp]
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
const int MAX_DATA = 4;			//データの最大数
const int ANSWER_NUMBER = 79;	//正解の値
}//namespaceはここまで

//=================================================
//メイン関数
//=================================================
void main(void)
{
	/* Winsockの初期化関数を実行する */

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//winsockの初期化処理

	if (nErr != 0)
	{//初期化に失敗した場合(※エラーメッセージを表示して終了)
		printf("\n 初期化失敗");
	}

	/* ソケット作成 */

	SOCKET sockServer;
	sockServer = socket(AF_INET, SOCK_STREAM, 0);	//ソケットを作成する。接続受付用のソケット作成

	if (sockServer == INVALID_SOCKET)
	{//エラーメッセージを表示して終了
		printf("\n error");
	}

	/* 接続を受け付けるための準備 */

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22333);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(sockServer, (struct sockaddr*)&addr, sizeof(addr));	//ソケットにポートを割り当て
	listen(sockServer, 10);										//接続受付の準備

	/* 接続を待つ */

	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);
	SOCKET sock = accept(sockServer, (struct sockaddr*)&clientAddr, &nLength);	//接続を受け付ける

	//接続元のIPアドレス・ポート番号取得
	const char* pClientIP = inet_ntoa(clientAddr.sin_addr);
	int nClientPort = clientAddr.sin_port;

	//質問を受信
	char aRecvQuestion[MAX_DATA] = {};
	int nRecvByte = recv(sock, &aRecvQuestion[0], sizeof(aRecvQuestion), 0);	//データを受信する

	if (nRecvByte <= 0)
	{//接続が切断されたら
		closesocket(sock);		//ソケットのクローズ処理を行う

		/* ※これ以降、送受信はできない */
	}

	/*
		ここで何かしら解答
	*/

	//変数
	char aAnswer[MAX_DATA] = {};

	//解答を送る
	send(sock, &aAnswer[0], strlen(&aAnswer[0]) + 1, 0);	//データを送信する

	/* 接続を切断する */

	//クライアントとの接続を閉じる
	closesocket(sock);

	//接続受付用ソケットを閉じる
	closesocket(sockServer);		//ソケットを閉じる

	/* Winsock終了処理 */

	WSACleanup();	//winsockの終了処理
}