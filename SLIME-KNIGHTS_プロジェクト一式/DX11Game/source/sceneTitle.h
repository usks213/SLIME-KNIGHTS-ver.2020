//==================================================================
//								sceneGame.h
//	GM21 �Q�[���V�[��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/18	�Q�[���N���X�쐬
//
//===================================================================
#pragma once


//====== �C���N���[�h�� ======
#include "../main.h"
#include "scene.h"


//===== �N���X��` =====
class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	~CSceneTitle();

	// �l�又��
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

private:

};


