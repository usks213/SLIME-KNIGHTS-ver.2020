//==================================================================
//								needle.h
//	�}�b�v�̐j	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/06	�j�[�h���N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "needle.h"
#include "collision.h"
#include "objectMgr.h"
#include "rigidbody.h"

#include "effect.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== �}�N����` =====


//===== �ÓI�����o =====
CTexture CNeedl::sm_texture;


//===== ���O��� =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CNeedl::CNeedl()
{
	// ���W�b�h�{�f�B
	m_pRigidbody = CRigidbody::Create(&m_transform, true);

	// �R���W����
	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// �|���S���̃p�����[�^�̏�����
	m_transform;

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::ENEMYBULLET;


}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CNeedl::~CNeedl()
{
	// �R���W����
	m_pCollision->Destroy();
	m_pRigidbody->Destroy();
}


//========================================
//
//	������
//
//========================================
void CNeedl::Init()
{
	// �e�N�X�`��
	sm_texture.LoadTexture(FILE_PATH"object/needle.tga");
}

//========================================
//
//	�I������
//
//========================================
void CNeedl::Uninit()
{
	// �e�N�X�`���̉��
	sm_texture.UnloadTexture();
}

//========================================
//
//	�X�V����
//
//========================================
void CNeedl::Update()
{

}

//========================================
//
//	�`�揈��
//
//========================================
void CNeedl::Draw()
{
	// ���Z����
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);


	// �l�p�`�̕`��
	m_sprite.Draw(&m_transform, &sm_texture);

	// �A���t�@����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

	m_bStop = false;
}

//========================================
//
//	����
//
//========================================
CNeedl* CNeedl::Create(Float3 pos)
{
	CNeedl *pBullet = CObjectManager::CreateObject<CNeedl>(pos);

	return pBullet;
}

//========================================
//
//	����
//
//========================================
void CNeedl::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	����
//
//========================================
void CNeedl::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
	}

	return;
}