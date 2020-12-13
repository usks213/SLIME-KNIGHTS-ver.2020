//==================================================================
//									combo.h
//	プレイヤーのコンボ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/10/28	コンボクラス作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== マクロ定義 =====
#define MAX_COMBO	(5)


//===== クラス定義 =====
class CCombo : public CObject
{
public:
	CCombo();
	~CCombo();

	static CCombo* Create(Float3 pos);
	void Destroy();

	virtual void Update(){}
	virtual void LateUpdate();
	virtual void Draw();

	static void Init();
	static void Uninit();

	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

	void UpdateComboTexCoord();

	void AddCombo(int num);
	void ResetCombo();
	bool GetCritical() {
		// ランダムでクリティカル
		int nCrt = rand() % 30;

		// コンボでクリティカルをアップ
		nCrt += m_nComboCount;

		// クリティカル判定
		if (rand() % 100 < nCrt) return true;
		else return false;
	}

	struct SComboData
	{
		CSprite m_spr;
		int m_nAnimNo;
	};


private:
	static CTexture sm_texture;		// マスターテクスチャ
	static CTexture sm_comboTex;	// コンボテクスチャ
	static CTexture sm_comboUITex;	// コンボテクスチャ

	int m_nComboCount;
	SComboData m_data[MAX_COMBO];
	int m_nComboTime;
	int m_nMaxComboTime;
};

