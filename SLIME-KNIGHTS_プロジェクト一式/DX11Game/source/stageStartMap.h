//==================================================================
//								sceneStartMap.h
//	�X�^�[�g�}�b�v
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/05	�X�^�[�g�}�b�v�N���X�̍쐬
//
//===================================================================
#pragma once


//====== �C���N���[�h�� ======
#include "../main.h"
#include "stage.h"


//===== �N���X��` =====
class CStageStartMap : public CStage
{
public:
	CStageStartMap();
	~CStageStartMap();

	// �l�又��
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


private:

};


