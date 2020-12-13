//==================================================================
//									flash.h
//	フラッシュ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/05	フラッシュクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "flash.h"
#include "sceneManager.h"
#include "enemySlimBoss.h"

#include "../sprite.h"
#include "../texture.h"


//===== マクロ定義 =====
#define FLASH_FRAME (120)
#define FLASH_TEMPO (16)

//===== 列挙 =====


//===== プロトタイプ宣言 =====


//===== グローバル変数 =====


//===== 静的メンバ =====
bool CFlash::m_bNowFlash = false;



//========================================
//
//	コンストラクタ
//
//========================================
CFlash::CFlash()
{
	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });

	// アルファ
	m_nAlpha = 0;

	// フレーム
	m_nFrame = FLASH_FRAME;

	// フラッシュ用のポリゴンカラーの設定
	m_sprite.SetColor(Float4{1.0f, 1.0f, 1.0f, m_nAlpha / 255.0f});

	// レイヤー
	m_enLayer = LAYER::FADE;

	m_texture.LoadTexture(FILE_PATH"fade.tga");

	
}


//========================================
//
//	デストラクタ
//
//========================================
CFlash::~CFlash()
{
	m_texture.UnloadTexture();
}


//======================================================
//
//	フラッシュの開始
//	フラッシュ開始時間に外からの呼び出す関数
//
//======================================================
void CFlash::StartFlash(void(*pSetEvent)(CEnemySlimBoss*), CEnemySlimBoss* pBoss)
{
	// 既にフラッシュ中の時は処理しない
	if (m_bNowFlash)
	{
		return;
	}

	m_nAlpha = 1;
	m_bNowFlash = true;
	m_nFrame = FLASH_FRAME;
	// 関数ポインタの格納
	m_pSetEvent = pSetEvent;
	m_pBoss = pBoss;


	// 画面を止める
	CSceneManager::SetStopFlag(true);
}


//========================================
//
//	更新
//
//========================================
void CFlash::Update()
{
	// フラッシュだったら
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
			// フラッシュ後の処理
			m_pSetEvent(m_pBoss);
		}

		m_sprite.SetColorW(m_nAlpha);
	}
}


//========================================
//
//	描画
//
//========================================
void CFlash::Draw()
{
	// 四角形の描画
	m_sprite.Draw(&m_transform, &m_texture, false);
}


