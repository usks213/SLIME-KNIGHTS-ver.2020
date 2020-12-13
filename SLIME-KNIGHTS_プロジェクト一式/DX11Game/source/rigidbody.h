//==================================================================
//									rigidbody.h
//	リジッドボディ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/12	リジッドボディクラス作成
//
//===================================================================
#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "List.h"

//===== マクロ定義 =====

namespace DIRECTION
{
	enum EDIRECTION
	{
		RIGHT,
		LEFT,
		UP,
		DOWN,

		MAX_DIRECTION,
	};
}

//===== クラス定義 =====
class CTransform;

// メモ： 汎用型にして
class CRigidbody
{
public:
	CRigidbody();
	~CRigidbody();
	static void Init();
	static void Uninit();
	static void Update();

	// 生成・消去
	static CRigidbody* Create(CTransform *pTrans, bool bSolid = false, bool bUseGravity = true, bool bTrigger = false);
	void Destroy();

	// 押し出し
	void Extrusion(CRigidbody *pOther);
	void ExtrusionCircleToCircle(CRigidbody *pOther);

	// ゲット関数
	CTransform* GetObj() { return m_pTrans; }
	bool GetUseGravity() { return m_bUseGravity; }
	DIRECTION::EDIRECTION GetHitDir() { return m_enHitDir; }
	Float3 GetForce() { return m_force; }
	Float3 GetDir() { return m_dir; }

	// セット関数
	void SetForce(Float3 force) { m_force = force; }
	void SetForceX(float forceX) { m_force.x = forceX; }
	void SetForceY(float forceY) { m_force.y = forceY; }
	void AddForceX(float forceX) { m_force.x += forceX; }
	void AddForceY(float forceY) { m_force.y += forceY; }
	void AddForce(Float3 force) 
	{ 
		m_force.x += force.x;
		m_force.y += force.y;
		m_force.z += force.z;
	}
	void SetDragX(float fDragX) { m_fDragX = fDragX; }
	void SetGravityForce(float fForce) { m_fGraviyForce = fForce; }
	void SetUseGravity(bool bUse) { m_bUseGravity = bUse; }
	void SetStop(bool bStop) { m_bStop = bStop; }
	void SetTrigger(bool bTrigger) { m_bTrigger = bTrigger; }
	void SetSolid(bool bSolid) { m_bSolid = bSolid; }
	void SetMass(float fMass) { m_fMass = fMass; }

private:
	static List<CRigidbody> m_list;
	CTransform *m_pTrans;

	// パラメータ
	Float3 m_velocity;
	Float3 m_force;
	float m_fMass;
	float m_fDragX;
	bool m_bSolid;		// 不動オブジェクト
	Float3 m_dir;		// 向き
	float m_fGraviyForce;

	DIRECTION::EDIRECTION m_enHitDir;

	bool m_bUseGravity;
	bool m_bTrigger;
	bool m_bStop;
};


