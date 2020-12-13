//==================================================================
//								miniMap.h
//	ミニマップ用ブロック
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/04	ミニマップクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

class CMiniMap : public CObject
{
public:
	CMiniMap();
	~CMiniMap();
	void Destroy();

	// 静的関数
	static void Init();
	static void Uninit();
	static CMiniMap* Create(Float3 pos, CTexture* nTex, int nTexPos, int nSplitX, int nSplitY);

	// 仮想関数
	virtual void Update();
	virtual void Draw();
	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision) { return; }

	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

protected:
	CTexture*	m_pTexture;

private:

};

