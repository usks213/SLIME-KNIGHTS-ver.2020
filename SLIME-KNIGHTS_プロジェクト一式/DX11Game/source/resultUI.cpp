//==================================================================
//									resultUI.h
//	���U���g���
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/07	���U���gUI�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "resultUI.h"
#include "../sprite.h"
#include "../texture.h"
#include "camera.h"
#include "objectMgr.h"

#include "../input.h"
#include "stageManager.h"
#include "stageStartMap.h"

#include "../Sound.h"

//===== �}�N����` =====


enum ERESULT_UI_TYPE
{
	RESULT_BG,
	RESULT_GAMEOVER,
	RESULT_BAR,

	MAX_RESULT_UI,
};


//===== �v���g�^�C�v�錾 =====


//===== �O���[�o���ϐ� =====
static CSound g_SE;
static CSound g_BGM;


//===== �ÓI�����o =====
CTexture CResultUI::sm_textureGameOver;
CTexture CResultUI::sm_textureBar;

int CResultUI::m_nExperience = 0;
int CResultUI::m_nEnemy = 0;
int CResultUI::m_nPrevLevel = 0;
int CResultUI::m_nCurLevel = 0;
int CResultUI::m_nDrawLevel = 0;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CResultUI::CResultUI()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform;
	m_transform.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::RESULT_UI;

	// ���U���gUI
	
	// BG
	m_colorBG = Float4{ 0.1f, 0.1f, 0.1f, 0.6f };
	m_fBgAlpha = 0;
	

	// GameOver
	m_fGameOverAlpha = 0;


	// BAR
	m_nBarCnt = 0;
	for (int i = 0; i < MAX_RESULT_BAR; i++) m_fBarPosY[i] = SCREEN_CENTER_Y * 2;


	// ���
	m_nState = RESULT_BG;

	m_nDrawLevel = m_nCurLevel - m_nPrevLevel;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CResultUI::~CResultUI()
{
	m_pString->Destroy();
}


//========================================
//
//	������
//
//========================================
void CResultUI::Init()
{
	// �e�N�X�`���̃��[�h
	sm_textureGameOver.LoadTexture(FILE_PATH"ui/gameover.tga");
	sm_textureBar.LoadTexture(FILE_PATH"ui/resultBar.tga");

	g_SE.Load(FILE_PATH"sound/result/se.wav");
	g_BGM.Load(FILE_PATH"sound/result/bgm2.wav");
}


//========================================
//
//	�I������
//
//========================================
void CResultUI::Uninit()
{
	// �e�N�X�`���̉��
	sm_textureGameOver.UnloadTexture();
	sm_textureBar.UnloadTexture();
}


//========================================
//
//	�X�V
//
//========================================
void CResultUI::Update()
{
	switch (m_nState)
	{
	case RESULT_BG:
		m_fBgAlpha += 0.01f;
		if (m_fBgAlpha > 0.6f)
		{
			m_nState++;
			// �T�E���h
			g_BGM.Play();
			m_nDrawLevel = m_nCurLevel - m_nPrevLevel;
		}
		break;
	case RESULT_GAMEOVER:
		m_fGameOverAlpha += 0.01f;
		if (m_fGameOverAlpha > 1.0f)
			m_nState++;

		break;
	case RESULT_BAR:
		m_fBarPosY[m_nBarCnt] -= 10;
		if (m_fBarPosY[m_nBarCnt] < m_nBarCnt * 18 * 5 - SCREEN_CENTER_Y / 5)
		{
			// �J�E���g���ς��^�C�~���O�ŃT�E���h
			g_SE.Play();

			m_nBarCnt++;

			if (m_nBarCnt >= MAX_RESULT_BAR)
				m_nState++;
		}

		break;
	case MAX_RESULT_UI:

		// �����œ��͏���
		if (GetKeyTrigger(VK_SPACE) || GetKeyTrigger(VK_RETURN))
		{
			CStageManager::SetTimerNextStage(new CStageStartMap(), 10, CStageManager::SetRestart);
			m_nState++;
			//this->Destroy();
		}

		break;
	default:
		break;
	}

}


