//==================================================================
//								levelupText.cpp
//	レベルアップ表示
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/05	レベルアップテキストクラス
//
//===================================================================


//====== インクルード部 ======
#include "levelupText.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "status.h"
#include "animation.h"

#include "../Sound.h"


//===== マクロ定義 =====
#define DAMAGE_FORCE_X (6)
#define DAMAGE_FORCE_Y (12)

#define EXIST_TIME (120)


//===== グローバル変数 =====
static CSound g_LevelUpSE;


//========================================
//
//	コンストラクタ
//
//========================================
CLevelUpText::CLevelUpText()
{
	// アニメーター
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	m_pRigidbody = CRigidbody::Create(&m_transform, false, true, true);

	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 50, 50 });

	// スプライトデータ
	m_sprite;


	// レイヤー
	m_enLayer = LAYER::EFFECT;

	// アニメーション


	// 飛び散り
	m_pRigidbody->SetDragX(0.001f);
	float rad = (float)(90);
	m_pRigidbody->SetForce(Float3{ cosf(AngleToRadian(rad)) * DAMAGE_FORCE_X, -sinf(AngleToRadian(rad)) * DAMAGE_FORCE_Y, 0.0f });
	m_pRigidbody->SetGravityForce(0.3f);
	m_fForceY =DAMAGE_FORCE_Y;

	// テキスト生成
	//m_pString = STRING::CString::Create();
	//m_pString->SetCamera(true);

	m_nExistTime = EXIST_TIME;

	g_LevelUpSE.Load(FILE_PATH"sound/player/LevelUp3.wav");
	g_LevelUpSE.Play(0.2f);
}


//========================================
//
//	デストラクタ
//
//========================================
CLevelUpText::~CLevelUpText()
{
	m_pCollision->Destroy();
	m_pAnimator->Destroy();
	m_pRigidbody->Destroy();
	m_pString->Destroy();

}


//========================================
//
//	初期化
//
//========================================
void CLevelUpText::Init()
{
}

//========================================
//
//	終了処理
//
//========================================
void CLevelUpText::Uninit()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CLevelUpText::Update()
{
	m_pString->SetPos(m_transform.GetPos());

	/*m_nExistTime--;
	if (m_nExistTime < 0)
	{
		this->Destroy();
	}*/
}

//========================================
//
//	描画処理
//
//========================================
void CLevelUpText::Draw()
{

}

//========================================
//
//	生成
//
//========================================
CLevelUpText* CLevelUpText::Create(Float3 pos)
{
	CLevelUpText *pDamageText = CObjectManager::CreateObject<CLevelUpText>(pos);

	pDamageText->m_pString = STRING::CString::Create("LEVEL UP", pos, Float2{50, 50}, Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y, true);
	//pDamageText->m_pString->SetWord(szText);

	// サウンド


	return pDamageText;
}

//========================================
//
//	破棄
//
//========================================
void CLevelUpText::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	コリジョン
//
//========================================
void CLevelUpText::OnCollision(CCollision *pCollision)
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::FIELD || pObj->GetLayer() == LAYER::FLOOR)
	{
		if(m_pRigidbody->GetHitDir() == DIRECTION::UP && m_pRigidbody->GetForce().y > 0.0f)
			this->Destroy();
	}

}


//========================================
//
//	アニメーター
//
//========================================
void CLevelUpText::OnAnimator(CAnimator *pAnimator)
{

}
