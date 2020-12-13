//==================================================================
//								characterAction.h
//	 
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/02	�L�����N�^�[�A�N�V�����N���X�̒ǉ�
//
//
//===================================================================


//====== �C���N���[�h�� ======
#include "characterAction.h"
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
#include "damageText.h"
#include "stageManager.h"
#include "stageStartMap.h"
#include "resultUI.h"
#include "combo.h"
#include "../input.h"


#ifdef _WIN32
#include "../Sound.h"

#endif // _WIN32


//===== �}�N����` =====
#define KNOCKBACK_FORCEX (18)
#define KNOCKBACK_FORCEY (12)
#define DEFAULT_ANIM_SPEED (12)

#define CRITICAL_HITSTOP_FRAME (12)
#define DEFAULT_HITSTOP_FRAME (6)

#define DAMAGE_SHAKE_FRAME (8)

#define DEFAULT_CAMERA_SHAKE_OFFSET (20)
#define CRITICAL_CAMERA_SHAKE_OFFSET (30)
#define DAMAGE_CAMERA_SHAKE_OFFSET (40)


//===== �ÓI�֐� =====
List<CCharacterAction> CCharacterAction::m_list;


//===== �O���[�o���ϐ� =====
static CSound g_SE_PlayerDamage;
static CSound g_SE_EnemyDamage;
static CSound g_SE_Destroy;
static CSound g_SE_CriticalHit;

static int g_nHitStopFrame = DEFAULT_HITSTOP_FRAME;
int GetHitStopFrame() { return g_nHitStopFrame; }


static bool g_bHitStop = true;
static bool g_bCameraShake = true;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CCharacterAction::CCharacterAction()
{
	m_pChara = nullptr;
	m_fMoveForce = 1.0f;
	m_fJumpForce = 1.0f;
	m_bRight = true;
	m_pAttackBase = nullptr;
	m_nAnimSpeed = 12;
	m_nFlashCnt = 0;
	m_eCurAction = WAIT;
	m_nHitStopCnt = -1;
	m_fAttackOffSetX = 0.0f;

	// ���X�g
	m_list.AddNode(this);
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CCharacterAction::~CCharacterAction()
{
	// ���X�g
	m_list.DestroyNode(this);

	// �U���G���A������
	if (m_pAttackBase != nullptr)
	{
		m_pAttackBase->Destroy();
		m_pAttackBase = nullptr;
	}
}


//========================================
//
//	������
//
//========================================
void CCharacterAction::Init()
{
	// �T�E���h�̃��[�h
	g_SE_Destroy.Load(FILE_PATH"sound/enemy/EnemyDestroy1.wav");
	g_SE_EnemyDamage.Load(FILE_PATH"sound/enemy/EnemyDamage2.wav");
	g_SE_PlayerDamage.Load(FILE_PATH"sound/player/PlayerNockBack.wav");
	g_SE_CriticalHit.Load(FILE_PATH"sound/player/CriticalHit.mp3");
}

//========================================
//
//	�I������
//
//========================================
void CCharacterAction::Uninit()
{

}


//========================================
//
//	�f�[�^�Z�b�g
//
//========================================
void CCharacterAction::SetActionData(CCharacter *pChara, float fMoveForce, float fJumpForce, int nAnimSpeed)
{
	m_pChara = pChara;
	m_fMoveForce = fMoveForce;
	m_fJumpForce = fJumpForce;
	if(nAnimSpeed > 0)
		m_nAnimSpeed = nAnimSpeed;
}


//========================================
//
//	�X�V
//
//========================================
void CCharacterAction::Update()
{
	// �U���G���A
	if (m_pAttackBase)
	{
		if (m_bRight)
		{
			m_pAttackBase->SetOffSetX(m_fAttackOffSetX);
			m_pAttackBase->GetTransform()->SetDir(Float3{ 1.0f, 0.0f, 0.0f });
		}
		else
		{
			m_pAttackBase->SetOffSetX(-m_fAttackOffSetX);
			m_pAttackBase->GetTransform()->SetDir(Float3{ -1.0f, 0.0f, 0.0f });
		}
	}


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
		if (fabsf(m_pChara->GetRb()->GetForce().x) < 0.1f)
		{
			// ��ԑJ��
			m_eCurAction = WAIT;
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

		if (m_nHitStopCnt < 0)
			m_nHitStopCnt = HIT_STOP_FRAME;

		m_nHitStopCnt--;
		if (m_nHitStopCnt < 0)
		{
			m_pChara->SetStop(false);
			m_pChara->GetAnim()->SetStop(false);
			m_pChara->GetRb()->SetStop(false);
			m_pChara->GetStatus()->SetStop(false);

			if (m_pAttackBase)
				m_pAttackBase->SetStop(false);
		}
	}


}


//========================================
//
//	�E�ړ�
//
//========================================
void CCharacterAction::Right(int nAnimSpeed)
{
	if (m_eCurAction != DAMAGE)
	{
		// �ړ�
		float speed = 1.0f + m_pChara->GetStatus()->GetMoveSpeed() / 100.0f;
		m_pChara->GetRb()->SetForceX(m_fMoveForce * speed);
	}

	if (m_eCurAction == WAIT || m_eCurAction == MOVE)
	{
		// �A�j���[�V����
		if(nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightMove", nAnimSpeed);
		else				m_pChara->GetAnim()->SetAnimation("RightMove", m_nAnimSpeed);
		// �t���O
		m_bRight = true;
		// ���
		m_eCurAction = MOVE;
	}
	else if (m_eCurAction == JUMP)
	{
		// �W�����v�̍ő�_�܂ł�������
		if (m_pChara->GetRb()->GetForce().y <= 0.0f)
		{
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightJump", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightJump", m_nAnimSpeed);
		}
		else
		{
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightFall", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightFall", m_nAnimSpeed);
		}
		// �t���O
		m_bRight = true;
	}
}

//========================================
//
//	���ړ�
//
//========================================
void CCharacterAction::Left(int nAnimSpeed)
{
	if (m_eCurAction != DAMAGE)
	{
		// �ړ�
		float speed = 1.0f + m_pChara->GetStatus()->GetMoveSpeed() / 100.0f;
		m_pChara->GetRb()->SetForceX(-m_fMoveForce * speed);
	}

	if (m_eCurAction == WAIT || m_eCurAction == MOVE)
	{
		// �A�j���[�V����
		if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftMove", nAnimSpeed);
		else				m_pChara->GetAnim()->SetAnimation("LeftMove", m_nAnimSpeed);
		// �t���O
		m_bRight = false;
		// ���
		m_eCurAction = MOVE;
	}
	else if (m_eCurAction == JUMP)
	{
		// �W�����v�̍ő�_�܂ł�������
		if (m_pChara->GetRb()->GetForce().y <= 0.0f)
		{
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftJump", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftJump", m_nAnimSpeed);
		}
		else
		{
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftFall", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftFall", m_nAnimSpeed);
		}
		// �t���O
		m_bRight = false;
	}
}

