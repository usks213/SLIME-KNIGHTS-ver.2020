//==================================================================
//								playerUI.h
//	プレイヤーのUI
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/05	プレイヤーUIクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "player.h"
#include "playerUI.h"
#include "objectMgr.h"
#include "status.h"



//===== マクロ定義 =====
#define BG_OFFSET_X (0)
#define BG_OFFSET_Y (0)
#define BG_SIZE_X (44)
#define BG_SIZE_Y (16)

#define UI_OFFSET_X (0)
#define UI_OFFSET_Y (0)
#define UI_SIZE_X (48)
#define UI_SIZE_Y (18)

#define HP_OFFSET_X (8)
#define HP_OFFSET_Y (-3.5f)
#define HP_SIZE_X (28)
#define HP_SIZE_Y (5)

#define EX_OFFSET_X (8)
#define EX_OFFSET_Y (3.5f)
#define EX_SIZE_X (28)
#define EX_SIZE_Y (5)

#define LE_OFFSET_X (-16)
#define LE_OFFSET_Y (0)
#define LE_SIZE_X (10)
#define LE_SIZE_Y (10)



CTexture CPlayerUI::sm_UiTexture;



//========================================
//
//	コンストラクタ
//
//========================================
CPlayerUI::CPlayerUI()
{
	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 6, 6 });

	// スプライトデータ
	m_sprite;

	// レイヤー
	m_enLayer = LAYER::UI;

	// 文字列
	m_pExperience = nullptr;
	m_pHP = nullptr;
	m_pLevel = nullptr;

	// カラー
	m_colorBG = Float4{ 0.6f, 0.5f, 0.6f, 1.0f };
	m_colorUI = Float4{ 1, 1, 1, 1.0f };
	m_colorHP = Float4{ 1, 0, 0, 1.0f };
	m_colorEX = Float4{ 0, 1, 0, 1.0f };
	
	// 大きさ
	m_sizeEX.x = 1;
	m_sizeEX.y = 1;
	m_sizeHP.x = 1;
	m_sizeHP.y = 1;
}


//========================================
//
//	デストラクタ
//
//========================================
CPlayerUI::~CPlayerUI()
{
	m_pExperience->Destroy();
	m_pHP->Destroy();
	m_pLevel->Destroy();
}


//========================================
//
//	初期化
//
//========================================
void CPlayerUI::Init()
{
	// UIテクスチャのロード
	sm_UiTexture.LoadTexture(FILE_PATH"player/statusUI.tga");
}

//========================================
//
//	終了処理
//
//========================================
void CPlayerUI::Uninit()
{
	// テクスチャの解放
	sm_UiTexture.UnloadTexture();
}

//========================================
//
//	更新処理
//
//========================================
void CPlayerUI::Update()
{
}

//========================================
//
//	後更新処理
//
//========================================
void CPlayerUI::LateUpdate()
{
	CStatus status = CPlayer::GetBackUpStatus();
	char szText[256];

	// EX
	std::sprintf(szText, "%d/%d", status.GetExperience(), status.GetRequiredExperience());
	m_pExperience->SetWord(szText);
	m_sizeEX.x = 1.0f - (float)status.GetExperience() / status.GetRequiredExperience();

	// HP
	std::sprintf(szText, "%d/%d", status.GetHp(), status.GetMaxHp());
	m_pHP->SetWord(szText);
	m_sizeHP.x = 1.0f - (float)status.GetHp() / status.GetMaxHp();

	// LEVEL
	std::sprintf(szText, "%d", status.GetLevel());
	m_pLevel->SetWord(szText);


}

//========================================
//
//	描画処理
//
//========================================
void CPlayerUI::Draw()
{
	CTransform trans;
	Float3 pos = m_transform.GetPos();
	Float2 size = m_transform.GetSize();

	// BG
	trans.SetPos(Float3{pos.x + BG_OFFSET_X * size.x, pos.y + BG_OFFSET_Y * size.y, 0});
	trans.SetSize(Float2{ BG_SIZE_X * size.x, BG_SIZE_Y * size.y });
	m_sprite.SetColor(m_colorBG);
	m_sprite.Draw(&trans, nullptr, false);


	// HP
	trans.SetPos(Float3{ pos.x + (HP_OFFSET_X - m_sizeHP.x * HP_SIZE_X / 2) * size.x, pos.y + HP_OFFSET_Y * size.y, 0 });
	trans.SetSize(Float2{ HP_SIZE_X * size.x * (1.0f - m_sizeHP.x), HP_SIZE_Y * size.y });
	m_sprite.SetColor(m_colorHP);
	m_sprite.Draw(&trans, nullptr, false);


	// EX
	trans.SetPos(Float3{ pos.x + (EX_OFFSET_X - m_sizeEX.x * EX_SIZE_X / 2) * size.x, pos.y + EX_OFFSET_Y * size.y, 0 });
	trans.SetSize(Float2{ EX_SIZE_X * size.x * (1.0f - m_sizeEX.x), EX_SIZE_Y * size.y });
	m_sprite.SetColor(m_colorEX);
	m_sprite.Draw(&trans, nullptr, false);


	// UI
	trans.SetPos(Float3{ pos.x + UI_OFFSET_X * size.x, pos.y + UI_OFFSET_Y * size.y, 0 });
	trans.SetSize(Float2{ UI_SIZE_X * size.x, UI_SIZE_Y * size.y });
	m_sprite.SetColor(m_colorUI);
	m_sprite.Draw(&trans, &sm_UiTexture, false);

	// STRING
	m_pExperience->Draw();
	m_pHP->Draw();
	m_pLevel->Draw();

}

//========================================
//
//	生成
//
//========================================
CPlayerUI* CPlayerUI::Create(Float3 pos)
{
	CPlayerUI *pPlayerUI = CObjectManager::CreateObject<CPlayerUI>(pos);
	Float2 size = pPlayerUI->m_transform.GetSize();

	// EX
	pPlayerUI->m_pExperience = STRING::CString::Create("12/32",
		Float3{ pos.x + EX_OFFSET_X * size.x, pos.y + EX_OFFSET_Y * size.y, 0 }, 
		Float2{ 26, 26 }, Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);

	// HP
	pPlayerUI->m_pHP = STRING::CString::Create("14/35", 
		Float3{ pos.x + HP_OFFSET_X * size.x, pos.y + HP_OFFSET_Y * size.y, 0 },
		Float2{ 26, 26 }, Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);

	// LE
	pPlayerUI->m_pLevel = STRING::CString::Create("10", 
		Float3{ pos.x + LE_OFFSET_X * size.x, pos.y + LE_OFFSET_Y * size.y, 0 },
		Float2{ 50, 50 }, Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);

	return pPlayerUI;
}

//========================================
//
//	破棄
//
//========================================
void CPlayerUI::Destroy()
{
	CObjectManager::DestroyObject(this);
}

