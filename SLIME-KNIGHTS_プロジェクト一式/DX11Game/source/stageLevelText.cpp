//==================================================================
//								stageLevelText.h
//	ステージレベルの表示
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/07	ステージレベルクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "stageLevelText.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "status.h"
#include "animation.h"



//===== マクロ定義 =====
#define DAMAGE_FORCE_X (6)
#define DAMAGE_FORCE_Y (12)

#define EXIST_TIME (120)


//========================================
//
//	コンストラクタ
//
//========================================
CStageLevelText::CStageLevelText()
{
	// アニメーター
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 50, 50 });

	// スプライトデータ
	m_sprite;


	// レイヤー
	m_enLayer = LAYER::EFFECT;

	// アニメーション

	// テキスト生成
	//m_pString = STRING::CString::Create();
	//m_pString->SetCamera(true);

}


//========================================
//
//	デストラクタ
//
//========================================
CStageLevelText::~CStageLevelText()
{
	m_pAnimator->Destroy();
	m_pString->Destroy();

}


//========================================
//
//	初期化
//
//========================================
void CStageLevelText::Init()
{
	
}

//========================================
//
//	終了処理
//
//========================================
void CStageLevelText::Uninit()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CStageLevelText::Update()
{
	m_pString->SetPos(m_transform.GetPos());


	if (m_fAlpha > 1.7f && !m_bAlpha)
	{
		m_bAlpha = true;
	}

	if (m_bAlpha)
	{
		m_fAlpha -= 0.01f;
	}
	else
	{
		m_fAlpha += 0.007f;
	}

	m_pString->SetColor(Float4{ 0.9375f,0.9375f,0.9375f,m_fAlpha });

	if (m_fAlpha < 0)
	{
		this->Destroy();
	}
}

//========================================
//
//	描画処理
//
//========================================
void CStageLevelText::Draw()
{

}

//========================================
//
//	生成
//
//========================================
CStageLevelText* CStageLevelText::Create(Float3 pos, int nLevel)
{
	CStageLevelText *pDamageText = CObjectManager::CreateObject<CStageLevelText>(pos);

	std::sprintf(pDamageText->m_szText, "STAGE LEVEL : %d", nLevel);
	pDamageText->m_pString = STRING::CString::Create(pDamageText->m_szText, pos, Float2{100, 100}, 
					Float4{ 1,1,1,0 }, STRING::CENTER_X, STRING::CENTER_Y);

	pDamageText->m_fAlpha = 0;
	pDamageText->m_bAlpha = false;
	//pDamageText->m_pString->SetWord(szText);

	// サウンド


	return pDamageText;
}

//========================================
//
//	破棄
//
//========================================
void CStageLevelText::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	コリジョン
//
//========================================
void CStageLevelText::OnCollision(CCollision *pCollision)
{

}


//========================================
//
//	アニメーター
//
//========================================
void CStageLevelText::OnAnimator(CAnimator *pAnimator)
{

}
