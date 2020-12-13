//==================================================================
//									combo.cpp
//	�v���C���[�̃R���{
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/10/28	�R���{�N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "combo.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"


//===== �}�N����` =====
#define ANIM_COMBO_SPLIT_X (10)  // �摜�̕�����(��)
#define ANIM_COMBO_SPLIT_Y (1)  // �摜�̕�����(�c)

#define COMBO_SIZE_X	(50)
#define COMBO_OFFSET_X	(COMBO_SIZE_X)

#define COMBO_TIME (300)

#define GAUGE_BG_SIZE_X (290)
#define GAUGE_BG_SIZE_Y (28)

#define GAUGE_UI_SIZE_X (300)
#define GAUGE_UI_SIZE_Y (30)

#define GAUGE_SIZE_X (GAUGE_BG_SIZE_X)
#define GAUGE_SIZE_Y (GAUGE_BG_SIZE_Y)


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====
CTexture CCombo::sm_texture;
CTexture CCombo::sm_comboTex;
CTexture CCombo::sm_comboUITex;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CCombo::CCombo()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ COMBO_SIZE_X, COMBO_SIZE_X });

	// �X�v���C�g�f�[�^
	for (int i = 0; i < MAX_COMBO; i++)
	{
		m_data[i].m_spr.SetTexSize(Float2{ 1.0f / (float)ANIM_COMBO_SPLIT_X, 1.0f / (float)ANIM_COMBO_SPLIT_Y });
	}
	// ���C���[
	m_enLayer = LAYER::UI;

	m_nComboCount = 0;
	m_nComboTime = 0;
	m_nMaxComboTime = COMBO_TIME;

	Init();
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CCombo::~CCombo()
{
	Uninit();
}


//========================================
//
//	������
//
//========================================
void CCombo::Init()
{
	// �e�N�X�`���̃��[�h
	sm_texture.LoadTexture(FILE_PATH"ui/critical.tga");
	sm_comboTex.LoadTexture(FILE_PATH"ui/combo.tga");
	sm_comboUITex.LoadTexture(FILE_PATH"ui/comboUI.tga");
}


//========================================
//
//	�I������
//
//========================================
void CCombo::Uninit()
{
	sm_texture.UnloadTexture();
	sm_comboTex.UnloadTexture();
	sm_comboUITex.UnloadTexture();
}


//========================================
//
//	�X�V
//
//========================================
void CCombo::LateUpdate()
{
	// ���Ԍo�߂ŃR���{�𖳂���
	if (m_nComboCount > 0)
	{
		m_nComboTime--;
		if (m_nComboTime < 0)
		{
			m_nComboCount -= 10;
			if (m_nComboCount < 0)
				m_nComboCount = 0;
			m_nComboTime = COMBO_TIME;
			UpdateComboTexCoord();
		}
	}
}


//========================================
//
//	�R���{UV�X�V
//
//========================================
void CCombo::UpdateComboTexCoord()
{
	int tmp = m_nComboCount;

	for (int i = MAX_COMBO - 1; 0 <= i; i--)
	{
		m_data[i].m_nAnimNo = tmp % 10;

		m_data[i].m_spr.SetTexPos(Float2{ m_data[i].m_spr.GetTexSize().x * (m_data[i].m_nAnimNo % ANIM_COMBO_SPLIT_X) ,
											m_data[i].m_spr.GetTexSize().y * (m_data[i].m_nAnimNo / ANIM_COMBO_SPLIT_X) });

		tmp /= 10;
	}
}


//========================================
//
//	�`��
//
//========================================
void CCombo::Draw()
{
	// �R���{�Ȃ�
	if (m_nComboCount <= 0) return;

	// �^�C���Q�[�W�̕\��
	CTransform trans = m_transform;
	Float3 pos = m_transform.GetPos();

	// �Q�[�W���W
	pos.x -= COMBO_OFFSET_X * 1.75f;
	pos.y += COMBO_SIZE_X;

	// �Q�[�WBG
	trans.SetSize({ GAUGE_BG_SIZE_X, GAUGE_BG_SIZE_Y });
	trans.SetPos(pos);
	m_sprite.SetColor({ 0.6f, 0.5f, 0.6f, 1.0f });
	m_sprite.Draw(&trans, nullptr, false);

	// �Q�[�W�{��
	float sizeX = GAUGE_SIZE_X * ((float)m_nComboTime / m_nMaxComboTime);
	trans.SetSize({ sizeX, GAUGE_SIZE_Y });

	pos.x += sizeX / 2.0f - GAUGE_SIZE_X / 2.0f;
	trans.SetPos(pos);
	m_sprite.SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
	m_sprite.Draw(&trans, nullptr, false);


	// �Q�[�WUI
	trans.SetSize({ GAUGE_UI_SIZE_X, GAUGE_UI_SIZE_Y });
	pos = m_transform.GetPos();
	pos.x -= COMBO_OFFSET_X * 1.75f;
	pos.y += COMBO_SIZE_X;
	trans.SetPos(pos);
	m_sprite.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_sprite.Draw(&trans, &sm_comboUITex, false);

	// �R���{�̕\��
	trans = m_transform;
	pos = m_transform.GetPos();
	trans.SetSize({ COMBO_SIZE_X / 2 * 5, COMBO_OFFSET_X / 2 });
	pos.x -= COMBO_OFFSET_X / 5.0f;
	pos.y += COMBO_OFFSET_X / 4.0f;
	trans.SetPos(pos);
	m_sprite.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_sprite.Draw(&trans, &sm_comboTex, false);


	// �R���{�J�E���g�̕\��
	trans = m_transform;
	pos = m_transform.GetPos();
	int temp = m_nComboCount;
	int nCnt = 0;
	// �����𐔂���
	while (temp > 0)
	{
		temp /= 10;
		nCnt++;
	}

	pos.x -= COMBO_OFFSET_X;
	for (int i = MAX_COMBO - 1; 0 <= i; i--)
	{
		pos.x -= COMBO_OFFSET_X;
		trans.SetPos(pos);

		if (nCnt - (MAX_COMBO - i) >= 0)
		{
			m_data[i].m_spr.Draw(&trans, &sm_texture, false);
		}
	}
}


//========================================
//
//	����
//
//========================================
CCombo* CCombo::Create(Float3 pos)
{
	CCombo* pCombo = CObjectManager::CreateObject<CCombo>(pos);

	return pCombo;
}


//========================================
//
//	�j��
//
//========================================
void CCombo::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	�R���{�̉��Z
//
//========================================
void CCombo::AddCombo(int num)
{
	m_nComboCount += num;
	m_nComboTime = COMBO_TIME;

	if (99999 < m_nComboCount)
	{
		m_nComboCount = 99999;
	}

	UpdateComboTexCoord();

	// �X�g�b�v������
	m_bStop = false;
}


//========================================
//
//	�R���{�̌��Z
//
//========================================
void CCombo::ResetCombo()
{
	m_nComboCount -= 3;
	m_nComboTime = COMBO_TIME;

	if (m_nComboCount < 0)
	{
		m_nComboCount = 0;
	}

	UpdateComboTexCoord();
}