//==================================================================
//									Animator.h
//	コリジョン
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/08	アニメータークラスの作成
//
//===================================================================

//====== インクルード部 ======
#include "animator.h"
#include "object.h"
#include "animation.h"
#include "../sprite.h"


//===== マクロ定義 =====


//===== クラス定義 =====



//===== プロトタイプ宣言 =====


// 静的メンバの初期化
List<CAnimator> CAnimator::m_list;


//========================================
//
//	コンストラクタ
//
//========================================
CAnimator::CAnimator()
{
	m_nCurrentAnimNo = 0;
	m_nFrame = 0;
	m_nSpeed = 0;
	m_nSplitX = 0;
	m_nSplitY = 0;
	m_pCurrentAnimation = nullptr;
	m_pSpr = nullptr;
	m_bStop = false;
}


//========================================
//
//	デストラクタ
//
//========================================
CAnimator::~CAnimator()
{

}


//========================================
//
//	初期化
//
//========================================
void CAnimator::Init()
{
	

}

//========================================
//
//	終了処理
//
//========================================
void CAnimator::Uninit()
{

}

//========================================
//
//	更新
//
//========================================
void CAnimator::Update()
{
	// 先頭リストの取得
	List<CAnimator>* pHead = m_list.GetHead();
	List<CAnimator>* pTail = m_list.GetTail();

	// ノード無し
	if (pHead == nullptr) return;

	// アニメーターのワーク
	CAnimator *pAnimator;
	CAnimation *pAnimation;
	CSprite *pSpr;
	Float2 texPos;

	// リスト内の一斉更新
	List<CAnimator> *pNode = nullptr;
	List<CAnimator> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		// 次のポインタのバックアップを取る
		pNextBack = pNode->GetNext();

		// 空なら飛ばす
		if (pNode->GetThis()->m_pCurrentAnimation == nullptr) continue;

		// ノードの情報を取得
		pAnimator = pNode->GetThis();
		pAnimation = pAnimator->m_pCurrentAnimation;
		pSpr = pAnimator->GetSpr();

		// アニメーションのコマの更新
		if (0 == pAnimator->m_nFrame % pAnimator->m_nSpeed)
		{	
			// テクスチャ座標の更新
			texPos.x = pSpr->GetTexSize().x * (pAnimation->GetAnimNoArray()[pAnimator->m_nCurrentAnimNo] % pAnimator->m_nSplitX);
			texPos.y = pSpr->GetTexSize().y * (pAnimation->GetAnimNoArray()[pAnimator->m_nCurrentAnimNo] / pAnimator->m_nSplitX);
			pSpr->SetTexPos(texPos);

			if (pAnimator->m_bStop) continue;
			// 現在のコマ番号の更新
			pAnimator->m_nCurrentAnimNo++;
			pAnimator->m_nFrame = 0;
		}

		if (pAnimator->m_bStop) continue;

		//  フレームの更新
		pAnimator->m_nFrame++;

		// アニメーションの終了(最終フレーム)
		if (pAnimator->m_nCurrentAnimNo >= pAnimation->GetArraySize() && pAnimator->m_nFrame >= pAnimator->m_nSpeed)
		{
			// ここにアニメーションのアップデートを書く
			pNode->GetThis()->m_pObj->OnAnimator(pNode->GetThis());

			pAnimator->m_nCurrentAnimNo = 0;
		}
	}


}


//========================================
//
//	生成
//
//========================================
CAnimator* CAnimator::Create(CSprite *pSpr, CObject* pObj)
{
	CAnimator *pAniml = new CAnimator;

	m_list.AddNode(pAniml);

	pAniml->m_pSpr = pSpr;	
	pAniml->m_pObj = pObj;

	return pAniml;
}


//========================================
//
//	消去
//
//========================================
void CAnimator::Destroy()
{
	// 先頭リストの取得
	List<CAnimation>* pHead = m_animationList.GetHead();

	// ノード無し
	if (pHead != nullptr)
	{
		CAnimation *pAnim;
		// リスト内で検索
		List<CAnimation> *pNode = nullptr;
		List<CAnimation> *pNextBack = nullptr;
		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			// 次のポインタのバックアップを取る
			pNextBack = pNode->GetNext();

			// アニメーターが同じなら
			//if (this == pNode->GetThis()->GetAnimator())
			{
				pAnim = pNode->GetThis();
				if (m_animationList.DestroyNode(pNode))
				{
					pAnim->Destroy();
				}
			}
		}
	}

	if (m_list.DestroyNode(this))
	{
		delete this;
	}
}


//========================================
//
//	アニメーターにアニメーションのセット
//
//========================================
void CAnimator::SetAnimation(const char *pszName)
{
	// 先頭リストの取得
	List<CAnimation>* pHead = m_animationList.GetHead();

	// ノード無し
	if (pHead == nullptr) return;

	// アニメーションの再生
	//m_bStop = false;

	// リスト内で検索
	List<CAnimation> *pNode = nullptr;
	List<CAnimation> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		// 次のポインタのバックアップを取る
		pNextBack = pNode->GetNext();

		// 名前と同じのがあればセット
		if (pNode->GetThis()->GetName() == pszName)
		{
			// アニメーションが変わってないなら
			if (m_pCurrentAnimation == pNode->GetThis()) return;

			m_pCurrentAnimation = pNode->GetThis();
			m_nFrame = 0;
			m_nCurrentAnimNo = 0;
			return;
		}
	}

}
//========================================
//
//	アニメーターにアニメーションのセット
//
//========================================
void CAnimator::SetAnimation(const char *pszName, int nSpeed)
{
	SetAnimation(pszName);
	if(nSpeed > 0)
		m_nSpeed = nSpeed;
}
//========================================
//
//	アニメーターにアニメーションのセット
//
//========================================
void CAnimator::SetAnimation(const char *pszName, int nSpeed, int nSplitX, int nSplitY)
{
	SetAnimation(pszName, nSpeed);
	m_nSplitX = nSplitX;
	m_nSplitY = nSplitY;

	Float2 texSize;
	texSize.x = 1.0f / nSplitX;
	texSize.y = 1.0f / nSplitY;

	m_pSpr->SetTexSize(texSize);
}