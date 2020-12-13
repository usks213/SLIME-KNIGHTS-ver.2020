//==================================================================
//									resultUI.h
//	リザルト画面
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/07	リザルトUIクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "string.h"


//===== マクロ定義 =====
#define MAX_RESULT_BAR (5)

//===== クラス定義 =====
class CResultUI : public CObject
{
public:
	CResultUI();
	~CResultUI();

	static CResultUI* Create(Float3 pos = Float3{0,0,0});
	void Destroy();

	virtual void Update();
	virtual void Draw();

	static void Init();
	static void Uninit();

	static void Reset(int nPrevLevel) {
		m_nEnemy = 0;
		m_nExperience = 0;
		m_nPrevLevel = nPrevLevel;
		m_nCurLevel = 0;
	}

	static void AddEnemy() { m_nEnemy++; }
	static void AddExperience(int nEx) { m_nExperience += nEx; }
	static void SetCurLevel(int nLevel) { m_nCurLevel = nLevel; }

private:
	// 状態
	int m_nState;

	// BG
	Float4 m_colorBG;
	float m_fBgAlpha;


	// GAME OVER
	static CTexture sm_textureGameOver;		// マスターテクスチャ
	float m_fGameOverAlpha;

	// BAR
	static CTexture sm_textureBar;				// マスターテクスチャ
	float m_fBarPosY[MAX_RESULT_BAR];
	int m_nBarCnt;

	// ストリング
	STRING::CString* m_pString;


	// リザルトUIのデータ
	static int m_nExperience;
	static int m_nEnemy;
	static int m_nPrevLevel;
	static int m_nCurLevel;
	static int m_nDrawLevel;
	int m_nTime;
};
