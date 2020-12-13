//==================================================================
//								sceneBoss.cpp
//	ボスステージ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/04	ボスステージクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "stageBoss.h"
#include "field.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "sceneManager.h"
#include "BossMakeArea.h"
#include "light.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32

//===== マクロ定義 =====


//===== グローバル変数 =====
static CTexture g_TexBG;
static CTexture g_TexTile;


//========================================
//
//	コンストラクタ
//
//========================================
CStageBoss::CStageBoss()
{
	
}


//========================================
//
//	デストラクタ
//
//========================================
CStageBoss::~CStageBoss()
{

}


//========================================
//
//	初期化
//
//========================================
void CStageBoss::Init()
{
	// テクスチャ
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");

	// ライト
	CLight::SetBoss(true);

	// マップのロード
	// ロードするマップのパスを作成
	//BG
	CField::CreateBg(FILE_PATH"map/renga/boss/map_bg.csv", &g_TexBG, 1, 1);
	// TILE
	CField::Create(FILE_PATH"map/renga/boss/map_tile.csv", &g_TexTile, 11, 5);
	// OBJECT
	CField::SetObject(FILE_PATH"map/renga/boss/map_object.csv");

	// プレイヤーのセット
	CStageManager::SetPlayerPos(Float3{ 96 * 3, 96 * 15, 0 });

	// ボス生成エリアのセット
	CBossMakeArea::Create(Float3{ 96 * 37, 96 * 12, 0 });

	// BGMストップ
	CStageManager::StopBGM();

	// コンボをストップ
	CStageManager::GetMainPlayer()->GetCombo()->SetStop(true);
}

//========================================
//
//	終了処理
//
//========================================
void CStageBoss::Uninit()
{
	// テクスチャ
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();

	// ライト
	CLight::SetBoss(false);
}

//========================================
//
//	全てのオブジェクトの更新
//
//========================================
void CStageBoss::Update()
{

#ifdef _WIN32
	
#endif // _WIN32
}


//========================================
//
//	全てのオブジェクトの描画
//
//========================================
void CStageBoss::Draw()
{

}

