//==================================================================
//								playerAction.cpp
//	 
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/13	�v���C���[�A�N�V�����N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "playerAction.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "animation.h"
#include "objectMgr.h"
#include "character.h"
#include "attackBase.h"
#include "effect.h"
#include "experience.h"
#include "camera.h"
#include "player.h"

#ifdef _WIN32
#include "../Sound.h"

#endif // _WIN32


//===== �}�N����` =====
#define KNOCKBACK_FORCEX (12)
#define KNOCKBACK_FORCEY (12)
#define DEFAULT_ANIM_SPEED (12)
#define ATTACK_OFFSET_X (96)

#define ATTACK_INTERVAL (12)

//===== �ÓI�֐� =====


//===== �O���[�o���ϐ� =====
static CSound g_SE_Attack;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CPlayerAction::CPlayerAction()
{
	m_bAttack = false;
	m_nAttackAnimSpeed = 10;
	m_pPlayer = nullptr;
	m_bDown = false;
	m_nAttackInterval = 0;
	m_nFlashCnt = 0;
}

//========================================
//
//	�f�X�g���N�^
//
//========================================
CPlayerAction::~CPlayerAction()
{

}


//========================================
//
//	������
//
//========================================
void CPlayerAction::Init()
{
	g_SE_Attack.Load(FILE_PATH"sound/player/Dagger woosh 5.wav");
	
}

//========================================
//
//	�I������
//
//========================================
void CPlayerAction::Uninit()
{

}


//========================================
//
//	�X�V
//
//========================================
void CPlayerAction::Update()
{
	// �v���C���[�̎�̓���
	if (m_bRight)
	{
		// �A�j���[�V����
		if (m_bDown)
		{
			m_pPlayer->GetAttackAnimator()->SetAnimation("RightAttackUp", m_nAttackAnimSpeed);
		}
		else
		{
			m_pPlayer->GetAttackAnimator()->SetAnimation("RightAttackDown", m_nAttackAnimSpeed);
		}
		// �A�^�b�N�G���A�̍��W
		if(m_pAttackBase != nullptr)
			m_pAttackBase->SetOffSetX(ATTACK_OFFSET_X);
	}
	else
	{
		if (m_bDown)
		{
			m_pPlayer->GetAttackAnimator()->SetAnimation("LeftAttackUp", m_nAttackAnimSpeed);
		}
		else
		{
			m_pPlayer->GetAttackAnimator()->SetAnimation("LeftAttackDown", m_nAttackAnimSpeed);
		}
		// �A�^�b�N�G���A�̍��W
		if(m_pAttackBase != nullptr)
			m_pAttackBase->SetOffSetX(-ATTACK_OFFSET_X);
	}
	// �E�F�|���̈ʒu
	m_pPlayer->GetMainWeapon()->SetPos(m_bRight, m_bDown);

	// �_���[�W
	if (m_eCurAction == DAMAGE || m_pChara->GetStatus()->GetInvincible())
	{
		m_nFlashCnt++;
		if (m_nFlashCnt % 4 == 0)
		{
			m_pChara->GetSprite()->SetColor(Float4{1, 1, 1, 0});
		}
		else
		{
			m_pChara->GetSprite()->SetColor(Float4{ 1, 1, 1, 1 });
		}

		// �󂯐g�̏I��
		if (fabsf(m_pChara->GetRb()->GetForce().x) < 2.0f || !m_pChara->GetRb()->GetUseGravity())
		{
			// ��ԑJ��
			m_eCurAction = WAIT;
			m_pChara->GetRb()->SetDragX(1.0f);
		}
	}
	else
	{
		m_pChara->GetSprite()->SetColor(Float4{ 1, 1, 1, 1 });
		m_nFlashCnt = 0;
	}

	if (m_eCurAction == JUMP)
	{
		// �W�����v�̍ő�_�܂ł�������
		if (m_pChara->GetRb()->GetForce().y > 0.0f)
		{
			// �E������
			if (m_bRight)
			{
				// �A�j���[�V����
				m_pChara->GetAnim()->SetAnimation("RightFall", m_nAnimSpeed);
			}
			else
			{
				// �A�j���[�V����
				m_pChara->GetAnim()->SetAnimation("LeftFall", m_nAnimSpeed);
			}
		}

		// �n�ʂɒ�������
		if(!m_pChara->GetRb()->GetUseGravity())
		{
			m_eCurAction = MOVE;
		}
	}


	// �q�b�g�X�g�b�v
	if (m_pAttackBase)
	{
		if (m_pAttackBase->GetStop())
		{
			m_pChara->SetStop(true);
		}
	}

	if (m_pChara->GetStop())
	{
		m_pChara->GetAnim()->SetStop(true);
		m_pChara->GetRb()->SetStop(true);
		// �v���C���[
		m_pPlayer->GetAttackAnimator()->SetStop(true);
		m_pPlayer->GetMainWeapon()->SetStop(true);

		if (m_nHitStopCnt < 0)
			m_nHitStopCnt = HIT_STOP_FRAME;

		m_nHitStopCnt--;
		if (m_nHitStopCnt < 0)
		{
			m_pChara->SetStop(false);
			m_pChara->GetAnim()->SetStop(false);
			m_pChara->GetRb()->SetStop(false);
			m_pChara->GetStatus()->SetStop(false);
			// �v���C���[
			m_pPlayer->GetAttackAnimator()->SetStop(false);
			m_pPlayer->GetMainWeapon()->SetStop(false);
			m_bAttack = true;

			if(m_pAttackBase)
				m_pAttackBase->SetStop(false);
		}
	}


	// �U���Ԋu
	if (!m_bAttack)
	{
		if(m_nAttackInterval >= 0)
			m_nAttackInterval--;
	}

}


//========================================
//
//	�\�[�h�U��
//
//========================================
void CPlayerAction::Attack(int nAnimSpeed)
{
	if (m_bAttack || m_nAttackInterval > 0) return;

	if (m_eCurAction == WAIT || m_eCurAction == MOVE || m_eCurAction == JUMP)
	{
		// �U���X�s�[�h
		m_nAttackAnimSpeed = nAnimSpeed;

		// �E������
		if (m_bRight)
		{
			// �U���G���A����
			m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), ATTACK_OFFSET_X);
			m_pAttackBase->GetTransform()->SetDir(Float3{ 1.0f, 0.0f, 0.0f });
			m_pAttackBase->GetTransform()->SetSize(Float2{ 150, 150 });
			m_pAttackBase->SetLayer(LAYER::PLAYERATTACK);
			// �G�t�F�N�g
			Float3 pos = m_pChara->GetTransform()->GetPos();
			pos.x += ATTACK_OFFSET_X;
			CEffect::Create(EFFECT::SWORD_R, pos);
		}
		else
		{
			// �U���G���A����
			m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), -ATTACK_OFFSET_X);
			m_pAttackBase->GetTransform()->SetDir(Float3{ -1.0f, 0.0f, 0.0f });
			m_pAttackBase->GetTransform()->SetSize(Float2{150, 150});
			m_pAttackBase->SetLayer(LAYER::PLAYERATTACK);
			// �G�t�F�N�g
			Float3 pos = m_pChara->GetTransform()->GetPos();
			pos.x -= ATTACK_OFFSET_X;
			CEffect::Create(EFFECT::SWORD_L, pos);
		}

		// �E�F�|��
		m_pPlayer->GetMainWeapon()->StartMove(m_nAttackAnimSpeed * 3, m_bRight, m_bDown);

		// ���
		m_bAttack = true;
		// �A�j���[�V�����Đ�
		m_pPlayer->GetAttackAnimator()->SetStop(false);
		// ��ʗh��
		//CCamera::SetCameraShake(1);
		// �T�E���h
		g_SE_Attack.Play();

	}
}

