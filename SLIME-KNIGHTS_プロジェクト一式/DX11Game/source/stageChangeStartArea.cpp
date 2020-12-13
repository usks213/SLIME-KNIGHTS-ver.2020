//==================================================================
//											stageChageStartArea.cpp
//	�X�e�[�W�`�F���W�G���A�̃X�^�[�g�}�b�v��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/04	�X�e�[�W�`�F���W�X�^�[�g�G���A�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageChangeStartArea.h"

#include "collision.h"
#include "objectMgr.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "fade.h"
#include "stageStartMap.h"

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



//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageChangeStartArea::CStageChangeStartArea()
{
	// �R���W����
	m_pCollision = CCollision::Create(this, nullptr);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 150, 150 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 0.0f, 0.0f, 1.0f, 0.3f });

	// ���C���[
	m_enLayer = LAYER::FIELD;

	m_Hit = false;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageChangeStartArea::~CStageChangeStartArea()
{
	// �R���W����
	m_pCollision->Destroy();
}


//========================================
//
//	�X�V����
//
//========================================
void CStageChangeStartArea::Update()
{
	
}

//========================================
//
//	�X�V����
//
//========================================
void CStageChangeStartArea::LateUpdate()
{

}

//========================================
//
//	�`�揈��
//
//========================================
void CStageChangeStartArea::Draw()
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
CStageChangeStartArea* CStageChangeStartArea::Create(Float3 pos)
{
	CStageChangeStartArea *pStageChangeArea = CObjectManager::CreateObject<CStageChangeStartArea>(pos);
	pStageChangeArea->GetTransform()->SetSize(Float2{ 80, 800 });

	return pStageChangeArea;
}

//========================================
//
//	����
//
//========================================
void CStageChangeStartArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�����蔻��
//
//========================================
void CStageChangeStartArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		if (FADE::GetNowFade()) return;
		if (m_Hit) return;


		CStageManager::SetNextStage(new CStageStartMap());
		CStageManager::SetTutorialClear(true);

		m_Hit = true;
	}
}
