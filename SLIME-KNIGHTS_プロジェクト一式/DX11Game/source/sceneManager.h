//==================================================================
//								sceneManager.h
//	GM21 �V�[���Ǘ�
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/16	�V�[���Ǘ��N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "scene.h"
#include "flash.h"

//===== �N���X��` =====

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	// �l�又��
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �V�[���̃Z�b�g
	static void SetNextScene(CScene *pNextScene);
	static void SetSceneChange();

	// �X�V�X�g�b�v�t���O
	static void SetStopFlag(bool bStop) { m_bStop = bStop; }

	// �t���b�V��
	static CFlash* GetFlash() { return m_pFlash; }

private:
	static CScene* m_pCurrentScene;
	static CScene* m_pNextScene;

	static bool m_bStop;
	static CFlash* m_pFlash;
};

