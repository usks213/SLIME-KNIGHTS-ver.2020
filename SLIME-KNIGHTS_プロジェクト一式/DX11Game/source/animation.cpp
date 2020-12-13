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

//====== インクルード部 ======
#include "animation.h"
#include "animator.h"

//===== マクロ定義 =====


//===== クラス定義 =====



//===== プロトタイプ宣言 =====




//========================================
//
//	コンストラクタ
//
//========================================
CAnimation::CAnimation()
{
	m_nArraySize = 0;
	m_pAnimNoArray = nullptr;
	m_pszName = nullptr;
}


//========================================
//
//	デストラクタ
//
//========================================
CAnimation::~CAnimation()
{
	/*if (m_pAnimNoArray != nullptr)
	{
		delete[] this->m_pAnimNoArray;
	}*/
}


//========================================
//
//	生成
//
//========================================
CAnimation* CAnimation::Create(CAnimator* pAnimator, const char *pszName, int nMaxFrame, ...)
{
	// 可変引数リスト
	va_list args;
	int nCount;
	
	// 動的にアニメーションクラスの確保
	CAnimation *pAnim = new CAnimation;

	// 可変引数リスト作成
	va_start(args, nMaxFrame);

	// 可変引数の数を計算
	nCount = nMaxFrame;

	// 可変引数分メモリ確保
	pAnim->m_pAnimNoArray = new int[nCount];

	// 配列にnAnimNoを順番に格納
	for (int i = 0; i < nCount; i++)
	{
		pAnim->m_pAnimNoArray[i] = va_arg(args, int);
	}

	// 可変引数リスト終了
	va_end(args);

	// アニメーションの名前の格納
	pAnim->m_pszName = pszName;
	// 配列(アニメーションのコマ)の数を格納
	pAnim->m_nArraySize = nCount;

	// 最後にアニメーターのリストに新しく作ったアニメーションを格納
	pAnimator->AddAnimation(pAnim);
	pAnim->m_pAnimator = pAnimator;

	return pAnim;
}

//========================================
//
//	生成 (自動でコマ番号振り分け)
//
//========================================
CAnimation* CAnimation::Create(CAnimator* pAnimator, const char *pszName, unsigned int nMaxFrame)
{
	// 動的にアニメーションクラスの確保
	CAnimation *pAnim = new CAnimation;

	// メモリ確保
	pAnim->m_pAnimNoArray = new int[nMaxFrame];

	// 配列にnAnimNoを順番に格納
	for (int i = 0; i < (int)nMaxFrame; i++)
	{
		pAnim->m_pAnimNoArray[i] = i;
	}

	// アニメーションの名前の格納
	pAnim->m_pszName = pszName;
	// 配列(アニメーションのコマ)の数を格納
	pAnim->m_nArraySize = nMaxFrame;

	// 最後にアニメーターのリストに新しく作ったアニメーションを格納
	pAnimator->AddAnimation(pAnim);
	pAnim->m_pAnimator = pAnimator;

	return pAnim;
}


//========================================
//
//	消去
//
//========================================
void CAnimation::Destroy()
{
	if (m_pAnimNoArray != nullptr)
	{
		delete[] this->m_pAnimNoArray;
	}
	delete this;
}


