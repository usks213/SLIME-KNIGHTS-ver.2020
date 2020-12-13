//==================================================================
//								viewArea.h
//	視野エリア	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/18	視野エリアクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

class CEnemy;

class CViewArea : public CObject
{
public:
	CViewArea();
	~CViewArea();

	// 静的関数
	static CViewArea* Create(CEnemy *pEnemy);

	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);

	// ゲット関数
	CCollision* GetCol() { return m_pCollision; }

	// セット関数

protected:
	// コンポーネント
	CCollision* m_pCollision;	// コリジョン

	// エネミー
	CEnemy *m_pParentEnemy;

private:

};

