//==================================================================
//									key.h
//	キーボードの画像
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/06	キークラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== マクロ定義 =====

namespace KEY
{
	enum EKEY_TYPE
	{
		W,
		A,
		S,
		D,
		R,
		Z,
		X,
		C,
		J,
		K,
		L,
		RIGHT,
		LEFT,
		UP,
		DOWN,
		TAB,
		SPACE,

		MAX_KEY_TYPE,
	};
}

//===== クラス定義 =====
class CKey : public CObject
{
public:
	CKey();
	~CKey();

	static CKey* Create(KEY::EKEY_TYPE eType, Float3 pos = Float3{0,0,0}, bool bCamera = true);
	void Destroy();

	virtual void Update();
	virtual void Draw();

	static void Init();
	static void Uninit();

	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

private:
	static CTexture sm_texture[KEY::MAX_KEY_TYPE];		// マスターテクスチャ
	CTexture* m_pTexture;
	bool m_bCamera;
};
