//==================================================================
//								stageChageArea.h
//	�X�e�[�W�`�F���W�G���A	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/23	�X�e�[�W�`�F���W�G���A
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageChangeArea.h"

#include "collision.h"
#include "rigidbody.h"
#include "objectMgr.h"
#include "stageManager.h"
#include "stageDebug.h"
#include "stageMaker.h"
#include "fade.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== �}�N����` =====

enum EMAP_AREA_TYPE
{
	L,
	R,
	T,
	B,
};

//===== ���O��� =====


//===== �ÓI�����o =====
int CStageChangeArea::m_nGotoChangeArea = 1;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageChangeArea::CStageChangeArea()
{
	// ���W�b�h�{�f�B
	//m_pRb = CRigidbody::Create(&m_transform, false, false, true);
	// �R���W����
	m_pCollision = CCollision::Create(this);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 150, 150 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 0.0f, 0.0f, 1.0f, 0.3f });

	// ���C���[
	m_enLayer = LAYER::FIELD;

	m_nChangeAreaType = 0;

	m_Hit = false;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageChangeArea::~CStageChangeArea()
{
	// �R���W����
	m_pCollision->Destroy();
	//m_pRb->Destroy();
}


//========================================
//
//	�X�V����
//
//========================================
void CStageChangeArea::Update()
{
	
}

//========================================
//
//	�X�V����
//
//========================================
void CStageChangeArea::LateUpdate()
{

}

//========================================
//
//	�`�揈��
//
//========================================
void CStageChangeArea::Draw()
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
CStageChangeArea* CStageChangeArea::Create(Float3 pos, int nAreaType)
{
	CStageChangeArea *pStageChangeArea = CObjectManager::CreateObject<CStageChangeArea>(pos);
	pStageChangeArea->m_nChangeAreaType = nAreaType;
	if (nAreaType <= R)
	{
		pStageChangeArea->GetTransform()->SetSize(Float2{ 80, 800 });
	}
	else
	{
		pStageChangeArea->GetTransform()->SetSize(Float2{ 800, 80 });
	}

	return pStageChangeArea;
}

//========================================
//
//	����
//
//========================================
void CStageChangeArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�����蔻��
//
//========================================
void CStageChangeArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		if (FADE::GetNowFade()) return;
		if (m_Hit) return;

		switch (m_nChangeAreaType)
		{
		case L:
			m_nGotoChangeArea = R;
			CStageMaker::SubCurMapPosX();
			break;
		case R:
			m_nGotoChangeArea = L;
			CStageMaker::AddCurMapPosX();
			break;
		case T:
			m_nGotoChangeArea = B;
			CStageMaker::SubCurMapPosY();
			break;
		case B:
			m_nGotoChangeArea = T;
			CStageMaker::AddCurMapPosY();
			break;
		default:
			break;
		}

		CStageManager::SetNextStage(new CStageDebug());

		m_Hit = true;
	}
}
