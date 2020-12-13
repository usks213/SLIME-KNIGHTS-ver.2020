//==================================================================
//									fade.cpp
//	GM21 フェードイン・フェードアウト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/17	フェードの描画
//	2020/06	19	続き
//
//===================================================================


//====== インクルード部 ======
#include "fade.h"
#include "sceneManager.h"

#include "../sprite.h"
#include "../texture.h"


//===== マクロ定義 =====


//===== 列挙 =====
namespace
{
	enum E_STATE_FADE	// フェードの状態の列挙
	{
		E_STATE_FADE_NODE = 0,
		E_STATE_FADE_OUT,
		E_STATE_FADE_IN,

		E_STATE_FADE_MAX,
	};
}


//===== プロトタイプ宣言 =====


//===== グローバル変数 =====


//===== 静的メンバ =====
bool FADE::m_bNowFade = false;



//========================================
//
//	コンストラクタ
//
//========================================
FADE::FADE(void(*pSetChange)())
{
	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });

	// アルファ
	m_nAlpha = 0;

	// ステート
	m_nState = E_STATE_FADE_NODE;

	// フレーム
	m_nFrame = 20;

	// フェード用のポリゴンカラーの設定
	m_sprite.SetColor(Float4{1.0f, 1.0f, 1.0f, m_nAlpha / 255.0f});

	// レイヤー
	m_enLayer = LAYER::FADE;

	m_texture.LoadTexture(FILE_PATH"fade.tga");

	// 関数ポインタの格納
	m_pSetChange = pSetChange;
}


//========================================
//
//	デストラクタ
//
//========================================
FADE::~FADE()
{
	m_texture.UnloadTexture();
}


//======================================================
//
//	フェードアウトの開始
//	フェードアウト開始時間に外からの呼び出す関数
//
//======================================================
void FADE::StartFadeOut()
{
	// 既にフェード中の時は処理しない
	if (E_STATE_FADE_NODE != m_nState)
	{
		return;
	}

	m_nAlpha = 0;
	m_nState = E_STATE_FADE_OUT;
	m_bNowFade = true;
}


//========================================
//
//	更新
//
//========================================
void FADE::Update()
{
	// 状態により分岐
	switch (m_nState)
	{
	case(E_STATE_FADE_IN):		// フェードイン
		// α値の減少
		m_nAlpha -= (int)(255.0f / m_nFrame);

		// α値が0より小さくなったら終了
		if (m_nAlpha < 0)
		{
			m_nAlpha = 0;
			m_nState = E_STATE_FADE_NODE;

			// フェードイン終了後の処理
			m_bNowFade = false;

		}
		else if (m_nAlpha < 255 / 2)
		{
			// フェードイン終了まで画面を止める
			CSceneManager::SetStopFlag(false);
		}

		// α値の更新
		m_sprite.SetColorW(m_nAlpha / 255.0f);
		break;

	case(E_STATE_FADE_OUT):		// フェードアウト
		// α値の増加
		m_nAlpha += (int)(255.0f / m_nFrame);

		// α値が255を超えたらフェードインへ
		if (m_nAlpha > 255)
		{
			m_nAlpha = 255;
			m_nState = E_STATE_FADE_IN;

			// フェードアウトが終わったときに実装する処理
			// シーンの移動
			if (m_pSetChange)
				m_pSetChange();
			//CSceneManager::SetSceneChange();	
		}

		// α値の更新
		m_sprite.SetColorW(m_nAlpha / 255.0f);
		break;

	default:
		break;
	}

	m_sprite.SetColorW(m_nAlpha / 255.0f);

}


//========================================
//
//	描画
//
//========================================
void FADE::Draw()
{
	// 四角形の描画
	m_sprite.Draw(&m_transform, &m_texture, false);
}


