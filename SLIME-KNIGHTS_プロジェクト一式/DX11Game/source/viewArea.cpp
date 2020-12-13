//==================================================================
//								viewArea.h
//	����G���A	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/18	����G���A�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "viewArea.h"

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
CViewArea::CViewArea()
{
	// �R���W����
	m_pCollision = CCollision::Create(this, nullptr);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 500, 500 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 0.0f, 1.0f, 0.0f, 0.08f });

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
CViewArea::~CViewArea()
{
	// �R���W����
	m_pCollision->Destroy();
}


//========================================
//
//	�X�V����
//
//========================================
void CViewArea::Update()
{
	
}

//========================================
//
//	�X�V����
//
//========================================
void CViewArea::LateUpdate()
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
void CViewArea::Draw()
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
CViewArea* CViewArea::Create(CEnemy *pParent)
{
	CViewArea *pViewArea = CObjectManager::CreateObject<CViewArea>();

	pViewArea->m_pParentEnemy = pParent;

	return pViewArea;
}

//========================================
//
//	����
//
//========================================
void CViewArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�����蔻��
//
//========================================
void CViewArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		m_pParentEnemy->SetTarget(pObj->GetTransform());
	}
}
