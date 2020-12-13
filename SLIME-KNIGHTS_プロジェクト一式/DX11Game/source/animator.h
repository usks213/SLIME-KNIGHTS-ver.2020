//==================================================================
//									animator.h
//	アニメーター
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/08	アニメータークラス作成
//
//===================================================================
#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "List.h"

//===== マクロ定義 =====


//===== クラス定義 =====
class CSprite;
class CObject;
class CAnimation;

// メモ： 汎用型にして
class CAnimator
{
public:
	CAnimator();
	~CAnimator();
	static void Init();
	static void Uninit();
	static void Update();

	// 生成・消去
	static CAnimator* Create(CSprite *pSpr, CObject* pObj);
	void Destroy();

	// ゲット関数
	CSprite* GetSpr() { return m_pSpr; }

	// アニメーションリスト管理
	void AddAnimation(CAnimation *pAnim) { m_animationList.AddNode(pAnim); }
	void DestroyAnimation(CAnimation *pAnim) { m_animationList.DestroyNode(pAnim); }
	void SetAnimation(const char *pszName);
	void SetAnimation(const char *pszName, int nSpeed);
	void SetAnimation(const char *pszName, int nSpeed, int nSplitX, int nSplitY);

	// ゲット関数
	CAnimation* GetCurrentAnimation() { return m_pCurrentAnimation; }

	// セット関数
	void SetStop(bool bStop) { m_bStop = bStop; }

	void SetCurAnimNo(int nAnimNo) { m_nCurrentAnimNo = nAnimNo; }

private:
	static List<CAnimator> m_list;
	List<CAnimation> m_animationList;
	CSprite *m_pSpr;
	CObject *m_pObj;

	// アニメーションの変数
	int m_nSpeed;
	int m_nSplitX;
	int m_nSplitY;
	int m_nFrame;
	int m_nCurrentAnimNo;
	CAnimation *m_pCurrentAnimation;
	bool m_bStop;
};

