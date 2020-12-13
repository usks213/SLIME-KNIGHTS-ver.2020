////==================================================================
//								attackArea.h
//	�U������G���A	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/18	�U������G���A�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "attackArea.h"

#include "collision.h"
#include "objectMgr.h"
#include "enemy.h"

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
CAttackArea::CAttackArea()
{
	// �R���W����
	m_pCollision = CCollision::Create(this, nullptr);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 300, 300 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 1.0f, 0.0f, 1.0f, 0.08f });

	// ���C���[
	m_enLayer = LAYER::MAX_LAYER;

	// �G�l�~�[�f�[�^
	m_pParentEnemy = nullptr;

}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CAttackArea::~CAttackArea()
{
	// �R���W����
	m_pCollision->Destroy();
}


//========================================
//
//	�X�V����
//
//========================================
void CAttackArea::Update()
{

}

//========================================
//
//	�X�V����
//
//========================================
void CAttackArea::LateUpdate()
{
	if (m_pParentEnemy == nullptr) return;
	Float3 pos = m_pParentEnemy->GetTransform()->GetPos();

	m_transform.SetPos(pos);
}

//========================================
//
//	�`�揈��
//
//========================================
void CAttackArea::Draw()
{
	// ���Z����
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// �l�p�`�̕`��
	if (GetDebugFlag())
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
CAttackArea* CAttackArea::Create(CEnemy *pParent)
{
	CAttackArea *pViewArea = CObjectManager::CreateObject<CAttackArea>();

	pViewArea->m_pParentEnemy = pParent;

	return pViewArea;
}

//========================================
//
//	����
//
//========================================
void CAttackArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�����蔻��
//
//========================================
void CAttackArea::OnCollision(CCollision *pCollision)
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		m_pParentEnemy->SetAttack(true);
	}
}
