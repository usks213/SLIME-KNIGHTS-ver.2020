//==================================================================
//								enemyBigWnig.h
//	デカ羽スライム
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/06	デカ羽スライムクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "enemy.h"

//===== クラス定義 =====
class CEnemyBigWing : public CEnemy
{
public:
	CEnemyBigWing();
	~CEnemyBigWing();
	// 仮想関数
	virtual void Update();

private:
	int m_nShotInterval;
	bool m_bUp;
	bool m_bRight;
	int m_nUpPos;
	int m_nRightPos;

};


