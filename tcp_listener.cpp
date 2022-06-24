//=================================================
//
//�I�����C�����p�Z�p�`�T�[�o�[���`[tcp_listener.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//�C���N���[�h
//*******************************
#include "tcp_listener.h"
#include "tcp_client.h"

#include <stdio.h>

//=================================================
//�R���X�g���N�^
//=================================================
CTcpListener::CTcpListener():
	m_sockServer(INVALID_SOCKET)
{
}

//=================================================
//�f�X�g���N�^
//=================================================
CTcpListener::~CTcpListener()
{
}

//=================================================
//������
//=================================================
bool CTcpListener::Init(int nPortNum)
{
	/*
		�\�P�b�g�쐬
	*/

	//�ڑ���t�p�̃\�P�b�g�쐬
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sockServer == INVALID_SOCKET)
	{//�G���[���b�Z�[�W��\�����ďI��
		printf("\n error");
		return false;	//���s
	}

	/*
		�ڑ����󂯕t���邽�߂̏���
	*/

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));	//�\�P�b�g�Ƀ|�[�g�����蓖��
	listen(m_sockServer, 10);									//�ڑ���t�̏���

	return true;	//����
}

//=================================================
//�ڑ��҂���
//=================================================
CTcpClient* CTcpListener::Accept()
{
	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);
	SOCKET sock = accept(m_sockServer, (struct sockaddr*)&clientAddr, &nLength);	//�ڑ����󂯕t����

	/* TCP�N���C�A���g */

	CTcpClient* pTcpClient = nullptr;	//�|�C���^

	if (pTcpClient != nullptr)
	{//NULL�`�F�b�N
		pTcpClient = nullptr;
	}

	if (pTcpClient == nullptr)
	{//NULL�`�F�b�N
		pTcpClient = new CTcpClient;	//�������̓��I�m��
	}

	//������
	pTcpClient->Init(sock);

	return pTcpClient;	//�����������̂�Ԃ�
}

//=================================================
//�I��
//=================================================
void CTcpListener::Uninit()
{
	if (m_sockServer == INVALID_SOCKET)
	{//�Ҏ�\�P�b�g�������ς݂�
		printf("\n error");
		return;
	}

	/* ��������Ă���ꍇ */

	//�\�P�b�g�����
	closesocket(m_sockServer);

	m_sockServer = INVALID_SOCKET;	//������
}