//========================================
//
//	��ړ�
//
//========================================
void CCharacterAction::Up(int nAnimSpeed)
{
	// �ړ�
	//if (m_eCurAction != DAMAGE)
	{
		float speed = 1.0f + m_pChara->GetStatus()->GetMoveSpeed() / 100.0f;
		m_pChara->GetRb()->SetForceY(-m_fMoveForce * speed);
	}

	if (m_eCurAction == WAIT || m_eCurAction == MOVE)
	{
		// ���
		m_eCurAction = MOVE;
	}
}

//========================================
//
//	���ړ�
//
//========================================
void CCharacterAction::Down(int nAnimSpeed)
{
	// �ړ�
	//if (m_eCurAction != DAMAGE)
	{
		float speed = 1.0f + m_pChara->GetStatus()->GetMoveSpeed() / 100.0f;
		m_pChara->GetRb()->SetForceY(m_fMoveForce * speed);
	}

	if (m_eCurAction == WAIT || m_eCurAction == MOVE)
	{
		// ���
		m_eCurAction = MOVE;
	}
}

//========================================
//
//	�W�����v
//
//========================================
void CCharacterAction::Jump(int nAnimSpeed)
{
	if (m_eCurAction == WAIT || m_eCurAction == MOVE || m_eCurAction == JUMP)
	{
		// �ړ�
		m_pChara->GetRb()->SetForceY(-m_fJumpForce);
		// �E������
		if (m_bRight)
		{
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightJump", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightJump", m_nAnimSpeed);
		}
		else
		{
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftJump", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftJump", m_nAnimSpeed);
		}
		// ���
		m_eCurAction = JUMP;
	}
}

