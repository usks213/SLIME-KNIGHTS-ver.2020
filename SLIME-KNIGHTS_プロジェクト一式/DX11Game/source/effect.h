//==================================================================
//								effect.h
//	GM21 エフェクト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/11	エフェクトクラスの作成	
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

namespace EFFECT
{
	enum EEFFECT_NAME
	{
		PLAYER_DAMAGE,
		ENEMY_DAMAGE,
		DUST_L,
		DUST_R,
		SWORD_L,
		SWORD_R,

		MAX_EFFECT_NAME,
	};
}

class CEffect : public CObject
{
public:
	CEffect();
	~CEffect();
	void Destroy();

	// 静的関数
	static void Init();
	static void Uninit();
	static void Create(EFFECT::EEFFECT_NAME enName, Float3 pos);

	// 仮想関数
	virtual void Update();
	virtual void Draw();
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision) { return; }		// キャラクターに持たせる
	// アニメーション終了時に呼び出される関数
	virtual void OnAnimator(CAnimator *pAnimator);
protected:
	CCollision* m_pCollision;	// コンポーネント
	CAnimator* m_pAnimator;		// コンポーネント
	static CTexture sm_aTexture[EFFECT::MAX_EFFECT_NAME];
	CTexture *m_pTexture;
private:

};


//===== プロトタイプ宣言 =====
