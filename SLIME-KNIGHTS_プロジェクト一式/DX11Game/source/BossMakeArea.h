//==================================================================
//											BossMakeArea.h
//	ボス生成エリア
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/04	ボス生成エリアクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

class CBossMakeArea : public CObject
{
public:
	CBossMakeArea();
	~CBossMakeArea();

	// 静的関数
	static CBossMakeArea* Create(Float3 pos);

	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);

	// ゲット関数
	CCollision* GetCol() { return m_pCollision; }

protected:
	// コンポーネント
	CCollision* m_pCollision;	// コリジョン


	bool m_Hit;
private:

};

