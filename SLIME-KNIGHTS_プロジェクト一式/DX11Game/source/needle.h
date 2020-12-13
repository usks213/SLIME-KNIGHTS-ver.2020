//==================================================================
//								needle.h
//	マップの針	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/06	ニードルクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "status.h"


//===== クラス定義 =====

class CNeedl : public CObject
{
public:
	CNeedl();
	~CNeedl();
	void Destroy();

	// 静的関数
	static void Init();
	static void Uninit();
	static CNeedl* Create(Float3 pos);

	// 仮想関数
	virtual void Update();
	virtual void Draw();
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);


	CRigidbody* GetRigid() { return m_pRigidbody; }
	CCollision* GetCol() { return m_pCollision; }
	virtual CStatus* GetStatus() { return &m_status; }

protected:
	CCollision* m_pCollision;	// コンポーネント
	CRigidbody* m_pRigidbody;	// リジッドボディ

 	static CTexture sm_texture;
	CStatus m_status;
private:
};

