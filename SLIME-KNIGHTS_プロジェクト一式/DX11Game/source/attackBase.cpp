//==================================================================
//								attackBase.h
//	�U��	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/03	�U���̃N���X
//
//===================================================================


//====== �C���N���[�h�� ======
#include "attackBase.h"

#include "collision.h"
#include "objectMgr.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"

#include "effect.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== �}�N����` =====


//===== ���O��� =====


//========================================
//
//	�R���X�g���N�^
//
//========================================
CAttackBase::CAttackBase()
{
	// �R���W����
	m_pCollision = CCollision::Create(this, nullptr);
	// �A�j���[�^�[
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 100, 100 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 1.0f, 0.0f, 0.0f, 0.1f });

	// ���C���[
	m_enLayer = LAYER::PLAYERATTACK;

	// ���W�X�V�f�[�^
	m_fOffSetX = 0.0f;
	m_pParentStatus = nullptr;
	m_pParentTrans = nullptr;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CAttackBase::~CAttackBase()
{
	// �R���W����
	m_pCollision->Destroy();
	m_pAnimator->Destroy();
}


//========================================
//
//	�X�V����
//
//========================================
void CAttackBase::Update()
{
	if (m_pParentTrans == nullptr) return;
	Float3 pos = m_pParentTrans->GetPos();
	pos.x += m_fOffSetX;

	m_transform.SetPos(pos);
}

//========================================
//
//	�X�V����
//
//========================================
void CAttackBase::LateUpdate()
{
	if (m_pParentTrans == nullptr) return;
	Float3 pos = m_pParentTrans->GetPos();
	pos.x += m_fOffSetX;

	m_transform.SetPos(pos);
}

//========================================
//
//	�`�揈��
//
//========================================
void CAttackBase::Draw()
{
	// ���Z����
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// �l�p�`�̕`��
	if(GetDebugFlag())
		m_sprite.Draw(&m_transform, nullptr);

	// �A���t�@����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	����
//
//========================================
CAttackBase* CAttackBase::Create(CStatus *pStatus, CTransform *pParent, float fOffSet)
{
	CAttackBase *pAttackBase = CObjectManager::CreateObject<CAttackBase>();

	pAttackBase->m_pParentTrans = pParent;

	pAttackBase->m_pParentStatus = pStatus;

	pAttackBase->m_fOffSetX = fOffSet;

	return pAttackBase;
}

//========================================
//
//	����
//
//========================================
void CAttackBase::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�����蔻��
//
//========================================
void CAttackBase::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::ENEMY)
	{
		//CEffect::Create(EFFECT::EXPLOSION, m_pos);
		//CObjectManager::DestroyObject(this);
	}
	
}

//========================================
//
//	�����蔻��
//
//========================================
void CAttackBase::OnAnimator(CAnimator *pAnim)
{
	CAnimation *pAn = pAnim->GetCurrentAnimation();
	if (pAn == nullptr) return;

	if (pAn->GetName() == "a")
	{

	}
}