//==================================================================
//								enemyUI.cpp
//	�G�l�~�[��UI
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/07	�G�l�~�[UI�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "enemyUI.h"
#include "enemy.h"
#include "objectMgr.h"
#include "status.h"



//===== �}�N����` =====
#define BG_OFFSET_X (0)
#define BG_OFFSET_Y (0)
#define BG_SIZE_X (18)
#define BG_SIZE_Y (5)

#define UI_OFFSET_X (0)
#define UI_OFFSET_Y (0)
#define UI_SIZE_X (16)
#define UI_SIZE_Y (18)

#define HP_OFFSET_X (0)
#define HP_OFFSET_Y (0)
#define HP_SIZE_X (16)
#define HP_SIZE_Y (3)


CTexture CEnemyUI::sm_UiTexture;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CEnemyUI::CEnemyUI()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 4, 4 });

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::UI;

	// �J���[
	m_colorBG = Float4{ 0.6f, 0.5f, 0.6f, 1.0f };
	m_colorUI = Float4{ 1, 1, 1, 1.0f };
	m_colorHP = Float4{ 1, 0, 0, 1.0f };
	
	// �傫��
	m_sizeHP.x = 1;
	m_sizeHP.y = 1;

	m_bDraw = true;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEnemyUI::~CEnemyUI()
{
}


//========================================
//
//	������
//
//========================================
void CEnemyUI::Init()
{
	// UI�e�N�X�`���̃��[�h
	sm_UiTexture.LoadTexture(FILE_PATH"player/statusUI.tga");
}

//========================================
//
//	�I������
//
//========================================
void CEnemyUI::Uninit()
{
	// �e�N�X�`���̉��
	sm_UiTexture.UnloadTexture();
}

//========================================
//
//	�X�V����
//
//========================================
void CEnemyUI::Update()
{
}

//========================================
//
//	��X�V����
//
//========================================
void CEnemyUI::LateUpdate()
{
	CStatus status = *m_pParent->GetStatus();

	// HP
	m_sizeHP.x = 1.0f - (float)status.GetHp() / status.GetMaxHp();

}

//========================================
//
//	�`�揈��
//
//========================================
void CEnemyUI::Draw()
{
	if (!m_bDraw) return;
 
	CTransform trans;
	Float3 pos = m_pParent->GetTransform()->GetPos();
	Float2 size = m_transform.GetSize();
	pos.y -= 24 * size.y;

	// BG
	trans.SetPos(Float3{pos.x + BG_OFFSET_X * size.x, pos.y + BG_OFFSET_Y * size.y, 0});
	trans.SetSize(Float2{ BG_SIZE_X * size.x, BG_SIZE_Y * size.y });
	m_sprite.SetColor(m_colorBG);
	m_sprite.Draw(&trans, nullptr);


	// HP
	trans.SetPos(Float3{ pos.x + (HP_OFFSET_X - m_sizeHP.x * HP_SIZE_X / 2) * size.x, pos.y + HP_OFFSET_Y * size.y, 0 });
	trans.SetSize(Float2{ HP_SIZE_X * size.x * (1.0f - m_sizeHP.x), HP_SIZE_Y * size.y });
	m_sprite.SetColor(m_colorHP);
	m_sprite.Draw(&trans, nullptr);


	// UI
	trans.SetPos(Float3{ pos.x + UI_OFFSET_X * size.x, pos.y + UI_OFFSET_Y * size.y, 0 });
	trans.SetSize(Float2{ UI_SIZE_X * size.x, UI_SIZE_Y * size.y });
	m_sprite.SetColor(m_colorUI);
//	m_sprite.Draw(&trans, &sm_UiTexture);
}

//========================================
//
//	����
//
//========================================
CEnemyUI* CEnemyUI::Create(CEnemy* pParent)
{
	Float3 pos = pParent->GetTransform()->GetPos();

	CEnemyUI *pEnemyUI = CObjectManager::CreateObject<CEnemyUI>(pos);
	Float2 size = pEnemyUI->m_transform.GetSize();
	pEnemyUI->m_pParent = pParent;

	return pEnemyUI;
}

//========================================
//
//	�j��
//
//========================================
void CEnemyUI::Destroy()
{
	CObjectManager::DestroyObject(this);
}

