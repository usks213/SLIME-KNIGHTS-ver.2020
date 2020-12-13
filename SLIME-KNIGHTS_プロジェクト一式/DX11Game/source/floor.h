//==================================================================
//								floor.h
//	フィールド用床	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/29	フロアクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

class CFloor : public CObject
{
public:
	CFloor();
	~CFloor();
	void Destroy();

	// 静的関数
	static void Init();
	static void Uninit();
	static CFloor* Create(Float3 pos);

	// 仮想関数
	virtual void Update();
	virtual void Draw();
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);


	CRigidbody* GetRigid() { return m_pRigidBody; }
	CCollision* GetCol() { return m_pCollision; }

	void SetRigid(CRigidbody* pRb) { m_pRigidBody = pRb; }
	void SetCol(CCollision* pCol) { m_pCollision = pCol; }
	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

protected:
	CCollision* m_pCollision;	// コンポーネント
	CRigidbody* m_pRigidBody;
	static CTexture	sm_texture;

private:

};