//========================================
//
//	�u�[�������U��
//
//========================================
void CPlayerAction::Attack(int nAnimSpeed, CTransform* pTrans)
{
	if (m_bAttack || m_nAttackInterval > 0) return;

	if (m_eCurAction == WAIT || m_eCurAction == MOVE || m_eCurAction == JUMP)
	{
		// �U���X�s�[�h
		m_nAttackAnimSpeed = nAnimSpeed;

		// �E������
		if (m_bRight)
		{
			// �U���G���A����
			m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), pTrans, ATTACK_OFFSET_X);
			m_pAttackBase->GetTransform()->SetDir(Float3{ 1.0f, 0.0f, 0.0f });
			m_pAttackBase->GetTransform()->SetSize(Float2{ 150, 150 });
			m_pAttackBase->SetLayer(LAYER::PLAYERATTACK);
			// �G�t�F�N�g
			Float3 pos = m_pChara->GetTransform()->GetPos();
			pos.x += ATTACK_OFFSET_X;
			CEffect::Create(EFFECT::SWORD_R, pos);
		}
		else
		{
			// �U���G���A����
			m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), pTrans, -ATTACK_OFFSET_X);
			m_pAttackBase->GetTransform()->SetDir(Float3{ -1.0f, 0.0f, 0.0f });
			m_pAttackBase->GetTransform()->SetSize(Float2{ 150, 150 });
			m_pAttackBase->SetLayer(LAYER::PLAYERATTACK);
			// �G�t�F�N�g
			Float3 pos = m_pChara->GetTransform()->GetPos();
			pos.x -= ATTACK_OFFSET_X;
			CEffect::Create(EFFECT::SWORD_L, pos);
		}

		// �E�F�|��
		m_pPlayer->GetMainWeapon()->SetPos(m_pPlayer->GetTransform()->GetPos());
		m_pPlayer->GetMainWeapon()->StartMove(m_nAttackAnimSpeed * 3, m_bRight, m_bDown);

		// ���
		m_bAttack = true;
		// �A�j���[�V�����Đ�
		m_pPlayer->GetAttackAnimator()->SetStop(false);
		// ��ʗh��
		//CCamera::SetCameraShake(1);
		// �T�E���h
		g_SE_Attack.Play();

	}
}



//========================================
//
//	�A�j���[�V�����I�����ɌĂяo��
//
//========================================
void CPlayerAction::OnAnimatorAction(CAnimator *pAnim)
{
	// �I�������A�j���[�V�����̖��O�ŕ���
	if (pAnim->GetCurrentAnimation()->GetName() == "RightAttackDown" || pAnim->GetCurrentAnimation()->GetName() == "LeftAttackDown" ||
		pAnim->GetCurrentAnimation()->GetName() == "RightAttackUp"   || pAnim->GetCurrentAnimation()->GetName() == "LeftAttackUp")
	{
		if (m_bAttack)
		{
			// �U���G���A������
			if (m_pAttackBase != nullptr)
			{
				m_pAttackBase->Destroy();
				m_pAttackBase = nullptr;
			}
			// ��ԑJ��
			m_bAttack = false;
			m_bDown ^= 1;

			// �U�����x�̃C���^�[�o��
			float speed = (m_pChara->GetStatus()->GetAttackSpeed() / 100.0f);
			m_nAttackInterval = ATTACK_INTERVAL - ATTACK_INTERVAL * speed;

			// �A�j���[�V�����X�g�b�v
			pAnim->SetStop(true);

			// �T�E���h�X�g�b�v
			g_SE_Attack.Stop();
		}
	}
}

