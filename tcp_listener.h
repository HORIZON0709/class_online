//=================================================
//
//�I�����C�����p�Z�p�`�T�[�o�[���`[listener.h]
//Author:KishimotoEiji
//
//=================================================
#ifndef _TCP_LISTENER_H_
#define _TCP_LISTENER_H_

#include "main.h"

//*******************************
//�O���錾
//*******************************
class CTcpClient;

//*******************************
//TCP���X�i�[�N���X�̒�`
//*******************************
class CTcpListener
{/* ��{�N���X */
public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CTcpListener();
	~CTcpListener();

public: /* �����o�֐� */
	bool Init(int nPortNum);	//������
	CTcpClient* Accept();		//�ڑ��҂���
	void Uninit();				//�I��

private: /* �����o�֐� */
	SOCKET m_sockServer;	//�T�[�o�[�p�\�P�b�g
};

#endif