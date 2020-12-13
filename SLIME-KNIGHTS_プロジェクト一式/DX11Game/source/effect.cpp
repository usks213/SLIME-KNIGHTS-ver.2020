//==================================================================
//								effect.h
//	GM21 エフェクト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/11	エフェクトクラスの作成	
//
//===================================================================


//====== インクルード部 ======
#include "effect.h"
#include "collision.h"
#include "animator.h"
#include "objectMgr.h"
#include "animation.h"

#include "../sprite.h"
#include "../texture.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64


//===== マクロ定義 =====


//===== 静的メンバ =====
CTexture CEffect::sm_aTexture[EFFECT::MAX_EFFECT_NAME];

//===== 名前空間 =====
using namespace EFFECT;


//========================================
//
//	コンストラクタ
//
//========================================
CEffect::CEffect()
{
	// コリジョン
	//m_pCollision = CCollision::Create(this);
	// アニメーター
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// ポリゴンのパラメータの初期化
	m_transform;

	// スプライトデータ
	m_sprite;

	// テクスチャデータ
	m_pTexture = nullptr;

	// レイヤー
	m_enLayer = LAYER::EFFECT;
}


//========================================
//
//	デストラクタ
//
//========================================
CEffect::~CEffect()
{
	// コリジョン
	//m_pCollision->Destroy();
	// アニメーター
	m_pAnimator->Destroy();

}


//========================================
//
//	初期化
//
//========================================
void CEffect::Init()
{
	// テクスチャのロード
	sm_aTexture[EFFECT::ENEMY_DAMAGE].LoadTexture(FILE_PATH"player/hit_effect.tga");
	sm_aTexture[EFFECT::PLAYER_DAMAGE].LoadTexture(FILE_PATH"player/player_damage.tga");
	sm_aTexture[EFFECT::DUST_L].LoadTexture(FILE_PATH"player/dust_L2.tga");
	sm_aTexture[EFFECT::DUST_R].LoadTexture(FILE_PATH"player/dust_R2.tga");
	sm_aTexture[EFFECT::SWORD_L].LoadTexture(FILE_PATH"player/sword_effect_L.tga");
	sm_aTexture[EFFECT::SWORD_R].LoadTexture(FILE_PATH"player/sword_effect_R.tga");

}

//========================================
//
//	終了処理
//
//========================================
void CEffect::Uninit()
{
	// テクスチャの解放
	for (int i = 0; i < EFFECT::MAX_EFFECT_NAME; i++)
	{
		sm_aTexture[i].UnloadTexture();
	}
}

//========================================
//
//	更新処理
//
//========================================
void CEffect::Update()
{

}

//========================================
//
//	描画処理
//
//========================================
void CEffect::Draw()
{
	// 加算合成
	//glBlendFunc(GL_ONE, GL_ONE);
	CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// 四角形の描画
	m_sprite.Draw(&m_transform, m_pTexture);

	// アルファ合成
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);
}

//========================================
//
//	生成
//
//========================================
void CEffect::Create(EFFECT::EEFFECT_NAME enName, Float3 pos)
{
	CEffect *pEffect = CObjectManager::CreateObject<CEffect>(pos);
	Float3 vpos;

	switch (enName)
	{
	case EFFECT::ENEMY_DAMAGE:
		// 大きさ
		pEffect->m_transform.SetSize(Float2{ 90 * 2.5f, 90 * 2.5f });
		// テクスチャ
		pEffect->m_pTexture = &sm_aTexture[EFFECT::ENEMY_DAMAGE];
		// アニメーション
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)6);
		pEffect->m_pAnimator->SetAnimation("test", 4, 6, 1);
		pEffect->m_transform.SetAngle(rand() % 360);
		vpos = pos;
		pos.x += rand() % 40 - 20;
		pos.y += rand() % 40 - 20;
		pEffect->m_transform.SetPos(pos);

		break;
	case EFFECT::PLAYER_DAMAGE:
		// 大きさ
		pEffect->m_transform.SetSize(Float2{ 90 * 2, 90 * 2 });
		// テクスチャ
		pEffect->m_pTexture = &sm_aTexture[EFFECT::PLAYER_DAMAGE];
		// アニメーション
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)5);
		pEffect->m_pAnimator->SetAnimation("test", 5, 5, 1);
		pEffect->m_transform.SetAngle(rand() % 360);
		vpos = pos;
		pos.x += rand() % 40 - 20;
		pos.y += rand() % 40 - 20;
		pEffect->m_transform.SetPos(pos);

		break;
	case EFFECT::DUST_L:
		// 大きさ
		pEffect->m_transform.SetSize(Float2{ 48, 48 });
		// テクスチャ
		pEffect->m_pTexture = &sm_aTexture[EFFECT::DUST_L];
		// アニメーション
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)8);
		pEffect->m_pAnimator->SetAnimation("test", 4, 8, 1);
		//pEffect->m_sprite.SetColorW(0.8f);

		break;
	case EFFECT::DUST_R:
		// 大きさ
		pEffect->m_transform.SetSize(Float2{ 48, 48 });
		// テクスチャ
		pEffect->m_pTexture = &sm_aTexture[EFFECT::DUST_R];
		// アニメーション
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)8);
		pEffect->m_pAnimator->SetAnimation("test", 4, 8, 1);
		//pEffect->m_sprite.SetColorW(0.8f);

		break;
	case EFFECT::SWORD_L:
		// 大きさ
		pEffect->m_transform.SetSize(Float2{ 96 * 2, 96 * 2 });
		// テクスチャ
		pEffect->m_pTexture = &sm_aTexture[EFFECT::SWORD_L];
		// アニメーション
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)4);
		pEffect->m_pAnimator->SetAnimation("test", 3, 4, 1);
		//pEffect->m_sprite.SetColorW(0.8f);

		break;
	case EFFECT::SWORD_R:
		// 大きさ
		pEffect->m_transform.SetSize(Float2{ 96 * 2, 96 * 2 });
		// テクスチャ
		pEffect->m_pTexture = &sm_aTexture[EFFECT::SWORD_R];
		// アニメーション
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)4);
		pEffect->m_pAnimator->SetAnimation("test", 3, 4, 1);
		//pEffect->m_sprite.SetColorW(0.8f);

		break;
	case EFFECT::MAX_EFFECT_NAME:
		break;
	default:
		break;
	}

}

//========================================
//
//	初期化
//
//========================================
void CEffect::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	アニメーター
//
//========================================
void CEffect::OnAnimator(CAnimator *pAnimator)
{
	CObjectManager::DestroyObject(this);
}
