//==================================================================
//									fade.h
//	GM21 フェードイン・フェードアウト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/17	フェードの描画
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== マクロ定義 =====


//===== クラス定義 =====
class FADE : public CObject
{
public:
	FADE(void(*pSetChange)());
	~FADE();
	// フェードアウトの開始
	void StartFadeOut();
	// 仮想関数
	virtual void Update();
	virtual void Draw();

	static bool GetNowFade() { return m_bNowFade; }
	void SetChangeEvent(void(*pSetChange)()) { m_pSetChange = pSetChange; }

private:
	int m_nAlpha;	// フェード用ポリゴンのアルファ値(0～255)
	int m_nState;	// 状態
	int m_nFrame;	// フェードにかかるフレーム数

	CTexture m_texture;
	void(*m_pSetChange)() = nullptr;

	static bool m_bNowFade;
};
