//==================================================================
//								bullet.h
//	GM21 バレット	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/17	バレットクラス作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "status.h"

namespace BULLET
{
	enum EBULLET_TYPE
	{
		BLUE,
		GREEN,
		PURPLE,
		ARROW,

		MAX_BULLET_TYPE,
	};
}


//===== クラス定義 =====

class CBullet : public CObject
{
public:
	CBullet();
	~CBullet();
	void Destroy();

	// 静的関数
	static void Init();
	static void Uninit();
	static CBullet* Create(Float3 pos, Float3 force, CStatus *pStatus, BULLET::EBULLET_TYPE eType = BULLET::BLUE);

	// 仮想関数
	virtual void Update();
	virtual void Draw();
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);


	CRigidbody* GetRigid() { return m_pRigidbody; }
	CCollision* GetCol() { return m_pCollision; }
	virtual CStatus* GetStatus() { return &m_pParentStatus; }

protected:
	CCollision* m_pCollision;	// コンポーネント
	CRigidbody* m_pRigidbody;	// リジッドボディ

	BULLET::EBULLET_TYPE m_eType;
 	static CTexture sm_texture[BULLET::MAX_BULLET_TYPE];
private:
	CStatus m_pParentStatus;
};

