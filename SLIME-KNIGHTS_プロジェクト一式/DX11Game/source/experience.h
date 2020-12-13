//==================================================================
//								experience.h
//	ドロップする経験値
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/05	エクスペリエンスクラスの作成	
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== 定数定義 =====

//===== クラス定義 =====

class CExperience : public CObject
{
public:
	// 通常関数
	CExperience();
	~CExperience();
	void Destroy();

	// 静的関数
	static void Create(int nNum, Float3 pos);
	static void Init();
	static void Uninit();

	// 仮想関数
	virtual void Update();
	virtual void Draw();
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);
	// アニメーション終了時に呼び出される関数
	virtual void OnAnimator(CAnimator *pAnimator);

	// コンポーネント
	CCollision* GetCol() { return m_pCollision; }
	CRigidbody* GetRb()  { return m_pRigidbody; }

protected:
	CCollision* m_pCollision;	// コンポーネント
	CRigidbody* m_pRigidbody;	// コンポーネント

	// 経験値
	static CTexture sm_texture;
	static CTexture sm_textureLight;
	float m_fForceY;
	Float2 m_size;
	int m_nExperience;
private:

};



//===== プロトタイプ宣言 =====
