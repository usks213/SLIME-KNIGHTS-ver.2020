//==================================================================
//								sceneGame.h
//	GM21 ゲームシーン
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/18	ゲームシーンクラス作成
//
//===================================================================


//====== インクルード部 ======
#include "sceneTitle.h"
#include "sceneManager.h"
#include "sceneGame.h"

#include "stageManager.h"
#include "stageDebug.h"
#include "stageMaker.h"
#include "stageStartMap.h"
#include "stageTutorial.h"

#include "fade.h"
#include "camera.h"
#include "object.h"
#include "bg.h"
#include "block.h"
#include "floor.h"
#include "Fire.h"
#include "light.h"
#include "needle.h"

#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "field.h"
#include "bullet.h"
#include "attackBase.h"
#include "enemySlim.h"
#include "enemyWing.h"
#include "enemyLance.h"
#include "playerUI.h"
#include "key.h"
#include "characterAction.h"
#include "weapon.h"

#include "objectMgr.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "status.h"
#include "string.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32


//===== マクロ定義 =====


//===== グローバル変数 =====
static CSound g_BGM;
static CTexture g_TexBG;
static CTexture g_TexTile;
static CTexture g_CMark;
static CTexture g_Title;

static CEnemy* g_pEnemy;
//static STRING::CString* g_pString;
static STRING::CString* g_pStringPush;
static STRING::CString* g_pStringName;

//========================================
//
//	コンストラクタ
//
//========================================
CSceneTitle::CSceneTitle()
{
	
}


//========================================
//
//	デストラクタ
//
//========================================
CSceneTitle::~CSceneTitle()
{

}


//========================================
//
//	初期化
//
//========================================
void CSceneTitle::Init()
{
	// サウンド
	g_BGM.Load(FILE_PATH"sound/bgm/TitleBGM.mp3", true);
	g_BGM.Play(0.9f);

	// テクスチャ
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");
	g_CMark.LoadTexture(FILE_PATH"ui/c_mark.tga");
	g_Title.LoadTexture(FILE_PATH"ui/slime_knights.tga");

	// 背景の初期化
	CBG::Init();
	// ブロックの初期化
	CBlock::Init();
	// フロアの初期化
	CFloor::Init();
	// 灯りの初期化
	CFire::Init();
	CLight::Init();
	// 針の初期化
	CNeedl::Init();
	// キーの初期化
	CKey::Init();

	// エネミーの初期化
	CEnemy::Init();
	// エフェクトの初期化
	CEffect::Init();
	// 弾
	CBullet::Init();
	// ウェポン
	CWeapon::Init();

	// キャラクターアクションの初期化
	CCharacterAction::Init();

	// マップのロード
	// ロードするマップのパスを作成
	//BG
	CField::CreateBg(FILE_PATH"map/titleMap/map_bg.csv", &g_TexBG, 1, 1);
	// TILE
	CField::Create(FILE_PATH"map/titleMap/map_tile.csv", &g_TexTile, 11, 5);
	// OBJECT
	CField::SetObject(FILE_PATH"map/titleMap/map_object.csv");
	// ENEMY
	CField::SetEnemy(FILE_PATH"map/titleMap/map_enemy.csv");
	// PLAYER
	CField::SetPlayer(FILE_PATH"map/titleMap/map_player.csv", 0);
	// AREA
	CField::SetChangeArea(FILE_PATH"map/titleMap/map_area.csv");


	// 敵の生成
	g_pEnemy = CObjectManager::CreateObject<CEnemySlim>(Float3{ 96 * 15, 96 * 11, 0 });
	g_pEnemy->GetUI()->SetDraw(false);
	// カメラ
	CCamera::SetCameraTarget(g_pEnemy->GetTransform());

	// テキスト
	/*g_pString = new	STRING::CString("SLIME KNIGHTS", Float3{ 0, -100, 0 }, Float2{ 150, 150 },
		Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);*/
	g_pStringPush = new	STRING::CString("Push Enter", Float3{ 0, 0, 0 }, Float2{ 50, 50 },
		Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);
	g_pStringName = new	STRING::CString("Koshi Usami 2020", Float3{ -530, 310, 0 }, Float2{ 24, 24 },
		Float4{ 1,1,1,1 }, STRING::LEFT, STRING::CENTER_Y);
}

//========================================
//
//	終了処理
//
//========================================
void CSceneTitle::Uninit()
{
	// テキスト
	//g_pString->Destroy();
	g_pStringPush->Destroy();
	g_pStringName->Destroy();

	// キャラクターアクションの終了処理
	CCharacterAction::Uninit();

	// ウェポン
	CWeapon::Uninit();
	// 弾
	CBullet::Uninit();
	// エフェクトの終了処理
	CEffect::Uninit();
	// エネミーの終了処理
	CEnemy::Uninit();

	// キーの終了処理
	CKey::Uninit();
	// 針の終了処理
	CNeedl::Uninit();
	// 灯りの終了処理
	CFire::Uninit();
	CLight::Uninit();
	// フロアの終了処理
	CFloor::Uninit();
	// ブロックの終了処理
	CBlock::Uninit();
	// 背景の終了処理
	CBG::Uninit();

	// サウンド
	g_BGM.Stop();

	// テクスチャ
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();
	g_CMark.UnloadTexture();
	g_Title.UnloadTexture();
}

//========================================
//
//	全てのオブジェクトの更新
//
//========================================
void CSceneTitle::Update()
{
	// カメラ
	static CTransform enemyTrans = *g_pEnemy->GetTransform();
	enemyTrans = *g_pEnemy->GetTransform();
	Float3 pos = enemyTrans.GetPos();
	pos.y -= 96 * 3;
	enemyTrans.SetPos(pos);

	CCamera::SetCameraTarget(&enemyTrans);

#ifdef _WIN32
	if(GetKeyRelease(VK_RETURN))
	{
		CSceneManager::SetNextScene(new CSceneGame());
	}
	
#endif // _WIN32

}

//========================================
//
//	全てのオブジェクトの描画
//
//========================================
void CSceneTitle::Draw()
{
	// BG
	CSprite bg;
	CTransform trans;
	bg.SetColor(Float4{ 0.0f, 0.0f, 0.0f, 0.25f });
	trans.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });
	bg.Draw(&trans, nullptr, false);

	// テキスト
	static int nPushDraw = 0;
	if (nPushDraw++ % 100 > 30)
	{
		g_pStringPush->Draw();
	}

	// タイトル
	//g_pString->Draw();
	trans.SetSize(Float2{ 250 * 3, 27 * 8 });
	trans.SetPos(Float3{ 0, -180, 0 });
	bg.SetColor(Float4{ 1,1,1,1 });
	bg.Draw(&trans, &g_Title, false);


	// 名前
	g_pStringName->Draw();

	// Cマーク
	trans.SetSize(Float2{ 24, 24 });
	trans.SetPos(Float3{ -560, 309, 0 });
	bg.SetColor(Float4{ 1,1,1,1 });
	bg.Draw(&trans, &g_CMark, false);
}

