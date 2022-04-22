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
const int MAX_DATA = 4;		//�f�[�^�̍ő吔
}// namespace�͂����܂�

//*******************************
//�v���g�^�C�v�錾
//*******************************
namespace
{
void ZeroClear(unsigned char* aData);
void CopyNumber(int nNum, unsigned char* aData);
void Output(unsigned char* aData);
void WaitPressEnter(void);
}// namespace�͂����܂�

//=================================================
//���C���֐�
//=================================================
void main(void)
{
	int nNum = 0x01020304;			//int�^�ϐ�
	unsigned char aData[MAX_DATA];	//�z��

	//�[���N���A
	ZeroClear(&aData[0]);

	//nNum�̒l��aData�ɃR�s�[����
	CopyNumber(nNum, &aData[0]);

	//�o��
	Output(&aData[0]);

	//Enter���͑҂�
	WaitPressEnter();
}

namespace
{
//=================================================
//�[���N���A
//=================================================
void ZeroClear(unsigned char* aData)
{
	//�������̃Z�b�g(�Z�b�g��̃A�h���X,�Z�b�g����l,�Z�b�g����T�C�Y)
	memset(&aData[0], 0, sizeof(aData));
}

//=================================================
//�l���R�s�[����
//=================================================
void CopyNumber(int nNum, unsigned char* aData)
{
	//�������̃R�s�[(�R�s�[��̃A�h���X,�R�s�[���A�h���X,�R�s�[����T�C�Y)
	memcpy(&aData[0], &nNum, sizeof(aData));
}

//=================================================
//�o��
//=================================================
void Output(unsigned char* aData)
{
	//aData�̃|�C���^
	unsigned char* pData = (unsigned char*)&aData[0];

	//���b�Z�[�W
	printf("\n �s 16�i���\�� �t\n");

	for (int i = 0; i < sizeof(int); i++)
	{//16�i���ŕ\������
		printf("\n [ 0x%.2x ]", *(pData + i));
	}
}

//=================================================
//Enter���͑҂�
//=================================================
void WaitPressEnter(void)
{
	printf("\n\n Press Enter");		//���b�Z�[�W
	rewind(stdin);
	getchar();
}
}// namespace�͂����܂