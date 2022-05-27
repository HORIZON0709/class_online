//=================================================
//
//�I�����C�����p�Z�p�`�T�[�o�[���`[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//�C���N���[�h
//*******************************
#include "main.h"

#include <stdio.h>
#include <string.h>

//*******************************
//�萔�̒�`
//*******************************
namespace
{
const int MAX_DATA = 4;			//�f�[�^�̍ő吔
const int ANSWER_NUMBER = 79;	//�����̒l
}//namespace�͂����܂�

//=================================================
//���C���֐�
//=================================================
void main(void)
{
	/* Winsock�̏������֐������s���� */

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//winsock�̏���������

	if (nErr != 0)
	{//�������Ɏ��s�����ꍇ(���G���[���b�Z�[�W��\�����ďI��)
		printf("\n ���������s");
	}

	/* �\�P�b�g�쐬 */

	SOCKET sockServer;
	sockServer = socket(AF_INET, SOCK_STREAM, 0);	//�\�P�b�g���쐬����B�ڑ���t�p�̃\�P�b�g�쐬

	if (sockServer == INVALID_SOCKET)
	{//�G���[���b�Z�[�W��\�����ďI��
		printf("\n error");
	}

	/* �ڑ����󂯕t���邽�߂̏��� */

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22333);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(sockServer, (struct sockaddr*)&addr, sizeof(addr));	//�\�P�b�g�Ƀ|�[�g�����蓖��
	listen(sockServer, 10);										//�ڑ���t�̏���

	/* �ڑ���҂� */

	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);
	SOCKET sock = accept(sockServer, (struct sockaddr*)&clientAddr, &nLength);	//�ڑ����󂯕t����

	//�ڑ�����IP�A�h���X�E�|�[�g�ԍ��擾
	const char* pClientIP = inet_ntoa(clientAddr.sin_addr);
	int nClientPort = clientAddr.sin_port;

	//�������M
	char aRecvQuestion[MAX_DATA] = {};
	int nRecvByte = recv(sock, &aRecvQuestion[0], sizeof(aRecvQuestion), 0);	//�f�[�^����M����

	if (nRecvByte <= 0)
	{//�ڑ����ؒf���ꂽ��
		closesocket(sock);		//�\�P�b�g�̃N���[�Y�������s��

		/* ������ȍ~�A����M�͂ł��Ȃ� */
	}

	/*
		�����ŉ��������
	*/

	//�ϐ�
	char aAnswer[MAX_DATA] = {};

	//�𓚂𑗂�
	send(sock, &aAnswer[0], strlen(&aAnswer[0]) + 1, 0);	//�f�[�^�𑗐M����

	/* �ڑ���ؒf���� */

	//�N���C�A���g�Ƃ̐ڑ������
	closesocket(sock);

	//�ڑ���t�p�\�P�b�g�����
	closesocket(sockServer);		//�\�P�b�g�����

	/* Winsock�I������ */

	WSACleanup();	//winsock�̏I������
}