//========================================
//
//	�`��
//
//========================================
void CResultUI::Draw()
{
	CTransform trans;

	// BG
	trans.SetPos(Float3{ 0,0,0 });
	trans.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });
	m_colorBG.w = m_fBgAlpha;
	m_sprite.SetColor(m_colorBG);
	m_sprite.Draw(&trans, nullptr, false);


	// GAME OVER
	trans.SetPos(Float3{ 0,-SCREEN_CENTER_Y / 3 * 2,0 });
	trans.SetSize(Float2{ 188 * 6, 27 * 6 });
	m_sprite.SetColor(Float4{1,1,1,m_fGameOverAlpha});
	m_sprite.Draw(&trans, &sm_textureGameOver, false);


	// BAR * 6
	for (int i = 0; i < MAX_RESULT_BAR; i++)
	{
		trans.SetPos(Float3{ 0,m_fBarPosY[i],0 });
		trans.SetSize(Float2{ 128 * 5, 18 * 5 });
		m_sprite.SetColor(Float4{ 1,1,1,1 });
		m_sprite.Draw(&trans, &sm_textureBar, false);

		// �e�L�X�g
		m_pString->SetPos(Float3{ -42 * 5, m_fBarPosY[i], 0 });
		switch (i)
		{
		case 0:
			m_pString->SetWord("TIME");
			break;
		case 1:
			m_pString->SetWord("STAGE");
			break;
		case 2:
			m_pString->SetWord("ENEMY");
			break;
		case 3:
			m_pString->SetWord("EXPERIENCE");
			break;
		case 4:
			m_pString->SetWord("LEVEL UP");
			break;
		}
		m_pString->SetOffSet(STRING::CENTER_X, STRING::CENTER_Y);
		m_pString->Draw();
	}

	// TEXT
	for (int i = 0; i < MAX_RESULT_BAR; i++)
	{
		m_pString->SetOffSet(STRING::RIGHT, STRING::CENTER_Y);
		m_pString->SetPos(Float3{ 58 * 5, m_fBarPosY[i], 0 });
		char szText[256];
		int time = 0;

		switch (i)
		{
		case 0:
			time = m_nTime;
			std::sprintf(szText, "%02dh %02dm %02ds", time / 60 / 60 / 60, time / 60 / 60 % 60, time / 60 % 60);
			break;
		case 1:
			std::sprintf(szText, "LEVEL : %d", CStageManager::GetStageLevel() + 1);
			break;
		case 2:
			// ENEMY
			std::sprintf(szText, "%d", m_nEnemy);
			break;
		case 3:
			// EXPERIENCE
			std::sprintf(szText, "+%d", m_nExperience);

			break;
		case 4:
			// LEVEL
			std::sprintf(szText, "+%d", m_nDrawLevel);

			break;
		}

		m_pString->SetWord(szText);
		if(i < m_nBarCnt)
			m_pString->Draw();
	}


	// �{�^���e�L�X�g
	if (m_nState == MAX_RESULT_UI)
	{
		static int nPushCnt = 0;
		if (nPushCnt++ % 100 > 30)
		{
			m_pString->SetOffSet(STRING::CENTER_X, STRING::CENTER_Y);
			m_pString->SetPos(Float3{ SCREEN_CENTER_X / 4 * 3, SCREEN_CENTER_Y / 5 * 4, 0 });
			m_pString->SetWord("Push Enter");
			m_pString->Draw();
		}
	}

}


//========================================
//
//	����
//
//========================================
CResultUI* CResultUI::Create(Float3 pos)
{
	CResultUI* pBg = new CResultUI();

	pBg->GetTransform()->SetPos(pos);
	pBg->m_pString = STRING::CString::Create("", Float3{-999,-999,0}, Float2{ 8 * 5, 8 * 5 }, Float4{ 1,1,1,1 },
		STRING::CENTER_X, STRING::CENTER_Y);
	pBg->m_nTime = CStageManager::GetGameTime();

	return pBg;
}


//========================================
//
//	�j��
//
//========================================
void CResultUI::Destroy()
{
	//CObjectManager::DestroyObject(this);
	delete this;
}

