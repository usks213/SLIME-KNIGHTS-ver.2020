//==================================================================
//									key.cpp
//	�L�[�{�[�h�̉摜
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/06	�L�[�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "key.h"
#include "../sprite.h"
#include "../texture.h"
#include "camera.h"
#include "objectMgr.h"


//===== �}�N����` =====


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====
CTexture CKey::sm_texture[KEY::MAX_KEY_TYPE];



//========================================
//
//	�R���X�g���N�^
//
//========================================
CKey::CKey()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform;
	m_transform.SetSize(Float2{ DEFAULT_OBJECT_SIZE, DEFAULT_OBJECT_SIZE });

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::MAP_OBJ;

	m_pTexture = nullptr;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CKey::~CKey()
{

}


//========================================
//
//	������
//
//========================================
void CKey::Init()
{
	// �e�N�X�`���̃��[�h
	sm_texture[KEY::W].LoadTexture(FILE_PATH"button/key_w.tga");
	sm_texture[KEY::A].LoadTexture(FILE_PATH"button/key_a.tga");
	sm_texture[KEY::S].LoadTexture(FILE_PATH"button/key_s.tga");
	sm_texture[KEY::D].LoadTexture(FILE_PATH"button/key_d.tga");
	sm_texture[KEY::R].LoadTexture(FILE_PATH"button/key_r.tga");

	sm_texture[KEY::Z].LoadTexture(FILE_PATH"button/key_z.tga");
	sm_texture[KEY::X].LoadTexture(FILE_PATH"button/key_x.tga");
	sm_texture[KEY::C].LoadTexture(FILE_PATH"button/key_c.tga");

	sm_texture[KEY::J].LoadTexture(FILE_PATH"button/key_j.tga");
	sm_texture[KEY::K].LoadTexture(FILE_PATH"button/key_k.tga");
	sm_texture[KEY::L].LoadTexture(FILE_PATH"button/key_l.tga");

	sm_texture[KEY::RIGHT].LoadTexture(FILE_PATH"button/key_right.tga");
	sm_texture[KEY::LEFT].LoadTexture(FILE_PATH"button/key_left.tga");
	sm_texture[KEY::UP].LoadTexture(FILE_PATH"button/key_up.tga");
	sm_texture[KEY::DOWN].LoadTexture(FILE_PATH"button/key_down.tga");

	sm_texture[KEY::TAB].LoadTexture(FILE_PATH"button/key_tab.tga");
	sm_texture[KEY::SPACE].LoadTexture(FILE_PATH"button/key_space.tga");

}


//========================================
//
//	�I������
//
//========================================
void CKey::Uninit()
{
	// �e�N�X�`���̉��
	for (int i = 0; i < KEY::MAX_KEY_TYPE; i++)
	{
		sm_texture[i].UnloadTexture();
	}
}


//========================================
//
//	�X�V
//
//========================================
void CKey::Update()
{


}


//========================================
//
//	�`��
//
//========================================
void CKey::Draw()
{
	m_sprite.Draw(&m_transform, m_pTexture, m_bCamera);

}


//========================================
//
//	����
//
//========================================
CKey* CKey::Create(KEY::EKEY_TYPE eType, Float3 pos, bool bCamera)
{
	CKey* pBg = CObjectManager::CreateObject<CKey>(pos);

	pBg->m_pTexture = &sm_texture[eType];
	if (eType == KEY::SPACE) pBg->GetTransform()->SetSize(Float2{ 162, 96 });
	if (eType == KEY::TAB) pBg->GetTransform()->SetSize(Float2{ 144 * 0.6f, 96 * 0.6f });

	pBg->m_bCamera = bCamera;

	return pBg;
}


//========================================
//
//	�j��
//
//========================================
void CKey::Destroy()
{
	CObjectManager::DestroyObject(this);
}

