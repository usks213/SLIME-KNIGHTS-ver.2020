//==================================================================
//								levelupText.h
//	レベルアップ表示
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/05	レベルアップテキストクラス
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "string.h"


//===== 定数定義 =====


//===== クラス定義 =====

class CLevelUpText : public CObject
{
public:
	// 通常関数
	CLevelUpText();
	~CLevelUpText();
	void Destroy();

	// 静的関数
	static CLevelUpText* Create(Float3 pos);
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
	CCollision* GetCol() { return m_pCollision; }
	CAnimator* GetAnim() { return m_pAnimator; }
	CRigidbody* GetRb()  { return m_pRigidbody; }

protected:
	CCollision* m_pCollision;	// コンポーネント
	CAnimator* m_pAnimator;		// コンポーネント
	CRigidbody* m_pRigidbody;	// コンポーネント

	STRING::CString *m_pString;
	float m_fForceY;
	char m_szText[30];
private:
	int m_nExistTime;
};



//===== プロトタイプ宣言 =====
