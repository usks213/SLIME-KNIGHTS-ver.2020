//==================================================================
//									bg.h
//	GM21 背景
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/05	背景描画
//	2020/06/17	オブジェクト指向に
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== マクロ定義 =====

namespace BG
{
	enum EBG_TYPE
	{
		TITLE,
		GAME,
		RESALT,
		BOSS_MOVIE,

		MAX_BG_TYPE,
	};
}

//===== クラス定義 =====
class CBG : public CObject
{
public:
	CBG();
	~CBG();

	static CBG* Create(BG::EBG_TYPE eType, Float3 pos = Float3{0,0,0});
	void Destroy();

	virtual void Update();
	virtual void Draw();

	static void Init();
	static void Uninit();

	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

private:
	static CTexture sm_texture[BG::MAX_BG_TYPE];		// マスターテクスチャ
	CTexture* m_pTexture;
};
