//==================================================================
//								stageLevelText.h
//	�X�e�[�W���x���̕\��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/07	�X�e�[�W���x���N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageLevelText.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "status.h"
#include "animation.h"



//===== �}�N����` =====
#define DAMAGE_FORCE_X (6)
#define DAMAGE_FORCE_Y (12)

#define EXIST_TIME (120)


//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageLevelText::CStageLevelText()
{
	// �A�j���[�^�[
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 50, 50 });

	// �X�v���C�g�f�[�^
	m_sprite;


	// ���C���[
	m_enLayer = LAYER::EFFECT;

	// �A�j���[�V����

	// �e�L�X�g����
	//m_pString = STRING::CString::Create();
	//m_pString->SetCamera(true);

}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageLevelText::~CStageLevelText()
{
	m_pAnimator->Destroy();
	m_pString->Destroy();

}


//========================================
//
//	������
//
//========================================
void CStageLevelText::Init()
{
	
}

//========================================
//
//	�I������
//
//========================================
void CStageLevelText::Uninit()
{
	
}

//========================================
//
//	�X�V����
//
//========================================
void CStageLevelText::Update()
{
	m_pString->SetPos(m_transform.GetPos());


	if (m_fAlpha > 1.7f && !m_bAlpha)
	{
		m_bAlpha = true;
	}

	if (m_bAlpha)
	{
		m_fAlpha -= 0.01f;
	}
	else
	{
		m_fAlpha += 0.007f;
	}

	m_pString->SetColor(Float4{ 0.9375f,0.9375f,0.9375f,m_fAlpha });

	if (m_fAlpha < 0)
	{
		this->Destroy();
	}
}

//========================================
//
//	�`�揈��
//
//========================================
void CStageLevelText::Draw()
{

}

//========================================
//
//	����
//
//========================================
CStageLevelText* CStageLevelText::Create(Float3 pos, int nLevel)
{
	CStageLevelText *pDamageText = CObjectManager::CreateObject<CStageLevelText>(pos);

	std::sprintf(pDamageText->m_szText, "STAGE LEVEL : %d", nLevel);
	pDamageText->m_pString = STRING::CString::Create(pDamageText->m_szText, pos, Float2{100, 100}, 
					Float4{ 1,1,1,0 }, STRING::CENTER_X, STRING::CENTER_Y);

	pDamageText->m_fAlpha = 0;
	pDamageText->m_bAlpha = false;
	//pDamageText->m_pString->SetWord(szText);

	// �T�E���h


	return pDamageText;
}

//========================================
//
//	�j��
//
//========================================
void CStageLevelText::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	�R���W����
//
//========================================
void CStageLevelText::OnCollision(CCollision *pCollision)
{

}


//========================================
//
//	�A�j���[�^�[
//
//========================================
void CStageLevelText::OnAnimator(CAnimator *pAnimator)
{

}