//========================================
//
//	�E�F�C�g
//
//========================================
void CCharacterAction::Wait(int nAnimSpeed)
{
	if (m_eCurAction != ATTACK && m_eCurAction != DAMAGE && m_eCurAction != JUMP)
	{
		// �E������
		if (m_bRight)
		{
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightWait", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightWait", m_nAnimSpeed);
		}
		else
		{
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftWait", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftWait", m_nAnimSpeed);
		}
		// ���
		m_eCurAction = WAIT;
	}
}

//========================================
//
//	�U��
//
//========================================
void CCharacterAction::Attack(int nAnimSpeed)
{
	if (m_eCurAction == WAIT || m_eCurAction == MOVE || m_eCurAction == JUMP)
	{
		// �T�C�Y
		Float2 size = m_pChara->GetTransform()->GetSize();
		size.x *= 1.2f;
		size.y *= 1.2f;
		// �E������
		if (m_bRight)
		{
			// �U���G���A����
			if (m_pAttackBase == nullptr)
			{
				m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), 0);
				m_pAttackBase->GetTransform()->SetDir(Float3{ 1.0f, 0.0f, 0.0f });
				m_pAttackBase->SetLayer(LAYER::ENEMYATTACK);
				m_pAttackBase->GetTransform()->SetSize(size);
			}
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightAttack", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightAttack", m_nAnimSpeed);
		}
		else
		{
			// �U���G���A����
			if (m_pAttackBase == nullptr)
			{
				m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), 0);
				m_pAttackBase->GetTransform()->SetDir(Float3{ -1.0f, 0.0f, 0.0f });
				m_pAttackBase->SetLayer(LAYER::ENEMYATTACK);
				m_pAttackBase->GetTransform()->SetSize(size);
			}
			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftAttack", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftAttack", m_nAnimSpeed);
		}
		// ���
		m_eCurAction = ATTACK;
	}
}

//========================================
//
//	�U�����󂯂�
//
//========================================
void CCharacterAction::Damage(CStatus *pStatus, int nAnimSpeed)
{
	if (m_eCurAction != DAMAGE)
	{
		// �X�e�[�^�X
		int nHp = m_pChara->GetStatus()->AttackDamage(pStatus);
		// ���񂾂�
		if (nHp <= 0)
		{
			// ���S�G�t�F�N�g

			// �����̐���

			// ����
			CObjectManager::DestroyObject(m_pChara);
		}

		// �E������
		if (m_bRight)
		{
			// �m�b�N�o�b�N
			m_pChara->GetRb();

			// �_��

			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightDamage", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightDamage", m_nAnimSpeed);
		}
		else
		{
			// �m�b�N�o�b�N
			m_pChara->GetRb();

			// �_��

			// �A�j���[�V����
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftDamage", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftDamage", m_nAnimSpeed);
		}
		// ���
		m_eCurAction = DAMAGE;
	}
}

