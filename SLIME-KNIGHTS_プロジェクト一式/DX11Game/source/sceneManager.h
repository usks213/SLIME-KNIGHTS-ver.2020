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

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "scene.h"
#include "flash.h"

//===== クラス定義 =====

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	// 四大処理
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// シーンのセット
	static void SetNextScene(CScene *pNextScene);
	static void SetSceneChange();

	// 更新ストップフラグ
	static void SetStopFlag(bool bStop) { m_bStop = bStop; }

	// フラッシュ
	static CFlash* GetFlash() { return m_pFlash; }

private:
	static CScene* m_pCurrentScene;
	static CScene* m_pNextScene;

	static bool m_bStop;
	static CFlash* m_pFlash;
};

