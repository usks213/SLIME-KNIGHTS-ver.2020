//==================================================================
//									stage.cpp
//	GM21 居合切りのステージ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/14	オブジェクト指向で書き直し
//	
//	
//
//===================================================================


//====== インクルード部 ======
#include "stageTest.h"
#include "../sprite.h"
#include "../texture.h"

#ifdef _WIN32
#include "../input.h"
#else
#include "../controller.h"
#endif // _WIN32

#include "object.h"
#include "bg.h"
#include "block.h"
#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "fade.h"
#include "field.h"
#include "bullet.h"
#include "attackBase.h"
#include "enemySlim.h"
#include "enemyWing.h"
#include "enemyLance.h"

#include "camera.h"

#include "List.h"
#include "objectMgr.h"
#include "collision.h"


//===== マクロ定義 =====


//===== プロトタイプ宣言 =====


//===== グローバル変数 =====
static CTexture g_TexBG;
static CTexture g_TexTile;


//========================================
//
//	初期化
//
//========================================
void InitStage(void)
{
	// 背景の初期化
	CBG::Init();
	// ブロックの初期化
	CBlock::Init();
	// ターゲットの初期化
	CEnemy::Init();
	// エフェクトの初期化
	CEffect::Init();
	// 弾
	CBullet::Init();
	// プレイヤーの初期化
	CPlayer::Init();
	
	// フィールド生成
	//g_pField = CField::Create(FILE_PATH"untitled.csv", FILE_PATH"tile.tga", 11, 15);
	CField::CreateBg(FILE_PATH"map/renga_bg.csv", &g_TexBG, 1, 1);
	CField::Create(FILE_PATH"map/renga_tile.csv", &g_TexTile, 11, 5);
	CField::SetObject(FILE_PATH"map/renga_object.csv");

	// プレイヤーの生成
	//g_pPlayer = CObjectManager::CreateObject<CPlayer>(Float3{ 96.0f * 15, 96.0f * 10, 0 });

}


//========================================
//
//	終了
//
//========================================
void UninitStage(void)
{
	// テクスチャ
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();

	// プレイヤーの終了処理
	CPlayer::Uninit();

	// 弾
	CBullet::Uninit();

	// エフェクトの終了処理
	CEffect::Uninit();

	// ターゲットの終了処理
	CEnemy::Uninit();

	// ブロックの終了処理
	CBlock::Uninit();

	// 背景の終了処理
	CBG::Uninit();
}


//========================================
//
//	更新
//
//========================================
void UpdateStage(void)
{
	// カメラ
	//CCamera::SetCameraTarget(g_pPlayer->GetTransform());

	for (int i = 0; i < 100; i++)
	{
		//CEffect::Create(EFFECT::EXPLOSION, Float3{ rand() % 96 * (float)g_pField->GetWidth(), rand() % 96 * (float)g_pField->GetHieght(), 0 });

	}
	
#ifdef _WIN32
	
#else

#endif // _WIN32
	
}


//========================================
//
//	描画
//
//========================================
void DrawStage(void)
{

}

