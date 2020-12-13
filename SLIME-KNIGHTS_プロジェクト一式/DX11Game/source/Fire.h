//==================================================================
//								Fire.h
//	マップの灯り
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/06	ファイヤクラスの作成	
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== 定数定義 =====

//===== クラス定義 =====

class CFire : public CObject
{
public:
	// 通常関数
	CFire();
	~CFire();
	void Destroy();

	// 静的関数
	static void Create(Float3 pos);
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

protected:
	CCollision* m_pCollision;	// コンポーネント
	CAnimator*  m_pAnimator;	// コンポーネント

	// ライト
	static CTexture sm_textureFire;
	static CTexture sm_textureBottom;
	CSprite m_spriteDefault;
private:

};



//===== プロトタイプ宣言 =====
