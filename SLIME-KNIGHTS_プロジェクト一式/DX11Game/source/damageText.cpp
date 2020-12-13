//==================================================================
//								experience.cpp
//	ドロップするお金
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/08/07	マネークラスの作成	
//
//===================================================================


//====== インクルード部 ======
#include "damageText.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "status.h"
#include "animation.h"



//===== マクロ定義 =====
#define DAMAGE_FORCE_X (6)
#define DAMAGE_FORCE_Y (10)

#define TEXT_SIZE (40.0f)

#define EXIST_TIME (120)

//========================================
//
//	コンストラクタ
//
//========================================
CDamageText::CDamageText()
{
	// アニメーター
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	m_pRigidbody = CRigidbody::Create(&m_transform, false, true, true);

	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 50, 50 });

	// スプライトデータ
	m_sprite.SetColor(Float4{ 1,0,0,1 });


	// レイヤー
	m_enLayer = LAYER::EFFECT;

	// アニメーション


	// 飛び散り
	m_pRigidbody->SetDragX(0.001f);
	float rad = (float)(rand() % 90 + 45);
	m_pRigidbody->SetForce(Float3{ cosf(AngleToRadian(rad)) * DAMAGE_FORCE_X, -sinf(AngleToRadian(rad)) * DAMAGE_FORCE_Y, 0.0f });
	m_pRigidbody->SetGravityForce(0.3f);
	m_fForceY =DAMAGE_FORCE_Y;

	// テキスト生成
	//m_pString = STRING::CString::Create();
	//m_pString->SetCamera(true);

	m_nExistTime = EXIST_TIME;
}


//========================================
//
//	デストラクタ
//
//========================================
CDamageText::~CDamageText()
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
void CDamageText::Init()
{
	
}

//========================================
//
//	終了処理
//
//========================================
void CDamageText::Uninit()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CDamageText::Update()
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
void CDamageText::Draw()
{

}

//========================================
//
//	生成
//
//========================================
CDamageText* CDamageText::Create(int nDamage, Float3 pos, Float4 col, bool bCritical)
{
	CDamageText *pDamageText = CObjectManager::CreateObject<CDamageText>(pos);

	std::sprintf(pDamageText->m_szText, "%d", nDamage);

	// クリティカル発生
	if (bCritical)
	{
		pDamageText->m_pString = STRING::CString::Create(pDamageText->m_szText,
			pos, Float2{ TEXT_SIZE*1.5f, TEXT_SIZE*1.5f }, col,
			STRING::CENTER_X, STRING::CENTER_Y, true);
	}
	else
	{
		pDamageText->m_pString = STRING::CString::Create(pDamageText->m_szText,
			pos, Float2{ TEXT_SIZE, TEXT_SIZE }, col,
			STRING::CENTER_X, STRING::CENTER_Y, true);
	}
	//pDamageText->m_pString->SetWord(szText);

	return pDamageText;
}

//========================================
//
//	破棄
//
//========================================
void CDamageText::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	コリジョン
//
//========================================
void CDamageText::OnCollision(CCollision *pCollision)
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
void CDamageText::OnAnimator(CAnimator *pAnimator)
{

}
