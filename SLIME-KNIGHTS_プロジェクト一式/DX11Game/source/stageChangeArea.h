//==================================================================
//								stageChageArea.h
//	ステージチェンジエリア	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/23	ステージチェンジエリア
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

class CStageChangeArea : public CObject
{
public:
	CStageChangeArea();
	~CStageChangeArea();

	// 静的関数
	static CStageChangeArea* Create(Float3 pos, int nAreaType);

	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);

	// ゲット関数
	CCollision* GetCol() { return m_pCollision; }
	static int GetGotoChangeArea() { return m_nGotoChangeArea; }

	// セット関数
	static void SetGotoChangeArea(int nAreaType) { m_nGotoChangeArea = nAreaType; }

protected:
	// コンポーネント
	CCollision* m_pCollision;	// コリジョン
//	CRigidbody* m_pRb;

	// 移動エリアのタイプ
	int m_nChangeAreaType;

	// プレイヤーのステージ移動ステート
	static int m_nGotoChangeArea;

	bool m_Hit;
private:

};

