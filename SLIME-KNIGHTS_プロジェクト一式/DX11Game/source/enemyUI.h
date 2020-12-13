//==================================================================
//								enemyUI.h
//	エネミーのUI
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/07	エネミーUIクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== 定数定義 =====


//===== クラス定義 =====
class CEnemy;

class CEnemyUI : public CObject
{
public:
	// 通常関数
	CEnemyUI();
	~CEnemyUI();
	void Destroy();

	// 静的関数
	static CEnemyUI* Create(CEnemy* pParent);
	static void Init();
	static void Uninit();

	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();

	void SetDraw(bool bFlag) { m_bDraw = bFlag; }

protected:
	// BG
	Float4 m_colorBG;
	// UI
	Float4 m_colorUI;
	// HP
	Float4 m_colorHP;
	Float2 m_sizeHP;

	// テクスチャデータ
	static CTexture sm_UiTexture;

	CEnemy* m_pParent;

	bool m_bDraw;
private:
};


