//==================================================================
//								weapon.h
//	����	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/14	�E�F�|���̃N���X
//
//===================================================================


//====== �C���N���[�h�� ======
#include "weapon.h"

#include "objectMgr.h"
#include "animation.h"
#include "animator.h"
#include "rigidbody.h"
#include "collision.h"

#include "effect.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"
#endif // _WIN64

//===== �}�N����` =====
#define OFFSET_X (20)
#define OFFSET_Y (12)


//===== �ÓI�����o =====
CTexture CWeapon::sm_texture[WEAPON::MAX_WEAPON_TYPE];


//===== ���O��� =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CWeapon::CWeapon()
{
	// �A�j���[�^�[
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 192, 192 });
	m_transform.SetAngle(45);

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 1.f, 1.f, 1.f, 1.0f });

	// ���C���[
	m_enLayer = LAYER::WEAPON;

	// ���W�X�V�f�[�^
	m_pParentTrans = nullptr;
	m_nMoveFrame = 0;
	m_nMoveCnt = 0;
	m_bRight = false;
	
	// �I�t�Z�b�g
	m_fOffSetX = OFFSET_X;
	m_fOffSetY = OFFSET_Y;

	// �^�C�v
	m_eWeaponType = WEAPON::SWORD;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CWeapon::~CWeapon()
{
	m_pAnimator->Destroy();
}


//========================================
//
//	������
//
//========================================
void CWeapon::Init()
{
	// �e�N�X�`��
	//sm_texture.LoadTexture(FILE_PATH"player/weapon_base.tga");
	sm_texture[WEAPON::SWORD].LoadTexture(FILE_PATH"weapon/weapon_sword.tga");
	sm_texture[WEAPON::LANCE].LoadTexture(FILE_PATH"weapon/weapon_lance.tga");
	sm_texture[WEAPON::BOW].LoadTexture(FILE_PATH"weapon/weapon_bow.tga");
	sm_texture[WEAPON::STICK].LoadTexture(FILE_PATH"weapon/weapon_stick.tga");
}

//========================================
//
//	�I������
//
//========================================
void CWeapon::Uninit()
{
	// �e�N�X�`���̉��
	for (int i = 0; i < WEAPON::MAX_WEAPON_TYPE; i++)
	{
		sm_texture[i].UnloadTexture();
	}
}

//========================================
//
//	�X�V����
//
//========================================
void CWeapon::Update()
{
	// ���W�X�V
	if (m_pParentTrans == nullptr) return;
	Float3 pos = m_pParentTrans->GetPos();
	pos.y += m_fOffSetY;

	m_transform.SetPos(pos);
}

//========================================
//
//	�X�V����
//
//========================================
void CWeapon::LateUpdate()
{
	// ���W�X�V
	if (m_pParentTrans == nullptr) return;
	Float3 pos = m_pParentTrans->GetPos();
	pos.y += m_fOffSetY;

	// �E������
	if (m_bRight)
	{
		pos.x += m_fOffSetX;
		// �p�x�X�V
		if (m_nMoveCnt > 0)
		{
			float addAng = 90.0f / m_nMoveFrame;
			if (m_bDown)
			{
				float angle = m_transform.GetAngle() + addAng;
				m_transform.SetAngle(angle);
			}
			else
			{
				float angle = m_transform.GetAngle() - addAng;
				m_transform.SetAngle(angle);
			}

			m_nMoveCnt--;
		}
	}
	else
	{
		pos.x -= m_fOffSetX;
		// �p�x�X�V
		if (m_nMoveCnt > 0)
		{
			float addAng = 90.0f / m_nMoveFrame;
			if (m_bDown)
			{
				float angle = m_transform.GetAngle() - addAng;
				m_transform.SetAngle(angle);
			}
			else
			{
				float angle = m_transform.GetAngle() + addAng;
				m_transform.SetAngle(angle);
			}

			m_nMoveCnt--;
		}
	}
	m_transform.SetPos(pos);


}

//========================================
//
//	�`�揈��
//
//========================================
void CWeapon::Draw()
{
	// ���Z����
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// �l�p�`�̕`��
	m_sprite.Draw(&m_transform, &sm_texture[m_eWeaponType]);

	// �A���t�@����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	����
//
//========================================
CWeapon* CWeapon::Create(CTransform *pParent, WEAPON::EWEAPON_TYPE eType)
{
	CWeapon *pWeapon = CObjectManager::CreateObject<CWeapon>();

	pWeapon->m_pParentTrans = pParent;
	pWeapon->m_eWeaponType = eType;

	return pWeapon;
}

//========================================
//
//	����
//
//========================================
void CWeapon::Destroy()
{
	CObjectManager::DestroyObject(this);

}


//========================================
//
//	�����蔻��
//
//========================================
void CWeapon::OnAnimator(CAnimator *pAnim)
{
	CAnimation *pAn = pAnim->GetCurrentAnimation();
	if (pAn == nullptr) return;

	if (pAn->GetName() == "a")
	{

	}
}


//========================================
//
//	���̃��[�V�����X�^�[�g
//
//========================================
void CWeapon::StartMove(int nFrame, bool bRight, bool bDown)
{
	m_nMoveFrame = m_nMoveCnt = nFrame;
	m_bRight = bRight;
	m_bDown = bDown;

	if (m_bRight)
	{
		if (m_bDown)
		{
			m_transform.SetAngle(180);
		}
		else
		{
			m_transform.SetAngle(270);
		}
	}
	else
	{
		if (m_bDown)
		{
			m_transform.SetAngle(90);
		}
		else
		{
			m_transform.SetAngle(0);
		}
	}
}


void CWeapon::SetPos(bool bRight, bool bDown)
{
	m_bRight = bRight;
	m_bDown = bDown;

	if (m_nMoveCnt > 0) return;

	if (m_bRight)
	{
		if (m_bDown)
		{
			m_transform.SetAngle(180);
		}
		else
		{
			m_transform.SetAngle(270);
		}
	}
	else
	{
		if (m_bDown)
		{
			m_transform.SetAngle(90);
		}
		else
		{
			m_transform.SetAngle(0);
		}
	}

	/*if (m_bRight)
	{
		if (m_bDown)
		{
			m_transform.SetAngle(-45);
		}
		else
		{
			m_transform.SetAngle(45);
		}
	}
	else
	{
		if (m_bDown)
		{
			m_transform.SetAngle(225);
		}
		else
		{
			m_transform.SetAngle(135);
		}
	}*/
}


void CWeapon::SetTargetAngle(Float3 targetPos)
{
	Float3 myPos = m_pParentTrans->GetPos();

	Float3 vec = targetPos;
	vec.x -= myPos.x;
	vec.y -= myPos.y;
	vec.z = 0;

	vec = Normalize(vec);



	Float3 right = Float3{ 1.0f, 0.0f, 0.0f };
	float rad = acosf(Dot(right, vec));
	float angle = rad / 3.1415f * 180.0f;
	float cross = Cross2D(right, vec);

	// �O�`�P�W�O
	if (cross >= 0)
	{
		m_transform.SetAngle(-(angle + 90.0f + 45.0f));
	}
	// �P�W�O�`�R�U�O
	else
	{
		m_transform.SetAngle(angle - 90 - 45.0f);
	}

}
