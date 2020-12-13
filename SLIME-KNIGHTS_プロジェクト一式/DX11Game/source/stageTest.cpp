//==================================================================
//									stage.cpp
//	GM21 �����؂�̃X�e�[�W
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/14	�I�u�W�F�N�g�w���ŏ�������
//	
//	
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageTest.h"
#include "../sprite.h"
#include "../texture.h"

#ifdef _WIN32
#include "../input.h"
#else
#include "../controller.h"
#endif // _WIN32

#include "object.h"
#include "bg.h"
#include "block.h"
#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "fade.h"
#include "field.h"
#include "bullet.h"
#include "attackBase.h"
#include "enemySlim.h"
#include "enemyWing.h"
#include "enemyLance.h"

#include "camera.h"

#include "List.h"
#include "objectMgr.h"
#include "collision.h"


//===== �}�N����` =====


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====
static CTexture g_TexBG;
static CTexture g_TexTile;


//========================================
//
//	������
//
//========================================
void InitStage(void)
{
	// �w�i�̏�����
	CBG::Init();
	// �u���b�N�̏�����
	CBlock::Init();
	// �^�[�Q�b�g�̏�����
	CEnemy::Init();
	// �G�t�F�N�g�̏�����
	CEffect::Init();
	// �e
	CBullet::Init();
	// �v���C���[�̏�����
	CPlayer::Init();
	
	// �t�B�[���h����
	//g_pField = CField::Create(FILE_PATH"untitled.csv", FILE_PATH"tile.tga", 11, 15);
	CField::CreateBg(FILE_PATH"map/renga_bg.csv", &g_TexBG, 1, 1);
	CField::Create(FILE_PATH"map/renga_tile.csv", &g_TexTile, 11, 5);
	CField::SetObject(FILE_PATH"map/renga_object.csv");

	// �v���C���[�̐���
	//g_pPlayer = CObjectManager::CreateObject<CPlayer>(Float3{ 96.0f * 15, 96.0f * 10, 0 });

}


//========================================
//
//	�I��
//
//========================================
void UninitStage(void)
{
	// �e�N�X�`��
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();

	// �v���C���[�̏I������
	CPlayer::Uninit();

	// �e
	CBullet::Uninit();

	// �G�t�F�N�g�̏I������
	CEffect::Uninit();

	// �^�[�Q�b�g�̏I������
	CEnemy::Uninit();

	// �u���b�N�̏I������
	CBlock::Uninit();

	// �w�i�̏I������
	CBG::Uninit();
}


//========================================
//
//	�X�V
//
//========================================
void UpdateStage(void)
{
	// �J����
	//CCamera::SetCameraTarget(g_pPlayer->GetTransform());

	for (int i = 0; i < 100; i++)
	{
		//CEffect::Create(EFFECT::EXPLOSION, Float3{ rand() % 96 * (float)g_pField->GetWidth(), rand() % 96 * (float)g_pField->GetHieght(), 0 });

	}
	
#ifdef _WIN32
	
#else

#endif // _WIN32
	
}


//========================================
//
//	�`��
//
//========================================
void DrawStage(void)
{

}

