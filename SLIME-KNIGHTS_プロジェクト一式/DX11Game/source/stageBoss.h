//==================================================================
//								sceneBoss.h
//	�{�X�X�e�[�W
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/04	�{�X�X�e�[�W�N���X�̍쐬
//
//===================================================================
#pragma once


//====== �C���N���[�h�� ======
#include "../main.h"
#include "stage.h"


//===== �N���X��` =====
class CStageBoss : public CStage
{
public:
	CStageBoss();
	~CStageBoss();

	// �l�又��
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


private:

};


