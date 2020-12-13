//==================================================================
//								playerAction.h
//	 
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/13	プレイヤーアクションクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "characterAction.h"


//===== クラス定義 =====

class CPlayer;

class CPlayerAction : public CCharacterAction
{
public:
	// コンストラクタ・デストラクタ
	CPlayerAction();
	~CPlayerAction();

	// 初期化・終了処理
	static void Init();
	static void Uninit();

	// 更新
	virtual void Update();

	// 行動パターン
	virtual void Attack(int nAnimSpeed = 0);
	virtual void Attack(int nAnimSpeed, CTransform* pTrans);


	// OnCollisionにセット
	//virtual void OnCollisionAction(CCollision *pCol);
	// OnAnimatorにセット
	virtual void OnAnimatorAction(CAnimator *pAnim);

	void SetPlayerAttackData(CPlayer *pPlayer, int nAttackAnimSpeed)
	{ 
		m_pPlayer = pPlayer; 
		m_nAttackAnimSpeed = nAttackAnimSpeed;
	}
	void SetAttackAnimSpeed(int nAttackAnimSpeed) { m_nAttackAnimSpeed = nAttackAnimSpeed; }

protected:
	CPlayer *m_pPlayer;

	int m_nAttackAnimSpeed;
	bool m_bAttack;
	bool m_bDown;
	int m_nAttackInterval;
};

