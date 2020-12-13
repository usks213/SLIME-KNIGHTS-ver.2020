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


//====== �C���N���[�h�� ======
#include "stageStartMap.h"
#include "field.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "sceneManager.h"
#include "resultUI.h"

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
CStageStartMap::CStageStartMap()
{
	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageStartMap::~CStageStartMap()
{

}


//========================================
//
//	������
//
//========================================
void CStageStartMap::Init()
{
	// �e�N�X�`��
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");


	// �}�b�v�̃��[�h
	// ���[�h����}�b�v�̃p�X���쐬
	//BG
	CField::CreateBg(FILE_PATH"map/startMap/map_bg.csv", &g_TexBG, 1, 1);
	// TILE
	CField::Create(FILE_PATH"map/startMap/map_tile.csv", &g_TexTile, 11, 5);
	// OBJECT
	CField::SetObject(FILE_PATH"map/startMap/map_object.csv");
	// PLAYER
	CField::SetPlayer(FILE_PATH"map/startMap/map_player.csv", 0);
	// AREA
	CField::SetChangeArea(FILE_PATH"map/startMap/map_area.csv");

	// �X�e�[�W���x���̏�����
	//CStageManager::SetStageLevel(0);

	// ���U���gUI
	CResultUI::Reset(CStageManager::GetMainPlayer()->GetStatus()->GetLevel());

	// �����_���}�b�v�̐���
	CStageMaker::CreateRendomMap();
	CStageMaker::SubCurMapPosY();
	CStageMaker::SetStartFlag(true);


	// BGM�Đ�
	CStageManager::SetBGM(BGM::START_MAP);

}

//========================================
//
//	�I������
//
//========================================
void CStageStartMap::Uninit()
{
	// �e�N�X�`��
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();
}

//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CStageStartMap::Update()
{

#ifdef _WIN32
	
#endif // _WIN32
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CStageStartMap::Draw()
{

}

