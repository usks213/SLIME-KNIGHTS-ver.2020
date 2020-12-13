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

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "stage.h"
#include "player.h"
#include "transform.h"
#include "../Sound.h"
#include "resultUI.h"


//===== 列挙型 =====
namespace BGM
{
	enum EMAP_BGM
	{
		START_MAP,

		RENGA_RANDOM,
		RENGA_BOSS,

		MAX_MAP_BGM,
	};
}


//===== クラス定義 =====
class CStageManager
{
public:
	CStageManager();
	~CStageManager();

	// 四大処理
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// ステージのセット
	static void SetNextStage(CStage *pNextStage);
	static void SetTimerNextStage(CStage *pNextStage, int nTimerFrame, void(*pFadeOutEvent)() = SetStageChange);
	static void SetStageChange();
	
	// プレイヤー
	static void SetRestart();
	static void SetPlayerPos(Float3 pos) {
		if (m_pMainPlayer) {
			//m_pMainPlayer->GetTransform()->SetPos(pos);
			m_pMainPlayer->SetReStartPos(pos);
		}
	}
	static CPlayer* GetMainPlayer() { return m_pMainPlayer; }

	// ステージデータ
	static void SetStageLevel(int nLevel) { m_nStageLevel = nLevel; }
	static void AddStageLevel() { m_nStageLevel++; }
	static int GetStageLevel() { return m_nStageLevel; }
	static void SetTutorialClear(bool bFlag) { m_bTutorialClear = bFlag; }

	// BGM
	static void SetBGM(BGM::EMAP_BGM eBGM, float fVolume = 0.5f);
	static void StopBGM() {
		for(int i = 0; i < BGM::MAX_MAP_BGM; i++)
		sm_aBGM[i].Stop(); 
	}
	static void PlayBGM() { sm_aBGM[m_eCurBGM].Play(0.5f); }
	static int GetGameTime() { return m_nGameTime; }
	static void CreateResult() { m_pResultUI = CResultUI::Create(); }

private:
	static CStage* m_pCurrentStage;
	static CStage* m_pNextStage;
	static CPlayer* m_pMainPlayer;
	static int m_nTimer;

	// ステージの階層
	static int m_nStageLevel;
	static bool m_bTutorialClear;

	// BGM
	static CSound sm_aBGM[BGM::MAX_MAP_BGM];
	static BGM::EMAP_BGM m_eCurBGM;

	static CResultUI* m_pResultUI;
	static int m_nGameTime;
};

