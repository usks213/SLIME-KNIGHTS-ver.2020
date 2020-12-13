//==================================================================
//								enemyUI.cpp
//	エネミーのUI
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/07	エネミーUIクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "enemyUI.h"
#include "enemy.h"
#include "objectMgr.h"
#include "status.h"



//===== マクロ定義 =====
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
//	コンストラクタ
//
//========================================
CEnemyUI::CEnemyUI()
{
	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 4, 4 });

	// スプライトデータ
	m_sprite;

	// レイヤー
	m_enLayer = LAYER::UI;

	// カラー
	m_colorBG = Float4{ 0.6f, 0.5f, 0.6f, 1.0f };
	m_colorUI = Float4{ 1, 1, 1, 1.0f };
	m_colorHP = Float4{ 1, 0, 0, 1.0f };
	
	// 大きさ
	m_sizeHP.x = 1;
	m_sizeHP.y = 1;

	m_bDraw = true;
}


//========================================
//
//	デストラクタ
//
//========================================
CEnemyUI::~CEnemyUI()
{
}


//========================================
//
//	初期化
//
//========================================
void CEnemyUI::Init()
{
	// UIテクスチャのロード
	sm_UiTexture.LoadTexture(FILE_PATH"player/statusUI.tga");
}

//========================================
//
//	終了処理
//
//========================================
void CEnemyUI::Uninit()
{
	// テクスチャの解放
	sm_UiTexture.UnloadTexture();
}

//========================================
//
//	更新処理
//
//========================================
void CEnemyUI::Update()
{
}

//========================================
//
//	後更新処理
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
//	描画処理
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
//	生成
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
//	破棄
//
//========================================
void CEnemyUI::Destroy()
{
	CObjectManager::DestroyObject(this);
}

