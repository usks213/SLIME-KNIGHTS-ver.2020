//==================================================================
//									bg.cpp
//	GM21 �w�i
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/05	�w�i�`��
//	2020/06/17	�I�u�W�F�N�g�w����
//
//===================================================================


//====== �C���N���[�h�� ======
#include "bg.h"
#include "../sprite.h"
#include "../texture.h"
#include "camera.h"
#include "objectMgr.h"


//===== �}�N����` =====


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====
CTexture CBG::sm_texture[BG::MAX_BG_TYPE];



//========================================
//
//	�R���X�g���N�^
//
//========================================
CBG::CBG()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform;
	m_transform.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::BG;

	m_pTexture = nullptr;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CBG::~CBG()
{

}


//========================================
//
//	������
//
//========================================
void CBG::Init()
{
	// �e�N�X�`���̃��[�h
	sm_texture[BG::TITLE].LoadTexture(FILE_PATH"title.tga");
	sm_texture[BG::BOSS_MOVIE].LoadTexture(FILE_PATH"ui/movie.tga");

}


//========================================
//
//	�I������
//
//========================================
void CBG::Uninit()
{
	// �e�N�X�`���̉��
	for (int i = 0; i < BG::MAX_BG_TYPE; i++)
	{
		sm_texture[i].UnloadTexture();
	}
}


//========================================
//
//	�X�V
//
//========================================
void CBG::Update()
{


}


//========================================
//
//	�`��
//
//========================================
void CBG::Draw()
{
	m_sprite.Draw(&m_transform, m_pTexture, false);

}


//========================================
//
//	����
//
//========================================
CBG* CBG::Create(BG::EBG_TYPE eType, Float3 pos)
{
	CBG* pBg = CObjectManager::CreateObject<CBG>(pos);

	pBg->m_pTexture = &sm_texture[eType];

	return pBg;
}


//========================================
//
//	�j��
//
//========================================
void CBG::Destroy()
{
	CObjectManager::DestroyObject(this);
}

