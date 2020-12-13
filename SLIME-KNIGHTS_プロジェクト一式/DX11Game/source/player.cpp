//==================================================================
//								player.cpp
//	GM21 �v���C���[�֘A
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/05	�v���C���[�`��
//
//	2020/06/10	�R���g���[���[����
//
//	2020/06/12	�Z���T�[����
//
//===================================================================


//====== �C���N���[�h�� ======
#include "player.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "animator.h"
#include "animation.h"
#include "rigidbody.h"
#include "bullet.h"
#include "camera.h"
#include "levelupText.h"

#include "weapon.h"
#include "string.h"
#include "effect.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#else
#include "../controller.h"
#endif // _WIN32

//===== �}�N����` =====
#define MAX_PLAYER	(1)
#define MAX_PLAYER_TEX_X (4)
#define MAX_PLAYER_TEX_Y (32)
#define PLAYER_SPEED (12.0f)
#define THROUGH_TIME (20)
#define ANIM_SPEED (6)

//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====
// �����x�Z���T�[�p�ϐ�
Float3 g_accPlayer;			// ���݂̉����x��ۑ�
Float3 g_accPlayerPrev;		// ���O�t���[���̉����x�Z���T�[
// �W���C���Z���T�[�p�ϐ�
Float3 g_gyroPlayer;		// (x,y,z)���e(0.0�`1.0)�̊Ԃ̊p�x
Float3 g_gyroReset;			// �W���C���Z���T�[�̊p�x���Z�b�g�p


//===== �ÓI�����o =====
CTexture CPlayer::sm_texture;
CTexture CPlayer::sm_attackTexture;
CStatus CPlayer::sm_backupStatus;

//===== �O���[�o���ϐ� =====
static CSound g_SE_Move;
static CSound g_SE_Jump;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CPlayer::CPlayer()
{
	// �|���S���̃p�����[�^�̏�����
	//m_transform.SetPos(Float3{ 96 * 4, 96 * 11, 0 });

	// �X�v���C�g�f�[�^
	m_sprite;
	
	// ���C���[
	m_enLayer = LAYER::PLAYER;

	// �X���[
	m_nThrouTime = 0;

	// �A�j���[�V�����̍Đ�
	// ��~
	CAnimation::Create(m_pAnimator, "LeftWait",  6, 0, 1, 2, 3,  4,  5);
	CAnimation::Create(m_pAnimator, "RightWait", 6, 6, 7, 8, 9, 10, 11);
	// ���s
	CAnimation::Create(m_pAnimator, "LeftMove",  4, 12, 13, 14, 15);
	CAnimation::Create(m_pAnimator, "RightMove", 4, 18, 19, 20, 21);
	// �W�����v
	CAnimation::Create(m_pAnimator, "LeftJump", 2, 24, 25);
	CAnimation::Create(m_pAnimator, "RightJump", 2, 33, 32);
	// ����
	CAnimation::Create(m_pAnimator, "LeftFall", 2, 26, 27);
	CAnimation::Create(m_pAnimator, "RightFall", 2, 31, 30);


	// �U���p�A�j���[�^�[�̐���
	m_pAttackAnimator = CAnimator::Create(&m_attackSprite, this);
	// �U���A�j���[�V����
	CAnimation::Create(m_pAttackAnimator, "LeftAttackDown", 3, 0, 1, 2);
	CAnimation::Create(m_pAttackAnimator, "RightAttackDown", 3, 3, 4, 5);
	CAnimation::Create(m_pAttackAnimator, "LeftAttackUp", 3, 6, 7, 8);
	CAnimation::Create(m_pAttackAnimator, "RightAttackUp", 3, 9, 10, 11);
	m_pAttackAnimator->SetAnimation("LeftAttack", 10, 3, 4);
	m_pAttackAnimator->SetStop(true);

	// �A�j���[�V�����̃Z�b�g
	m_pAnimator->SetAnimation("LeftWait", 18, 6, 8);


	// �T�E���h
	g_SE_Move.Load(FILE_PATH"sound/player/Concrete footsteps 5.wav");
	g_SE_Jump.Load(FILE_PATH"sound/player/PlayerJump.mp3");

	// �ړ�SE�t���O
	m_bMoveSE = false;
	m_nMoveSECnt = 0;

	// �L�����N�^�[�A�N�V�����̃Z�b�g
	m_charaAction.SetActionData(this, PLAYER_SPEED, PLAYER_SPEED * 2.0f, ANIM_SPEED);
	m_charaAction.SetPlayerAttackData(this, 4);

	// �E�F�|��
	m_pMainWeapon = CWeapon::Create(&m_transform, WEAPON::SWORD);
	//m_pMainWeapon = CObjectManager::CreateObject<CBoomerang>();

	// �R���{
	m_pCombo = CCombo::Create(Float3{ SCREEN_CENTER_X - 96, SCREEN_CENTER_Y - 88, 0 });

	// �X�e�[�^�X
	m_status.SetLevel(0);
	m_status.AddLevel(1);
	m_status.SetExperience(0);
	m_status.SetInvincibleTime(90);
	m_status;

	// �t���O
	m_bPlayerStop = false;
	m_bInputStop = false;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CPlayer::~CPlayer()
{
	m_pMainWeapon->Destroy();
	m_pAttackAnimator->Destroy();
	m_pCombo->Destroy();
}

//========================================
//
//	������
//
//========================================
void CPlayer::Init()
{
	// �e�N�X�`���̃��[�h
	//sm_texture.LoadTexture(FILE_PATH"Chara.tga");
	sm_texture.LoadTexture(FILE_PATH"player/player_anim_2.tga");
	sm_attackTexture.LoadTexture(FILE_PATH"player/player_attack.tga");

	// �E�F�|��
	CWeapon::Init();


	// �����ŃX�e�[�^�X�f�[�^�̓ǂݍ���


}

//========================================
//
//	�I������
//
//========================================
void CPlayer::Uninit()
{
	// �e�N�X�`���̉��
	sm_texture.UnloadTexture();
	sm_attackTexture.UnloadTexture();


	// �E�F�|��
	CWeapon::Uninit();

	// �����ŃX�e�[�^�X�f�[�^�̏�������


}

//========================================
//
//	�X�V
//
//========================================
void CPlayer::Update()
{
	if (m_bPlayerStop || m_bInputStop) return;

#ifdef _WIN32
	static bool bRight;
	// input
	// �{�^���F�v���X
	if (GetKeyPress(VK_D) || GetKeyPress(VK_RIGHT))
	{
		bRight = true;
		m_charaAction.Right();
		// �T�E���h 
		if (m_nMoveSECnt < 0 && !m_pRigidbody->GetUseGravity())
		{
			g_SE_Move.Play();
			m_bMoveSE = false;
			m_nMoveSECnt = ANIM_SPEED * 2;
			// �G�t�F�N�g
			Float3 pos = m_transform.GetPos();
			pos.x -= m_transform.GetSizeX() / 4;
			pos.y += m_transform.GetSize().y / 3;
			CEffect::Create(EFFECT::DUST_R, pos);
		}
	}
	else if (GetKeyPress(VK_A) || GetKeyPress(VK_LEFT))
	{
		bRight = false;
		m_charaAction.Left();
		// �T�E���h 
		if (m_nMoveSECnt < 0 && !m_pRigidbody->GetUseGravity())
		{
			g_SE_Move.Play();
			m_bMoveSE = false;
			m_nMoveSECnt = ANIM_SPEED * 2;
			// �G�t�F�N�g
			Float3 pos = m_transform.GetPos();
			pos.x += m_transform.GetSizeX() / 4;
			pos.y += m_transform.GetSize().y / 3;
			CEffect::Create(EFFECT::DUST_L, pos);
		}
	}
	else
	{
		// �E�F�C�g
		m_charaAction.Wait();

		m_nMoveSECnt = 0;
	}
	// �����
	if (GetKeyPress(VK_S) || GetKeyPress(VK_DOWN))
	{
		m_bFloorThrough = true;
	}
	// �W�����v
	if ((GetKeyPress(VK_SPACE) || GetKeyPress(VK_W) || GetKeyPress(VK_UP)
		|| GetKeyPress(VK_X) || GetKeyPress(VK_K))
		&& !m_pRigidbody->GetUseGravity())
	{
		m_charaAction.Jump();
		// �T�E���h
		g_SE_Jump.Play(0.6f);
	}
	// �U��
	if (GetKeyPress(VK_Z) || GetKeyPress(VK_L))
	{
		if (bRight)
		{
			//CBullet::Create(Float3{m_transform.GetPos().x + 96, m_transform.GetPos().y, 0}, 50, &m_status);
			//m_charaAction.Attack(3);
		}
		else
		{
			//CBullet::Create(Float3{ m_transform.GetPos().x - 96, m_transform.GetPos().y, 0 }, -50, &m_status);
			//m_charaAction.Attack(3);
		}

		m_charaAction.Attack(3, m_pMainWeapon->GetTransform());

	}

	// �f�o�b�O
	/*if (GetKeyPress(VK_C))
	{
		CLevelUpText::Create(m_transform.GetPos());
	}*/

#else
	static bool bRight;
	// input
	// �{�^���F�v���X
	if (GetControllerPress(NpadButton::Right::Index))
	{
		bRight = true;
		m_charaAction.Right();
	}
	else if (GetControllerPress(NpadButton::Left::Index))
	{
		bRight = false;
		m_charaAction.Left();
	}
	else if (GetControllerPress(NpadButton::Down::Index))
	{
		m_bFloorThrough = true;
	}
	else
	{
		m_charaAction.Wait();
	}
	// �W�����v
	if (GetControllerPress(NpadButton::B::Index))
	{
		//m_pRigidbody->SetForceY(-PLAYER_SPEED * 1.2f);
		m_charaAction.Jump();
	}
	// �U��
	if (GetControllerPress(NpadButton::Y::Index))
	{
		if (bRight)
		{
			//CBullet::Create(Float3{m_transform.GetPos().x + 96, m_transform.GetPos().y, 0}, 50, &m_status);
			m_charaAction.Attack(4);
		}
		else
		{
			//CBullet::Create(Float3{ m_transform.GetPos().x - 96, m_transform.GetPos().y, 0 }, -50, &m_status);
			m_charaAction.Attack(4);
		}
	}


#endif // _WIN32

	// �X���[�t���O�̊Ǘ�
	if (m_bFloorThrough)
	{
		m_nThrouTime++;
		if (m_nThrouTime > THROUGH_TIME)
		{
			m_bFloorThrough = false;
			m_nThrouTime = 0;
		}
	}

	// �ړ�SE
	m_nMoveSECnt--;

	// �X�e�[�^�X�̃o�b�N�A�b�v�����
	sm_backupStatus = m_status;

	// �J����
	CCamera::SetCameraTarget(this->GetTransform());

}

//========================================
//
//	�X�V
//
//========================================
void CPlayer::LateUpdate()
{
	// �X�e�[�^�X�̃o�b�N�A�b�v�����
	sm_backupStatus = m_status;

	if (m_bPlayerStop)
	{
		m_pRigidbody->SetStop(true);
	}
}

//========================================
//
//	�`��
//
//========================================
void CPlayer::Draw()
{
	//if (m_bPlayerStop) return;

	m_sprite.Draw(&m_transform, &sm_texture);
	m_attackSprite.Draw(&m_transform, &sm_attackTexture);
	
}


//========================================
//
//	�����蔻��
//
//========================================
void CPlayer::OnCollision(CCollision *pCol)
{
	if (m_bPlayerStop) return;

	CObject *pObj = pCol->GetObj();

	// �L�����N�^�[�����������̏���
	m_charaAction.OnCollisionAction(pCol);

	// �X�e�[�^�X�̃o�b�N�A�b�v�����
	sm_backupStatus = m_status;
}


//========================================
//
//	�A�j���[�V�����I�����ɌĂяo��
//
//========================================
void CPlayer::OnAnimator(CAnimator *pAnim)
{
	if (m_bPlayerStop) return;

	// �v���C���[�A�N�V����
	m_charaAction.OnAnimatorAction(pAnim); 

	// �I�������A�j���[�V�����̖��O�ŕ���
	if (pAnim->GetCurrentAnimation()->GetName() == "RightMove" || 
		pAnim->GetCurrentAnimation()->GetName() == "LeftMove")
	{
		//m_bMoveSE = true;
	}
};