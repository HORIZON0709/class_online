//=================================================
//
//オンライン利用技術～サーバー側～[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//インクルード
//*******************************
#include "tcp_listener.h"
#include "tcp_client.h"

#include <stdio.h>
#include <string.h>
#include <thread>

//*******************************
//定数の定義
//*******************************
namespace
{
const int MAX_QUESTION = 32;	//最大問題数
const int MAX_DATA = 512;		//データの最大数
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
//スレッドプロシージャ
//=================================================
void ThreadProc(CTcpClient* pTcpClient, ResponseMsg aRpsMsg[])
{
	while (1)
	{
		char aRecvQuestion[MAX_DATA] = {};	//質問受信用
		int nRecvByte = 0;					//受信データのサイズ

		//質問を受信
		nRecvByte = pTcpClient->Recv(&aRecvQuestion[0], sizeof(aRecvQuestion));

		if (nRecvByte <= 0)
		{//接続が切断されたら
			break;	//ループ終了
		}

		/* 質問への返答 */

		char aSendBuffer[MAX_DATA] = {};	//回答送信用

		int i = 0;	//カウント

		for (i = 0; i < MAX_QUESTION; i++)
		{//質問判定文字列と比較する
			if (!strstr(&aRecvQuestion[0], &aRpsMsg[i].aJudgeMsg[0]))
			{//部分一致しない場合
				continue;
			}

			/* 部分一致した場合 */

			//回答をコピー
			strcpy(&aSendBuffer[0], &aRpsMsg[i].aResponseMsg[0]);
			break;
		}

		//回答を送る
		pTcpClient->Send(&aSendBuffer[0], strlen(&aSendBuffer[0]) + 1);

		//送った回答を表示
		printf("\n [%s]を送信しました。", &aRpsMsg[i].aResponseMsg[0]);
	}
}

//=================================================
//メイン関数
//=================================================
void main(void)
{
	ResponseMsg aRpsMsg[MAX_QUESTION] = {};	//応答メッセージ
	aRpsMsg[0].aJudgeMsg[0] = {};
	aRpsMsg[0].aResponseMsg[0] = {};

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

	/* TCPリスナー */

	CTcpListener* pTcpListener = nullptr;	//ポインタ

	if (pTcpListener != nullptr)
	{//NULLチェック
		pTcpListener = nullptr;
	}

	if (pTcpListener == nullptr)
	{//NULLチェック
		pTcpListener = new CTcpListener;	//メモリの動的確保
	}

	if ((pTcpListener == nullptr) || !(pTcpListener->Init(22333)))
	{//インスタンスがnullptr or 初期化に失敗
		pTcpListener->Uninit();	//接続受付用ソケットを閉じる
		WSACleanup();			//winsockの終了処理
	}

	/* nullptrではない & 初期化に成功 */

	CTcpClient* pTcpClient = nullptr;

	while (1)
	{
		//接続を待つ
		pTcpClient = pTcpListener->Accept();

		//スレッドの作成
		std::thread th(ThreadProc, pTcpClient, aRpsMsg);

		//スレッドを切り離す
		th.detach();
	}

	if (pTcpClient != nullptr)
	{//NULLチェック
		pTcpClient->Uninit();	//終了
		delete pTcpClient;		//メモリの解放
		pTcpClient = nullptr;	//nullptrにする
	}

	/*
		接続を切断する
	*/

	//終了(接続受付用ソケットを閉じる)
	pTcpListener->Uninit();

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

	if (pFile == nullptr)
	{//ファイルが開けなかったら
		printf("\n ファイルが開けません。");	//メッセージ
		return;
	}

	/* ファイルが開けたら */

	char aText[MAX_DATA] = "\0";	//テキスト格納用
	int nCnt = 0;					//カウント

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
		}
		else if (strcmp(&aText[0], "Answer") == 0)
		{//回答
			fscanf(pFile, "%s", &aText[0]);	//「 = 」を読み込む
			fscanf(pFile, "%s", &pRpsMsg[nCnt].aResponseMsg[0]);	//回答を読み込む
			nCnt++;	//カウントアップ
		}
	}

	//ファイルを閉じる
	fclose(pFile);
}
}//namespaceはここまで