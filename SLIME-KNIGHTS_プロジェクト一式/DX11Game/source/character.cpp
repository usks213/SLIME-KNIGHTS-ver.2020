//==================================================================
//								character.h
//	GM21 
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/03	�L�����N�^�[�N���X�쐬	
//
//
//===================================================================


//====== �C���N���[�h�� ======
#include "character.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"

//========================================
//
//	�R���X�g���N�^
//
//========================================
CCharacter::CCharacter()
{
	// �A�j���[�^�[
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	m_pRigidbody = CRigidbody::Create(&m_transform);

	m_pCollision = CCollision::Create(this, m_pRigidbody);

	//m_charaAction.SetActionData(this, 5, 10);
	m_bFloorThrough = false;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CCharacter::~CCharacter()
{
	m_pCollision->Destroy();
	m_pAnimator->Destroy();
	m_pRigidbody->Destroy();
}
