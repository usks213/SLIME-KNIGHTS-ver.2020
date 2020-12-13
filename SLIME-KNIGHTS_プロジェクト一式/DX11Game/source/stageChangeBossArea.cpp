//==================================================================
//											stageChageBossArea.h
//	�X�e�[�W�`�F���W�G���A�̃{�X������
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/04	�X�e�[�W�`�F���W�{�X�G���A�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageChangeBossArea.h"

#include "collision.h"
#include "objectMgr.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "stageBoss.h"
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
CTexture CStageChangeBossArea::sm_texture;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageChangeBossArea::CStageChangeBossArea()
{
	// �R���W����
	m_pCollision = CCollision::Create(this, nullptr);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 150, 150 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 0.8f, 0.8f, 0.8f, 1 });
	// ���C���[
	m_enLayer = LAYER::FIELD;

	m_Hit = false;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageChangeBossArea::~CStageChangeBossArea()
{
	// �R���W����
	m_pCollision->Destroy();
}

//========================================
//
//	������
//
//========================================
void CStageChangeBossArea::Init()
{
	sm_texture.LoadTexture(FILE_PATH"object/boss_gate.tga");
}

//========================================
//
//	�I������
//
//========================================
void CStageChangeBossArea::Uninit()
{
	sm_texture.UnloadTexture();
}


//========================================
//
//	�X�V����
//
//========================================
void CStageChangeBossArea::Update()
{
	
}

//========================================
//
//	�X�V����
//
//========================================
void CStageChangeBossArea::LateUpdate()
{

}

//========================================
//
//	�`�揈��
//
//========================================
void CStageChangeBossArea::Draw()
{
	// ���Z����
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// �l�p�`�̕`��
	//if (GetDebugFlag())
	m_sprite.Draw(&m_transform, &sm_texture);

	// �A���t�@����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	����
//
//========================================
CStageChangeBossArea* CStageChangeBossArea::Create(Float3 pos)
{
	pos.y -= 96 + 48;
	CStageChangeBossArea *pStageChangeArea = CObjectManager::CreateObject<CStageChangeBossArea>(pos);
	pStageChangeArea->GetTransform()->SetSize(Float2{ 96*3, 96*4 });

	return pStageChangeArea;
}

//========================================
//
//	����
//
//========================================
void CStageChangeBossArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�����蔻��
//
//========================================
void CStageChangeBossArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		if (FADE::GetNowFade()) return;
		if (m_Hit) return;


		CStageManager::SetNextStage(new CStageBoss());

		m_Hit = true;
	}
}
