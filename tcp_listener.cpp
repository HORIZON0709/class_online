//=================================================
//
//オンライン利用技術～サーバー側～[tcp_listener.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//インクルード
//*******************************
#include "tcp_listener.h"
#include "tcp_client.h"

#include <stdio.h>

//=================================================
//コンストラクタ
//=================================================
CTcpListener::CTcpListener():
	m_sockServer(INVALID_SOCKET)
{
}

//=================================================
//デストラクタ
//=================================================
CTcpListener::~CTcpListener()
{
}

//=================================================
//初期化
//=================================================
bool CTcpListener::Init(int nPortNum)
{
	/*
		ソケット作成
	*/

	//接続受付用のソケット作成
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sockServer == INVALID_SOCKET)
	{//エラーメッセージを表示して終了
		printf("\n error");
		return false;	//失敗
	}

	/*
		接続を受け付けるための準備
	*/

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));	//ソケットにポートを割り当て
	listen(m_sockServer, 10);									//接続受付の準備

	return true;	//成功
}

//=================================================
//接続待ち受け
//=================================================
CTcpClient* CTcpListener::Accept()
{
	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);
	SOCKET sock = accept(m_sockServer, (struct sockaddr*)&clientAddr, &nLength);	//接続を受け付ける

	/* TCPクライアント */

	CTcpClient* pTcpClient = nullptr;	//ポインタ

	if (pTcpClient != nullptr)
	{//NULLチェック
		pTcpClient = nullptr;
	}

	if (pTcpClient == nullptr)
	{//NULLチェック
		pTcpClient = new CTcpClient;	//メモリの動的確保
	}

	//初期化
	pTcpClient->Init(sock);

	return pTcpClient;	//生成したものを返す
}

//=================================================
//終了
//=================================================
void CTcpListener::Uninit()
{
	if (m_sockServer == INVALID_SOCKET)
	{//待受ソケットが生成済みか
		printf("\n error");
		return;
	}

	/* 生成されている場合 */

	//ソケットを閉じる
	closesocket(m_sockServer);

	m_sockServer = INVALID_SOCKET;	//初期化
}