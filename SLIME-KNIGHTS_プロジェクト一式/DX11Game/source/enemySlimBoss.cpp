//==================================================================
//								enemySlimBoss.cpp
//	�X���C���{�X
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/04	�X���C���{�X�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "enemySlimBoss.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"
#include "effect.h"
#include "flash.h"
#include "sceneManager.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "stageDebug.h"
#include "bullet.h"
#include "enemyWing.h"
#include "enemyLance.h"
#include "enemyBow.h"
#include "enemyBigWing.h"
#include "movieUI.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#else
#include "../controller.h"
#endif // _WIN32

//===== �}�N����` =====
#define MAX_ENEMY_TEX_X (4)
#define MAX_ENEMY_TEX_Y (2)

#define KAKUSAN_SHOT_INTERVAL (180)
#define TUIBI_SHOT_INTERVAL (60)
#define TUIBI_KAKUSAN_SHOT_INTERVAL (90)
#define SHOT_FORCE	(8)

#define BULLET_NUM (10)
#define BULLET_ANGLE (360.0f / BULLET_NUM)

#define STATE_TIME (240)

enum EBOSS_STATE
{
	KAKUSANN_SHOT,
	TUIBI_SHOT,
	TUIBI_KAKUSAN_SHOT,
	ENEMY_POP,

	MAX_STATE,
};


//===== �v���g�^�C�v�錾 =====

//===== �O���[�o���ϐ� =====

//===== �ÓI�����o =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CEnemySlimBoss::CEnemySlimBoss()
{
	// �T�C�Y
	m_transform.SetSize(Float2{ 96 * 2 * 3, 96 * 3 });

	// �d�͂�����
	m_pRigidbody->SetGravityForce(0.0f);
	m_pRigidbody->SetMass(5.0f);
	m_pRigidbody->SetDragX(1);
	m_pRigidbody->SetStop(true);
	m_pRigidbody->SetTrigger(true);
	//m_pRigidbody->SetSolid(true);

	// �G���A�̃T�C�Y
	m_pViewArea->GetTransform()->SetSize(Float2{ 3000, 1500 });
	m_pAttackArea->GetTransform()->SetSize(Float2{ 2500, 1500 });

	// �A�j���[�V����
	// ��~
	CAnimation::Create(m_pAnimator, "LeftWait", 4, 0, 1, 2, 3);
	CAnimation::Create(m_pAnimator, "RightWait", 4, 4, 5, 6, 7);
	// ���s
	CAnimation::Create(m_pAnimator, "LeftMove", 4, 0, 1, 2, 3);
	CAnimation::Create(m_pAnimator, "RightMove", 4, 4, 5, 6, 7);

	// �A�j���[�V�����̃Z�b�g
	m_pAnimator->SetAnimation("LeftWait", 15, MAX_ENEMY_TEX_X, MAX_ENEMY_TEX_Y);

	// �L�����N�^�[�A�N�V�����f�[�^
	m_charaAction.SetActionData(this, 0, 0, 6);

	// �^�C�v
	m_eType = ENEMY::BOSS;

	// UI
	m_pUI->GetTransform()->SetSize(Float2{ 4 * 5, 4 * 3 });
	m_pUI->SetDraw(false);

	// �e�ϐ�
	m_nShotInterval = 0;
	// BGM�̍Đ�
	CStageManager::SetBGM(BGM::RENGA_BOSS);

	// �����ݒ�
	m_nState = rand() % 3;
	m_nStateTime = 0;

	m_fAlpha = 0.0f;
	m_bMovie = true;
	m_nEnemyCnt = 0;

	// �X�e�[�^�X
	m_status.SetLevel((CStageManager::GetStageLevel()) * 15 + 10);
	m_status.SetHp(m_status.GetMaxHp() * 25);
	m_status.SetMaxHp(m_status.GetMaxHp() * 25);
	m_status.SetExperience(m_status.GetExperience() * 10);
	m_status.SetInvincibleCnt(60);
	m_status.SetInvincible(true);

	// MOVIE �w�i
	//m_pBg = CBG::Create(BG::BOSS_MOVIE);
	//m_pBg->SetLayer(LAYER::MAX_LAYER);
	CMovieUI::SetDraw(true);

	// �v���C���[�̒�~
	CStageManager::GetMainPlayer()->SetInputStop(true);
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEnemySlimBoss::~CEnemySlimBoss()
{

}


//========================================
//
//	�X�V
//
//========================================
void CEnemySlimBoss::Update()
{
	if (m_bMovie)
	{
		// ���l���グ�ď��X�ɏo��
		m_fAlpha += 0.004f;
		m_sprite.SetColorW(m_fAlpha);
		
		// �o�������������̏���
		if (m_fAlpha >= 1.0f)
		{
			m_bMovie = false;
			m_pUI->SetDraw(true);

			CMovieUI::SetDraw(false);
			// �v���C���[�̍ĊJ
			CStageManager::GetMainPlayer()->SetInputStop(false);
			/*if (m_pBg)
			{
				m_pBg->Destroy();
				m_pBg = nullptr;
			}*/
		}
		
	}
	else
	{
		if (!m_pTargetPlayer) return;

		Float3 vec;
		vec.x = m_pTargetPlayer->GetPos().x - m_transform.GetPos().x;
		vec.y = m_pTargetPlayer->GetPos().y - m_transform.GetPos().y;
		vec.z = 0;

		// �A�j���[�V����
		if (vec.x >= 0) m_charaAction.Right();
		else			m_charaAction.Left();

		// �U���p�^�[��
		switch (m_nState)
		{
		case KAKUSANN_SHOT:
			m_nShotInterval++;
			if (m_nShotInterval >= KAKUSAN_SHOT_INTERVAL)
			{
				Float3 force;
				for (int i = 0; i < BULLET_NUM; i++)
				{
					force.x = cosf(i * BULLET_ANGLE * 3.1415f / 180.0f) * SHOT_FORCE;
					force.y = sinf(i * BULLET_ANGLE * 3.1415f / 180.0f) * SHOT_FORCE;
					//�e�̐���
					CBullet::Create(m_transform.GetPos(), force, &m_status, BULLET::PURPLE);
				}

				m_nShotInterval = 0;
				// �T�E���h
				sm_SE[ENEMY::SE_MUL_SHOT].Play();
			}
			break;
		case TUIBI_SHOT:
			m_nShotInterval++;
			if (m_nShotInterval >= TUIBI_SHOT_INTERVAL)
			{
				//�e�̐���
				Float3 force = Normalize(vec);
				force.x *= SHOT_FORCE;
				force.y *= SHOT_FORCE;
				CBullet::Create(m_transform.GetPos(), force, &m_status, BULLET::PURPLE);
				m_nShotInterval = 0;
				// �T�E���h
				sm_SE[ENEMY::SE_BOSS_SHOT].Play();
			}
			break;
		case TUIBI_KAKUSAN_SHOT:
			m_nShotInterval++;
			if (m_nShotInterval >= TUIBI_KAKUSAN_SHOT_INTERVAL)
			{
				Float3 force = Normalize(vec);

				for (int i = -1; i < 2; i++)
				{
					//�e�̐���
					// �x�N�g���̉�]
					Float3 rotVec = force;
					rotVec.x = force.x * cosf(AngleToRadian(i * 15)) - force.y * sinf(AngleToRadian(i * 15));
					rotVec.y = force.y * cosf(AngleToRadian(i * 15)) + force.x * sinf(AngleToRadian(i * 15));

					rotVec.x *= SHOT_FORCE;
					rotVec.y *= SHOT_FORCE;
					CBullet::Create(m_transform.GetPos(), rotVec, &m_status, BULLET::PURPLE);
				}
				m_nShotInterval = 0;
				// �T�E���h
				sm_SE[ENEMY::SE_ONE_SHOT].Play(0.5f);
			}
			break;
		case ENEMY_POP:
			if (m_nStateTime == 0)
			{
				if (m_nEnemyCnt == 0)
				{
					// WING
					CObjectManager::CreateObject<CEnemyWing>(Float3{ 96 * 31, 96 * 11, 0 });
					CObjectManager::CreateObject<CEnemyWing>(Float3{ 96 * 43, 96 * 11, 0 });
				}
				else if (m_nEnemyCnt == 1)
				{
					// BOW
					CObjectManager::CreateObject<CEnemyBow>(Float3{ 96 * 24, 96 * 13, 0 });
					CObjectManager::CreateObject<CEnemyBow>(Float3{ 96 * 50, 96 * 13, 0 });
				}
				else if(m_nEnemyCnt == 2)
				{
					CObjectManager::CreateObject<CEnemyBow>(Float3{ 96 * 31, 96 * 13, 0 });
					CObjectManager::CreateObject<CEnemyBow>(Float3{ 96 * 43, 96 * 13, 0 });
				}
				else if (m_nEnemyCnt == 3)
				{
					// BIG WING
					CObjectManager::CreateObject<CEnemyBigWing>(Float3{ 96 * 28, 96 * 12, 0 });
					CObjectManager::CreateObject<CEnemyBigWing>(Float3{ 96 * 46, 96 * 12, 0 });
				}

				m_nEnemyCnt++;
				if (m_nEnemyCnt > 3) m_nEnemyCnt = 0;
			}

			break;
		}

		// ��ԑJ��
		m_nStateTime++;
		if (m_nStateTime > STATE_TIME)
		{
			m_nPrevState = m_nState;
			m_nState = rand() % MAX_STATE;
			while (m_nState == m_nPrevState)
			{
				m_nState = rand() % MAX_STATE;
			}

			m_nStateTime = 0;
			m_nShotInterval = 0;
		}

	}
	// �^�[�Q�b�g
	//m_pTargetPlayer = nullptr;
	//m_bAttack = false;

}


//========================================
//
//	�X�V
//
//========================================
void CEnemySlimBoss::LateUpdate()
{
	m_sprite.SetColorW(m_fAlpha);
	m_pRigidbody->SetStop(true);
	m_pRigidbody->SetForce(Float3{ 0,0,0 });
}


//========================================
//
//	�j��
//
//========================================
void CEnemySlimBoss::Destroy()
{
	// �t���b�V��
	CSceneManager::GetFlash()->StartFlash(FlashAfter, this);
	m_sprite.SetColorW(1.0f);
	// �T�E���h
	CEnemy::sm_SE[ENEMY::SE_BOSS_DESTROY].Play();

	// BGM�X�g�b�v
	CStageManager::StopBGM();

	// �R���{���X�g�b�v
	CStageManager::GetMainPlayer()->GetCombo()->SetStop(true);
}

//========================================
//
//	�t���b�V����
//
//========================================
void CEnemySlimBoss::FlashAfter(CEnemySlimBoss* pBoss)
{
	// �o���l�̐���
	CExperience::Create(pBoss->GetStatus()->GetExperience(), pBoss->GetTransform()->GetPos());

	// �{�X�̔j��
	CObjectManager::DestroyObject(pBoss);
	CObjectManager::SelectClearList(LAYER::ENEMY);
	CObjectManager::SelectClearList(LAYER::ENEMYBULLET);

	// ��莞�Ԍ�G���A�ړ�
	CStageManager::SetTimerNextStage(new CStageDebug(), 600);
	CStageMaker::CreateRendomMap();
	CStageManager::AddStageLevel();
	CStageMaker::SetStartFlag(true);

}