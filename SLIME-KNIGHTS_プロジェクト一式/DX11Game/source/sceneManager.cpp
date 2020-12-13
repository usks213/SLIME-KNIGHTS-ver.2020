//==================================================================
//								sceneManager.h
//	GM21 シーン管理
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/16	シーン管理クラス作成
//
//===================================================================


//====== インクルード部 ======
#include "sceneManager.h"
#include "sceneGame.h"
#include "sceneTitle.h"
#include "fade.h"
#include "flash.h"
#include "camera.h"
#include "stageMaker.h"

#include "objectMgr.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "status.h"
#include "characterAction.h"
#include "string.h"


//===== マクロ定義 =====


//===== グローバル変数 =====
static FADE *g_pFade;

CScene* CSceneManager::m_pCurrentScene	= nullptr;
CScene* CSceneManager::m_pNextScene		= nullptr;
bool CSceneManager::m_bStop = false;
CFlash* CSceneManager::m_pFlash = nullptr;



//========================================
//
//	コンストラクタ
//
//========================================
CSceneManager::CSceneManager()
{
	// 最初のシーン
	m_pCurrentScene = nullptr;
	m_pNextScene = nullptr;
}


//========================================
//
//	デストラクタ
//
//========================================
CSceneManager::~CSceneManager()
{
	// 最初のシーン
	m_pCurrentScene = nullptr;
	m_pNextScene = nullptr;
}


//========================================
//
//	初期化
//
//========================================
void CSceneManager::Init()
{
	// 最初のシーンのセット
	//m_pCurrentScene	= new CSceneGame();
	m_pCurrentScene	= new CSceneTitle();
	m_pNextScene	= m_pCurrentScene;

	// オブジェクトマネージャーの初期化
	CObjectManager::Init();

	// ランダムステージの生成
	CStageMaker::CreateRendomMap();

	// 最初のシーンの初期化
	m_pCurrentScene->Init();

	// 文字列表示の初期化
	STRING::CString::Init();

	// フェードの生成
	g_pFade = new FADE(SetSceneChange);
	// フラッシュの生成
	m_pFlash = new CFlash();

	// ストップフラグ
	m_bStop = false;
}


//========================================
//
//	終了処理
//
//========================================
void CSceneManager::Uninit()
{
	// フラッシュの消去
	delete m_pFlash;
	// フェードの消去
	delete g_pFade;

	// 文字列表示の終了処理
	STRING::CString::Uninit();

	// シーンの終了処理
	m_pCurrentScene->Uninit();

	// オブジェクトマネージャーの終了処理
	CObjectManager::Uninit();
}


//========================================
//
//	全てのオブジェクトの更新
//
//========================================
void CSceneManager::Update()
{
	// カメラ 
	CCamera::SetCameraTarget(nullptr);

	// 現在のシーンの更新処理
	m_pCurrentScene->Update();

	// オブジェクト系の更新処理
	if (!m_bStop)
	{
		// オブジェクトの一斉更新
		CObjectManager::Update();

		// リジッドボディ
		CRigidbody::Update();
		// 当たり判定の更新処理
		CCollision::Update();
		// アニメーションの更新
		CAnimator::Update();
		// ステータスの更新
		CStatus::ListUpdate();
		// キャラクターアクションの更新
		CCharacterAction::ListUpdate();
		// オブジェクトの遅延更新
		CObjectManager::LateUpdate();
	}
	else
	{
		//　UIの更新処理

	}

	// フェードの更新処理
	g_pFade->Update();
	// フラッシュの更新処理
	m_pFlash->Update();

	// カメラ
	CCamera::Update();
}


//========================================
//
//	全てのオブジェクトの描画
//
//========================================
void CSceneManager::Draw()
{
	// オブジェクトの一斉描画
	CObjectManager::Draw();

	// 現在のシーンの描画処理
	m_pCurrentScene->Draw();

	// コリジョンの描画
	if(GetDebugFlag()) CCollision::Draw();

	// フェードの描画処理
	g_pFade->Draw();
	// フラッシュの描画処理
	m_pFlash->Draw();
}


//========================================================
//
//	次のシーンをセット
//
//========================================================
void CSceneManager::SetNextScene(CScene *pNextScene)
{
	// 次のシーンを格納
	m_pNextScene = pNextScene;

	// シーンのエフェクトなんか
	// スイッチ文とかでどのシーンエフェクト、フェードを使うか選べたら面白そう
	g_pFade->StartFadeOut();

}

//========================================================
//
//	次のシーンへ移動
//
//========================================================
void CSceneManager::SetSceneChange()
{
	// 現在のシーンの終了処理を呼ぶ
	m_pCurrentScene->Uninit();

	// オブジェクトマネージャーの終了処理
	CObjectManager::Uninit();

	// 現在のシーンの消去
	delete m_pCurrentScene;

	// 現在のシーンの変更
	m_pCurrentScene = m_pNextScene;

	// オブジェクトマネージャーの初期化
	CObjectManager::Init();

	// 次のシーンの初期化
	m_pCurrentScene->Init();
}