//========================================
//
//	�����蔻���ɌĂяo��
//
//========================================
void CCharacterAction::OnCollisionAction(CCollision *pCol)
{
	// �G�l�~�[
	if (m_pChara->GetLayer() == LAYER::ENEMY)
	{
		// ���������I�u�W�F�N�g�ŕ���
		if (pCol->GetObj()->GetLayer() == LAYER::PLAYERATTACK || pCol->GetObj()->GetLayer() == LAYER::PLAYERBULLET)
		{
			CStatus *pStatus = pCol->GetObj()->GetStatus();
			if (pStatus != nullptr)
			{
				// ���G����Ȃ��Ȃ�
				if (m_pChara->GetStatus()->GetInvincible() == false)
				{
					// ��ԑJ��
					m_eCurAction = DAMAGE;

					// �G�t�F�N�g
					CEffect::Create(EFFECT::ENEMY_DAMAGE, m_pChara->GetTransform()->GetPos());

					// �m�b�N�o�b�N
					CRigidbody *pRb = m_pChara->GetRb();
					if (pCol->GetObj()->GetTransform()->GetDir().x < 0.0f)
					{
						pRb->SetForceX(-KNOCKBACK_FORCEX);
					}
					else
					{
						pRb->SetForceX(KNOCKBACK_FORCEX);
					}
					pRb->SetForceY(-KNOCKBACK_FORCEY);

					// �q�b�g�X�g�b�v
					if (g_bHitStop)
					{
						m_pChara->SetStop(true);
						m_pChara->GetStatus()->SetStop(true);
						pCol->GetObj()->SetStop(true);
					}

					//�R���{���Z
					CStageManager::GetMainPlayer()->GetCombo()->AddCombo(1);

					// �N���e�B�J���v�Z
					bool isCrt = CStageManager::GetMainPlayer()->GetCombo()->GetCritical();
					int nHp = 0;

					// �N���e�B�J������
					if (isCrt)
					{
						// �_���[�W�\�L
						CDamageText::Create(pStatus->GetDamage() * 2, m_pChara->GetTransform()->GetPos(), {1,1,0,1}, true);

						// �_���[�W�v�Z
						nHp = m_pChara->GetStatus()->AttackDamage(pStatus, true);

						// �q�b�g�X�g�b�v�t���[��
						g_nHitStopFrame = CRITICAL_HITSTOP_FRAME;

						// ��ʗh��
						if(g_bCameraShake)
							CCamera::SetCameraShake(CRITICAL_HITSTOP_FRAME, CRITICAL_CAMERA_SHAKE_OFFSET);

						// �T�E���h
						g_SE_CriticalHit.Play();
					}
					else // �������ĂȂ�
					{
						// �_���[�W�\�L
						CDamageText::Create(pStatus->GetDamage(), m_pChara->GetTransform()->GetPos());

						// �_���[�W�v�Z
						nHp = m_pChara->GetStatus()->AttackDamage(pStatus);

						// �q�b�g�X�g�b�v�t���[��
						g_nHitStopFrame = DEFAULT_HITSTOP_FRAME;

						// ��ʗh��
						CCamera::SetCameraShake(DEFAULT_HITSTOP_FRAME, DEFAULT_CAMERA_SHAKE_OFFSET);

						
					}
					// �T�E���h
					g_SE_EnemyDamage.Play();

					// ���񂾂�
					if (nHp <= 0)
					{
						// ���l��߂�
						m_pChara->GetSprite()->SetColorW(1.0f);

						// ���S�G�t�F�N�g

						// �T�E���h
						g_SE_Destroy.Play();

						// �J�E���^�[
						CResultUI::AddEnemy();


						// �o���l�̐���
						//CExperience::Create(m_pChara->GetStatus()->GetExperience(), m_pChara->GetTransform()->GetPos());

						// �o���l
						//pStatus->AddExperience(m_pChara->GetStatus()->GetExperience());

						// ����
						//CObjectManager::DestroyObject(m_pChara);
						m_pChara->Destroy();
					}
				}
			}
		}

	}
	// �v���C���[
	else if (m_pChara->GetLayer() == LAYER::PLAYER)
	{
		// ���������I�u�W�F�N�g�ŕ���
		if (pCol->GetObj()->GetLayer() == LAYER::ENEMYATTACK || pCol->GetObj()->GetLayer() == LAYER::ENEMYBULLET)
		{
			CStatus *pStatus = pCol->GetObj()->GetStatus();
			if (pStatus != nullptr)
			{
				// ���G����Ȃ��Ȃ�
				if (m_pChara->GetStatus()->GetInvincible() == false)
				{
					// ��ԑJ��
					m_eCurAction = DAMAGE;

					// ��ʗh��
					CCamera::SetCameraShake(DAMAGE_SHAKE_FRAME, DAMAGE_CAMERA_SHAKE_OFFSET);

					// �G�t�F�N�g
					CEffect::Create(EFFECT::PLAYER_DAMAGE, m_pChara->GetTransform()->GetPos());

					// �m�b�N�o�b�N
					CRigidbody *pRb = m_pChara->GetRb();
					if (pCol->GetObj()->GetTransform()->GetDir().x < 0.0f)
					{
						pRb->SetForceX(-KNOCKBACK_FORCEX);
					}
					else
					{
						pRb->SetForceX(KNOCKBACK_FORCEX);
					}
					pRb->SetForceY(-KNOCKBACK_FORCEY);
					pRb->SetDragX(0.08f);

					// �q�b�g�X�g�b�v
					m_pChara->SetStop(true);
					m_pChara->GetStatus()->SetStop(true);
					pCol->GetObj()->SetStop(true);
					// �q�b�g�X�g�b�v�t���[��
					g_nHitStopFrame = DEFAULT_HITSTOP_FRAME;

					// �T�E���h
					g_SE_EnemyDamage.Play(1.0f);

					// �R���{���Z
					CStageManager::GetMainPlayer()->GetCombo()->ResetCombo();

					// �_���[�W�\�L
					CDamageText::Create(pStatus->GetDamage(), m_pChara->GetTransform()->GetPos(), {1, 0, 0, 1});

					// �_���[�W�v�Z
					int nHp = m_pChara->GetStatus()->AttackDamage(pStatus);
					// ���񂾂�
					if (nHp <= 0)
					{
						// ���S�G�t�F�N�g

						// �T�E���h
						g_SE_Destroy.Play();

						//// �����̐���
						//for (int i = 0; i < m_pChara->GetStatus()->GetMoney(); i++)
						//	CExperience::Create(EXPERIENCE::ONE, m_pChara->GetTransform()->GetPos());
						// �o���l�̐���
						CExperience::Create(m_pChara->GetStatus()->GetExperience(), m_pChara->GetTransform()->GetPos());

						// HP�ƌo���l���O��
						m_pChara->GetStatus()->SetHp(0);
						m_pChara->GetStatus()->SetExperience(0);

						// ����
						//CObjectManager::DestroyObject(m_pChara);
						// ���l�O�ŃX�g�b�v��������
						m_pChara->GetTransform()->SetPos(Float3{ -1000, -1000, 0 });
						m_pChara->GetRb()->SetStop(true);
						static_cast<CPlayer*>(m_pChara)->SetPlayerStop(true);
						CCamera::SetCameraTarget(nullptr);

						// ���U���h
						CResultUI::SetCurLevel(m_pChara->GetStatus()->GetLevel());

						// ���X�^�[�g
						//CStageManager::SetTimerNextStage(new CStageStartMap(), 300, CStageManager::SetRestart);
						// ���������U���g�\���ɁI
						//CResultUI::Create();
						CStageManager::CreateResult();

						CStageManager::SetBGM(BGM::RENGA_BOSS);
						CStageManager::StopBGM();
					}
				}
			}
		}
	}
}

