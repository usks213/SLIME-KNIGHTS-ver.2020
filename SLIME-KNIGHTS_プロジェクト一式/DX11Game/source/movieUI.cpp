//==================================================================
//									movieUI.cpp
//	���[�r�[���̍�����
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/08	���[�r�[UI�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "movieUI.h"
#include "../sprite.h"
#include "../texture.h"
#include "camera.h"
#include "objectMgr.h"


//===== �}�N����` =====


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====
CTexture CMovieUI::sm_texture;
bool CMovieUI::m_bDraw = false;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CMovieUI::CMovieUI()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform;
	m_transform.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::FADE;

	// �\���t���O
	m_bDraw = false;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CMovieUI::~CMovieUI()
{

}


//========================================
//
//	������
//
//========================================
void CMovieUI::Init()
{
	// �e�N�X�`���̃��[�h
	sm_texture.LoadTexture(FILE_PATH"ui/movie.tga");

}


//========================================
//
//	�I������
//
//========================================
void CMovieUI::Uninit()
{
	// �e�N�X�`���̉��
	sm_texture.UnloadTexture();
}


//========================================
//
//	�X�V
//
//========================================
void CMovieUI::Update()
{


}


//========================================
//
//	�`��
//
//========================================
void CMovieUI::Draw()
{
	if (!m_bDraw) return;

	m_sprite.Draw(&m_transform, &sm_texture, false);

}


//========================================
//
//	����
//
//========================================
CMovieUI* CMovieUI::Create(Float3 pos)
{
	CMovieUI* pBg = CObjectManager::CreateObject<CMovieUI>(pos);

	return pBg;
}


//========================================
//
//	�j��
//
//========================================
void CMovieUI::Destroy()
{
	CObjectManager::DestroyObject(this);
}

