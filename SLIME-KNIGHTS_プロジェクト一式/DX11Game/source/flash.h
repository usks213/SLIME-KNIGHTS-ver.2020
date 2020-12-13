//==================================================================
//									flash.h
//	フラッシュ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/05	フラッシュクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== マクロ定義 =====


//===== クラス定義 =====
class CEnemySlimBoss;

class CFlash : public CObject
{
public:
	CFlash();
	~CFlash();
	// フラッシュアウトの開始
	void StartFlash(void(*pSetEvent)(CEnemySlimBoss*), CEnemySlimBoss* pBoss);
	// 仮想関数
	virtual void Update();
	virtual void Draw();

	static bool GetNowFlash() { return m_bNowFlash; }

private:
	int m_nAlpha;	// フラッシュ用ポリゴンのアルファ値(0～255)
	int m_nFrame;	// フラッシュにかかるフレーム数

	CTexture m_texture;
	void(*m_pSetEvent)(CEnemySlimBoss*) = nullptr;
	CEnemySlimBoss* m_pBoss;

	static bool m_bNowFlash;
};
