//==================================================================
//								sceneStartMap.h
//	スタートマップ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/05	スタートマップクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "stageStartMap.h"
#include "field.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "sceneManager.h"
#include "resultUI.h"

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
CStageStartMap::CStageStartMap()
{
	
}


//========================================
//
//	デストラクタ
//
//========================================
CStageStartMap::~CStageStartMap()
{

}


//========================================
//
//	初期化
//
//========================================
void CStageStartMap::Init()
{
	// テクスチャ
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");


	// マップのロード
	// ロードするマップのパスを作成
	//BG
	CField::CreateBg(FILE_PATH"map/startMap/map_bg.csv", &g_TexBG, 1, 1);
	// TILE
	CField::Create(FILE_PATH"map/startMap/map_tile.csv", &g_TexTile, 11, 5);
	// OBJECT
	CField::SetObject(FILE_PATH"map/startMap/map_object.csv");
	// PLAYER
	CField::SetPlayer(FILE_PATH"map/startMap/map_player.csv", 0);
	// AREA
	CField::SetChangeArea(FILE_PATH"map/startMap/map_area.csv");

	// ステージレベルの初期化
	//CStageManager::SetStageLevel(0);

	// リザルトUI
	CResultUI::Reset(CStageManager::GetMainPlayer()->GetStatus()->GetLevel());

	// ランダムマップの生成
	CStageMaker::CreateRendomMap();
	CStageMaker::SubCurMapPosY();
	CStageMaker::SetStartFlag(true);


	// BGM再生
	CStageManager::SetBGM(BGM::START_MAP);

}

//========================================
//
//	終了処理
//
//========================================
void CStageStartMap::Uninit()
{
	// テクスチャ
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();
}

//========================================
//
//	全てのオブジェクトの更新
//
//========================================
void CStageStartMap::Update()
{

#ifdef _WIN32
	
#endif // _WIN32
}


//========================================
//
//	全てのオブジェクトの描画
//
//========================================
void CStageStartMap::Draw()
{

}

