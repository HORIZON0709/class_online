//=================================================
//
//オンライン利用技術～サーバー側～[listener.h]
//Author:KishimotoEiji
//
//=================================================
#ifndef _TCP_LISTENER_H_
#define _TCP_LISTENER_H_

#include "main.h"

//*******************************
//前方宣言
//*******************************
class CTcpClient;

//*******************************
//TCPリスナークラスの定義
//*******************************
class CTcpListener
{/* 基本クラス */
public: /* コンストラクタ・デストラクタ */
	CTcpListener();
	~CTcpListener();

public: /* メンバ関数 */
	bool Init(int nPortNum);	//初期化
	CTcpClient* Accept();		//接続待ち受け
	void Uninit();				//終了

private: /* メンバ関数 */
	SOCKET m_sockServer;	//サーバー用ソケット
};

#endif