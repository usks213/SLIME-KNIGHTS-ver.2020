//==================================================================
//								sceneBoss.cpp
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


//====== �C���N���[�h�� ======
#include "stageBoss.h"
#include "field.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "sceneManager.h"
#include "BossMakeArea.h"
#include "light.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32

//===== �}�N����` =====


//===== �O���[�o���ϐ� =====
static CTexture g_TexBG;
static CTexture g_TexTile;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageBoss::CStageBoss()
{
	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageBoss::~CStageBoss()
{

}


//========================================
//
//	������
//
//========================================
void CStageBoss::Init()
{
	// �e�N�X�`��
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");

	// ���C�g
	CLight::SetBoss(true);

	// �}�b�v�̃��[�h
	// ���[�h����}�b�v�̃p�X���쐬
	//BG
	CField::CreateBg(FILE_PATH"map/renga/boss/map_bg.csv", &g_TexBG, 1, 1);
	// TILE
	CField::Create(FILE_PATH"map/renga/boss/map_tile.csv", &g_TexTile, 11, 5);
	// OBJECT
	CField::SetObject(FILE_PATH"map/renga/boss/map_object.csv");

	// �v���C���[�̃Z�b�g
	CStageManager::SetPlayerPos(Float3{ 96 * 3, 96 * 15, 0 });

	// �{�X�����G���A�̃Z�b�g
	CBossMakeArea::Create(Float3{ 96 * 37, 96 * 12, 0 });

	// BGM�X�g�b�v
	CStageManager::StopBGM();

	// �R���{���X�g�b�v
	CStageManager::GetMainPlayer()->GetCombo()->SetStop(true);
}

//========================================
//
//	�I������
//
//========================================
void CStageBoss::Uninit()
{
	// �e�N�X�`��
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();

	// ���C�g
	CLight::SetBoss(false);
}

//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CStageBoss::Update()
{

#ifdef _WIN32
	
#endif // _WIN32
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CStageBoss::Draw()
{

}

