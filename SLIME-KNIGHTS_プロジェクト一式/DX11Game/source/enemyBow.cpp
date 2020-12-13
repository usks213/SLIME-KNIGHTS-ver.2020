//==================================================================
//								enemyBow.h
//	�|�G�l�~�[
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/06	�|�G�l�~�[
//
//===================================================================


//====== �C���N���[�h�� ======
#include "enemyBow.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"
#include "effect.h"
#include "attackBase.h"
#include "bullet.h"

#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#else
#include "../controller.h"
#endif // _WIN32

//===== �}�N����` =====
#define MAX_ENEMY_TEX_X (2)
#define MAX_ENEMY_TEX_Y (2)
#define ENEMYSPEED (10.0f)

#define SHOT_INTERVAL (300)
#define SHOT_FORCE	(8)


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CEnemyBow::CEnemyBow()
{
	// �I�u�W�F�N�g�̃T�C�Y
	m_transform.SetSize(Float2{ 96, 72 });

	//m_pRigidbody->SetMass(1.0f);
	m_pRigidbody->SetSolid(true);

	// �G���A�̃T�C�Y
	m_pViewArea->GetTransform()->SetSize(Float2{ 3000, 3000 });
	m_pAttackArea->GetTransform()->SetSize(Float2{ 2500, 2500 });

	// �A�j���[�V����
	// ��~
	CAnimation::Create(m_pAnimator, "LeftWait",  2, 0, 1);
	CAnimation::Create(m_pAnimator, "RightWait", 2, 2, 3);
	// ���s
	CAnimation::Create(m_pAnimator, "LeftMove", 2, 0, 1);
	CAnimation::Create(m_pAnimator, "RightMove", 2, 2, 3);

	// �A�j���[�V�����̃Z�b�g
	m_pAnimator->SetAnimation("RightWait", 15, MAX_ENEMY_TEX_X, MAX_ENEMY_TEX_Y);

	// �L�����N�^�[�A�N�V�����f�[�^
	m_charaAction.SetActionData(this, 0, 0);

	// �^�C�v
	m_eType = ENEMY::BOW;

	// �E�F�|��
	m_pWeapon = CWeapon::Create(&m_transform, WEAPON::BOW);
	m_pWeapon->SetOffSetX(0);
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEnemyBow::~CEnemyBow()
{
	// �E�F�|��
	m_pWeapon->Destroy();
}


//========================================
//
//	�X�V
//
//========================================
void CEnemyBow::Update()
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
		float y = m_pTargetPlayer->GetPos().y - m_transform.GetPos().y;

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

		m_nMoveInterval--;

		// �U��
		//if (m_bAttack)
		{
			if (m_nMoveInterval < 0)
			{
				//�e�̐���
				Float3 force = Normalize(Float3{ x, y, 0 });
				force.x *= SHOT_FORCE;
				force.y *= SHOT_FORCE;
				CBullet::Create(m_transform.GetPos(), force, &m_status, BULLET::ARROW);
				m_nMoveInterval = SHOT_INTERVAL;
				// �T�E���h
				CEnemy::sm_SE[ENEMY::SE_ONE_SHOT].Play(0.2f);
			}
		}

		m_pWeapon->SetTargetAngle(m_pTargetPlayer->GetPos());
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
		}
	}

	// �^�[�Q�b�g
	m_pTargetPlayer = nullptr;
	m_bAttack = false;

}

