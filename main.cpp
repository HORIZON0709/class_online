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
void ZeroClear(unsigned char* aData);
void CopyNumber(unsigned char* aData, int nNum, char cNum, int aNum[]);
void Output(unsigned char* aData);
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

	unsigned char aData[MAX_DATA];	//�z��

	//�[���N���A
	ZeroClear(&aData[0]);

	//�l���R�s�[����
	CopyNumber(aData, nNum, cNum, &aNum[0]);

	//�o��
	Output(aData);

	//Enter���͑҂�
	WaitPressEnter();
}

namespace
{
//-------------------------------------------------
//�[���N���A
//-------------------------------------------------
void ZeroClear(unsigned char* aData)
{
	//�������̃Z�b�g
	memset(&aData[0], 0, sizeof(aData));
}

//-------------------------------------------------
//�l���R�s�[����
//-------------------------------------------------
void CopyNumber(unsigned char* aData, int nNum, char cNum, int aNum[])
{
	//nNum
	memcpy(&aData[0], &nNum, sizeof(nNum));

	//cNum
	memcpy(&aData[sizeof(nNum)], &cNum, sizeof(cNum));

	for (int i = 0; i < MAX_NUMBER; i++)
	{
		//�A�h���X�̃C���f�b�N�X��
		int nIndex = sizeof(nNum) + sizeof(char) + (sizeof(int) * i);

		//aNum[0] �` aNum[3]
		memcpy(&aData[nIndex], &aNum[i], sizeof(aNum));
	}
}

//-------------------------------------------------
//�o��
//-------------------------------------------------
void Output(unsigned char* aData)
{
	//aData�̃|�C���^
	unsigned char* pData = (unsigned char*)&aData[0];

	//���b�Z�[�W
	printf("\n �s 16�i���\�� �t\n");

	//�\���ɕK�v�ȃT�C�Y
	int nSize = sizeof(int) + sizeof(char) + sizeof(int[4]);

	for (int i = 0; i < nSize; i++)
	{//16�i���ŕ\������
		printf("\n [ 0x%.2x ]", *(pData + i));
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