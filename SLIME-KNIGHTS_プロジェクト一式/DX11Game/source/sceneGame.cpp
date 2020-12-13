//==================================================================
//								sceneGame.h
//	GM21 �Q�[���V�[��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/18	�Q�[���V�[���N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "sceneGame.h"
#include "sceneTitle.h"
#include "sceneManager.h"
#include "stageManager.h"
#include "experience.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32

//===== �}�N����` =====


//===== �O���[�o���ϐ� =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CSceneGame::CSceneGame()
{
	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CSceneGame::~CSceneGame()
{

}


//========================================
//
//	������
//
//========================================
void CSceneGame::Init()
{
	CStageManager::Init();
	CExperience::Init();

}

//========================================
//
//	�I������
//
//========================================
void CSceneGame::Uninit()
{
	CStageManager::Uninit();
	CExperience::Uninit();

	// �T�E���h
	//g_pVoice->Stop();

}

//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CSceneGame::Update()
{
	CStageManager::Update();

#ifdef _WIN32
	/*if (GetKeyRelease(VK_RETURN))
	{
		CSceneManager::SetNextScene(new CSceneTitle());
	}*/

#endif // _WIN32
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CSceneGame::Draw()
{
	CStageManager::Draw();
}

