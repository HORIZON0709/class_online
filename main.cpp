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
const int MAX_QUESTION = 24;				//最大問題数
const int MAX_DATA = 256;					//データの最大数
}//namespaceはここまで

//*******************************
//構造体の定義
//*******************************
namespace
{
typedef struct
{/* 応答メッセージ */
	char aJudgeMsg[MAX_DATA];		//質問判定文
	char aResponseMsg[MAX_DATA];	//回答
}ResponseMsg;
}//namespaceはここまで

//*******************************
//プロトタイプ宣言
//*******************************
namespace
{
void LoadFile(ResponseMsg* pRpsMsg);
}//namespaceはここまで

//=================================================
//メイン関数
//=================================================
void main(void)
{
	ResponseMsg aRpsMsg[MAX_QUESTION] = {};	//応答メッセージ
	
	//ファイル読み込み
	LoadFile(&aRpsMsg[0]);

	/*
		Winsockの初期化関数を実行する
	*/

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//winsockの初期化処理

	if (nErr != 0)
	{//初期化に失敗した場合(※エラーメッセージを表示して終了)
		printf("\n 初期化失敗");
	}

	/*
		ソケット作成
	*/

	SOCKET sockServer;
	sockServer = socket(AF_INET, SOCK_STREAM, 0);	//ソケットを作成する。接続受付用のソケット作成

	if (sockServer == INVALID_SOCKET)
	{//エラーメッセージを表示して終了
		printf("\n error");
	}

	/*
		接続を受け付けるための準備
	*/

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22333);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(sockServer, (struct sockaddr*)&addr, sizeof(addr));	//ソケットにポートを割り当て
	listen(sockServer, 10);										//接続受付の準備

	/*
		接続を待つ
	*/

	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);
	SOCKET sock = accept(sockServer, (struct sockaddr*)&clientAddr, &nLength);	//接続を受け付ける

	//接続元のIPアドレス・ポート番号取得
	const char* pClientIP = inet_ntoa(clientAddr.sin_addr);
	int nClientPort = clientAddr.sin_port;

	while (1)
	{
		//質問を受信
		char aRecvQuestion[MAX_DATA] = {};
		int nRecvByte = recv(sock, &aRecvQuestion[0], sizeof(aRecvQuestion), 0);

		if (nRecvByte <= 0)
		{//接続が切断されたら
			break;
		}

		/* 質問への返答 */

		char aSendBuffer[MAX_DATA] = {};	//回答送信用

		int i = 0;	//カウント

		for (i = 0; i < MAX_QUESTION; i++)
		{//質問判定文字列と比較する
			if (!strstr(&aRpsMsg[i].aJudgeMsg[0], &aRecvQuestion[0]))
			{//部分一致しない場合
				continue;
			}

			/* 部分一致した場合 */

			//回答をコピー
			strcpy(&aSendBuffer[0], &aRpsMsg[i].aResponseMsg[0]);
			break;
		}

		//回答を送る
		send(sock, &aSendBuffer[0], strlen(&aSendBuffer[0]) + 1, 0);

		//送った回答を表示
		printf("\n [%s]に[%s]を送信しました。", &pClientIP[0], &aRpsMsg[i].aResponseMsg[0]);
	}

	/*
		接続を切断する
	*/

	//クライアントとの接続を閉じる
	closesocket(sock);

	//接続受付用ソケットを閉じる
	closesocket(sockServer);		//ソケットを閉じる

	/*
		Winsock終了処理
	*/

	WSACleanup();	//winsockの終了処理
}

namespace
{
//-------------------------------------------------
//ファイルを読み込む
//-------------------------------------------------
void LoadFile(ResponseMsg* pRpsMsg)
{
	//ファイルを開く
	FILE* pFile = fopen("data/Answer.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けたら
		char aText[MAX_DATA];	//テキスト格納用
		int nCnt = 0;

		while (strncmp(&aText[0], "SCRIPT", 6) != 0)
		{//テキストの最初の行を読み込むまで繰り返す
			fgets(aText, MAX_DATA, pFile);		//1行丸ごと読み込む
		}

		while (1)
		{
			fscanf(pFile, "%s", &aText[0]);		/* 読み込み開始 */

			if (strcmp(&aText[0], "END_SCRIPT") == 0)
			{//テキストの最終行
				break;	//読み込み終了
			}

			if (strncmp(&aText[0], "#-", 2) == 0)
			{//見出しで囲うやつ
				continue;	//『読み込み開始』まで戻る
			}
			else if (strncmp(&aText[0], "#", 1) == 0)
			{//コメント
				fgets(aText, MAX_DATA, pFile);	//1行丸ごと読み込む
				continue;	//『読み込み開始』まで戻る
			}

			if (strcmp(&aText[0], "Question") == 0)
			{//質問判定文字列
				fscanf(pFile, "%s", &aText[0]);	//「 = 」を読み込む
				fscanf(pFile, "%s", &pRpsMsg[nCnt].aJudgeMsg[0]);	//質問判定を読み込む
				continue;	//『読み込み開始』まで戻る
			}
			else if (strcmp(&aText[0], "Answer") == 0)
			{//回答
				fscanf(pFile, "%s", &aText[0]);	//「 = 」を読み込む
				fscanf(pFile, "%s", &pRpsMsg[nCnt].aResponseMsg[0]);	//回答を読み込む
				nCnt++;	//カウントアップ
				continue;	//『読み込み開始』まで戻る
			}
		}

		//ファイルを閉じる
		fclose(pFile);
		return;
	}

	/* ファイルが開けなかったら */

	//メッセージ
	printf("\n ファイルが開けません。");
}
}//namespaceはここまで