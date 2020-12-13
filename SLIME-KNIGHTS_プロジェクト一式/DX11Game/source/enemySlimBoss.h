//==================================================================
//								enemySlimBoss.cpp
//	スライムボス
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/04	スライムボスクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "enemy.h"
#include "bg.h"

//===== クラス定義 =====
class CEnemySlimBoss : public CEnemy
{
public:
	CEnemySlimBoss();
	~CEnemySlimBoss();
	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Destroy();

	static void FlashAfter(CEnemySlimBoss* pBoss);

private:
	int m_nShotInterval;
	int m_nState;
	int m_nPrevState;
	int m_nStateTime;
	int m_nEnemyCnt;

	bool m_bMovie;
	float m_fAlpha;

	//CBG* m_pBg;
};


