//==================================================================
//								block.h
//	GM21 フィールド用ブロック	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/12	ブロッククラス作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

class CBlock : public CObject
{
public:
	CBlock();
	~CBlock();
	void Destroy();

	// 静的関数
	static void Init();
	static void Uninit();
	static CBlock* Create(Float3 pos, CTexture* nTex, int nTexPos, int nSplitX, int nSplitY);

	// 仮想関数
	virtual void Update();
	virtual void Draw();
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision) { return; }


	CRigidbody* GetRigid() { return m_pRigidBody; }
	CCollision* GetCol() { return m_pCollision; }

	void SetRigid(CRigidbody* pRb) { m_pRigidBody = pRb; }
	void SetCol(CCollision* pCol) { m_pCollision = pCol; }
	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

protected:
	CCollision* m_pCollision;	// コンポーネント
	CRigidbody* m_pRigidBody;
	CTexture*	m_pTexture;

private:

};

