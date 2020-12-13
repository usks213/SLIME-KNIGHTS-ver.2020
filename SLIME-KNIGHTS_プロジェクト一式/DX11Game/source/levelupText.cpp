//==================================================================
//								levelupText.cpp
//	���x���A�b�v�\��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/05	���x���A�b�v�e�L�X�g�N���X
//
//===================================================================


//====== �C���N���[�h�� ======
#include "levelupText.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "status.h"
#include "animation.h"

#include "../Sound.h"


//===== �}�N����` =====
#define DAMAGE_FORCE_X (6)
#define DAMAGE_FORCE_Y (12)

#define EXIST_TIME (120)


//===== �O���[�o���ϐ� =====
static CSound g_LevelUpSE;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CLevelUpText::CLevelUpText()
{
	// �A�j���[�^�[
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	m_pRigidbody = CRigidbody::Create(&m_transform, false, true, true);

	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 50, 50 });

	// �X�v���C�g�f�[�^
	m_sprite;


	// ���C���[
	m_enLayer = LAYER::EFFECT;

	// �A�j���[�V����


	// ��юU��
	m_pRigidbody->SetDragX(0.001f);
	float rad = (float)(90);
	m_pRigidbody->SetForce(Float3{ cosf(AngleToRadian(rad)) * DAMAGE_FORCE_X, -sinf(AngleToRadian(rad)) * DAMAGE_FORCE_Y, 0.0f });
	m_pRigidbody->SetGravityForce(0.3f);
	m_fForceY =DAMAGE_FORCE_Y;

	// �e�L�X�g����
	//m_pString = STRING::CString::Create();
	//m_pString->SetCamera(true);

	m_nExistTime = EXIST_TIME;

	g_LevelUpSE.Load(FILE_PATH"sound/player/LevelUp3.wav");
	g_LevelUpSE.Play(0.2f);
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CLevelUpText::~CLevelUpText()
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
void CLevelUpText::Init()
{
}

//========================================
//
//	�I������
//
//========================================
void CLevelUpText::Uninit()
{
	
}

//========================================
//
//	�X�V����
//
//========================================
void CLevelUpText::Update()
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
void CLevelUpText::Draw()
{

}

//========================================
//
//	����
//
//========================================
CLevelUpText* CLevelUpText::Create(Float3 pos)
{
	CLevelUpText *pDamageText = CObjectManager::CreateObject<CLevelUpText>(pos);

	pDamageText->m_pString = STRING::CString::Create("LEVEL UP", pos, Float2{50, 50}, Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y, true);
	//pDamageText->m_pString->SetWord(szText);

	// �T�E���h


	return pDamageText;
}

//========================================
//
//	�j��
//
//========================================
void CLevelUpText::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	�R���W����
//
//========================================
void CLevelUpText::OnCollision(CCollision *pCollision)
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
void CLevelUpText::OnAnimator(CAnimator *pAnimator)
{

}
