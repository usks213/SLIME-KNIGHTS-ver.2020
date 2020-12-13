//==================================================================
//								enemyWnig.cpp
//	�H�X���C��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/19	�H�X���C���N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "enemyWing.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"
#include "effect.h"
#include "bullet.h"



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

#define SHOT_INTERVAL (300)
#define SHOT_FORCE	(5)
#define RIGHT_POS	(200)
#define UP_POS		(100)


//===== �v���g�^�C�v�錾 =====

//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CEnemyWing::CEnemyWing()
{
	// �T�C�Y
	m_transform.SetSize(Float2{ 96 * 2, 96 });

	// �d�͂�����
	m_pRigidbody->SetGravityForce(0.0f);

	// �G���A�̃T�C�Y
	m_pViewArea->GetTransform()->SetSize(Float2{ 1500, 1300 });
	m_pAttackArea->GetTransform()->SetSize(Float2{ 1000, 1000 });

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
	m_charaAction.SetActionData(this, 2, 16, 6);

	// �^�C�v
	m_eType = ENEMY::WING;


	// �e�ϐ�
	m_bRight = false;
	m_bUp = false;
	m_nRightPos = RIGHT_POS + rand() % RIGHT_POS;
	m_nUpPos = UP_POS + rand() % UP_POS * 2;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEnemyWing::~CEnemyWing()
{

}


//========================================
//
//	�X�V
//
//========================================
void CEnemyWing::Update()
{
	m_nMoveCnt--;
	if (m_nMoveCnt < 0)
	{
		m_nMoveType = rand() % 4;
		m_nMoveCnt = 240 + rand() % 120;
	}

	// �^�[�Q�b�g�����鎞
	if (m_pTargetPlayer)
	{
		float x = m_pTargetPlayer->GetPos().x - m_transform.GetPos().x;
		float y = m_pTargetPlayer->GetPos().y - m_transform.GetPos().y;

		if (y < m_nUpPos)		m_bUp = true;
		else if(y > m_nUpPos * 2)	m_bUp = false;
		if (x > m_nRightPos)		m_bRight = false;
		else if(x < -m_nRightPos)	m_bRight = true;

		// �ړ�
		if (m_bRight)		m_charaAction.Left();
		else				m_charaAction.Right();
		if (m_bUp)			m_charaAction.Up();
		else				m_charaAction.Down();

		// �U��
	//	if (m_bAttack)
		{
			m_nMoveInterval--;
			if (m_nMoveInterval < 0)
			{
				//�e�̐���
				Float3 force = Normalize(Float3{ x, y, 0 });
				force.x *= SHOT_FORCE;
				force.y *= SHOT_FORCE;
				CBullet::Create(m_transform.GetPos(), force, &m_status, BULLET::BLUE);
				m_nMoveInterval = SHOT_INTERVAL;
				// �T�E���h
				sm_SE[ENEMY::SE_ONE_SHOT].Play(0.2f);
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
			m_charaAction.Up();
			break;
		case 3:
			m_charaAction.Down();
			break;
		default:
			break;
		}
	}

	// �^�[�Q�b�g
	m_pTargetPlayer = nullptr;
	m_bAttack = false;

}

