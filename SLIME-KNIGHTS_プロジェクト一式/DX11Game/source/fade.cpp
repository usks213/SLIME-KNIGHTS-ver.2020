//==================================================================
//									fade.cpp
//	GM21 �t�F�[�h�C���E�t�F�[�h�A�E�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/17	�t�F�[�h�̕`��
//	2020/06	19	����
//
//===================================================================


//====== �C���N���[�h�� ======
#include "fade.h"
#include "sceneManager.h"

#include "../sprite.h"
#include "../texture.h"


//===== �}�N����` =====


//===== �� =====
namespace
{
	enum E_STATE_FADE	// �t�F�[�h�̏�Ԃ̗�
	{
		E_STATE_FADE_NODE = 0,
		E_STATE_FADE_OUT,
		E_STATE_FADE_IN,

		E_STATE_FADE_MAX,
	};
}


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====
bool FADE::m_bNowFade = false;



//========================================
//
//	�R���X�g���N�^
//
//========================================
FADE::FADE(void(*pSetChange)())
{
	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });

	// �A���t�@
	m_nAlpha = 0;

	// �X�e�[�g
	m_nState = E_STATE_FADE_NODE;

	// �t���[��
	m_nFrame = 20;

	// �t�F�[�h�p�̃|���S���J���[�̐ݒ�
	m_sprite.SetColor(Float4{1.0f, 1.0f, 1.0f, m_nAlpha / 255.0f});

	// ���C���[
	m_enLayer = LAYER::FADE;

	m_texture.LoadTexture(FILE_PATH"fade.tga");

	// �֐��|�C���^�̊i�[
	m_pSetChange = pSetChange;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
FADE::~FADE()
{
	m_texture.UnloadTexture();
}


//======================================================
//
//	�t�F�[�h�A�E�g�̊J�n
//	�t�F�[�h�A�E�g�J�n���ԂɊO����̌Ăяo���֐�
//
//======================================================
void FADE::StartFadeOut()
{
	// ���Ƀt�F�[�h���̎��͏������Ȃ�
	if (E_STATE_FADE_NODE != m_nState)
	{
		return;
	}

	m_nAlpha = 0;
	m_nState = E_STATE_FADE_OUT;
	m_bNowFade = true;
}


//========================================
//
//	�X�V
//
//========================================
void FADE::Update()
{
	// ��Ԃɂ�蕪��
	switch (m_nState)
	{
	case(E_STATE_FADE_IN):		// �t�F�[�h�C��
		// ���l�̌���
		m_nAlpha -= (int)(255.0f / m_nFrame);

		// ���l��0��菬�����Ȃ�����I��
		if (m_nAlpha < 0)
		{
			m_nAlpha = 0;
			m_nState = E_STATE_FADE_NODE;

			// �t�F�[�h�C���I����̏���
			m_bNowFade = false;

		}
		else if (m_nAlpha < 255 / 2)
		{
			// �t�F�[�h�C���I���܂ŉ�ʂ��~�߂�
			CSceneManager::SetStopFlag(false);
		}

		// ���l�̍X�V
		m_sprite.SetColorW(m_nAlpha / 255.0f);
		break;

	case(E_STATE_FADE_OUT):		// �t�F�[�h�A�E�g
		// ���l�̑���
		m_nAlpha += (int)(255.0f / m_nFrame);

		// ���l��255�𒴂�����t�F�[�h�C����
		if (m_nAlpha > 255)
		{
			m_nAlpha = 255;
			m_nState = E_STATE_FADE_IN;

			// �t�F�[�h�A�E�g���I������Ƃ��Ɏ������鏈��
			// �V�[���̈ړ�
			if (m_pSetChange)
				m_pSetChange();
			//CSceneManager::SetSceneChange();	
		}

		// ���l�̍X�V
		m_sprite.SetColorW(m_nAlpha / 255.0f);
		break;

	default:
		break;
	}

	m_sprite.SetColorW(m_nAlpha / 255.0f);

}


//========================================
//
//	�`��
//
//========================================
void FADE::Draw()
{
	// �l�p�`�̕`��
	m_sprite.Draw(&m_transform, &m_texture, false);
}