//========================================
//
//	�A�j���[�V�����I�����ɌĂяo��
//
//========================================
void CCharacterAction::OnAnimatorAction(CAnimator *pAnim)
{
	// �I�������A�j���[�V�����̖��O�ŕ���
	if (pAnim->GetCurrentAnimation()->GetName() == "RightAttack" || pAnim->GetCurrentAnimation()->GetName() == "LeftAttack")
	{
		// �U���G���A������
		if (m_pAttackBase != nullptr)
		{
			m_pAttackBase->Destroy();
			m_pAttackBase = nullptr;
		}

		// ��ԑJ��
		m_eCurAction = WAIT;
	}
}


//========================================
//
//	���X�g�X�V
//
//========================================
void CCharacterAction::ListUpdate()
{
	// ���o�I���I�t
	if (GetKeyTrigger(VK_7))
	{
		g_bCameraShake ^= 1;
		g_bHitStop ^= 1;
	}


	// �擪���X�g�̎擾
	List<CCharacterAction>* pHead = m_list.GetHead();

	// �m�[�h����
	if (pHead == nullptr) return;

	// ���X�g���̈�čX�V
	List<CCharacterAction> *pNode = nullptr;
	List<CCharacterAction> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		// ���̃|�C���^�̃o�b�N�A�b�v�����
		pNextBack = pNode->GetNext();

		// ��čX�V
		pNode->GetThis()->Update();
	}
}


//========================================
//
//	���X�g�X�V
//
//========================================
void CCharacterAction::CreateAttackBase(LAYER::LAYER eLayer, float fOffSetX)
{
	if (m_pAttackBase == nullptr)
	{
		m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), fOffSetX);
		m_pAttackBase->SetLayer(eLayer);
		m_fAttackOffSetX = fOffSetX;
	}

}