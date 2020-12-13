//==================================================================
//									combo.cpp
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


//====== インクルード部 ======
#include "combo.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"


//===== マクロ定義 =====
#define ANIM_COMBO_SPLIT_X (10)  // 画像の分割数(横)
#define ANIM_COMBO_SPLIT_Y (1)  // 画像の分割数(縦)

#define COMBO_SIZE_X	(50)
#define COMBO_OFFSET_X	(COMBO_SIZE_X)

#define COMBO_TIME (300)

#define GAUGE_BG_SIZE_X (290)
#define GAUGE_BG_SIZE_Y (28)

#define GAUGE_UI_SIZE_X (300)
#define GAUGE_UI_SIZE_Y (30)

#define GAUGE_SIZE_X (GAUGE_BG_SIZE_X)
#define GAUGE_SIZE_Y (GAUGE_BG_SIZE_Y)


//===== プロトタイプ宣言 =====


//===== グローバル変数 =====


//===== 静的メンバ =====
CTexture CCombo::sm_texture;
CTexture CCombo::sm_comboTex;
CTexture CCombo::sm_comboUITex;



//========================================
//
//	コンストラクタ
//
//========================================
CCombo::CCombo()
{
	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ COMBO_SIZE_X, COMBO_SIZE_X });

	// スプライトデータ
	for (int i = 0; i < MAX_COMBO; i++)
	{
		m_data[i].m_spr.SetTexSize(Float2{ 1.0f / (float)ANIM_COMBO_SPLIT_X, 1.0f / (float)ANIM_COMBO_SPLIT_Y });
	}
	// レイヤー
	m_enLayer = LAYER::UI;

	m_nComboCount = 0;
	m_nComboTime = 0;
	m_nMaxComboTime = COMBO_TIME;

	Init();
}


//========================================
//
//	デストラクタ
//
//========================================
CCombo::~CCombo()
{
	Uninit();
}


//========================================
//
//	初期化
//
//========================================
void CCombo::Init()
{
	// テクスチャのロード
	sm_texture.LoadTexture(FILE_PATH"ui/critical.tga");
	sm_comboTex.LoadTexture(FILE_PATH"ui/combo.tga");
	sm_comboUITex.LoadTexture(FILE_PATH"ui/comboUI.tga");
}


//========================================
//
//	終了処理
//
//========================================
void CCombo::Uninit()
{
	sm_texture.UnloadTexture();
	sm_comboTex.UnloadTexture();
	sm_comboUITex.UnloadTexture();
}


//========================================
//
//	更新
//
//========================================
void CCombo::LateUpdate()
{
	// 時間経過でコンボを無くす
	if (m_nComboCount > 0)
	{
		m_nComboTime--;
		if (m_nComboTime < 0)
		{
			m_nComboCount -= 10;
			if (m_nComboCount < 0)
				m_nComboCount = 0;
			m_nComboTime = COMBO_TIME;
			UpdateComboTexCoord();
		}
	}
}


//========================================
//
//	コンボUV更新
//
//========================================
void CCombo::UpdateComboTexCoord()
{
	int tmp = m_nComboCount;

	for (int i = MAX_COMBO - 1; 0 <= i; i--)
	{
		m_data[i].m_nAnimNo = tmp % 10;

		m_data[i].m_spr.SetTexPos(Float2{ m_data[i].m_spr.GetTexSize().x * (m_data[i].m_nAnimNo % ANIM_COMBO_SPLIT_X) ,
											m_data[i].m_spr.GetTexSize().y * (m_data[i].m_nAnimNo / ANIM_COMBO_SPLIT_X) });

		tmp /= 10;
	}
}


//========================================
//
//	描画
//
//========================================
void CCombo::Draw()
{
	// コンボなし
	if (m_nComboCount <= 0) return;

	// タイムゲージの表示
	CTransform trans = m_transform;
	Float3 pos = m_transform.GetPos();

	// ゲージ座標
	pos.x -= COMBO_OFFSET_X * 1.75f;
	pos.y += COMBO_SIZE_X;

	// ゲージBG
	trans.SetSize({ GAUGE_BG_SIZE_X, GAUGE_BG_SIZE_Y });
	trans.SetPos(pos);
	m_sprite.SetColor({ 0.6f, 0.5f, 0.6f, 1.0f });
	m_sprite.Draw(&trans, nullptr, false);

	// ゲージ本体
	float sizeX = GAUGE_SIZE_X * ((float)m_nComboTime / m_nMaxComboTime);
	trans.SetSize({ sizeX, GAUGE_SIZE_Y });

	pos.x += sizeX / 2.0f - GAUGE_SIZE_X / 2.0f;
	trans.SetPos(pos);
	m_sprite.SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
	m_sprite.Draw(&trans, nullptr, false);


	// ゲージUI
	trans.SetSize({ GAUGE_UI_SIZE_X, GAUGE_UI_SIZE_Y });
	pos = m_transform.GetPos();
	pos.x -= COMBO_OFFSET_X * 1.75f;
	pos.y += COMBO_SIZE_X;
	trans.SetPos(pos);
	m_sprite.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_sprite.Draw(&trans, &sm_comboUITex, false);

	// コンボの表示
	trans = m_transform;
	pos = m_transform.GetPos();
	trans.SetSize({ COMBO_SIZE_X / 2 * 5, COMBO_OFFSET_X / 2 });
	pos.x -= COMBO_OFFSET_X / 5.0f;
	pos.y += COMBO_OFFSET_X / 4.0f;
	trans.SetPos(pos);
	m_sprite.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_sprite.Draw(&trans, &sm_comboTex, false);


	// コンボカウントの表示
	trans = m_transform;
	pos = m_transform.GetPos();
	int temp = m_nComboCount;
	int nCnt = 0;
	// 桁数を数える
	while (temp > 0)
	{
		temp /= 10;
		nCnt++;
	}

	pos.x -= COMBO_OFFSET_X;
	for (int i = MAX_COMBO - 1; 0 <= i; i--)
	{
		pos.x -= COMBO_OFFSET_X;
		trans.SetPos(pos);

		if (nCnt - (MAX_COMBO - i) >= 0)
		{
			m_data[i].m_spr.Draw(&trans, &sm_texture, false);
		}
	}
}


//========================================
//
//	生成
//
//========================================
CCombo* CCombo::Create(Float3 pos)
{
	CCombo* pCombo = CObjectManager::CreateObject<CCombo>(pos);

	return pCombo;
}


//========================================
//
//	破棄
//
//========================================
void CCombo::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	コンボの加算
//
//========================================
void CCombo::AddCombo(int num)
{
	m_nComboCount += num;
	m_nComboTime = COMBO_TIME;

	if (99999 < m_nComboCount)
	{
		m_nComboCount = 99999;
	}

	UpdateComboTexCoord();

	// ストップを解除
	m_bStop = false;
}


//========================================
//
//	コンボの減算
//
//========================================
void CCombo::ResetCombo()
{
	m_nComboCount -= 3;
	m_nComboTime = COMBO_TIME;

	if (m_nComboCount < 0)
	{
		m_nComboCount = 0;
	}

	UpdateComboTexCoord();
}