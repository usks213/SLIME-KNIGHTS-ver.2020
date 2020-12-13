//==================================================================
//								sceneDebug.h
//	�f�o�b�O�X�e�[�W
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/23	�f�o�b�O�X�e�[�W�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageDebug.h"
#include "field.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "floor.h"
#include "sceneManager.h"
#include "BossMakeArea.h"
#include "stageLevelText.h"
#include "fade.h"
#include "key.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32

//===== �}�N����` =====


//===== �O���[�o���ϐ� =====
static STRING::CString* g_pString = nullptr;
static STRING::CString* g_pStringRestart = nullptr;
static CKey* g_pTab = nullptr;
static CKey* g_pC = nullptr;
static CKey* g_pJ = nullptr;
static CKey* g_pR = nullptr;

static CSound g_SE_Open;
static CSound g_SE_Close;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageDebug::CStageDebug()
{
	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageDebug::~CStageDebug()
{

}


//========================================
//
//	������
//
//========================================
void CStageDebug::Init()
{
	// ���񎞂͊K�w��\��
	if (CStageMaker::GetStartFlag())
	{
		CStageLevelText::Create(Float3{ 0,-130,0 }, CStageManager::GetStageLevel() + 1);
	}

	// �}�b�v�̃��[�h
	CStageMaker::CreateStage();

	// BGM
	CStageManager::SetBGM(BGM::RENGA_RANDOM);

	//CBossMakeArea::Create(Float3{ 96 * 15, 96 * 8, 0 });

	// �}�b�v
	g_pTab = CKey::Create(KEY::TAB, Float3{ -SCREEN_CENTER_X + 80, SCREEN_CENTER_Y / 10  * 9.25f - 16, 0 }, false);
	g_pTab->SetLayer(LAYER::UI);

	g_pC = CKey::Create(KEY::C, Float3{ -SCREEN_CENTER_X + 160, SCREEN_CENTER_Y / 10 * 9.25f - 16, 0 }, false);
	g_pC->GetTransform()->SetSize(Float2{ 48, 48 });
	g_pC->SetLayer(LAYER::UI);

	g_pJ = CKey::Create(KEY::J, Float3{ -SCREEN_CENTER_X + 216, SCREEN_CENTER_Y / 10 * 9.25f - 16, 0 }, false);
	g_pJ->GetTransform()->SetSize(Float2{ 48, 48 });
	g_pJ->SetLayer(LAYER::UI);

	g_pR = CKey::Create(KEY::R, Float3{ -SCREEN_CENTER_X + 216 + 200, SCREEN_CENTER_Y / 10 * 9.25f - 16, 0 }, false);
	g_pR->GetTransform()->SetSize(Float2{ 48, 48 });
	g_pR->SetLayer(LAYER::UI);


	// �e�L�X�g
	g_pString = new	STRING::CString("�}�b�v", Float3{ -SCREEN_CENTER_X + 216 + 86, SCREEN_CENTER_Y / 10 * 9.25f - 16, 0 }, Float2{ 32, 32 },
		Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);
	// �e�L�X�g
	g_pStringRestart = new	STRING::CString("���X�^�[�g", Float3{ -SCREEN_CENTER_X + 216 + 200 + 116, SCREEN_CENTER_Y / 10 * 9.25f - 16, 0 }, Float2{ 32, 32 },
		Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);


	// �T�E���h
	g_SE_Close.Load(FILE_PATH"sound/miniMap/CloseMenu.mp3");
	g_SE_Open.Load(FILE_PATH"sound/miniMap/OpenMenu.mp3");
}

//========================================
//
//	�I������
//
//========================================
void CStageDebug::Uninit()
{
	g_pTab->Destroy();
	g_pC->Destroy();
	g_pJ->Destroy();
	g_pR->Destroy();

	g_pString->Destroy();
	g_pStringRestart->Destroy();
}

//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CStageDebug::Update()
{

#ifdef _WIN32
	//if (GetKeyRelease(VK_0))
	//{
	//	/*CStageMaker::CreateRendomMap();
	//	CStageManager::SetNextStage(new CStageDebug());*/
	//}
	if (GetKeyRelease(VK_R))
	{
		CStageManager::SetNextStage(new CStageDebug());
	}

	static bool bObjStop = false;;
	if ((GetKeyTrigger(VK_TAB) || GetKeyTrigger(VK_C) || GetKeyTrigger(VK_J)) && !FADE::GetNowFade())
	{
		bObjStop ^= 1;
		CSceneManager::SetStopFlag(bObjStop);
		CStageMaker::SetMiniMapDraw(bObjStop);
		// �T�E���h
		if (bObjStop)
		{
			g_SE_Open.Play(0.6f);
		}
		else
		{
			g_SE_Close.Play();
		}

	}

	g_pTab->Update();
	g_pString->Update();

#endif // _WIN32
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CStageDebug::Draw()
{
	// �}�b�v�\��
	g_pTab->Draw();
	g_pC->Draw();
	g_pJ->Draw();
	g_pR->Draw();


	g_pString->Draw();
	g_pStringRestart->Draw();

	// �~�j�}�b�v
	CStageMaker::MiniMapDraw();

}

