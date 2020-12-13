//==================================================================
//								experience.cpp
//	�h���b�v���邨��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/08/07	�}�l�[�N���X�̍쐬	
//
//===================================================================


//====== �C���N���[�h�� ======
#include "damageText.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "status.h"
#include "animation.h"



//===== �}�N����` =====
#define DAMAGE_FORCE_X (6)
#define DAMAGE_FORCE_Y (10)

#define TEXT_SIZE (40.0f)

#define EXIST_TIME (120)

//========================================
//
//	�R���X�g���N�^
//
//========================================
CDamageText::CDamageText()
{
	// �A�j���[�^�[
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	m_pRigidbody = CRigidbody::Create(&m_transform, false, true, true);

	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 50, 50 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 1,0,0,1 });


	// ���C���[
	m_enLayer = LAYER::EFFECT;

	// �A�j���[�V����


	// ��юU��
	m_pRigidbody->SetDragX(0.001f);
	float rad = (float)(rand() % 90 + 45);
	m_pRigidbody->SetForce(Float3{ cosf(AngleToRadian(rad)) * DAMAGE_FORCE_X, -sinf(AngleToRadian(rad)) * DAMAGE_FORCE_Y, 0.0f });
	m_pRigidbody->SetGravityForce(0.3f);
	m_fForceY =DAMAGE_FORCE_Y;

	// �e�L�X�g����
	//m_pString = STRING::CString::Create();
	//m_pString->SetCamera(true);

	m_nExistTime = EXIST_TIME;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CDamageText::~CDamageText()
{
	m_pCollision->Destroy();
	m_pAnimator->Destroy();
	m_pRigidbody->Destroy();
	m_pString->Destroy();

}


//========================================
//
//	������
//
//========================================
void CDamageText::Init()
{
	
}

//========================================
//
//	�I������
//
//========================================
void CDamageText::Uninit()
{
	
}

//========================================
//
//	�X�V����
//
//========================================
void CDamageText::Update()
{
	m_pString->SetPos(m_transform.GetPos());

	/*m_nExistTime--;
	if (m_nExistTime < 0)
	{
		this->Destroy();
	}*/
}

//========================================
//
//	�`�揈��
//
//========================================
void CDamageText::Draw()
{

}

//========================================
//
//	����
//
//========================================
CDamageText* CDamageText::Create(int nDamage, Float3 pos, Float4 col, bool bCritical)
{
	CDamageText *pDamageText = CObjectManager::CreateObject<CDamageText>(pos);

	std::sprintf(pDamageText->m_szText, "%d", nDamage);

	// �N���e�B�J������
	if (bCritical)
	{
		pDamageText->m_pString = STRING::CString::Create(pDamageText->m_szText,
			pos, Float2{ TEXT_SIZE*1.5f, TEXT_SIZE*1.5f }, col,
			STRING::CENTER_X, STRING::CENTER_Y, true);
	}
	else
	{
		pDamageText->m_pString = STRING::CString::Create(pDamageText->m_szText,
			pos, Float2{ TEXT_SIZE, TEXT_SIZE }, col,
			STRING::CENTER_X, STRING::CENTER_Y, true);
	}
	//pDamageText->m_pString->SetWord(szText);

	return pDamageText;
}

//========================================
//
//	�j��
//
//========================================
void CDamageText::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	�R���W����
//
//========================================
void CDamageText::OnCollision(CCollision *pCollision)
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::FIELD || pObj->GetLayer() == LAYER::FLOOR)
	{
		if(m_pRigidbody->GetHitDir() == DIRECTION::UP && m_pRigidbody->GetForce().y > 0.0f)
			this->Destroy();
	}

}


//========================================
//
//	�A�j���[�^�[
//
//========================================
void CDamageText::OnAnimator(CAnimator *pAnimator)
{

}
