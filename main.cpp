//=================================================
//
//�I�����C�����p�Z�p[main.cpp]
//Date:2022/04/15
//Author:KishimotoEiji
//
//=================================================

//********************************
//�C���N���[�h
//********************************
#include <stdio.h>

//=================================================
//���C���֐�
//=================================================
void main(void)
{
	int nNum = 0;	//int�^�ϐ�

	//����
	printf("\n �l����� > ");
	scanf("%d", &nNum);

	unsigned char* pNum = (unsigned char*)&nNum;	//�|�C���^

	//�o��
	printf("\n �s 16�i���\�� �t\n");

	for (int i = 0; i < sizeof(int); i++)
	{//16�i���ŕ\������
		printf("\n [ 0x%.2x ]", *(pNum + i));
	}

	//Enter���͑҂�
	printf("\n\n Press Enter");
	rewind(stdin);
	getchar();
}