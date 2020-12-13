//==================================================================
//								enemyLance.h
//	�����X�G�l�~�[
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/20	�����X�G�l�~�[�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "enemyLance.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"
#include "effect.h"
#include "attackBase.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#else
#include "../controller.h"
#endif // _WIN32

//===== �}�N����` =====
#define MAX_ENEMY_TEX_X (4)
#define MAX_ENEMY_TEX_Y (2)
#define ENEMYSPEED (10.0f)


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CEnemyLance::CEnemyLance()
{
	// �I�u�W�F�N�g�̃T�C�Y
	m_transform.SetSize(Float2{ 96, 72 });

	// �G���A�̃T�C�Y
	m_pViewArea->GetTransform()->SetSize(Float2{ 1000, 200 });
	m_pAttackArea->GetTransform()->SetSize(Float2{ 300, 300 });

	// �A�j���[�V����
	// ��~
	CAnimation::Create(m_pAnimator, "LeftWait",  4, 0, 1, 2, 3);
	CAnimation::Create(m_pAnimator, "RightWait", 4, 4, 5, 6, 7);
	// ���s
	CAnimation::Create(m_pAnimator, "LeftMove",  4, 0, 1, 2, 3);
	CAnimation::Create(m_pAnimator, "RightMove", 4, 4, 5, 6, 7);

	// �A�j���[�V�����̃Z�b�g
	m_pAnimator->SetAnimation("RightWait", 15, MAX_ENEMY_TEX_X, MAX_ENEMY_TEX_Y);

	// �L�����N�^�[�A�N�V�����f�[�^
	m_charaAction.SetActionData(this, 4, 16);

	// �^�C�v
	m_eType = ENEMY::LANCE;

	// �E�F�|��
	m_pWeapon = CWeapon::Create(&m_transform, WEAPON::LANCE);
	m_pWeapon->SetOffSetX(0);

	// �U���G���A
	m_charaAction.CreateAttackBase(LAYER::ENEMYATTACK, 50);
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEnemyLance::~CEnemyLance()
{
	// �E�F�|��
	m_pWeapon->Destroy();
}


//========================================
//
//	�X�V
//
//========================================
void CEnemyLance::Update()
{
	m_nMoveCnt--;
	if (m_nMoveCnt < 0)
	{
		m_nMoveType = rand() % 3;
		m_nMoveCnt = 240 + rand() % 120;
	}

	// �^�[�Q�b�g�����鎞
	if (m_pTargetPlayer)
	{
		float x = m_pTargetPlayer->GetPos().x - m_transform.GetPos().x;
		if (x < 0)
		{
			m_charaAction.Left();
			m_pWeapon->SetLeft();
			m_transform.SetDir(Float3{ -1.0f, 0.0f, 0.0f});
		}
		else
		{
			m_charaAction.Right();
			m_pWeapon->SetRight();
			m_transform.SetDir(Float3{ 1.0f, 0.0f, 0.0f });
		}

		if (m_bAttack)
		{
			if (!m_pRigidbody->GetUseGravity())
			{
				//m_charaAction.Jump();
			}
		}


		//m_pWeapon->SetTargetAngle(m_pTargetPlayer->GetPos());
	}
	else
	{
		switch (m_nMoveType)
		{
		case 0:
			m_charaAction.Right();
			m_pWeapon->SetRight();
			break;
		case 1:
			m_charaAction.Left();
			m_pWeapon->SetLeft();
			break;
		case 2:
			m_charaAction.Jump();
			if (m_charaAction.GetRight())
			{
				m_nMoveType = 0;
			}
			else
			{
				m_nMoveType = 1;
			}
			break;
		default:
			break;
		}
	}

	// �^�[�Q�b�g
	m_pTargetPlayer = nullptr;
	m_bAttack = false;

}

