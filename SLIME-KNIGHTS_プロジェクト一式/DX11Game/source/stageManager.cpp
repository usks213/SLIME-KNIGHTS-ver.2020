//==================================================================
//								stageManager.h
//	ステージ管理
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/23	ステージ管理クラス作成
//
//===================================================================


//====== インクルード部 ======
#include "stageManager.h"
#include "stageDebug.h"
#include "stageMaker.h"
#include "sceneManager.h"
#include "stageBoss.h"
#include "stageStartMap.h"
#include "stageTutorial.h"
#include "stageChangeBossArea.h"

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
#include "fade.h"
#include "field.h"
#include "bullet.h"
#include "attackBase.h"
#include "enemySlim.h"
#include "enemyWing.h"
#include "enemyLance.h"
#include "playerUI.h"
#include "key.h"
#include "resultUI.h"
#include "movieUI.h"

#include "objectMgr.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "status.h"
#include "characterAction.h"
#include "string.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32

//===== マクロ定義 =====
#define SAVE_DATA_FILE (FILE_PATH"savedata.bin")


//===== 構造体 =====
struct SSAVE_DATA
{
	CStatus m_status;
	bool m_bTutorialClear = false;
	int m_nStageLevel = 0;
};


//===== グローバル変数 =====
static FADE *g_pFadeStage;
static CMovieUI* g_pMovieUI;
static CPlayerUI* g_pPlayerUI;
static CSound g_SE;

CStage* CStageManager::m_pCurrentStage	= nullptr;
CStage* CStageManager::m_pNextStage		= nullptr;
CPlayer* CStageManager::m_pMainPlayer	= nullptr;
int CStageManager::m_nTimer	= -1;
int CStageManager::m_nStageLevel = 0;
bool CStageManager::m_bTutorialClear = false;
int CStageManager::m_nGameTime = 0;
CResultUI* CStageManager::m_pResultUI = nullptr;


CSound CStageManager::sm_aBGM[BGM::MAX_MAP_BGM];
BGM::EMAP_BGM CStageManager::m_eCurBGM = BGM::RENGA_RANDOM;


//========================================
//
//	コンストラクタ
//
//========================================
CStageManager::CStageManager()
{
	// 最初のシーン
	m_pCurrentStage = nullptr;
	m_pNextStage = nullptr;
}


//========================================
//
//	デストラクタ
//
//========================================
CStageManager::~CStageManager()
{
	// 最初のシーン
	m_pCurrentStage = nullptr;
	m_pNextStage = nullptr;
}


