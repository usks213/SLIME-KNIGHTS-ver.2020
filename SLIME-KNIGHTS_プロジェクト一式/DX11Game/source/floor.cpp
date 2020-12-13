//==================================================================
//								floor.cpp
//	�t�B�[���h�p��	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/29	�t���A�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "floor.h"
#include "collision.h"
#include "objectMgr.h"
#include "animation.h"
#include "rigidbody.h"
#include "character.h"

#include "../texture.h"

//===== �}�N����` =====

//===== �ÓI�����o =====
CTexture CFloor::sm_texture;


//===== ���O��� =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CFloor::CFloor()
{
	// �R���W����
	m_pRigidBody = CRigidbody::Create(&m_transform, true, false, true);
	m_pCollision = CCollision::Create(this, m_pRigidBody);


	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ DEFAULT_OBJECT_SIZE, DEFAULT_OBJECT_SIZE / 2 });

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::FLOOR;


}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CFloor::~CFloor()
{
	// �R���W����
	if (m_pCollision != nullptr)
		m_pCollision->Destroy();

	if (m_pRigidBody != nullptr)
		m_pRigidBody->Destroy();
}


//========================================
//
//	������
//
//========================================
void CFloor::Init()
{
	// �e�N�X�`���̃��[�h
	sm_texture.LoadTexture(FILE_PATH"map/floor.tga");
}

//========================================
//
//	�I������
//
//========================================
void CFloor::Uninit()
{
	// �e�N�X�`���̉��
	sm_texture.UnloadTexture();
}

//========================================
//
//	�X�V����
//
//========================================
void CFloor::Update()
{

}

//========================================
//
//	�`�揈��
//
//========================================
void CFloor::Draw()
{
	m_sprite.Draw(&m_transform, &sm_texture);
}


//========================================
//
//	����
//
//========================================
CFloor* CFloor::Create(Float3 pos)
{
	pos.y -= 24;
	CFloor *pBlock = CObjectManager::CreateObject<CFloor>(pos);

	return pBlock;
}

//========================================
//
//	����
//
//========================================
void CFloor::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�����蔻��
//
//========================================
void CFloor::OnCollision(CCollision *pCollision)
{
	CObject *pObj = pCollision->GetObj();

	// �L�����N�^�[�̂Ƃ�
	if (pObj->GetLayer() == LAYER::PLAYER || pObj->GetLayer() == LAYER::ENEMY)
	{
		CCharacter *pChara = static_cast<CCharacter*>(pObj);

		// �X���[
		if (pChara->GetFloorThrough()) return;

		// �ォ��Ԃ����Ă����Ƃ�
		if (m_pRigidBody->GetHitDir() == DIRECTION::DOWN)
		{
			if (pChara->GetRb()->GetForce().y >= 0)
			{
				Float3 pos = m_transform.GetPos();
				pos.x = pObj->GetTransform()->GetPos().x;
				pos.y -= m_transform.GetSize().y / 2 + pObj->GetTransform()->GetSize().y / 2;
				pObj->GetTransform()->SetPos(pos);

				pChara->GetRb()->SetUseGravity(false);
				pChara->GetRb()->SetForceY(0);
			}
		}
	}
}