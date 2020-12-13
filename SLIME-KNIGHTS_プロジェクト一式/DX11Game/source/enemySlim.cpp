//==================================================================
//								enemySlim.cpp
//	�X���C��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/19	�X���C���N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "enemySlim.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"
#include "effect.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#else
#include "../controller.h"
#endif // _WIN32

//===== �}�N����` =====
#define MAX_ENEMY_TEX_X (8)
#define MAX_ENEMY_TEX_Y (4)
#define ENEMYSPEED (10.0f)

//===== �v���g�^�C�v�錾 =====

//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CEnemySlim::CEnemySlim()
{
	// �G���A�̃T�C�Y
	m_pViewArea->GetTransform()->SetSize(Float2{ 500, 100 });
	m_pAttackArea->GetTransform()->SetSize(Float2{ 300, 100 });

	// �A�j���[�V����
	// ��~
	CAnimation::Create(m_pAnimator, "LeftWait",  4, 0, 1, 2, 3);
	CAnimation::Create(m_pAnimator, "RightWait", 4, 8, 9, 10, 11);
	// ���s
	CAnimation::Create(m_pAnimator, "LeftMove",  4, 0, 1, 2, 3);
	CAnimation::Create(m_pAnimator, "RightMove", 4, 8, 9, 10, 11);
	//�U��
	CAnimation::Create(m_pAnimator, "LeftAttack", 8, 16, 17, 18, 19, 20, 21, 22, 23);
	CAnimation::Create(m_pAnimator, "RightAttack",  8, 24, 25, 26, 27, 28, 29, 30, 31);

	// �A�j���[�V�����̃Z�b�g
	m_pAnimator->SetAnimation("RightWait", 15, MAX_ENEMY_TEX_X, MAX_ENEMY_TEX_Y);

	// �L�����N�^�[�A�N�V�����f�[�^
	m_charaAction.SetActionData(this, 2, 16);

	// �^�C�v
	m_eType = ENEMY::SLIM;

}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEnemySlim::~CEnemySlim()
{

}


//========================================
//
//	�X�V
//
//========================================
void CEnemySlim::Update()
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
		}
		else
		{
			m_charaAction.Right();
		}

		m_nJumpInterval--;
		if (m_bAttack)
		{
			if (!m_pRigidbody->GetUseGravity())
			{
				if (m_nJumpInterval < 0)
				{
					m_charaAction.Jump();
					m_charaAction.Attack(4);
					m_nJumpInterval = 180;
					// �T�E���h
					CEnemy::sm_SE[ENEMY::SE_SLIME].Play(0.4f);
				}
			}
		}
	}
	else
	{
		switch (m_nMoveType)
		{
		case 0:
			m_charaAction.Right();
			break;
		case 1:
			m_charaAction.Left();
			break;
		case 2:
			// �T�E���h
			CEnemy::sm_SE[ENEMY::SE_SLIME].Play(0.4f);
			m_charaAction.Jump();
			m_charaAction.Attack(4);
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

