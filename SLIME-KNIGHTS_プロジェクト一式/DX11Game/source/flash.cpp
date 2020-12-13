//==================================================================
//									flash.h
//	�t���b�V��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/05	�t���b�V���N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "flash.h"
#include "sceneManager.h"
#include "enemySlimBoss.h"

#include "../sprite.h"
#include "../texture.h"


//===== �}�N����` =====
#define FLASH_FRAME (120)
#define FLASH_TEMPO (16)

//===== �� =====


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====
bool CFlash::m_bNowFlash = false;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CFlash::CFlash()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });

	// �A���t�@
	m_nAlpha = 0;

	// �t���[��
	m_nFrame = FLASH_FRAME;

	// �t���b�V���p�̃|���S���J���[�̐ݒ�
	m_sprite.SetColor(Float4{1.0f, 1.0f, 1.0f, m_nAlpha / 255.0f});

	// ���C���[
	m_enLayer = LAYER::FADE;

	m_texture.LoadTexture(FILE_PATH"fade.tga");

	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CFlash::~CFlash()
{
	m_texture.UnloadTexture();
}


//======================================================
//
//	�t���b�V���̊J�n
//	�t���b�V���J�n���ԂɊO����̌Ăяo���֐�
//
//======================================================
void CFlash::StartFlash(void(*pSetEvent)(CEnemySlimBoss*), CEnemySlimBoss* pBoss)
{
	// ���Ƀt���b�V�����̎��͏������Ȃ�
	if (m_bNowFlash)
	{
		return;
	}

	m_nAlpha = 1;
	m_bNowFlash = true;
	m_nFrame = FLASH_FRAME;
	// �֐��|�C���^�̊i�[
	m_pSetEvent = pSetEvent;
	m_pBoss = pBoss;


	// ��ʂ��~�߂�
	CSceneManager::SetStopFlag(true);
}


//========================================
//
//	�X�V
//
//========================================
void CFlash::Update()
{
	// �t���b�V����������
	if (m_bNowFlash)
	{
		m_nFrame--;
		if (m_nFrame % FLASH_TEMPO < FLASH_TEMPO / 4)
		{
			m_nAlpha = 1;
		}
		else
		{
			m_nAlpha = 0;
		}

		if (m_nFrame < 0)
		{
			m_nAlpha = 0;
			m_bNowFlash = false;
			CSceneManager::SetStopFlag(false);
			// �t���b�V����̏���
			m_pSetEvent(m_pBoss);
		}

		m_sprite.SetColorW(m_nAlpha);
	}
}


//========================================
//
//	�`��
//
//========================================
void CFlash::Draw()
{
	// �l�p�`�̕`��
	m_sprite.Draw(&m_transform, &m_texture, false);
}


