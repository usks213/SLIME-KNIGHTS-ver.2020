//==================================================================
//									movieUI.h
//	ムービー中の黒い縁
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/08	ムービーUIクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== マクロ定義 =====


//===== クラス定義 =====
class CMovieUI : public CObject
{
public:
	CMovieUI();
	~CMovieUI();

	static CMovieUI* Create(Float3 pos = Float3{0,0,0});
	void Destroy();

	virtual void Update();
	virtual void Draw();

	static void Init();
	static void Uninit();
	static void SetDraw(bool bFlag) { m_bDraw = bFlag; }

private:
	static CTexture sm_texture;		// マスターテクスチャ
	static bool m_bDraw;

};
