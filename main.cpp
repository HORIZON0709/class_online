//=================================================
//
//�I�����C�����p�Z�p�`�T�[�o�[���`[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//�C���N���[�h
//*******************************
#include "tcp_listener.h"
#include "tcp_client.h"

#include <stdio.h>
#include <string.h>
#include <thread>

//*******************************
//�萔�̒�`
//*******************************
namespace
{
const int MAX_QUESTION = 32;	//�ő��萔
const int MAX_DATA = 512;		//�f�[�^�̍ő吔
}//namespace�͂����܂�

//*******************************
//�\���̂̒�`
//*******************************
namespace
{
typedef struct
{/* �������b�Z�[�W */
	char aJudgeMsg[MAX_DATA];		//���┻�蕶
	char aResponseMsg[MAX_DATA];	//��
}ResponseMsg;
}//namespace�͂����܂�

//*******************************
//�v���g�^�C�v�錾
//*******************************
namespace
{
void LoadFile(ResponseMsg* pRpsMsg);
}//namespace�͂����܂�

//=================================================
//�X���b�h�v���V�[�W��
//=================================================
void ThreadProc(CTcpClient* pTcpClient, ResponseMsg aRpsMsg[])
{
	while (1)
	{
		char aRecvQuestion[MAX_DATA] = {};	//�����M�p
		int nRecvByte = 0;					//��M�f�[�^�̃T�C�Y

		//�������M
		nRecvByte = pTcpClient->Recv(&aRecvQuestion[0], sizeof(aRecvQuestion));

		if (nRecvByte <= 0)
		{//�ڑ����ؒf���ꂽ��
			break;	//���[�v�I��
		}

		/* ����ւ̕ԓ� */

		char aSendBuffer[MAX_DATA] = {};	//�񓚑��M�p

		int i = 0;	//�J�E���g

		for (i = 0; i < MAX_QUESTION; i++)
		{//���┻�蕶����Ɣ�r����
			if (!strstr(&aRecvQuestion[0], &aRpsMsg[i].aJudgeMsg[0]))
			{//������v���Ȃ��ꍇ
				continue;
			}

			/* ������v�����ꍇ */

			//�񓚂��R�s�[
			strcpy(&aSendBuffer[0], &aRpsMsg[i].aResponseMsg[0]);
			break;
		}

		//�񓚂𑗂�
		pTcpClient->Send(&aSendBuffer[0], strlen(&aSendBuffer[0]) + 1);

		//�������񓚂�\��
		printf("\n [%s]�𑗐M���܂����B", &aRpsMsg[i].aResponseMsg[0]);
	}
}

//=================================================
//���C���֐�
//=================================================
void main(void)
{
	ResponseMsg aRpsMsg[MAX_QUESTION] = {};	//�������b�Z�[�W
	aRpsMsg[0].aJudgeMsg[0] = {};
	aRpsMsg[0].aResponseMsg[0] = {};

	//�t�@�C���ǂݍ���
	LoadFile(&aRpsMsg[0]);

	/*
		Winsock�̏������֐������s����
	*/

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//winsock�̏���������

	if (nErr != 0)
	{//�������Ɏ��s�����ꍇ(���G���[���b�Z�[�W��\�����ďI��)
		printf("\n ���������s");
	}

	/* TCP���X�i�[ */

	CTcpListener* pTcpListener = nullptr;	//�|�C���^

	if (pTcpListener != nullptr)
	{//NULL�`�F�b�N
		pTcpListener = nullptr;
	}

	if (pTcpListener == nullptr)
	{//NULL�`�F�b�N
		pTcpListener = new CTcpListener;	//�������̓��I�m��
	}

	if ((pTcpListener == nullptr) || !(pTcpListener->Init(22333)))
	{//�C���X�^���X��nullptr or �������Ɏ��s
		pTcpListener->Uninit();	//�ڑ���t�p�\�P�b�g�����
		WSACleanup();			//winsock�̏I������
	}

	/* nullptr�ł͂Ȃ� & �������ɐ��� */

	CTcpClient* pTcpClient = nullptr;

	while (1)
	{
		//�ڑ���҂�
		pTcpClient = pTcpListener->Accept();

		//�X���b�h�̍쐬
		std::thread th(ThreadProc, pTcpClient, aRpsMsg);

		//�X���b�h��؂藣��
		th.detach();
	}

	if (pTcpClient != nullptr)
	{//NULL�`�F�b�N
		pTcpClient->Uninit();	//�I��
		delete pTcpClient;		//�������̉��
		pTcpClient = nullptr;	//nullptr�ɂ���
	}

	/*
		�ڑ���ؒf����
	*/

	//�I��(�ڑ���t�p�\�P�b�g�����)
	pTcpListener->Uninit();

	/*
		Winsock�I������
	*/

	WSACleanup();	//winsock�̏I������
}

namespace
{
//-------------------------------------------------
//�t�@�C����ǂݍ���
//-------------------------------------------------
void LoadFile(ResponseMsg* pRpsMsg)
{
	//�t�@�C�����J��
	FILE* pFile = fopen("data/Answer.txt", "r");

	if (pFile == nullptr)
	{//�t�@�C�����J���Ȃ�������
		printf("\n �t�@�C�����J���܂���B");	//���b�Z�[�W
		return;
	}

	/* �t�@�C�����J������ */

	char aText[MAX_DATA] = "\0";	//�e�L�X�g�i�[�p
	int nCnt = 0;					//�J�E���g

	while (strncmp(&aText[0], "SCRIPT", 6) != 0)
	{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
		fgets(aText, MAX_DATA, pFile);		//1�s�ۂ��Ɠǂݍ���
	}

	while (1)
	{
		fscanf(pFile, "%s", &aText[0]);		/* �ǂݍ��݊J�n */

		if (strcmp(&aText[0], "END_SCRIPT") == 0)
		{//�e�L�X�g�̍ŏI�s
			break;	//�ǂݍ��ݏI��
		}

		if (strncmp(&aText[0], "#-", 2) == 0)
		{//���o���ň͂����
			continue;	//�w�ǂݍ��݊J�n�x�܂Ŗ߂�
		}
		else if (strncmp(&aText[0], "#", 1) == 0)
		{//�R�����g
			fgets(aText, MAX_DATA, pFile);	//1�s�ۂ��Ɠǂݍ���
			continue;	//�w�ǂݍ��݊J�n�x�܂Ŗ߂�
		}

		if (strcmp(&aText[0], "Question") == 0)
		{//���┻�蕶����
			fscanf(pFile, "%s", &aText[0]);	//�u = �v��ǂݍ���
			fscanf(pFile, "%s", &pRpsMsg[nCnt].aJudgeMsg[0]);	//���┻���ǂݍ���
		}
		else if (strcmp(&aText[0], "Answer") == 0)
		{//��
			fscanf(pFile, "%s", &aText[0]);	//�u = �v��ǂݍ���
			fscanf(pFile, "%s", &pRpsMsg[nCnt].aResponseMsg[0]);	//�񓚂�ǂݍ���
			nCnt++;	//�J�E���g�A�b�v
		}
	}

	//�t�@�C�������
	fclose(pFile);
}
}//namespace�͂����܂