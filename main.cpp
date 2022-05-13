//=================================================
//
//�I�����C�����p�Z�p[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//�C���N���[�h
//*******************************
#include <stdio.h>
#include <string.h>

//*******************************
//�萔�̒�`
//*******************************
namespace
{
const int MAX_NUMBER = 4;		//���̍ő吔
const int MAX_DATA = 128;		//�f�[�^�̍ő吔
}// namespace�͂����܂�

//*******************************
//�v���g�^�C�v�錾
//*******************************
namespace
{
void ZeroClear(unsigned char* pMemory);
int CopyToBuffer(unsigned char* pMemory, void* pSource, int nIdx, int nSize, int nMaxSize);
void Output(unsigned char* pMemory);
void WaitPressEnter(void);
}// namespace�͂����܂�

//=================================================
//���C���֐�
//=================================================
void main(void)
{
	int nNum = 1;						//int�^�ϐ�
	char cNum = 2;						//char�^�ϐ�
	int aNum[MAX_NUMBER] = { 3,4,5,6 };	//int�^�z��
	unsigned char pMemory[MAX_DATA];	//�z��
	int nIdx = 0;						//�C���f�b�N�X��

	//�[���N���A
	ZeroClear(pMemory);

	//�l���R�s�[����
	nIdx += CopyToBuffer(pMemory, &nNum, nIdx, sizeof(nNum), MAX_DATA);
	nIdx += CopyToBuffer(pMemory, &cNum, nIdx, sizeof(cNum), MAX_DATA);
	nIdx += CopyToBuffer(pMemory, aNum, nIdx, sizeof(aNum), MAX_DATA);

	//�o��
	Output(pMemory);

	//Enter���͑҂�
	WaitPressEnter();
}

namespace
{
//-------------------------------------------------
//�[���N���A
//-------------------------------------------------
void ZeroClear(unsigned char* pMemory)
{
	//�������̃Z�b�g
	memset(&pMemory[0], 0, sizeof(pMemory));
}

//-------------------------------------------------
//�l���R�s�[����
//-------------------------------------------------
int CopyToBuffer(unsigned char* pMemory, void* pSource, int nIdx, int nSize, int nMaxSize)
{
	if ((nIdx + nSize) <= nMaxSize)
	{//�o�b�t�@�I�[�o�[�����̃`�F�b�N���Ė�薳��
		memcpy(&pMemory[nIdx], pSource, nSize);
	}
	else
	{//�I�[�o�[�������Ă���
		printf("\n �� �o�b�t�@�I�[�o�[���� ��");	//���b�Z�[�W
	}

	return nSize;
}

//-------------------------------------------------
//�o��
//-------------------------------------------------
void Output(unsigned char* pMemory)
{
	//pMemory�̃|�C���^
	unsigned char* pSource = pMemory;

	//���b�Z�[�W
	printf("\n �s 16�i���\�� �t\n");

	//�C���f�b�N�X��
	int nIdx = sizeof(int) + sizeof(char) + sizeof(int[MAX_NUMBER]);

	for (int i = 0; i < nIdx; i++)
	{//16�i���ŕ\������
		printf("\n [ 0x%.2x ]", *(pSource + i));
	}
}

//-------------------------------------------------
//Enter���͑҂�
//-------------------------------------------------
void WaitPressEnter(void)
{
	printf("\n\n Press Enter");		//���b�Z�[�W
	rewind(stdin);
	getchar();
}
}// namespace�͂����܂