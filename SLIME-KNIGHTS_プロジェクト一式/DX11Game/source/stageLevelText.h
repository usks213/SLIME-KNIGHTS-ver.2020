//==================================================================
//								stageLevelText.h
//	ステージレベルの表示
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/07	ステージレベルクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "string.h"


//===== 定数定義 =====


//===== クラス定義 =====

class CStageLevelText : public CObject
{
public:
	// 通常関数
	CStageLevelText();
	~CStageLevelText();
	void Destroy();

	// 静的関数
	static CStageLevelText* Create(Float3 pos, int nLevel);
	static void Init();
	static void Uninit();

	// 仮想関数
	virtual void Update();
	virtual void Draw();
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);
	// アニメーション終了時に呼び出される関数
	virtual void OnAnimator(CAnimator *pAnimator);

	// コンポーネント
	CAnimator* GetAnim() { return m_pAnimator; }

protected:
	CAnimator* m_pAnimator;		// コンポーネント

	STRING::CString *m_pString;
	char m_szText[30];
private:
	float m_fAlpha;
	bool m_bAlpha;
};



//===== プロトタイプ宣言 =====
