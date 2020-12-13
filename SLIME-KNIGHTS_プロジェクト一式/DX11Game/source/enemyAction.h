//==================================================================
//								enemyAction.h
//	 
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/16	エネミーアクションクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "characterAction.h"


//===== クラス定義 =====

class CEnemyAction : public CCharacterAction
{
public:
	// コンストラクタ・デストラクタ
	CEnemyAction();
	~CEnemyAction();

	// 行動パターン
	virtual void Attack(int nAnimSpeed = 0);

	// OnCollisionにセット
	//virtual void OnCollisionAction(CCollision *pCol);
	// OnAnimatorにセット
	virtual void OnAnimatorAction(CAnimator *pAnim);


protected:
};

