//==================================================================
//								playerUI.h
//	プレイヤーのUI
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/05	プレイヤーUIクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "string.h"


//===== 定数定義 =====


//===== クラス定義 =====

class CPlayerUI : public CObject
{
public:
	// 通常関数
	CPlayerUI();
	~CPlayerUI();
	void Destroy();

	// 静的関数
	static CPlayerUI* Create(Float3 pos);
	static void Init();
	static void Uninit();

	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();


protected:
	// BG
	Float4 m_colorBG;
	// UI
	Float4 m_colorUI;
	// HP
	Float4 m_colorHP;
	Float2 m_sizeHP;
	// EX
	Float4 m_colorEX;
	Float2 m_sizeEX;

	// テクスチャデータ
	static CTexture sm_UiTexture;

	// テキスト
	STRING::CString *m_pLevel;
	STRING::CString *m_pHP;
	STRING::CString *m_pExperience;
private:
};


