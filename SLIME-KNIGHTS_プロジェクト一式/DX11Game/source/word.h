//==================================================================
//									word.h
//	文字列表示
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/08	文字列表示クラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== マクロ定義 =====


//===== クラス定義 =====
class CWord
{
public:
	CWord();
	~CWord();

	void Update();
	void Draw(bool bCamera);

	static CWord* Create(Float3 pos, Float2 size, Float2 texPos, Float2 texSize, Float4 color, CTexture *pTexture);
	static CWord* Create();
	void Destroy();

	// ゲット関数
	CTransform* GetTrans() { return &m_trans; }
	CSprite* GetSprite() { return &m_sprite; }
	// セット関数
	void SetTexture(CTexture *pTexture) { m_pTexture = pTexture; }

private:
	CTransform m_trans;
	CSprite m_sprite;
	CTexture *m_pTexture;
};

