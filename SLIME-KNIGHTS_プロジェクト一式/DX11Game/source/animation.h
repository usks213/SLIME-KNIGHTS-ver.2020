//==================================================================
//									animation.h
//	アニメーション
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/10	アニメーションクラス作成
//
//===================================================================
#pragma once

//====== インクルード部 ======
#include "../main.h"
#include <stdarg.h>


//===== マクロ定義 =====


//===== クラス定義 =====
class CAnimator;

// メモ： 汎用型にして
class CAnimation
{
public:
	CAnimation();
	~CAnimation();
	// 生成・消去
	static CAnimation* Create(CAnimator* pAnimator, const char *pszName, int nMaxFrame, ...);
	static CAnimation* Create(CAnimator* pAnimator, const char *pszName, unsigned int nMaxFrame);
	void Destroy();
	// ゲット関数
	const char* GetName() { return m_pszName; }
	int* GetAnimNoArray() { return m_pAnimNoArray; }
	int GetArraySize() { return m_nArraySize; }
	CAnimator* GetAnimator() { return m_pAnimator; }
private:
	int* m_pAnimNoArray;
	int m_nArraySize;
	const char *m_pszName;
	CAnimator *m_pAnimator;
};

