//==================================================================
//								light.h
//	マップのライト	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/06	ライトクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====


class CLight : public CObject
{
public:
	CLight();
	~CLight();

	// 静的関数
	static CLight* Create(CTransform *pTrans, float fScale);
	static void Init();
	static void Uninit();

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
	static void SetBoss(bool bFlag) { m_bBoss = bFlag; }

protected:
	// コンポーネント
	CCollision* m_pCollision;	// コリジョン
	static CTexture sm_texture;

	CTransform *m_pParent;
	float m_fBaseSize;
	bool m_bExpansion;
	static bool m_bBoss;

private:

};

