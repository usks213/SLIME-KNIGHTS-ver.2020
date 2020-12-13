//==================================================================
//								character.h
//	GM21 
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/03	キャラクタークラス作成	
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "status.h"
#include "characterAction.h"
#include "objectMgr.h"

//===== クラス定義 =====


class CCharacter : public CObject
{
public:
	CCharacter();
	~CCharacter();
	// 仮想関数
	virtual void Update() = 0;
	virtual void Draw()   = 0;
	virtual void Destroy() { CObjectManager::DestroyObject(this); }
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision) { return; }
	// アニメーション終了時に呼び出される関数
	virtual void OnAnimator(CAnimator *pAnimator) { return; }

	// コンポーネント
	CCollision* GetCol() { return m_pCollision; }
	CAnimator* GetAnim() { return m_pAnimator; }
	CRigidbody* GetRb()  { return m_pRigidbody; }
	virtual CStatus* GetStatus() { return &m_status; }

	// ゲット・セット関数
	bool GetFloorThrough() { return m_bFloorThrough; }

protected:
	CCollision* m_pCollision;	// コンポーネント
	CAnimator* m_pAnimator;		// コンポーネント
	CRigidbody* m_pRigidbody;	// コンポーネント

	// ステータス
	CStatus m_status;
	//CCharacterAction m_charaAction;
	// 床用
	bool m_bFloorThrough;
private:

};



//===== プロトタイプ宣言 =====
