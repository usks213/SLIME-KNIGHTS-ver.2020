//==================================================================
//								bullet.h
//	GM21 �o���b�g	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/17	�o���b�g�N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "bullet.h"
#include "collision.h"
#include "objectMgr.h"
#include "rigidbody.h"

#include "effect.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== �}�N����` =====


//===== �ÓI�����o =====
CTexture CBullet::sm_texture[BULLET::MAX_BULLET_TYPE];


//===== ���O��� =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CBullet::CBullet()
{
	// ���W�b�h�{�f�B
	m_pRigidbody = CRigidbody::Create(&m_transform, false, false);
	m_pRigidbody->SetDragX(0);
	m_pRigidbody->SetGravityForce(0.0f);
	m_pRigidbody->SetTrigger(true);

	// �R���W����
	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{20, 20});

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::ENEMYBULLET;

	// �^�C�v
	m_eType = BULLET::BLUE;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CBullet::~CBullet()
{
	// �R���W����
	m_pCollision->Destroy();
	m_pRigidbody->Destroy();
}


//========================================
//
//	������
//
//========================================
void CBullet::Init()
{
	// �e�N�X�`��
	sm_texture[BULLET::BLUE].LoadTexture(FILE_PATH"bullet/bullet_blue.tga");
	sm_texture[BULLET::GREEN].LoadTexture(FILE_PATH"bullet/bullet_green.tga");
	sm_texture[BULLET::PURPLE].LoadTexture(FILE_PATH"bullet/bullet_purple.tga");
	sm_texture[BULLET::ARROW].LoadTexture(FILE_PATH"bullet/arrow.tga");
}

//========================================
//
//	�I������
//
//========================================
void CBullet::Uninit()
{
	// �e�N�X�`���̉��
	for (int i = 0; i < BULLET::MAX_BULLET_TYPE; i++)
	{
		sm_texture[i].UnloadTexture();
	}
}

//========================================
//
//	�X�V����
//
//========================================
void CBullet::Update()
{

}

//========================================
//
//	�`�揈��
//
//========================================
void CBullet::Draw()
{
	// ���Z����
//	glBlendFunc(GL_ONE, GL_ONE);
	//if(m_eType != BULLET::ARROW)
	CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// �l�p�`�̕`��
	CTransform trans = m_transform;
	trans.SetSize(Float2{ 40, 40 });
	m_sprite.Draw(&trans, &sm_texture[m_eType]);

	// �A���t�@����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	����
//
//========================================
CBullet* CBullet::Create(Float3 pos, Float3 force, CStatus *pStatus, BULLET::EBULLET_TYPE eType)
{
	CBullet *pBullet = CObjectManager::CreateObject<CBullet>(pos);

	pBullet->m_pRigidbody->SetForce(force);

	Float3 vec = Normalize(force);
	Float3 right = Float3{ 1.0f, 0.0f, 0.0f };
	float rad = acosf(Dot(right, vec));
	float angle = rad / 3.1415f * 180.0f;
	float cross = Cross2D(right, vec);

	// �O�`�P�W�O
	if (cross >= 0)
	{
		pBullet->m_transform.SetAngle(-(angle + 90.0f + 45.0f));
	}
	// �P�W�O�`�R�U�O
	else
	{
		pBullet->m_transform.SetAngle(angle - 90 - 45.0f);
	}

	pBullet->m_pParentStatus = *pStatus;
	pBullet->m_eType = eType;

	switch (eType)
	{
	case BULLET::BLUE:
		break;
	case BULLET::GREEN:
		break;
	case BULLET::PURPLE:
		break;
	case BULLET::ARROW:
		break;
	default:
		break;
	}

	return pBullet;
}

//========================================
//
//	����
//
//========================================
void CBullet::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	����
//
//========================================
void CBullet::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		//CEffect::Create(EFFECT::EXPLOSION, m_pos);
		CObjectManager::DestroyObject(this);
	}
	else if(pObj->GetLayer() == LAYER::FIELD)
	{
		this->Destroy();
	}

	return;
}