//========================================
//
//	初期化
//
//========================================
void CStageManager::Init()
{
	// ステージ
	CStageMaker::Init();
	CStageChangeBossArea::Init();

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
	// プレイヤーの初期化
	CPlayer::Init();

	// キャラクターアクションの初期化
	CCharacterAction::Init();
	// プレイヤーアクションの初期化
	CPlayerAction::Init();
	// プレイヤーUI
	CPlayerUI::Init();
	// リザルトUI
	CResultUI::Init();
	
	// ムービーUI
	CMovieUI::Init();
	g_pMovieUI = new CMovieUI();

	// フェードの生成
	g_pFadeStage = new FADE(SetStageChange);
	g_pFadeStage->GetSprite()->SetColor(Float4{ 0,0,0,1 });

	// プレイヤーの生成
	m_pMainPlayer = CObjectManager::CreateObject<CPlayer>();
	g_pPlayerUI = CPlayerUI::Create(Float3{ -SCREEN_CENTER_X / 4 * 3,-SCREEN_CENTER_Y / 5 * 4,0 });


	// セーブデータの読み込み
	FILE *fp;
	fp = fopen(SAVE_DATA_FILE, "rb");
	if (fp)
	{
		SSAVE_DATA save;
		std::fread(&save, sizeof(save), 1, fp);
		m_bTutorialClear = save.m_bTutorialClear;
		m_nStageLevel = save.m_nStageLevel;
		*m_pMainPlayer->GetStatus() = save.m_status;

		std::fclose(fp);
	}

	// 最初のステージセット
	if (m_bTutorialClear)
	{
		// クリア済みなら
		m_pCurrentStage = new CStageStartMap();
		//m_pCurrentStage = new CStageDebug();
		//m_pCurrentStage	= new CStageTutorial();
		//m_pCurrentStage	= new CStageBoss();
	}
	else
	{
		m_pCurrentStage = new CStageTutorial();
		//m_pCurrentStage = new CStageStartMap();

	}
	m_pNextStage = m_pCurrentStage;


	// 最初のステージ初期化
	m_pCurrentStage->Init();

	// サウンドのロード
	sm_aBGM[BGM::START_MAP].Load(FILE_PATH"sound/bgm/BaseMapBGM.mp3", true);
	sm_aBGM[BGM::RENGA_RANDOM].Load(FILE_PATH"sound/bgm/gameBGM.wav", true);
	sm_aBGM[BGM::RENGA_BOSS].Load(FILE_PATH"sound/bgm/BossBGM.mp3", true);

	// SE
	g_SE.Load(FILE_PATH"sound/fade/sceneswitch2.mp3");

	// 最初のサウンドのセット
	m_eCurBGM = BGM::START_MAP;
	PlayBGM();

	// リザルトUI
	m_nGameTime = 0;
	m_pResultUI = nullptr;

}


//========================================
//
//	終了処理
//
//========================================
void CStageManager::Uninit()
{
	// セーブデータの書き込み
	FILE *fp;
	fp = std::fopen(SAVE_DATA_FILE, "wb");

	SSAVE_DATA save;
	save.m_bTutorialClear = m_bTutorialClear;
	save.m_nStageLevel = m_nStageLevel;
	save.m_status = *m_pMainPlayer->GetStatus();

	std::fwrite(&save, sizeof(save), 1, fp);

	std::fclose(fp);

	// サウンドの停止
	sm_aBGM[m_eCurBGM].Stop();

	// ステージ終了処理
	m_pCurrentStage->Uninit();

	// プレイヤーの消去
	g_pPlayerUI->Destroy();
	CObjectManager::DestroyObject(m_pMainPlayer);
	m_pMainPlayer = nullptr;

	// フェードの消去
	delete g_pFadeStage;
	g_pFadeStage = nullptr;

	// ムービーUI
	delete g_pMovieUI;
	g_pMovieUI = nullptr;
	CMovieUI::Uninit();

	// リザルトUI
	CResultUI::Uninit();
	// プレイヤーUI
	CPlayerUI::Uninit();
	// プレイヤーアクションの終了処理
	CPlayerAction::Uninit();
	// キャラクターアクションの終了処理
	CCharacterAction::Uninit();

	// プレイヤーの終了処理
	CPlayer::Uninit();
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

	// ステージ
	CStageChangeBossArea::Uninit();
	CStageMaker::Uninit();
}


//========================================
//
//	全てのオブジェクトの更新
//
//========================================
void CStageManager::Update()
{
	// 現在のステージの更新処理
	m_pCurrentStage->Update();

	// リザルトUI
	if (m_pResultUI) m_pResultUI->Update();

	// フェードの更新処理
	g_pFadeStage->Update();

	// タイマーの更新
	if (m_nTimer >= 0) m_nTimer--;

	// 一定時間後にステージの移動
	if (m_nTimer == 0)
	{
		// シーンのエフェクトなんか
		// スイッチ文とかでどのシーンエフェクト、フェードを使うか選べたら面白そう
		g_pFadeStage->StartFadeOut();

		// サウンド
		g_SE.Play();

		// 画面を停止
		CSceneManager::SetStopFlag(true);
	}

	// ゲーム時間
	m_nGameTime++;
}


//========================================
//
//	全てのオブジェクトの描画
//
//========================================
void CStageManager::Draw()
{
	// 現在のステージ描画処理
	m_pCurrentStage->Draw();

	// リザルトUI
	if (m_pResultUI) m_pResultUI->Draw();

	// ムービーUI
	if (g_pMovieUI) g_pMovieUI->Draw();

	// フェードの描画処理
	g_pFadeStage->Draw();
}


//========================================================
//
//	次のシーンをセット
//
//========================================================
void CStageManager::SetNextStage(CStage *pNextStage)
{
	// 次のシーンを格納
	m_pNextStage = pNextStage;

	// シーンのエフェクトなんか
	// スイッチ文とかでどのシーンエフェクト、フェードを使うか選べたら面白そう
	g_pFadeStage->SetChangeEvent(SetStageChange);
	g_pFadeStage->StartFadeOut();

	// サウンド
	g_SE.Play();

	// 画面を停止
	CSceneManager::SetStopFlag(true);
}

//========================================================
//
//	一定時間後に次のシーンをセット
//
//========================================================
void CStageManager::SetTimerNextStage(CStage *pNextStage, int nTimerFrame, void(*pFadeOutEvent)())
{
	m_nTimer = nTimerFrame;

	// 次のシーンを格納
	m_pNextStage = pNextStage;

	// フェードイベントを格納する
	g_pFadeStage->SetChangeEvent(pFadeOutEvent);
}

//========================================================
//
//	次のシーンへ移動
//
//========================================================
void CStageManager::SetStageChange()
{
	// リザルトUI
	m_pResultUI->Destroy();
	m_pResultUI = nullptr;

	// 現在のシーンの終了処理を呼ぶ
	m_pCurrentStage->Uninit();

	// オブジェクトマネージャーの終了処理
	CObjectManager::Uninit();

	// 現在のシーンの消去
	delete m_pCurrentStage;

	// 現在のシーンの変更
	m_pCurrentStage = m_pNextStage;

	// オブジェクトマネージャーの初期化
	CObjectManager::Init();

	// 次のシーンの初期化
	m_pCurrentStage->Init();

	// プレイヤーデータがあれば
	if (m_pMainPlayer)
	{
		// カメラのセット
		CCamera::SetCameraTarget(m_pMainPlayer->GetTransform());
		// プレイヤーのリセット
		m_pMainPlayer->GetRb()->SetForce(Float3{ 0,0,0 });

	}
}


//========================================================
//
//	BGMをセット
//
//========================================================
void CStageManager::SetBGM(BGM::EMAP_BGM eBGM, float fVolume)
{
	// 今のBGMと同じならパス
	if (m_eCurBGM == eBGM) return;

	// 現在のBGMをストップ
	for(int i = 0; i < BGM::MAX_MAP_BGM; i++)
		sm_aBGM[i].Stop();

	// 新しいBGMのセット・再生
	m_eCurBGM = eBGM;
	sm_aBGM[m_eCurBGM].Play(fVolume);

}

//========================================================
//
//	ゲームのリスタート
//
//========================================================
void CStageManager::SetRestart()
{
	// リストをクリア
	//CCollision::Uninit();
	//CRigidbody::Uninit();

	// プレイヤーの生成
	//m_pMainPlayer = CObjectManager::CreateObject<CPlayer>();
	m_pMainPlayer->SetPlayerStop(false);
	m_pMainPlayer->GetRb()->SetStop(false);
	m_pMainPlayer->SetBackUpStatus();
	m_pMainPlayer->GetStatus()->SetHp(m_pMainPlayer->GetStatus()->GetMaxHp());
	m_pMainPlayer->GetStatus()->SetStop(false);
	m_pMainPlayer->GetStatus()->SetInvincibleCnt(0);

	// Result
	CResultUI::Reset(m_pMainPlayer->GetStatus()->GetLevel());
	m_nGameTime = 0;

	// ステージの移動
	SetStageChange();
}