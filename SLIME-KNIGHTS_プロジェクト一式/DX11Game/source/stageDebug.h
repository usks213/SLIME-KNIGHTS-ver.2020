//==================================================================
//								sceneDebug.h
//	�f�o�b�O�X�e�[�W
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/23	�f�o�b�O�X�e�[�W�N���X�̍쐬
//
//===================================================================
#pragma once


//====== �C���N���[�h�� ======
#include "../main.h"
#include "stage.h"


//===== �N���X��` =====
class CStageDebug : public CStage
{
public:
	CStageDebug();
	~CStageDebug();

	// �l�又��
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


private:

};


