//==================================================================
//								enemy.cpp
//	GM21 �G�l�~�[
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/05	�G�l�~�[
//
//===================================================================


//====== �C���N���[�h�� ======
#include "enemy.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"
#include "effect.h"
#include "enemyUI.h"

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
CTexture CEnemy::sm_texture[ENEMY::MAX_TYPE];
CSound CEnemy::sm_SE[ENEMY::MAX_ENEMY_SOUND ];


//========================================
//
//	�R���X�g���N�^
//
//========================================
CEnemy::CEnemy()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform;

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::ENEMY;

	// ���W�b�h�{�f�B
	m_pRigidbody->SetDragX(0.08f);

	// �X�e�[�^�X
	m_nMoveCnt = 0;
	m_nMoveType = 0;


	// �r���[�G���A
	m_pViewArea = CViewArea::Create(this);
	m_pAttackArea = CAttackArea::Create(this);

	// �G���A�̃T�C�Y
	m_pViewArea->GetTransform()->SetSize(Float2{ 1000, 1000 });
	m_pAttackArea->GetTransform()->SetSize(Float2{ 500, 500 });

	// �^�[�Q�b�g
	m_pTargetPlayer = nullptr;
	m_bAttack = false;

	// �^�C�v
	m_eType = ENEMY::SLIM;

	// UI
	m_pUI = CEnemyUI::Create(this);

	m_nJumpInterval = rand() % 120;
	m_nMoveInterval = rand() % 120;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEnemy::~CEnemy()
{
	// �r���[�G���A
	m_pViewArea->Destroy();
	m_pAttackArea->Destroy();
	// UI
	m_pUI->Destroy();
}

//========================================
//
//	������
//
//========================================
void CEnemy::Init()
{
	// �e�N�X�`���̃��[�h
	sm_texture[ENEMY::SLIM].LoadTexture(FILE_PATH"enemy/slim_anim.tga");
	sm_texture[ENEMY::WING].LoadTexture(FILE_PATH"enemy/slim_wing_anim.tga");
	sm_texture[ENEMY::WING_GREEN].LoadTexture(FILE_PATH"enemy/slim_wing_green_anim.tga");
	sm_texture[ENEMY::LANCE].LoadTexture(FILE_PATH"enemy/slim_lance_anim.tga");
	sm_texture[ENEMY::BOW].LoadTexture(FILE_PATH"enemy/slim_bow_anim.tga");
	sm_texture[ENEMY::BOSS].LoadTexture(FILE_PATH"enemy/slim_big_wing_anim.tga");

	// �T�E���h�̃��[�h
	sm_SE[ENEMY::SE_BOSS_DESTROY].Load(FILE_PATH"sound/enemy/BossDestroy.mp3");
	sm_SE[ENEMY::SE_ONE_SHOT].Load(FILE_PATH"sound/enemy/EnemyShot1.mp3");
	sm_SE[ENEMY::SE_MUL_SHOT].Load(FILE_PATH"sound/enemy/EnemyShot2.wav");
	sm_SE[ENEMY::SE_BOSS_SHOT].Load(FILE_PATH"sound/enemy/BossShot.wav");
	sm_SE[ENEMY::SE_SLIME].Load(FILE_PATH"sound/enemy/slime.mp3");

}

//========================================
//
//	�I������
//
//========================================
void CEnemy::Uninit()
{
	// �e�N�X�`���̉��
	for (int i = 0; i < ENEMY::MAX_TYPE; i++)
	{
		sm_texture[i].UnloadTexture();
	}
	
}

//========================================
//
//	�X�V
//
//========================================
void CEnemy::Update()
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


//========================================
//
//	�`��
//
//========================================
void CEnemy::Draw()
{
	// �l�p�`�̕`��
	m_sprite.Draw(&m_transform, &sm_texture[m_eType]);

}


//========================================
//
//	�����蔻��
//
//========================================
void CEnemy::OnCollision(CCollision *pCol)
{
	CObject *pObj = pCol->GetObj();

	// �L�����N�^�[�����������̏���
	m_charaAction.OnCollisionAction(pCol);

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		//CObjectManager::DestroyObject(this);
		//CObjectManager::DestroyObject(pObj);
	}
	else if (pObj->GetLayer() == LAYER::FIELD)
	{
		if (pCol->GetRb() == nullptr) return;
		//if (pCol->GetObj()->GetLayer() == LAYER::EXPERIENCE) return;
		if (pCol->GetRb()->GetHitDir() <= DIRECTION::LEFT)
		{
			if (rand() % 2)
			{
				m_nJumpInterval--;
				if (m_nJumpInterval < 0)
				{
					m_pRigidbody->SetForceY(-12);
					m_nJumpInterval = 180;
					//m_charaAction.Jump();
				}
			}
			else
			{
				m_nMoveCnt = -1;
				//CEffect::Create(EFFECT::EXPLOSION, m_pos);
			}
		}
	}
	else if(pObj->GetLayer() == LAYER::ENEMY)
	{
		m_nMoveCnt = -1;
	}

}

