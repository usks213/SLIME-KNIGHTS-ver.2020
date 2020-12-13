//==================================================================
//								block.h
//	GM21 �t�B�[���h�p�u���b�N	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/12	�u���b�N�N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "block.h"
#include "collision.h"
#include "objectMgr.h"
#include "animation.h"
#include "rigidbody.h"

#include "../texture.h"

//===== �}�N����` =====

//===== �ÓI�����o =====


//===== ���O��� =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CBlock::CBlock()
{
	// �R���W����
	m_pRigidBody = CRigidbody::Create(&m_transform, true, false);
	m_pCollision = CCollision::Create(this, m_pRigidBody);


	// �|���S���̃p�����[�^�̏�����
	m_transform;
	
	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::FIELD;


}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CBlock::~CBlock()
{
	// �R���W����
	if(m_pCollision != nullptr)
		m_pCollision->Destroy();

	if (m_pRigidBody != nullptr)
		m_pRigidBody->Destroy();
}


//========================================
//
//	������
//
//========================================
void CBlock::Init()
{

}

//========================================
//
//	�I������
//
//========================================
void CBlock::Uninit()
{

}

//========================================
//
//	�X�V����
//
//========================================
void CBlock::Update()
{

}

//========================================
//
//	�`�揈��
//
//========================================
void CBlock::Draw()
{
	m_sprite.Draw(&m_transform, m_pTexture);
}


//========================================
//
//	����
//
//========================================
CBlock* CBlock::Create(Float3 pos, CTexture* nTex, int nTexPos, int nSplitX, int nSplitY)
{
	CBlock *pBlock = CObjectManager::CreateObject<CBlock>(pos);

	// �e�N�X�`��
	pBlock->m_pTexture = nTex;

	// �e�N�X�`���T�C�Y
	pBlock->m_sprite.SetTexSize(Float2{ 1.0f / nSplitX, 1.0f / nSplitY });

	// �e�N�X�`�����W
	pBlock->m_sprite.SetTexPos(Float2{ nTexPos % nSplitX * pBlock->m_sprite.GetTexSize().x,
										nTexPos / nSplitX * pBlock->m_sprite.GetTexSize().y });

	return pBlock;
}

//========================================
//
//	����
//
//========================================
void CBlock::Destroy()
{
	CObjectManager::DestroyObject(this);

}