//==================================================================
//								miniMap.h
//	�~�j�}�b�v�p�u���b�N
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/04	�~�j�}�b�v�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "miniMap.h"
#include "objectMgr.h"

#include "../texture.h"

//===== �}�N����` =====

//===== �ÓI�����o =====


//===== ���O��� =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CMiniMap::CMiniMap()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{96, 96});
	
	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::UI;

}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CMiniMap::~CMiniMap()
{
}


//========================================
//
//	������
//
//========================================
void CMiniMap::Init()
{

}

//========================================
//
//	�I������
//
//========================================
void CMiniMap::Uninit()
{

}

//========================================
//
//	�X�V����
//
//========================================
void CMiniMap::Update()
{
	
}

//========================================
//
//	�`�揈��
//
//========================================
void CMiniMap::Draw()
{
	m_sprite.Draw(&m_transform, m_pTexture, false);
}


//========================================
//
//	����
//
//========================================
CMiniMap* CMiniMap::Create(Float3 pos, CTexture* nTex, int nTexPos, int nSplitX, int nSplitY)
{
	CMiniMap *pBlock = CObjectManager::CreateObject<CMiniMap>(pos);

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
void CMiniMap::Destroy()
{
	CObjectManager::DestroyObject(this);

}