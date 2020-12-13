//==================================================================
//								attackBase.h
//	攻撃	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/03	攻撃のクラス
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

class CAttackBase : public CObject
{
public:
	CAttackBase();
	~CAttackBase();

	// 静的関数
	static CAttackBase* Create(CStatus *pStatus, CTransform *pParent, float fOffSetX = 0.0f);

	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);
	virtual void OnAnimator(CAnimator  *pAnimator);

	// ゲット関数
	CCollision* GetCol() { return m_pCollision; }
	virtual CStatus* GetStatus() { return m_pParentStatus; }

	// セット関数
	void SetOffSetX(float fOffSetX) { m_fOffSetX = fOffSetX; }
	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

protected:
	// コンポーネント
	CCollision* m_pCollision;	// コリジョン
	CAnimator*  m_pAnimator;	// アニメーター

	// 親のステータス
	CStatus* m_pParentStatus;
	// 座標系更新用
	CTransform* m_pParentTrans;
	float m_fOffSetX;


private:

};

